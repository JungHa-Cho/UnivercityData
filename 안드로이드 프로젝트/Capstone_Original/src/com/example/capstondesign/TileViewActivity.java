package com.example.capstondesign;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import wifi.DataBaseforAPP;
import wifi.DbOpenHelper;
import wifi.WifiScan;
import background.ListeningService;

import com.qozix.tileview.TileView;

import AstarAlgorithm.Node;
import AstarAlgorithm.Pathfinder;
import AstarAlgorithm.firstfloor;
import android.app.Activity;
import android.app.KeyguardManager;
import android.app.KeyguardManager.KeyguardLock;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.database.Cursor;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Window;
import android.view.WindowManager;
import android.view.animation.Animation;
import android.view.animation.RotateAnimation;
import android.widget.ImageView;
import android.widget.Toast;


public class TileViewActivity extends Activity implements SensorEventListener
{	
	static final String TAG = "TileViewActivity";  // Tag String 
	private int scanCount = 0;                     // WifiScan Counting
	private CurrentPOS pos;                        // CurrentPOS
	private ImageView imageView;                   // ImageView
	private TileView tileView;                     // TileView
    private float currentDegree = 0f;              // record the compass picture angle turned
	private List<ScanResult> mScanResult;          // ScanResult List
    private SensorManager mSensorManager;
    private SensorManager sSensorManager;
    boolean activityRunning;
    private static ArrayList<ImageView> remarker;
    private Pathfinder pathfinder;
	private firstfloor firstfloor;
	private int tempcount = 0;
	private int funccount = 0;
	private String tempstring = "";
	private DataBaseforAPP DBforAPP;
	private List<DataBaseforAPP> ListDBforAPP;
	private LinkedList<DataBaseforAPP> ListTemp;
	private DbOpenHelper mDbOpenHelper;
	private Cursor mCursor;
	
	ScanResult result1;
	WifiManager wifimanager;
    ImageView marker;
    
	HashMap<Integer , DataBaseforAPP> map;       // DataBase 관련 변수들 
	Set<Entry<Integer, DataBaseforAPP>> set;     // 검색속도를 위한 Hash
	Iterator<Entry<Integer, DataBaseforAPP>> it; // 변환을 위한 Iterator
	
	//HashMap<Integer , DataBaseforAPP> map1;       // DataBase 관련 변수들 
	//Set<Entry<Integer, DataBaseforAPP>> set1;     // 검색속도를 위한 Hash
	//Iterator<Entry<Integer, DataBaseforAPP>> it1; // 변환을 위한 Iterator
	
	ArrayList<double[]> pointsD = new ArrayList<double[]>();
    
	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		//setContentView(R.layout.activity_tile_view);
		
		// 전체화면 밑 상단 타이틀 바 화면 눕히기 고정
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
		
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_SHOW_WHEN_LOCKED |
				WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON | 
				WindowManager.LayoutParams.FLAG_DISMISS_KEYGUARD);
		
		// 와이파이 관련 설정 셋없
		// Setup WIFI
		wifimanager = (WifiManager) getSystemService(WIFI_SERVICE);
		//Log.d(TAG, "Setup WIfiManager getSystemService");
		
		// if WIFIEnabled
		if (wifimanager.isWifiEnabled() == false)
			wifimanager.setWifiEnabled(true);
		
		//initWIFIScan();
		// Copy of Data Base
		//DBforAPP = new DataBaseforAPP();
		ListTemp = new LinkedList<DataBaseforAPP>();
		ListDBforAPP = new ArrayList<DataBaseforAPP>();
		mDbOpenHelper = new DbOpenHelper(this);
        mDbOpenHelper.open();
        map = new HashMap<Integer, DataBaseforAPP>();
		//map1 = new HashMap<Integer, DataBaseforAPP>();
		// 타일 뷰와 이미지 뷰 초기화
		tileView = new TileView(this);
		imageView = new ImageView(this);
		
		tileView.setSize(1754, 1240);// 이미지 풀 사이즈
		//tileView.setSize(2482, 1754);
		
		// 잘려져 있는 타일들
		//tileView.addDetailLevel(1.000f, "tiles/thirdfloor/1000/%col$%_%row%.jpg", "samples/thirdfloor.jpg");
		//tileView.addDetailLevel(0.500f, "tiles/thirdfloor/500/%col%_%row%.jpg", "samples/thirdfloor.jpg");
		//tileView.addDetailLevel(0.250f, "tiles/thirdfloor/250/%col%_%row%.jpg", "samples/thirdfloor.jpg");
		//tileView.addDetailLevel(0.125f, "tiles/thirdfloor/125/%col%_%row%.jpg", "samples/thirdfloor.jpg");
		tileView.addDetailLevel(1.000f, "tiles/firstfloor/1000/%col$%_%row%.jpg", "samples/firstfloor.jpg");
		tileView.addDetailLevel(0.500f, "tiles/firstfloor/500/%col%_%row%.jpg", "samples/firstfloor.jpg");
		tileView.addDetailLevel(0.250f, "tiles/firstfloor/250/%col%_%row%.jpg", "samples/firstfloor.jpg");
		tileView.addDetailLevel(0.125f, "tiles/firstfloor/125/%col%_%row%.jpg", "samples/firstfloor.jpg");
		
		tileView.setMarkerAnchorPoints(-0.5f, -0.5f); // center markers along both axes
		tileView.setScale(0);	// 초기 화면 스케일 설정
		tileView.setScaleLimits(0, 2);	// 최대 줌인 크기 설정
		tileView.setTransitionsEnabled( false );
		
		// 좌표 값 임의 설정 
		// 여백 계산 후 더하기
		//   20              상하 좌우 여백
		//4       5
		//   20             94x32
		//tileView.defineRelativeBounds(1, 1, 94  + 3.5 + 8, 32 + 20 + 20); // 상하좌우 max
		tileView.defineRelativeBounds(1, 1, 99, 32 + 17 + 17);
		
		mSensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
		sSensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
		
		firstfloor = new firstfloor();
		//points = new ArrayList<double[]>();
		remarker = new ArrayList<ImageView>();
		
		
		//frameTo(0.5, 0.5);
		// xy 한칸씩 빗나가는듯 애드핀 할때 1칸 씩 보정 해 주기
		// 94 x 32 
		// 47, 44가 정확한 elevator 찍히는 좌표
		// 48, 45
		//14.11.05 - y = 20.5               x = 3.5
		pos = new CurrentPOS();
		loadToDataBase();
		//drawPath(pos.Y, pos.X, 21, 90);
		//pos.setX(4);
		//pos.setY(18);
		//addPin(pos.getX(), pos.getY());
		initWIFIScan();
		//addPin(70, 22);
		setContentView(tileView);
		Log.d(TAG, "Start Wifi Scan");
		
		// start WIFIScan
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////         wifi scan을 위한 함수                                                                                                                                             ///////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 *  Wifi가 Scan 됐을때 BroadCastReceiver
	 */
	private BroadcastReceiver mReceiver = new BroadcastReceiver() 
	{
		@Override
		public void onReceive(Context context, Intent intent) 
		{
			final String action = intent.getAction();
			if (action.equals(WifiManager.SCAN_RESULTS_AVAILABLE_ACTION))
			{
				getWIFIScanResult(); // get WIFISCanResult
				wifimanager.startScan(); // for refresh 재스캔
			} 
			else if (action.equals(WifiManager.NETWORK_STATE_CHANGED_ACTION))
			{
				sendBroadcast(new Intent("wifi.ON_NETWORK_STATE_CHANGED"));
			}
		}
	};
	
	/**
	 * 
	 */
	public void getWIFIScanResult() 
	{
		funccount++;
		//unregisterReceiver(mReceiver); // stop WIFISCan
		// DBforAPP, ListDBforAPP
		mScanResult = wifimanager.getScanResults(); // ScanResult
		
		String textStatus;
	/*	int temp = 0;
		int temp2= 0;
		for(int i = 0 ; i < mScanResult.size(); i++)
		{
			result1 = mScanResult.get(i);
			if(i == 0)
			{
				temp = result1.level;
				temp2 = i;
				Log.i("", ""+temp+", "+i);
			}
			if(temp < result1.level)
			{
				temp = result1.level;
				temp2 = i;
				Log.i("", ""+temp+", "+i);
			}
		}
		Log.i("TileView", mScanResult.get(temp2).SSID.toString()+", "+mScanResult.get(temp2).level);
		DataBaseforAPP db = new DataBaseforAPP(1, mScanResult.get(temp2).SSID.toString(), mScanResult.get(temp2).BSSID, mScanResult.get(temp2).level, 0, 0);
		searchhash(db);*/
		
		for (int i = 0; i < mScanResult.size(); i++) 
		{
			
			result1 = mScanResult.get(i);
			//textStatus = ((i + 1) + ". SSID : " + result1.SSID.toString() + "\t\t RSSI : " + result1.level + " dBm, MAC : "+ result1.BSSID + "\n");
			DataBaseforAPP db = new DataBaseforAPP(i + 1, result1.SSID.toString(), result1.BSSID, result1.level, 0, 0);
			///////////////////////////////////////////		
	        // HashMap에 포함된 key, value 값을 호출 한다. 
			///////////////////////////////////////////
			// 여기에서 현재 측정된 Result를 이용하여 
			// Result Wifi 하나와 똑같은 Database를 모조리 검사 하며 각각의 Distance를 검사한다
			// 똑같은 이름을 가진 DB들과 Distance를 유클리드 거리법으로 계산후 리스트에 담는다
			//Log.i("", db.getCOUNTING());
			//Log.i(TAG,db.dbrssi+", "+db.getDistance()+", "+db.getCOUNTING()+", "+db.getNAME()+", rss: "+db.getRSSI()+", x:"+db.getX()+", y: "+db.getY());
			searchhash(db);
			//Log.e(TAG, db.getCOUNTING()+", "+db.getRSSI());
		}
		
		/*Log.i("", "--------------------------");
		for(int i = 0 ; i < ListTemp.size() ; i ++)
		{
			Log.i(TAG,ListTemp.get(i).getDistance()+", "+ListTemp.get(i).getCOUNTING()+", "+ListTemp.get(i).getNAME()+", rsss: "+ListTemp.get(i).dbrssi+", rss: "+ListTemp.get(i).getRSSI()+", x:"+ListTemp.get(i).getX()+", y: "+ListTemp.get(i).getY());
		}*/
		
		int minmax = 0;
		DataBaseforAPP temp1 = null;
		LinkedList<DataBaseforAPP> aaa = new LinkedList<DataBaseforAPP>();
		for(int i = 0 ; i < ListTemp.size() ; i ++)
		{
			//Log.e("", i+", "+(int)ListDBforAPP.get(i).getDistance());
			if(i == 0)
			{
				minmax = (int)ListTemp.get(i).getDistance();
				temp1 = ListTemp.get(i);
				//Log.e("", i+", "+(int)ListDBforAPP.get(i).getDistance());
			}
			if(minmax > (int)ListTemp.get(i).getDistance())
			{
				minmax = (int)ListTemp.get(i).getDistance();
				temp1 = ListTemp.get(i);
				//Log.i("", i+", "+(int)ListDBforAPP.get(i).getDistance());
				//Log.e("", ""+minmax);
			}
		}
		for(int i = 0 ; i < ListTemp.size(); i ++)
		{
			if(minmax == (int)ListTemp.get(i).getDistance())
			{
				aaa.add(ListTemp.get(i));
			}
		}
		//Log.e("", ""+aaa.size());
		int x = 0;
		int y = 0;
		if(aaa.size() > 1)
		{
			for(int i = 0 ; i < aaa.size() ; i ++)
			{
				x = x + aaa.get(i).getX();
				y = y + aaa.get(i).getY();
				//Log.e("", aaa.get(i).getX()+", "+aaa.get(i).getY()+", "+x / aaa.size()+", "+y / aaa.size());
				
			}
			x = x / aaa.size();
			y = y / aaa.size();
			
			temp1.setX(x);
			temp1.setY(y);
		}
		//Log.e("", ""+minmax);
		Log.d(TAG, "====================="+temp1.getX()+", "+temp1.getY()+", Total CMP count : "+funccount);
		pos.setX(temp1.getX());
		pos.setY(temp1.getY());
		//drawPath(temp.getY(), temp.getX(), pos.getX(), pos.getY());
		removePin();
		addPin(temp1.getX(), temp1.getY());
		//drawPath(pos.Y, pos.X, 21, 90);
		//addPin(pos.X, pos.Y);
		
		int i[] = {Pathfinder.generate(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[0][1], firstfloor.RoomCoordinate[0][0], firstfloor.getMap()).size(),
				   Pathfinder.generate(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[1][1], firstfloor.RoomCoordinate[1][0], firstfloor.getMap()).size(),
				   Pathfinder.generate(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[2][1], firstfloor.RoomCoordinate[2][0], firstfloor.getMap()).size(),
				   Pathfinder.generate(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[3][1], firstfloor.RoomCoordinate[3][0], firstfloor.getMap()).size()};

		if(min(i) == i[0])
		{
			SecondDrawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[0][1], firstfloor.RoomCoordinate[0][0]);
			Log.d(TAG, ""+min(i));
		}
		else if (min(i) == i[1])
		{
			SecondDrawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[1][1], firstfloor.RoomCoordinate[1][0]);
			Log.d(TAG, ""+min(i));
		}
		else if (min(i) == i[2])
		{
			SecondDrawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[2][1], firstfloor.RoomCoordinate[2][0]);
			Log.d(TAG, ""+min(i));
		}
		else if (min(i) == i[3])
		{
			SecondDrawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[3][1], firstfloor.RoomCoordinate[3][0]);
			Log.d(TAG, ""+min(i));
		}
		
		
		if(min2(i) == i[0])
		{
			//SeconddrawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[37][1], firstfloor.RoomCoordinate[37][0]);
			ThirdDrawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[0][1], firstfloor.RoomCoordinate[0][0]);
			Log.d(TAG, ""+min2(i));
		}
		else if (min2(i) == i[1])
		{
			//SeconddrawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[38][1], firstfloor.RoomCoordinate[38][0]);
			ThirdDrawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[1][1], firstfloor.RoomCoordinate[1][0]);
			Log.d(TAG, ""+min2(i));
		}
		else if (min2(i) == i[2])
		{
			//SeconddrawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[39][1], firstfloor.RoomCoordinate[39][0]);
			ThirdDrawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[2][1], firstfloor.RoomCoordinate[2][0]);
			Log.d(TAG, ""+min2(i));
		}
		else if (min2(i) == i[3])
		{
			//SeconddrawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[43][1], firstfloor.RoomCoordinate[43][0]);
			ThirdDrawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[3][1], firstfloor.RoomCoordinate[3][0]);
			Log.d(TAG, ""+min2(i));
		}
		
		//Log.d(TAG, ""+max(i));
		//Log.d(TAG, ""+Pathfinder.generate(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[37][1], firstfloor.RoomCoordinate[37][0], firstfloor.getMap()).size());
		//Log.d(TAG, ""+Pathfinder.generate(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[38][1], firstfloor.RoomCoordinate[38][0], firstfloor.getMap()).size());
		//Log.d(TAG, ""+Pathfinder.generate(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[39][1], firstfloor.RoomCoordinate[39][0], firstfloor.getMap()).size());
		//Log.d(TAG, ""+Pathfinder.generate(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[43][1], firstfloor.RoomCoordinate[43][0], firstfloor.getMap()).size());
		
		if(tempcount < 50)
		{
			tempstring = tempstring+ temp1.getX()+", "+temp1.getY()+", ";
			tempcount++;
		}
		/*if(tempcount%10 == 0)
			tempstring = tempstring + "\n";
		*/
		if(tempcount == 50)
		{
			Log.i("", tempstring);
		}
		ListTemp.clear();
		ListDBforAPP.clear();	
	}
	
	//////////////////////////// MinMax 찾기 함수들
	public int max(int n[]) 
	{
		int max = n[0];
		for (int i = 1; i < n.length; i++)
		{
			if (n[i] > max) max = n[i];
		}
		return max;
	}
	
	public int min(int n[]) 
	{
		int min = n[0];
		for (int i = 1; i < n.length; i++)
		{
			if (n[i] < min) min = n[i];
		}
		return min;
	}
	
	public int min2(int n[]) 
	{
		int min[] = n;
		Arrays.sort(min);
		return min[1];
	}

	
	/**
	 *  ScanResult
	 * @param db
	 */
	public void searchhash(DataBaseforAPP db)
	{
		// 미리 DB에서 HashMap으로 뽑아놓은 정보 초기화
		
		set = map.entrySet();
		it = set.iterator();
		int i = 0;
		while (it.hasNext()) 
		{
			Map.Entry<Integer, DataBaseforAPP> e = (Map.Entry<Integer, DataBaseforAPP>)it.next();
			if(db.getNAME().equals(e.getValue().getNAME()))
			{
				/////////////////////////////////////////////
				// 데이터베이스 해쉬함수에 넣은거 비교하는 곳                               //
				/////////////////////////////////////////////
				if(e.getValue().getRSSI() > -65)
				{
					double Distance = (double) Math.sqrt( Math.pow( ( e.getValue().getRSSI() - db.getRSSI() ), 2.0 ));
					if(Distance < 10)
					{
						//Log.d(TAG,Distance+", "+db.getCOUNTING()+", "+db.getNAME()+", rss: "+db.getRSSI()+", x:"+db.getX()+", y: "+db.getY());
						//DataBaseforAPP temp = new DataBaseforAPP(i + 1, result1.SSID.toString(), result1.BSSID, result1.level, 0, 0);
						DataBaseforAPP temp = new DataBaseforAPP(i, db.getCOUNTING(), db.getNAME(), db.getRSSI(), 0, 0);
						temp.setDistance(Distance);
						temp.setX(e.getValue().getX());
						temp.setY(e.getValue().getY());
						temp.dbrssi = e.getValue().getRSSI();
						//db.dbrssi = e.getValue().getRSSI();
						//temp.dbrssi = i;
						//ListDBforAPP.add(temp);
						ListTemp.add(temp);
						//map1.put(i++, db);
						//Log.d(TAG,Distance+", "+db.getCOUNTING()+", "+db.getNAME()+", rss: "+db.getRSSI6()+", x:"+db.getX()+", y: "+db.getY());
						//Log.i(TAG,db.getDistance()+", "+e.getValue().getCOUNTING()+", "+e.getValue().getNAME()+", rss: "+e.getValue().getRSSI()+", "+e.getValue().getX()+", "+e.getValue().getY());
						//ListDBforAPP.get(ListDBforAPP.size());
						//Log.d(TAG,ListDBforAPP.get(ListDBforAPP.size()).getDistance()+", "+ListDBforAPP.get(ListDBforAPP.size()).getCOUNTING()+", "+ListDBforAPP.get(ListDBforAPP.size()).getNAME()+", rss: "+ListDBforAPP.get(ListDBforAPP.size()).getRSSI()+", x:"+ListDBforAPP.get(ListDBforAPP.size()).getX()+", y: "+ListDBforAPP.get(ListDBforAPP.size()).getY());
						//Log.d(TAG,temp.dbrssi+", "+temp.getDistance()+", "+temp.getCOUNTING()+", "+temp.getNAME()+", rss: "+temp.getRSSI()+", x:"+temp.getX()+", y: "+temp.getY());
					}
				}
				//Log.d(TAG,db.getCOUNTING()+", "+e.getValue().getNAME()+", "+e.getValue().getRSSI());
			}
			
			//Log.e(TAG, db.getCOUNTING()+", "+db.getRSSI()+", "+e.getValue().getCOUNTING()+", "+e.getValue().getRSSI());
		}
	}
	
	/**
	 *  WifiScan 초기화 함수
	 */
	public void initWIFIScan() 
	{
		scanCount = 0;
		final IntentFilter filter = new IntentFilter(WifiManager.SCAN_RESULTS_AVAILABLE_ACTION);
		filter.addAction(WifiManager.NETWORK_STATE_CHANGED_ACTION);
		registerReceiver(mReceiver, filter);
		wifimanager.startScan();
		Log.d(TAG, "initWIFIScan()");
	}
	
	/**
	 *  DataBase 초기화
	 */
	public void loadToDataBase()
	{
       mCursor = null;
       mCursor = mDbOpenHelper.getAllColumns();
       Log.e(TAG, "COUNT = " + mCursor.getCount());

       while (mCursor.moveToNext()) 
       {
    	   DataBaseforAPP db = new DataBaseforAPP(mCursor.getInt(mCursor.getColumnIndex("_id")), 
    			   mCursor.getString(mCursor.getColumnIndex("couting")),
    			   mCursor.getString(mCursor.getColumnIndex("name")),
    			   Double.parseDouble(mCursor.getString(mCursor.getColumnIndex("rssi"))),
    			   Integer.parseInt(mCursor.getString(mCursor.getColumnIndex("x"))),
    			   Integer.parseInt(mCursor.getString(mCursor.getColumnIndex("y"))));
    	   
    	   /*Log.d(TAG,""+ Integer.parseInt(mCursor.getString(mCursor.getColumnIndex("x")))+", "+
    			   Integer.parseInt(mCursor.getString(mCursor.getColumnIndex("y"))));*/
    	   //Log.d(TAG,""+cnt++);
    	   map.put(mCursor.getInt(mCursor.getColumnIndex("_id")), db);
       }
       Log.d(TAG,"HashMap Size : "+ map.size());
       mCursor.close();
	}
	
	@Override
    protected void onDestroy() 
	{
		unregisterReceiver(mReceiver);
        mDbOpenHelper.close();
        super.onDestroy();
    }
	// 32 x 94
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////         핀과 갈 방향을 그려주는 함수들                                                                                                                                             ///////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 * 1차 최소 거리 경로 표시
	 * @param curY
	 * @param curX
	 * @param y
	 * @param x
	 */
	private void SecondDrawPath(int curY, int curX, int y, int x)
	{
		// 마커 들어 있으면 그려져 있는 마커 모조리 지움
		if(remarker.size() > 0)
		{
			for (int j = 0 ; j < remarker.size() ; j++)
			{
				tileView.removeMarker(remarker.get(j));
			}
			remarker.clear();
		}
		
		// 길찾기
		List<Node> ListPathfind = pathfinder.generate(curY, curX, y, x, firstfloor.getMap());
		
		for (int i = 0; i < ListPathfind.size(); i++) 
		{
			pointsD.add(new double[] {(double) ListPathfind.get(i).getY() + 2, (double) ListPathfind.get(i).getX() + 17 });
		}

		for (double[] point : pointsD) 
		{
			marker = new ImageView(this);
			marker.setTag(point);
			marker.setImageResource(R.drawable.ic_point); // 코너 마커
			remarker.add(marker);
		}
		//points.clear();
	}
	
	private void ThirdDrawPath(int curY, int curX, int y, int x)
	{
		/*if(remarker.size() > 0)
		{
			for (int j = 0 ; j < remarker.size() ; j++) {
				
				tileView.removeMarker(remarker.get(j));
				//Log.d("qhdwns", "size : remarker.size() : " + remarker.size());
			}
			//i = 0;
			remarker.clear();
			//Log.d("qhdwns", "size : remarker.size() : " + remarker.size());
		}*/
		List<Node> ListPathfind = pathfinder.generate(curY, curX, y, x, firstfloor.getMap());
		//Toast.makeText(this, ListPathfind.size(), Toast.LENGTH_SHORT).show();

		for (int i = 0; i < ListPathfind.size(); i++) 
		{
			// Log.e("dddd", (double)ListPathfind.get(i).getY() + " " +
			// (double)ListPathfind.get(i).getX());
			pointsD.add(new double[] {(double) ListPathfind.get(i).getY() + 1, (double) ListPathfind.get(i).getX() + 18 });
		}

		int i = 0;
		for (double[] point : pointsD)
		{ // pathfind.getPathArray()
			marker = new ImageView(this);
			marker.setTag(point);
			marker.setImageResource(R.drawable.ic_point4); // 코너 마커
			remarker.add(marker);
			tileView.addMarker(remarker.get(i), point[0], point[1]); // 코너에 마커 넣는거
			i++;
		}
		pointsD.clear();
	}
	
	private void drawPath(int curY, int curX, int y, int x)
	{
		if(remarker.size() > 0)
		{
			for (int j = 0 ; j < remarker.size() ; j++) {
				
				tileView.removeMarker(remarker.get(j));
				//Log.d("qhdwns", "size : remarker.size() : " + remarker.size());
			}
			//i = 0;
			remarker.clear();
			//Log.d("qhdwns", "size : remarker.size() : " + remarker.size());
		}
		List<Node> ListPathfind = pathfinder.generate(curY, curX, y, x, firstfloor.getMap());
		//Toast.makeText(this, ListPathfind.size(), Toast.LENGTH_SHORT).show();
		int j = 0;
		ArrayList<double[]> points = new ArrayList<double[]>();
		{
			for(int i = 0 ; i < ListPathfind.size(); i ++)
			{
				//Log.e("dddd", (double)ListPathfind.get(i).getY() + " " + (double)ListPathfind.get(i).getX());
				points.add(new double[] { (double)ListPathfind.get(i).getY()+ 4, (double)ListPathfind.get(i).getX()+ 17});
				j++;
			}
		}
		int i = 0;
		for (double[] point : points) { // pathfind.getPathArray()
			marker = new ImageView(this);
			marker.setTag(point);
			marker.setImageResource(R.drawable.ic_point); // 코너 마커
			remarker.add(marker);
			tileView.addMarker(remarker.get(i), point[0], point[1]); // 코너에 마커 넣는거
			i++;
		}
		points.clear();
	}
	
	private void addPin(double x ,double y)
	{
		imageView.setImageResource(R.drawable.arrow);
		//tileView.addMarker(imageView, x + 5,  y + 20);
		tileView.addMarker(imageView, x + 1, y  + 17.5);
	}

	private void removePin()
	{
		imageView.setImageResource(R.drawable.arrow);
		tileView.removeMarker(imageView);
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////         방향성 검출을 위한 센서 함수들                                                                                                                                             ///////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	@Override
    protected void onResume()
	{
        super.onResume();
        activityRunning = true;
        // for the system's orientation sensor registered listeners
        mSensorManager.registerListener(this, mSensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION), SensorManager.SENSOR_DELAY_GAME);
        sSensorManager.registerListener(this, sSensorManager.getDefaultSensor(Sensor.TYPE_STEP_DETECTOR), SensorManager.SENSOR_DELAY_UI);
    }
 
    @Override
    protected void onPause()
    {
        super.onPause();
        // to stop the listener and save battery
        mSensorManager.unregisterListener(this);
        activityRunning = false;
    }
	
    @Override
    public void onSensorChanged(SensorEvent event)
    {
    	if (activityRunning) 
    	{
            //Toast.makeText(getApplicationContext(), "Moving", Toast.LENGTH_LONG).show();
        }
        // get the angle around the z-axis rotated
        float degree = Math.round(event.values[0]);
        degree = degree + 260;
        //tvHeading.setText("Heading: " + Float.toString(degree) + " degrees");
 
        // create a rotation animation (reverse turn degree degrees)
        RotateAnimation ra = new RotateAnimation(
                currentDegree, 
                -degree,
                Animation.RELATIVE_TO_SELF, 0.5f, 
                Animation.RELATIVE_TO_SELF,
                0.5f);
 
        // how long the animation will take place
        ra.setDuration(210);
 
        // set the animation after the end of the reservation status
        ra.setFillAfter(true);
 
        // Start the animation
        imageView.startAnimation(ra);
        currentDegree = +degree;
 
    }

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		// TODO Auto-generated method stub
		//not use
	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////         메뉴 설정을 위한 함수들                                                                                                                                                       ///////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
		Log.d(TAG, "onPrepareOptionsMenu()");
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
		if(item.getItemId()==R.id.tilesubmenu)
		{
			Log.d(TAG, "Start Wifi Scan");
			initWIFIScan(); // start WIFIScan
		}
		if(item.getItemId()==R.id.tilesubmenu2)
		{
			Log.d(TAG, "Stop Wifi Scan");
			unregisterReceiver(mReceiver); // stop WIFISCan
		}
		if(item.getItemId()==R.id.tilesubmenu3)
		{

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
		
		if(item.getItemId()==R.id.SimpleMenu)
		{
			//Toast.makeText(this, "기본 메뉴가 터치되었습니다", Toast.LENGTH_SHORT).show();
			Intent i = new Intent(getApplicationContext(), TileViewActivity.class);
			startActivity(i);
			finish();
		}

		if(item.getItemId()==R.id.subMenu_2)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[0][1], firstfloor.RoomCoordinate[0][0]);
		}
		if(item.getItemId()==R.id.subMenu_3)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[1][1], firstfloor.RoomCoordinate[1][0]);
		}
		if(item.getItemId()==R.id.subMenu_4)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[2][1], firstfloor.RoomCoordinate[2][0]);
		}
		if(item.getItemId()==R.id.subMenu_5)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[3][1], firstfloor.RoomCoordinate[3][0]);
		}
		if(item.getItemId()==R.id.subMenu_6)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[4][1], firstfloor.RoomCoordinate[4][0]);
		}
		/*if(item.getItemId()==R.id.subMenu_7)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[5][1], firstfloor.RoomCoordinate[5][0]);
		}
		if(item.getItemId()==R.id.subMenu_8)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[6][1], firstfloor.RoomCoordinate[6][0]);
		}
		if(item.getItemId()==R.id.subMenu_9)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[7][1], firstfloor.RoomCoordinate[7][0]);
		}
		if(item.getItemId()==R.id.subMenu_10)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[8][1], firstfloor.RoomCoordinate[8][0]);
		}
		if(item.getItemId()==R.id.subMenu_11)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[9][1], firstfloor.RoomCoordinate[9][0]);
		}
		if(item.getItemId()==R.id.subMenu_12)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[10][1], firstfloor.RoomCoordinate[10][0]);
		}
		if(item.getItemId()==R.id.subMenu_13)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[11][1], firstfloor.RoomCoordinate[11][0]);
		}
		if(item.getItemId()==R.id.subMenu_14)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[12][1], firstfloor.RoomCoordinate[12][0]);
		}
		if(item.getItemId()==R.id.subMenu_15)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[13][1], firstfloor.RoomCoordinate[13][0]);
		}
		if(item.getItemId()==R.id.subMenu_16)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[14][1], firstfloor.RoomCoordinate[14][0]);
		}
		if(item.getItemId()==R.id.subMenu_17)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[15][1], firstfloor.RoomCoordinate[15][0]);
		}
		if(item.getItemId()==R.id.subMenu_18)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[16][1], firstfloor.RoomCoordinate[16][0]);
		}
		if(item.getItemId()==R.id.subMenu_19)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[17][1], firstfloor.RoomCoordinate[17][0]);
		}
		if(item.getItemId()==R.id.subMenu_20)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[18][1], firstfloor.RoomCoordinate[18][0]);
		}
		if(item.getItemId()==R.id.subMenu_21)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[19][1], firstfloor.RoomCoordinate[19][0]);
		}
		if(item.getItemId()==R.id.subMenu_22)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[20][1], firstfloor.RoomCoordinate[20][0]);
		}
		if(item.getItemId()==R.id.subMenu_23)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[21][1], firstfloor.RoomCoordinate[21][0]);
		}
		if(item.getItemId()==R.id.subMenu_24)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[22][1], firstfloor.RoomCoordinate[22][0]);
		}
		if(item.getItemId()==R.id.subMenu_25)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[23][1], firstfloor.RoomCoordinate[23][0]);
		}
		if(item.getItemId()==R.id.subMenu_26)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[24][1], firstfloor.RoomCoordinate[24][0]);
		}
		if(item.getItemId()==R.id.subMenu_27)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[25][1], firstfloor.RoomCoordinate[25][0]);
		}
		if(item.getItemId()==R.id.subMenu_28)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[26][1], firstfloor.RoomCoordinate[26][0]);
		}
		if(item.getItemId()==R.id.subMenu_29)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[27][1], firstfloor.RoomCoordinate[27][0]);
		}
		if(item.getItemId()==R.id.subMenu_30)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[28][1], firstfloor.RoomCoordinate[28][0]);
		}
		if(item.getItemId()==R.id.subMenu_31)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[29][1], firstfloor.RoomCoordinate[29][0]);
		}
		if(item.getItemId()==R.id.subMenu_32)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[30][1], firstfloor.RoomCoordinate[30][0]);
		}
		if(item.getItemId()==R.id.subMenu_33)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[31][1], firstfloor.RoomCoordinate[31][0]);
		}
		if(item.getItemId()==R.id.subMenu_34)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[32][1], firstfloor.RoomCoordinate[32][0]);
		}
		if(item.getItemId()==R.id.subMenu_35)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[33][1], firstfloor.RoomCoordinate[33][0]);
		}
		if(item.getItemId()==R.id.subMenu_36)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[34][1], firstfloor.RoomCoordinate[34][0]);
		}
		if(item.getItemId()==R.id.subMenu_37)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[35][1], firstfloor.RoomCoordinate[35][0]);
		}
		if(item.getItemId()==R.id.subMenu_38)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[36][1], firstfloor.RoomCoordinate[36][0]);
		}*/
/*		if(item.getItemId()==R.id.subMenu_39) // 전기관 중앙계단 우측계단 좌측계단
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[0][1], firstfloor.RoomCoordinate[0][0]);
		}
		if(item.getItemId()==R.id.subMenu_40)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[1][1], firstfloor.RoomCoordinate[1][0]);
		}
		if(item.getItemId()==R.id.subMenu_41)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[2][1], firstfloor.RoomCoordinate[2][0]);
		}
		if(item.getItemId()==R.id.subMenu_42)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[40][1], firstfloor.RoomCoordinate[40][0]);
		}
		if(item.getItemId()==R.id.subMenu_43)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[41][1], firstfloor.RoomCoordinate[41][0]);
		}
		if(item.getItemId()==R.id.subMenu_44)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[42][1], firstfloor.RoomCoordinate[42][0]);
		}
		if(item.getItemId()==R.id.subMenu_45)
		{
			drawPath(pos.getY(), pos.getX(), firstfloor.RoomCoordinate[3][1], firstfloor.RoomCoordinate[3][0]);
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
