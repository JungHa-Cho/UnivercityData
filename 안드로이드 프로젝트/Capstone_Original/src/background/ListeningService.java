package background;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import com.example.capstondesign.R;
import com.example.capstondesign.ServerUtilities;
import com.example.capstondesign.WakeLocker;

import android.app.AlarmManager;
import android.app.Notification;
import android.app.PendingIntent;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.location.Address;
import android.location.Criteria;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.IBinder;
import android.os.PowerManager;
import android.os.SystemClock;
import android.util.Log;
import android.widget.Toast;
import audio.record.AudioFeaturesExtractor;
import audio.record.DatabaseHandler;
import audio.record.Feature;
import audio.record.FeaturesMatchFinderTask;
import audio.record.RecordThread;
import audio.record.FeaturesMatchFinderTask.Match;

public class ListeningService extends Service implements Runnable
{	
	boolean threadFlag;
	private RecordThread recordThread;
	private List<Feature> existingFeaturesInDatabase;
	private AudioFeaturesExtractor featuresExtractor;
	public LinkedList<Match> Returnmatch;
	private PowerManager.WakeLock mWakeLock;
	ServerUtilities SU;
	AsyncTask<Void, Void, Void> mRegisterTask;
	
	
	/**
	 * �˶��� �̿��� ����ŸƮ ����
	 * @see (http://ccdev.tistory.com/20)
	 */
	public void registerRestartAlarm(boolean isOn)
	{
		Log.d("CapstonDesign", "registerRestartAlarm()");
		Intent intent = new Intent(ListeningService.this, RestartReceiver.class);
		intent.setAction(RestartReceiver.ACTION_RESTART_SERVICE);
		PendingIntent sender = PendingIntent.getBroadcast(getApplicationContext(), 0, intent, 0);	
		AlarmManager am = (AlarmManager)getSystemService(ALARM_SERVICE);
		
		if(isOn){
			/* @param1, ���� �ð� = 0 @param2, �������� ���� @param3, �ֱ�(1800ms) @param4, ACTION_RESTART_SERVICE ���� */
			am.setRepeating(AlarmManager.ELAPSED_REALTIME_WAKEUP, SystemClock.elapsedRealtime() + 1000, 1800000, sender);
		}else{
			am.cancel(sender);
		}
	}
	
	/**
	 * ���� ����� ������ ����Ǵ� �Լ�
	 * @see (http://nashorn.tistory.com/56)
	 * @see android.app.Service#onCreate()
	 * @param non
	 * @return non
	 */
	@Override
	public void onCreate(){
		Log.d("CapstonDesign", "onCreate()");
		Toast.makeText(getBaseContext(), "���� �����ߴ�", Toast.LENGTH_SHORT).show();
		threadFlag = false;
		recordThread = new RecordThread();
		featuresExtractor = new AudioFeaturesExtractor();
		Returnmatch = new LinkedList<Match>();
		registerReceiver(mHandleMessageReceiver, new IntentFilter("wake"));
	}
	
	/**
	 * �� ��ŸƮ
	 * (non-Javadoc)
	 * @see android.app.Service#onStart(android.content.Intent, int)
	 */
	@Override
	public void onStart(Intent intent, int startId){
		super.onStart(intent, startId);
		Log.d("CapstonDesign", "onStart()");
	}
	
	/**
	 * �½�ŸƮ Ŀ�ǵ�
	 * ����׶���� ����
	 * ����׶���� �ý��ۿ� ���� ���� �ʱ� ������ ��Ƽ�����̼����� ���������� �����ؾ� �Ѵ�.
	 * (non-Javadoc)
	 * @see http://ccdev.tistory.com/14
	 * @see android.app.Service#onStartCommand(android.content.Intent, int, int)
	 */
	@Override
	public int onStartCommand(Intent intent, int flags, int startId)
	{
		
		Log.d("CapstonDesign", "onStartCommand()");
		super.onStartCommand(intent, flags, startId);
		
		//registerRestartAlarm(true);
		
		Toast.makeText(getBaseContext(), "���� �����ߴ�", Toast.LENGTH_SHORT).show();
		Notification notification = new Notification(R.drawable.ic_launcher, "���� �����", System.currentTimeMillis());
		notification.setLatestEventInfo(getApplicationContext(), "�ҹ溧 ���� ��", "Foreground�� �����", null);
		startForeground(1, notification);
		
		threadFlag = false;
		Thread t = new Thread(null, this, "player");
		  // �� ������ Thread�� ������ �ȴ�.
		t.start();
		
		return START_STICKY;
	}
	
	/**
	 * Binding�� �ʿ��Ҷ�
	 * (non-Javadoc)
	 * @see android.app.Service#onBind(android.content.Intent)
	 * @param non
	 * @retrun non ( ���ε� �Ҷ� �ٸ� �ɷ� )
	 */
	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		Log.d("CapstonDesign", "onBind()");
		return null;
	}
	
	/**
	 * �Ҹ���
	 * (non-Javadoc)
	 * @see android.app.Service#onDestroy()
	 */
	@Override
	public void onDestroy(){
		super.onDestroy();
		Log.d("CapstonDesign", "onDestroy()");
		//threadFlag = false;
		//registerRestartAlarm(false);
		recordThread.stopRecord();
	}
	
	/**
	 * ������ ���� �ι�
	 * (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	@Override
	public void run() {
		// TODO Auto-generated method stub
		//isListening = true;
		final DatabaseHandler db = new DatabaseHandler(this);
		Log.d("service", "in db");

		existingFeaturesInDatabase = db.getAllFeatures();
		Log.d("service", "Features count: "+ existingFeaturesInDatabase.size());

		final int dbcnt = db.getFeaturesCount();
		
		recordThread = new RecordThread() 
		{
			int Index = 0;
			int cnt = 0;
			
			@Override
			protected void dataArrival(long timestamp, short[] data, int length, int frameLength) 
			{
				super.dataArrival(timestamp, data, length, frameLength);
				SimpleDateFormat sdfNow = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
				String strNow = sdfNow.format(new Date(System.currentTimeMillis()));
				Log.i("ListeningService", ""+strNow);
				if (Index % 5 == 0)
				{					
					FeaturesMatchFinderTask task = new FeaturesMatchFinderTask(dbcnt, featuresExtractor.extractFeatures(data));
					final String[] match = task.getPercent(existingFeaturesInDatabase);
					
					for(int i = 0 ; i < match.length ; i++)
					{
						Match matchvalue = task.returnmatch.poll();
						double nine = 91.0 ;
						double q = matchvalue.percentage;
						Log.i("", ""+matchvalue.percentage);
						if(matchvalue.name.equalsIgnoreCase("�ҹ溧1����") || 
								matchvalue.name.equalsIgnoreCase("�ҹ溧2��") || 
								matchvalue.name.equalsIgnoreCase("�ҹ溧3����") || 
								matchvalue.name.equalsIgnoreCase("�ҹ溧5����") ||
								matchvalue.name.equalsIgnoreCase("�ҹ溧"))
						{
							if(q > nine)
							{
								//Log.e("r", matchvalue.name);
								
								//final Context context = this;
								mRegisterTask = new AsyncTask<Void, Void, Void>() {

									@Override
									protected Void doInBackground(Void... params) {
										Map<String, String> params1 = new HashMap<String, String>();
								        params1.put("msg", "11");
										try {
											SU.post("http://165.229.88.50/gcm_server_php/testallpush.php", params1);
										} catch (IOException e) {
											// TODO Auto-generated catch block
											e.printStackTrace();
										}
										
										return null;
									}
									@Override
									protected void onPostExecute(Void result) {
										mRegisterTask = null;
									}

								};
								mRegisterTask.execute(null, null, null);
								
								
								
								ComponentName compName = new ComponentName("com.example.capstondesign", "com.example.capstondesign.EmergencyActivitiy"); 
							    Intent intent = new Intent("android.intent.action.Tile");
							    intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
							    intent.addCategory("android.intent.category.DEFAULT");
							    intent.setComponent(compName);
							    
							    PowerManager powerManager = (PowerManager)getSystemService(Context.POWER_SERVICE);
							    mWakeLock = powerManager.newWakeLock(PowerManager.FULL_WAKE_LOCK, "WakeLock!!");
							    mWakeLock.acquire();
							    
							    Intent intent1 = new Intent("wake");
						        sendBroadcast(intent1);
						        
						        Intent serviceIntent = new Intent(getBaseContext(), ListeningService.class);
								stopService(serviceIntent);
								
							    startActivity(intent);
							    
							}
						}
						//Log.d("service", matchvalue.name+", "+matchvalue.percentage+", "+matchvalue.matchValue);
						//Log.e("r", match[i]);
					}
					//Returnmatch = task.returnmatch;
					
					/*Iterator<Match> itr = Returnmatch.iterator();
					while (itr.hasNext()) 
					{
						Match temp = itr.next();
						if(temp.name.equals("�ҹ溧"))
						{
							if(temp.percentage > 80)
							{

								//Ÿ ������ Activity ����
								
								ComponentName compName = new ComponentName("com.example.capstondesign", "com.example.capstondesign.EmergencyActivitiy"); 
							    Intent intent = new Intent("android.intent.action.Tile");
							    intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
							    intent.addCategory("android.intent.category.DEFAULT");
							    intent.setComponent(compName);
							    
							    PowerManager powerManager = (PowerManager)getSystemService(Context.POWER_SERVICE);
							    mWakeLock = powerManager.newWakeLock(PowerManager.FULL_WAKE_LOCK, "WakeLock!!");
							    mWakeLock.acquire();
							    //startActivity("wake");
							    Intent intent1 = new Intent("wake");
						        //intent.putExtra(EXTRA_MESSAGE, message);
						        sendBroadcast(intent1);
							    
							    
							    startActivity(intent);
							     
							}
						}
						Log.d("service", temp.name+", "+temp.percentage+", "+temp.matchValue);
					}*/
				}
				if (Index == 100) {
					Index = 0;
				}
				Index++;
			}
			
		};
		recordThread.startRecord();
	}
	

	
	private final BroadcastReceiver mHandleMessageReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			//String newMessage = intent.getExtras().getString(EXTRA_MESSAGE);
			// Waking up mobile if it is sleeping
			WakeLocker.acquire(getApplicationContext());
			
			/**
			 * Take appropriate action on this message
			 * depending upon your app requirement
			 * For now i am just displaying it on the screen
			 * */
			
			// Showing received message
			//lblMessage.append(newMessage + "\n");			
			//Toast.makeText(getApplicationContext(), "New Message: " + newMessage, Toast.LENGTH_LONG).show();
			
			// Releasing wake lock
			WakeLocker.release();
		}
	};
}
