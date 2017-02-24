/**
 * File Name: "MainActivity.java"
 * Descrption:
 * - 실내 위치 측위를 이용한 재해 재난 탐지 및 탈출구 안내
 * 
 * Programmed by Jung-Ha Cho,
 * Last Updated: Version 2.0, 11 1, 2014 (by Jung-Ha Cho)
 * 
 * =================================================================================
 * Version Control (Explain Updates in detail)
 * =================================================================================
 * Name  	YYYY/MM/DD Version Remarks
 * JungHa	2014/10/27 1.0	   Make and Cording to ListeningService
 *                             Boot Receiver Cording
 * TEAM.JY	2014/10/28 1.1	   Service Cording    
 * TEAM.JY  2014/10/29 1.2	   GCM server cording
 * TEAM.JY	2014/10/30 1.3	   GCM service
 * TEAM.JY	2014/10/31 1.4	   GCM BroadCasting
 * TEAM.JY	2014/11/01 1.5	   GCM Marster
 * TEAM.JY	2014/11/04 1.6	   WifiScan
 * TEAM.JY	2014/11/09 1.7     Server Database
 * TEAM.JY	2014/11/10 1.8     Tile View
 * TEAM.JY	2014/11/12 2.0     Tile View In Wifi Scan
 * TEAM.JY	2014/11/13 2.1     Current Position View
 * TEAM.JY	2014/11/14 2.2     PathFinder
 * TEAM.JY	2014/11/15 2.3     Audio Litening
 * TEAM.JY	2014/11/19 2.4     Record Thread
 * TEAM.JY	2014/11/20 2.5     AudioFeaturesExtractor
 *          
 */
package com.example.capstondesign;


import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import wifi.WifiScan;

import com.example.capstondesign.R;

import static com.example.capstondesign.CommonUtilities.DISPLAY_MESSAGE_ACTION;
import static com.example.capstondesign.CommonUtilities.EXTRA_MESSAGE;
import static com.example.capstondesign.CommonUtilities.SENDER_ID;

import com.google.android.gcm.GCMRegistrar;

import edu.buffalo.realdoublefft.RealDoubleFFT;
import background.ListeningService;
import android.accounts.Account;
import android.accounts.AccountManager;
import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.AsyncTask;
import android.os.Bundle;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;
import audio.record.RecordActivity;

public class MainActivity extends Activity implements OnClickListener{
	//static final String EXTRA_MESSAGE = "message";
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	public static String name;
	public static String email;
	
	// Asyntask
	AsyncTask<Void, Void, Void> mRegisterTask;
	Button btnPush;
	Button test;
	EditText txt_input;
	ServerUtilities SU;
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	int frequency = 8000;
	int channelConfiguration = AudioFormat.CHANNEL_CONFIGURATION_MONO;
	int audioEncoding = AudioFormat.ENCODING_PCM_16BIT;
	
	private RealDoubleFFT transformer;
	int blockSize = 1920;
	Button startStopButton;
	boolean started = false;
	
	RecordAudio recordTask;
	
	ImageView imageView;
	Bitmap bitmap;
	Canvas canvas;
	Paint paint;
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	
	
	/**
	 * (non-Javadoc)
	 * @see android.app.Activity#onCreate(android.os.Bundle)
	 */
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	
		  
		///////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////
		txt_input = (EditText) findViewById(R.id.txt_input);
		name = readphonenumber();
		email = reademail();	
		// 디바이스 검사
		GCMRegistrar.checkDevice(this);
		// 매니페스트 검사
		GCMRegistrar.checkManifest(this);
		registerReceiver(mHandleMessageReceiver, new IntentFilter(DISPLAY_MESSAGE_ACTION));
		// Get GCM registration id
		final String regId = GCMRegistrar.getRegistrationId(this);
		btnPush = (Button) findViewById(R.id.btn_stop);
		btnPush.setOnClickListener(this);
		test = (Button) findViewById(R.id.test);
		test.setOnClickListener(this);
		
		// Check if regid already presents
		// regid 기기 고유번호 검사
		if (regId.equals("")) {
			// Registration is not present, register now with GCM			
			// this 컨텍스트와 센더 아이디로 등록 요청
			GCMRegistrar.register(this, SENDER_ID);
			//Toast.makeText(getApplicationContext(), "1", Toast.LENGTH_LONG).show();
		} else {
			// Device is already registered on GCM
			if (GCMRegistrar.isRegisteredOnServer(this)) {
				// Skips registration.				
				Toast.makeText(getApplicationContext(), "GCM : 등록된 기기 입니다.", Toast.LENGTH_LONG).show();
			} else {
				//Toast.makeText(getApplicationContext(), "3", Toast.LENGTH_LONG).show();
				// Try to register again, but not in the UI thread.
				// It's also necessary to cancel the thread onDestroy(),
				// hence the use of AsyncTask instead of a raw thread.
				final Context context = this;
				mRegisterTask = new AsyncTask<Void, Void, Void>() {

					@Override
					protected Void doInBackground(Void... params) {
						// Register on our server
						// On server creates a new user
						// 등록
						ServerUtilities.register(context, name, email, regId);
						return null;
					}

					@Override
					protected void onPostExecute(Void result) {
						mRegisterTask = null;
					}

				};
				mRegisterTask.execute(null, null, null);
			}
		}
		///////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////
		
		startStopButton = (Button) findViewById(R.id.StartStopButton);
		startStopButton.setOnClickListener(this);

		// RealDoubleFFT 클래스 컨스트럭터는 한번에 처리할 샘플들의 수를 받는다. 그리고 출력될 주파수 범위들의 수를
		// 나타낸다.
		transformer = new RealDoubleFFT(blockSize);

		// ImageView 및 관련 객체 설정 부분
		imageView = (ImageView) findViewById(R.id.ImageView01);
		bitmap = Bitmap.createBitmap((int) 1024, (int) 1024,
				Bitmap.Config.ARGB_8888);
		canvas = new Canvas(bitmap);
		paint = new Paint();
		paint.setColor(Color.GREEN);
		imageView.setImageBitmap(bitmap);
		
		///////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////
		

		
		
	}
	
	private class RecordAudio extends AsyncTask<Void, double[], Void> {
		@Override
		protected Void doInBackground(Void... params) {
			try {
				// AudioRecord를 설정하고 사용한다.
				int bufferSize = AudioRecord.getMinBufferSize(frequency,
						channelConfiguration, audioEncoding);

				AudioRecord audioRecord = new AudioRecord(
						MediaRecorder.AudioSource.MIC, frequency,
						channelConfiguration, audioEncoding, bufferSize);

				// short로 이뤄진 배열인 buffer는 원시 PCM 샘플을 AudioRecord 객체에서 받는다.
				// double로 이뤄진 배열인 toTransform은 같은 데이터를 담지만 double 타입인데, FFT
				// 클래스에서는 double타입이 필요해서이다.
				short[] buffer = new short[blockSize];
				double[] toTransform = new double[blockSize];

				audioRecord.startRecording();

				while (started) {
					int bufferReadResult = audioRecord.read(buffer, 0,
							blockSize);

					// AudioRecord 객체에서 데이터를 읽은 다음에는 short 타입의 변수들을 double 타입으로
					// 바꾸는 루프를 처리한다.
					// 직접 타입 변환(casting)으로 이 작업을 처리할 수 없다. 값들이 전체 범위가 아니라 -1.0에서
					// 1.0 사이라서 그렇다
					// short를 32,768.0(Short.MAX_VALUE) 으로 나누면 double로 타입이 바뀌는데,
					// 이 값이 short의 최대값이기 때문이다.
					for (int i = 0; i < blockSize && i < bufferReadResult; i++) {
						toTransform[i] = (double) buffer[i] / Short.MAX_VALUE; // 부호
																				// 있는
																				// 16비트
					}

					// 이제 double값들의 배열을 FFT 객체로 넘겨준다. FFT 객체는 이 배열을 재사용하여 출력 값을
					// 담는다. 포함된 데이터는 시간 도메인이 아니라
					// 주파수 도메인에 존재한다. 이 말은 배열의 첫 번째 요소가 시간상으로 첫 번째 샘플이 아니라는 얘기다.
					// 배열의 첫 번째 요소는 첫 번째 주파수 집합의 레벨을 나타낸다.

					// 256가지 값(범위)을 사용하고 있고 샘플 비율이 8,000 이므로 배열의 각 요소가 대략
					// 15.625Hz를 담당하게 된다. 15.625라는 숫자는 샘플 비율을 반으로 나누고(캡쳐할 수 있는
					// 최대 주파수는 샘플 비율의 반이다. <- 누가 그랬는데...), 다시 256으로 나누어 나온 것이다.
					// 따라서 배열의 첫 번째 요소로 나타난 데이터는 영(0)과 15.625Hz 사이에
					// 해당하는 오디오 레벨을 의미한다.
					transformer.ft(toTransform);
					// publishProgress를 호출하면 onProgressUpdate가 호출된다.
					publishProgress(toTransform);
				}

				audioRecord.stop();
			} catch (Throwable t) {
				Log.e("AudioRecord", "Recording Failed");
			}

			return null;
		}
		
		@Override
		protected void onProgressUpdate(double[]... toTransform) {
			canvas.drawColor(Color.BLACK);

			for (int i = 0; i < toTransform[0].length; i++) 
			{
				int x = i;
				int downy = (int) (512 - (toTransform[0][i] * 10));
				int upy = 512;

				canvas.drawLine(x, downy, x, upy, paint);
			}
			imageView.invalidate();
		}
	}

	

	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	/**
	 *  PushAll Message
	 */
	@Override
	public void onClick(View v)
	{
		if (v.getId() == R.id.StartStopButton) 
		{
			//Intent intent = new Intent(this, GPSservice.class);
			//startService(intent);
			if (started) {
				started = false;
				startStopButton.setText("Start");
				recordTask.cancel(true);
			} else {
				started = true;
				startStopButton.setText("Stop");
				recordTask = new RecordAudio();
				recordTask.execute();
			}
		}
		if (v.getId() == R.id.btn_stop) 
		{
			//////////////////////////////////////////////////////////
			//Toast.makeText(getApplicationContext(), "3", Toast.LENGTH_LONG).show();
			// Try to register again, but not in the UI thread.
			// It's also necessary to cancel the thread onDestroy(),
			// hence the use of AsyncTask instead of a raw thread.
			final Context context = this;
			mRegisterTask = new AsyncTask<Void, Void, Void>() {

				@Override
				protected Void doInBackground(Void... params) {
					// Register on our server
					// On server creates a new user
					// 등록
					//post("http://165.229.88.50/gcm_server_php/pushall.php", null);
					
				/*	try {
						URL url = new URL("http://165.229.88.50/gcm_server_php/pushall.php");

						InputStream isText = url.openStream();
						byte[] bText = new byte[250];
						int readSize = isText.read(bText);
						Log.i("Net", "readSize = " + readSize);
						Log.i("Net", "bText = " + new String(bText));
						isText.close();
					}catch(Exception e){
						Log.e("Net", "네트워크 에러가..났습니다...", e);
					}*/
					Map<String, String> params1 = new HashMap<String, String>();
					if(txt_input.getText() == null)
					{
						//Toast.makeText(this, "ListeningService가 종료 됩니다.", Toast.LENGTH_SHORT).show();
						return null;
					}
			        params1.put("msg", txt_input.getText().toString());
			        Log.e("", txt_input.getText().toString());
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
			//////////////////////////////////////////////////////////
		}
		
		if (v.getId() == R.id.test) 
		{
			Intent i = new Intent(getApplicationContext(), EmergencyActivitiy.class);
			startActivity(i);
			finish();

		}
	}
	
	public String reademail()
	{
	    AccountManager mgr = AccountManager.get(this);
	    Account[] accts = mgr.getAccounts();
	    final int count = accts.length;
	    Account acct = null;
	    for(int i=0;i<count;i++) {
	        acct = accts[i];
	        //Log.d("ANDROES", acct.name);
	    }       
		return accts[0].name;
	}
	/**
	 * 휴대폰 번호 출력
	 */
	public String readphonenumber()
	{
	    TelephonyManager systemService = (TelephonyManager)getSystemService    (Context.TELEPHONY_SERVICE);
	    String PhoneNumber = systemService.getLine1Number();
	    PhoneNumber = PhoneNumber.substring(PhoneNumber.length()-10,PhoneNumber.length());
	    PhoneNumber="0"+PhoneNumber;
		return PhoneNumber;
	}
	
	/**
	 * 메뉴 설정
	 * (non-Javadoc)
	 * @see android.app.Activity#onCreateOptionsMenu(android.view.Menu)
	 */
	public boolean onCreateOptionsMenu(Menu menu)
	{
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	/**
	 * (non-Javadoc)
	 * @return 
	 * @see android.app.Activity#onPrepareOptionsMenu(android.view.Menu)
	 */
	@Override
	public boolean onPrepareOptionsMenu(Menu menu)
	{
		Log.d("CapstonDesign", "onPrepareOptionsMenu()");
		SharedPreferences prefs = getSharedPreferences( "Variable" , MODE_PRIVATE);
		if(prefs.getBoolean("ServiceCheck", true))
		{
			//Toast.makeText(this, "prepare true", Toast.LENGTH_SHORT).show();
			menu.getItem(2).setChecked(true);
		}
		return super.onPrepareOptionsMenu(menu);
	}
	
	/**
	 * 메뉴 선택 됐을때 실행되는 것
	 * (non-Javadoc)
	 * @see android.app.Activity#onOptionsItemSelected(android.view.MenuItem)
	 */
	@Override
	public boolean onMenuItemSelected(int featureId, MenuItem item) {
		// TODO Auto-generated method stub
		
		/* 간단한 설정변수 저장 */
		SharedPreferences prefs = getSharedPreferences( "Variable" , MODE_PRIVATE);
		SharedPreferences.Editor ed = prefs.edit();

		if(item.getItemId()==R.id.subMenu2)
		{
			Toast.makeText(this, "Tileview 메뉴 입니다", Toast.LENGTH_SHORT).show();
		}
		
		if(item.getItemId()==R.id.SimpleMenu4)
		{
			Intent i = new Intent(getApplicationContext(), GraphViewActivity.class);
			startActivity(i);
			finish();	
		}
		
		
		if(item.getItemId()==R.id.SimpleMenu3)
		{
			Intent i = new Intent(getApplicationContext(), RecordActivity.class);
			startActivity(i);
			finish();			
		}
		
		if(item.getItemId()==R.id.SimpleMenu)
		{
			//Toast.makeText(this, "기본 메뉴가 터치되었습니다", Toast.LENGTH_SHORT).show();
			Intent i = new Intent(getApplicationContext(), TileViewActivity.class);
			startActivity(i);
			finish();
		}
		
		if(item.getItemId()==R.id.SimpleMenu2)
		{
			//Toast.makeText(this, "기본 메뉴가 터치되었습니다", Toast.LENGTH_SHORT).show();
			Intent i = new Intent(getApplicationContext(), WifiScan.class);
			startActivity(i);
			finish();
		}
		
		if(item.getItemId() == R.id.clickAbleMenu)
		{	
			if(item.isChecked())
			{
				ed.putBoolean("ServiceCheck" , false); // value : 저장될 값, 
				ed.commit(); // 필수! 이것을 안해주면 저장이 안되요!
				
				item.setChecked(false);
				Toast.makeText(this, "ListeningService가 종료 됩니다.", Toast.LENGTH_SHORT).show();
				Intent intent = new Intent(this, ListeningService.class);
				stopService(intent);
			}
			else
			{
				ed.putBoolean( "ServiceCheck" , true); // value : 저장될 값, 
				ed.commit(); // 필수! 이것을 안해주면 저장이 안되요!
				
				item.setChecked(true);
				Toast.makeText(this, "ListeningService가 실행 됩니다.", Toast.LENGTH_SHORT).show();
				Intent intent = new Intent(this, ListeningService.class);
				startService(intent);
			}
		}

/*		if(item.getItemId()==R.id.subMenu_2)
		{
			Toast.makeText(this, "서브메뉴 2가 터치되었습니다", Toast.LENGTH_SHORT).show();
		}
		if(item.getItemId()==R.id.subMenu_3)
		{
			Toast.makeText(this, "서브메뉴 3이 터치되었습니다", Toast.LENGTH_SHORT).show();
		}*/
		
		/*if(item.getItemId()==R.id.actionBarMenu){
			Toast.makeText(this, "액션바 메뉴가 터치되었습니다", Toast.LENGTH_SHORT).show();
		}
		if(item.getItemId()==R.id.IconMenu){
			Toast.makeText(this, "아이콘 메뉴가 터치되었습니다", Toast.LENGTH_SHORT).show();
		}*/
		
		return super.onMenuItemSelected(featureId, item);
	}
	
	/**
	 * Receiving push messages
	 * */
	private final BroadcastReceiver mHandleMessageReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			String newMessage = intent.getExtras().getString(EXTRA_MESSAGE);
			// Waking up mobile if it is sleeping
			WakeLocker.acquire(getApplicationContext());
			
			/**
			 * Take appropriate action on this message
			 * depending upon your app requirement
			 * For now i am just displaying it on the screen
			 * */
			
			// Showing received message
			//lblMessage.append(newMessage + "\n");			
			Toast.makeText(getApplicationContext(), "New Message: " + newMessage, Toast.LENGTH_LONG).show();
			
			// Releasing wake lock
			WakeLocker.release();
		}
	};
	
	@Override
	protected void onDestroy() {
		if (mRegisterTask != null) {
			mRegisterTask.cancel(true);
		}
		try {
			unregisterReceiver(mHandleMessageReceiver);
			GCMRegistrar.onDestroy(this);
		} catch (Exception e) {
			Log.e("UnRegister Receiver Error", "> " + e.getMessage());
		}
		super.onDestroy();
	}


}
