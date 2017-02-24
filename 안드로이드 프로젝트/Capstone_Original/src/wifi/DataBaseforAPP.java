package wifi;

public class DataBaseforAPP 
{
	private int ID;
	private String COUNTING;
	private String NAME;
	private double RSSI;
	private int X; 
	private int Y;
	public double dbrssi;
	
	private double distance;
	
	public DataBaseforAPP(int id, String counting, String bssid, double rssi, int x, int y)
	{
		ID = id;
		COUNTING = counting;
		NAME = bssid;
		RSSI = rssi;
		X = x;
		Y = y;
		distance = 0;
		dbrssi = 0;
	}
	
	public int getID(){return ID;}
	public void setID(int id){ID = id;}
	
	public String getCOUNTING(){return COUNTING;}
	public void setCOUNTING(String counting){COUNTING = counting;}
	
	public String getNAME(){return NAME;}
	public void setNAME(String name){NAME = name;}
	
	public double getRSSI(){return RSSI;}
	public void setRSSI(double rssi){RSSI = rssi;}
	
	public int getX(){return X;}
	public void setX(int x){X = x;}
	
	public int getY(){return Y;}
	public void setY(int y){Y = y;}
	
	public double getDistance(){return distance;}
	public void setDistance(double distance1){distance = distance1;}
}
