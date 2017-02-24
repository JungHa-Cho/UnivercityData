package wifi;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;






import com.example.capstondesign.R;
import com.example.capstondesign.TileViewActivity;


public class WifiScan extends Activity implements OnClickListener
{
	static final String TAG = "WIFIScanner";
	static final String SERVER_URL = "http://165.229.88.50/mysql/register.php";
	private DbOpenHelper mDbOpenHelper;
	private int scanCount = 0;
	private int DBcount = 0;
	int TotalCount = 0;
    private List<ScanResult> mScanResult; // ScanResult List
    
    List<ScanResultInfo> ListWifi;
	WifiManager wifimanager;
	TextView textStatus;
	
	Button btnScanStart;
	Button btnScanStop;
	Button btnGoDB;
	Button btnClear;
	
	EditText editText1;
	EditText editText2;
	
	String text = "";
	String result = "";
 
    ScanResult result1;
    
   	@Override
	protected void onCreate(Bundle savedInstanceState)
   	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_wifi_scan);
		
		// Setup UI
		textStatus = (TextView) findViewById(R.id.textStatus);
		btnScanStart = (Button) findViewById(R.id.btnScanStart);
		btnScanStop = (Button) findViewById(R.id.btnScanStop);
		btnGoDB = (Button) findViewById(R.id.btnDB);
		btnClear = (Button) findViewById(R.id.clear);

		// Setup OnClickListener
		btnScanStart.setOnClickListener(this);
		btnScanStop.setOnClickListener(this);
		btnGoDB.setOnClickListener(this);
		btnClear.setOnClickListener(this);
		
		editText1 = (EditText) findViewById(R.id.editText1); // counting
		editText2 = (EditText) findViewById(R.id.editText2); // x
		
		
		ListWifi = new ArrayList<ScanResultInfo>();
		
		mDbOpenHelper = new DbOpenHelper(this);
        mDbOpenHelper.open();
        
		// Setup WIFI
		wifimanager = (WifiManager)getSystemService(WIFI_SERVICE);
		Log.d(TAG, "Setup WIfiManager getSystemService");
		
		// if WIFIEnabled
		if (wifimanager.isWifiEnabled() == false)
			wifimanager.setWifiEnabled(true);
		
	}
	
	private BroadcastReceiver mReceiver = new BroadcastReceiver() 
	{
		@Override
		public void onReceive(Context context, Intent intent) 
		{
			final String action = intent.getAction();
			if (action.equals(WifiManager.SCAN_RESULTS_AVAILABLE_ACTION)) 
			{
				getWIFIScanResult(); // get WIFISCanResult
				wifimanager.startScan(); // for refresh
			} 
			else if (action.equals(WifiManager.NETWORK_STATE_CHANGED_ACTION)) 
			{
				sendBroadcast(new Intent("wifi.ON_NETWORK_STATE_CHANGED"));
			}
		}
	};

	public void getWIFIScanResult() {
		mScanResult = wifimanager.getScanResults(); // ScanResult
		
		textStatus.setText("Scan count is \t" + ++scanCount + " times \n");
		if(ListWifi.isEmpty())
		{
			textStatus.append("=======================================\n");
			for (int i = 0; i < mScanResult.size(); i++) {
				result1 = mScanResult.get(i);
				textStatus.append((i + 1) + ". SSID : " + result1.SSID.toString() + "\t\t RSSI : " + result1.level + " dBm \n" /*+ result1.frequency+ " " + result1.BSSID + "\n"*/);
				
				ScanResultInfo wifi = new ScanResultInfo(result1.SSID.toString(),result1.BSSID,result1.level, 1, 0, 0);
				ListWifi.add(wifi);
				Log.d("qqqq", "이름 매치 - " + ListWifi.get(i).name +", "+result1.BSSID+", "+ListWifi.get(i).counting+", "+ListWifi.get(i).RSSI);
			}
			textStatus.append("=======================================\n"+Integer.toString(ListWifi.size()));
			DBcount = ListWifi.size();
		}else{
			textStatus.append("=======================================\n");
			int compare = 0;
			for (int i = 0; i < mScanResult.size(); i++) {
				result1 = mScanResult.get(i);
				textStatus.append((i + 1) + ". SSID : " + result1.SSID.toString() + "\t\t RSSI : " + result1.level + " dBm \n" /*+ result1.frequency+ " " + result1.BSSID + "\n"*/);
				
				for(int j = 0 ; j < ListWifi.size() ; j ++)
				{
					String empty = result1.BSSID;
					if(ListWifi.get(j).BSSID.equals(empty))
					{
						ListWifi.get(j).RSSI = ListWifi.get(j).RSSI + result1.level;
						ListWifi.get(j).counting++;
						Log.d("qqqq", "이름 매치 - " + ListWifi.get(j).name +", "+result1.BSSID+", "+ListWifi.get(j).counting+", "+ListWifi.get(j).getRSSI());
						compare = 1;
					}
				}
				
				if(compare == 0)
				{
					ScanResultInfo wifi = new ScanResultInfo(result1.SSID.toString(),result1.BSSID,result1.level, 1, 0, 0);
					ListWifi.add(wifi);
				}
				compare = 0;
			}
			textStatus.append("=======================================\n"+Integer.toString(ListWifi.size()));
		}
		Log.d("qqqq", Integer.toString(ListWifi.size()));
	}

	public void initWIFIScan() 
	{
		scanCount = 0;
		text = "";
		final IntentFilter filter = new IntentFilter(WifiManager.SCAN_RESULTS_AVAILABLE_ACTION);
		filter.addAction(WifiManager.NETWORK_STATE_CHANGED_ACTION);
		registerReceiver(mReceiver, filter);
		wifimanager.startScan();
		Log.d(TAG, "initWIFIScan()");
	}
	
	public void printToast(String messageToast) 
	{
		Toast.makeText(this, messageToast, Toast.LENGTH_LONG).show();
	}
	
	@Override
	public void onClick(View v)
	{
		if (v.getId() == R.id.btnScanStart) 
		{
			Log.d(TAG, "OnClick() btnScanStart()");
			printToast("WIFI SCAN !!!");
			initWIFIScan(); // start WIFIScan
		}
		if (v.getId() == R.id.btnScanStop)
		{
			Log.d(TAG, "OnClick() btnScanStop()");
			printToast("WIFI STOP !!!");
			unregisterReceiver(mReceiver); // stop WIFISCan
			
		}
		if (v.getId() == R.id.clear)
		{
			Log.d("qqqq", "OnClick() btnScanStop()");
			printToast("clear");
			ListWifi.clear();
		}
		if (v.getId() == R.id.btnDB) 
		{
			Log.d("qqqq", "OnClick() btnScanStop()");
			printToast("register");
			textStatus.setText("Go DB\n");
			textStatus.append("=======================================\n");
			for (int i = 0; i < ListWifi.size(); i++)
			{
				textStatus.append((i + 1) + ListWifi.get(i).name + "\t\t RSSI : " + ListWifi.get(i).RSSI + ", avg : "+ListWifi.get(i).getRSSI()+", count : "+ListWifi.get(i).counting+"\n");
		        mDbOpenHelper.insertColumn(ListWifi.get(i).name, ListWifi.get(i).BSSID, String.valueOf(ListWifi.get(i).getRSSI()), editText2.getText().toString(), editText1.getText().toString(), String.valueOf(ListWifi.get(i).counting));
			}
			textStatus.append("Total Count = "+Integer.toString(mDbOpenHelper.getCulumnCnt().getCount()));
		}
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
		
		if(item.getItemId()==R.id.SimpleMenu)
		{
			//Toast.makeText(this, "기본 메뉴가 터치되었습니다", Toast.LENGTH_SHORT).show();
			Intent i = new Intent(getApplicationContext(), TileViewActivity.class);
			startActivity(i);
			finish();
		}
		return super.onMenuItemSelected(featureId, item);
	}
	
    @Override
    protected void onDestroy() 
    {
        mDbOpenHelper.close();
        super.onDestroy();
    }
}
