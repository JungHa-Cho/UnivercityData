package com.example.capstondesign;

import java.io.IOException;

import wifi.WifiScan;
import background.ListeningService;
import android.app.Activity;
import android.app.KeyguardManager;
import android.app.KeyguardManager.KeyguardLock;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.content.res.AssetFileDescriptor;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Toast;

public class EmergencyActivitiy extends Activity {
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		final MediaPlayer  audio_play = MediaPlayer.create(this, R.raw.siren);
		audio_play.setVolume(1, 1);
		audio_play.start();
		requestWindowFeature(Window.FEATURE_NO_TITLE);
				
		setContentView(R.layout.activity_emergency_activitiy);
		final Intent intent = new Intent(this, TileViewActivity.class);
		
		
		
		//splash
		Handler handler = new Handler(){
			public void handleMessage(Message msg){
				
				audio_play.stop();
				startActivity(intent);
				finish();
			}
		};
		handler.sendEmptyMessageDelayed(0, 3000);
	}
	
	
	// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ///////// �޴� ������ ���� �Լ��� ///////////
	// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 * �޴� ���� (non-Javadoc)
	 * 
	 * @see android.app.Activity#onCreateOptionsMenu(android.view.Menu)
	 */
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	/**
	 * (non-Javadoc)
	 * 
	 * @return
	 * @see android.app.Activity#onPrepareOptionsMenu(android.view.Menu)
	 */
	@Override
	public boolean onPrepareOptionsMenu(Menu menu) {
		//Log.d(TAG, "onPrepareOptionsMenu()");
		SharedPreferences prefs = getSharedPreferences("Variable", MODE_PRIVATE);
		if (prefs.getBoolean("ServiceCheck", true))
		{
			// Toast.makeText(this, "prepare true", Toast.LENGTH_SHORT).show();
			menu.getItem(1).setChecked(true);
		}
		return super.onPrepareOptionsMenu(menu);
	}

	/**
	 * �޴� ���� ������ ����Ǵ� �� (non-Javadoc)
	 * 
	 * @see android.app.Activity#onOptionsItemSelected(android.view.MenuItem)
	 */
	@Override
	public boolean onMenuItemSelected(int featureId, MenuItem item) {
		// TODO Auto-generated method stub

		/* ������ �������� ���� */
		SharedPreferences prefs = getSharedPreferences("Variable", MODE_PRIVATE);
		SharedPreferences.Editor ed = prefs.edit();

		if (item.getItemId() == R.id.subMenu2) {
			Toast.makeText(this, "Tileview �޴� �Դϴ�", Toast.LENGTH_SHORT).show();
		}
		if (item.getItemId() == R.id.tilesubmenu) {
			//Log.d(TAG, "Start Wifi Scan");
			//initWIFIScan(); // start WIFIScan
		}
		if (item.getItemId() == R.id.tilesubmenu2) {
			//Log.d(TAG, "Stop Wifi Scan");
			//unregisterReceiver(mReceiver); // stop WIFISCan
		}
		if (item.getItemId() == R.id.tilesubmenu3) {
			//TestKnn();
		}
		if (item.getItemId() == R.id.SimpleMenu2) {
			// Toast.makeText(this, "�⺻ �޴��� ��ġ�Ǿ����ϴ�",
			// Toast.LENGTH_SHORT).show();
			Intent i = new Intent(getApplicationContext(), WifiScan.class);
			startActivity(i);
			finish();
		}

		if (item.getItemId() == R.id.clickAbleMenu) {
			if (item.isChecked()) {
				ed.putBoolean("ServiceCheck", false); // value : ����� ��,
				ed.commit(); // �ʼ�! �̰��� �����ָ� ������ �ȵǿ�!

				item.setChecked(false);
				Toast.makeText(this, "ListeningService�� ���� �˴ϴ�.",
						Toast.LENGTH_SHORT).show();
				Intent intent = new Intent(this, ListeningService.class);
				stopService(intent);
			} else {
				ed.putBoolean("ServiceCheck", true); // value : ����� ��,
				ed.commit(); // �ʼ�! �̰��� �����ָ� ������ �ȵǿ�!

				item.setChecked(true);
				Toast.makeText(this, "ListeningService�� ���� �˴ϴ�.",
						Toast.LENGTH_SHORT).show();
				Intent intent = new Intent(this, ListeningService.class);
				startService(intent);
			}
		}

		if (item.getItemId() == R.id.SimpleMenu) {
			// Toast.makeText(this, "�⺻ �޴��� ��ġ�Ǿ����ϴ�",
			// Toast.LENGTH_SHORT).show();
			Intent i = new Intent(getApplicationContext(),
					TileViewActivity.class);
			startActivity(i);
			finish();
		}

		return super.onMenuItemSelected(featureId, item);
	}

}
