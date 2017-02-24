package audio.record;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import wifi.WifiScan;
import background.ListeningService;

import com.example.capstondesign.R;
import com.example.capstondesign.TileViewActivity;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import audio.record.FeaturesMatchFinderTask.Match;


public class RecordActivity extends Activity implements OnClickListener/*, Runnable*/
{
	Button btn_start;
	Button btn_stop;
	TextView text;
	EditText edit_name;
	private Handler handler;
	private Boolean isListening;
	private AudioFeaturesExtractor featuresExtractor;
	private RecordThread recordThread;
	LinkedList<Feature> audioFeatures;
	private boolean recordswitch;
	private boolean matchingswitch;
	private List<Feature> existingFeaturesInDatabase;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_record);
		
		recordThread = new RecordThread();
		handler = new Handler();
		audioFeatures = new LinkedList<Feature>();
		featuresExtractor = new AudioFeaturesExtractor();
		
		btn_start = (Button) findViewById(R.id.btn_record);
		btn_stop = (Button) findViewById(R.id.btn_stop);
		text = (TextView) findViewById(R.id.textStatus);
		edit_name = (EditText) findViewById(R.id.edit_name);
		
		btn_start.setOnClickListener(this);
		btn_stop.setOnClickListener(this);
		
		recordswitch = true;
		matchingswitch = true;
	}

	@Override
	public void onClick(View v)
	{
		// TODO Auto-generated method stub
		if (v.getId() == R.id.btn_record) 
		{
			if(recordswitch)
			{
				startRecord();
				recordswitch = false;
			}else{
				stopRecord();
				recordswitch = true;
			}
		}
		
		if (v.getId() == R.id.btn_stop) 
		{
			if(matchingswitch)
			{
				startListening();
				matchingswitch = false;
			}else{
				stopListening();
				matchingswitch = true;
			}
		}
	}
	
	private void getFeaturesFromDatabase() 
	{
		final DatabaseHandler db = new DatabaseHandler(this);
		Log.d("database", "in db");

		existingFeaturesInDatabase = db.getAllFeatures();
		Log.d("database", "Features count: "+ existingFeaturesInDatabase.size());

	}
	
	private void stopListening() 
	{
		isListening = false;
		recordThread.stopRecord();
	}
	
	private void startListening() 
	{
		
		//final List<Match> Temp = new ArrayList<Match>();
		isListening = true;
		getFeaturesFromDatabase();
		final DatabaseHandler db = new DatabaseHandler(this);
		final int dbcnt = db.getFeaturesCount();
		recordThread = new RecordThread() 
		{
			int count = 0;
			String s="";
			int frameIndex = 0;
			int cnt = 0;
			
			@Override
			protected void dataArrival(long timestamp, short[] data, int length, int frameLength) 
			{
				super.dataArrival(timestamp, data, length, frameLength);
				
				if (frameIndex % 5 == 0 && isListening)
				{				
					//Log.i("RecordActivity", "dataArrival");
					FeaturesMatchFinderTask task = new FeaturesMatchFinderTask(dbcnt, featuresExtractor.extractFeatures(data));
					final String[] match = task.getPercent(existingFeaturesInDatabase);
					//Log.e("TT", task.getPercent(existingFeaturesInDatabase)[0]);
					handler.post(new Runnable(){
						@Override
						public void run() 
						{
							text.setText("RecordCount = " + ++cnt+"\n");
							text.append("=======================================\n");
							for(int i = 0 ; i < match.length; i++)
							{
								
								text.append(match[i] + "\n");
							}
							text.append("=======================================\n");
						}
					});
					
					
					for(int i = 0 ; i < match.length; i++)
					{
						Match matchvalue = task.returnmatch.poll();
						if(matchvalue.name.equalsIgnoreCase("소방벨1미터"))
						{
							
							s = s + matchvalue.percentage+", ";
							Log.i("", ++count+", "+matchvalue.name+", "+matchvalue.percentage);
						}
						//Log.i("", cnt+", "+matchvalue.name+", "+matchvalue.percentage);
					}
					if(count == 50)
					{
						Log.i("", s);
					}
					/*
					String S = "";
					if(Temp.size() == 10)
					{
						for(int i = 0 ; i < Temp.size() ; i ++)
						{
							S = Temp.get(i).name+", "+Temp.get(i).percentage+", ";
						}
						Log.i("", S);
					}*/
					
				}
				if (frameIndex == 100) {
					frameIndex = 0;
				}
				frameIndex++;
			}
			
		};
		recordThread.startRecord();
	}
	
	public void stopRecord()
	{
		isListening = false;
		recordThread.stopRecord();
		
		String name = edit_name.getText().toString();
		
		DatabaseHandler db = new DatabaseHandler(this);

		Iterator<Feature> itr = audioFeatures.iterator();
		while (itr.hasNext()) 
		{
			Feature feature = itr.next();
			feature.setName(name);
			db.addFeature(feature);
		}

		// verify
		int featuresCount = db.getFeaturesCount();
		Toast.makeText(this, "Featues Added for " + name + " features new count: "+ featuresCount, Toast.LENGTH_LONG).show();

		db.close();
		
		audioFeatures.clear();
	}
	
	public void startRecord()
	{
		isListening = true;
		//int cnt = 0;
		recordThread = new RecordThread() 
		{
			int Index = 0;
			int cnt = 0;
			
			@Override
			protected void dataArrival(long timestamp, short[] data, int length, int frameLength) 
			{
				super.dataArrival(timestamp, data, length, frameLength);
				
				if (isListening && (Index%10==0)) 
				{//skip 10 frames for features extraction
					//Log.d("RecordThread", "RECORDING "+cnt++);
					final Feature feature = featuresExtractor.extractFeatures(data);
					audioFeatures.add(feature);
					
					handler.post(new Runnable(){
						@Override
						public void run() 
						{
							text.setText("RecordCount = " + ++cnt+"\n");
							text.append("=======================================\n");
							text.append("l1Norm - " + Double.toString(feature.getL1Norm())+"\n");
							text.append("l2Norm - " + Double.toString(feature.getL2Norm())+"\n");
							text.append("linfNorm - " + Double.toString(feature.getLinfNorm())+"\n");
							text.append("mfccs - " + feature.getMfccsAsString()+"\n");
							text.append("diffSecs - " + Double.toString(feature.getDiffSecs())+"\n");
							text.append("=======================================");
						}
					});
				}
				
				Index++;
				if(Index == Integer.MAX_VALUE - 1)
					Index = 0;
			}
		};
		
		recordThread.startRecord();
	
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 메뉴 관련 함수들
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
		//Log.d("CapstonDesign", "onPrepareOptionsMenu()");
		SharedPreferences prefs = getSharedPreferences( "Variable" , MODE_PRIVATE);
		if(prefs.getBoolean("ServiceCheck", true))
		{
			//Toast.makeText(this, "prepare true", Toast.LENGTH_SHORT).show();
			menu.getItem(1).setChecked(true);
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
		
		if(item.getItemId()==R.id.SimpleMenu3)
		{
			Toast.makeText(this, "RecordAudio 메뉴 입니다", Toast.LENGTH_SHORT).show();
			/*Intent i = new Intent(getApplicationContext(), RecordActivity.class);
			startActivity(i);
			finish();	*/		
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
}
