package wifi;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;

public class DbOpenHelper {
	public static final String DATABASE_NAME = "/mnt/sdcard/database/firstfloor.db3";
	private static final int DATABASE_VERSION = 1;
	public static SQLiteDatabase mDB;
	private DatabaseHelper mDBHelper;
	private Context mCtx;



	public DbOpenHelper(Context context)
	{
		this.mCtx = context;
	}

	public DbOpenHelper open() throws SQLException
	{
		mDBHelper = new DatabaseHelper(mCtx, DATABASE_NAME, null, DATABASE_VERSION);
		mDB = mDBHelper.getWritableDatabase();
		return this;
	}

	public void close()
	{
		mDB.close();
	}

	
	// Insert DB
	public long insertColumn(String counting, String name, String rssi, String x, String y, String count)
	{
		ContentValues values = new ContentValues();
		values.put(DataBases.CreateDB.COUNTING, counting);
		values.put(DataBases.CreateDB.NAME, name);
		values.put(DataBases.CreateDB.RSSI, rssi);
		values.put(DataBases.CreateDB.X, x);
		values.put(DataBases.CreateDB.Y, y);
		values.put(DataBases.CreateDB.COUNT, count);
		return mDB.insert(DataBases.CreateDB._TABLENAME, null, values);
	}

	// Update DB
	public boolean updateColumn(long id, String counting, String name, String rssi, String x, String y)
	{
		ContentValues values = new ContentValues();
		values.put(DataBases.CreateDB.COUNTING, counting);
		values.put(DataBases.CreateDB.NAME, name);
		values.put(DataBases.CreateDB.RSSI, rssi);
		values.put(DataBases.CreateDB.X, x);
		values.put(DataBases.CreateDB.Y, y);
		return mDB.update(DataBases.CreateDB._TABLENAME, values, "_id="+id, null) > 0;
	}

	// Delete ID
	public boolean deleteColumn(long id)
	{
		return mDB.delete(DataBases.CreateDB._TABLENAME, "_id="+id, null) > 0;
	}
	
	// Delete Contact
	public boolean deleteColumn(String number)
	{
		return mDB.delete(DataBases.CreateDB._TABLENAME, "contact="+number, null) > 0;
	}
	
	// Select All
	public Cursor getAllColumns()
	{
		return mDB.query(DataBases.CreateDB._TABLENAME, null, null, null, null, null, null, null);
	}

	// ID 컬럼 얻어 오기
	public Cursor getColumn(long id)
	{
		Cursor c = mDB.query(DataBases.CreateDB._TABLENAME, null, 
				"_id="+id, null, null, null, null);
		if(c != null && c.getCount() != 0)
			c.moveToFirst();
		return c;
	}

/*	// 이름 검색 하기 (rawQuery)
	public Cursor getMatchName(String name){
		Cursor c = mDB.rawQuery( "select * from address where name=" + "'" + name + "'" , null);
		return c;
	}*/
	
	public Cursor getCulumnCnt()
	{
		return getAllColumns();
	}


}






