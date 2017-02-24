package wifi;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import static wifi.DbOpenHelper.DATABASE_NAME;;

public class DatabaseHelper extends SQLiteOpenHelper
{
	// ������
	public DatabaseHelper(Context context, String name,CursorFactory factory, int version) 
	{
		super(context, DATABASE_NAME, null, version);
	}

	// ���� DB�� ���鶧 �ѹ��� ȣ��ȴ�	
	@Override
	public void onCreate(SQLiteDatabase db) 
	{
		db.execSQL(DataBases.CreateDB._CREATE);
		db.rawQuery("PRAGMA journal_mode=OFF", null);
	}

	// ������ ������Ʈ �Ǿ��� ��� DB�� �ٽ� ����� �ش�.
	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) 
	{
		db.execSQL("DROP TABLE IF EXISTS "+DataBases.CreateDB._TABLENAME);
		onCreate(db);
	}
}
