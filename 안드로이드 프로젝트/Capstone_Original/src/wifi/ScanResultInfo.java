package wifi;

import java.text.DecimalFormat;

public class ScanResultInfo
{
	public ScanResultInfo(String Name, String bs, int RSSi, int Counting, int X, int Y)
	{
		name = Name;
		BSSID = bs;
		RSSI = RSSi;
		counting = Counting;
		x = X;
		y = Y;
	}
	String name;
	String BSSID;
	int RSSI;
	int counting;
	int x;
	int y;
	double returnd;
	double getRSSI()
	{ 
		double a = RSSI;
		double b = counting;
		DecimalFormat format = new DecimalFormat("##.###");
		returnd = Double.parseDouble(format.format(a/b));
		return returnd;
	}
}