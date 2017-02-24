package wifi;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import static wifi.DbOpenHelper.DATABASE_NAME;;

public class DatabaseHelper extends SQLiteOpenHelper
{
	// 생성자
	public DatabaseHelper(Context context, String name,CursorFactory factory, int version) 
	{
		super(context, DATABASE_NAME, null, version);
	}

	// 최초 DB를 만들때 한번만 호출된다	
	@Override
	public void onCreate(SQLiteDatabase db) 
	{
		db.execSQL(DataBases.CreateDB._CREATE);
		db.rawQuery("PRAGMA journal_mode=OFF", null);
	}

	// 버전이 업데이트 되었을 경우 DB를 다시 만들어 준다.
	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) 
	{
		db.execSQL("DROP TABLE IF EXISTS "+DataBases.CreateDB._TABLENAME);
		onCreate(db);
	}
}
