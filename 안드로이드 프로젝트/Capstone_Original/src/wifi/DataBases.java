package wifi;

import android.provider.BaseColumns;

// DataBase Table
public final class DataBases 
{
	public static final class CreateDB implements BaseColumns
	{
		public static final String COUNTING = "couting";
		public static final String NAME = "name";
		public static final String RSSI = "rssi";
		public static final String X = "x";
		public static final String Y = "y";
		public static final String _TABLENAME = "floor";
		public static final String COUNT = "count";
		public static final String _CREATE = 
			"create table "+_TABLENAME+"(" 
					+_ID+" integer primary key autoincrement , " 
					+COUNTING+" text not null , "
					+NAME+" text not null , " 
					+RSSI+" text not null , " 
					+X+" text not null , " 
					+Y+" text not null , " 
					+COUNT+" text not null);";
	}
}
