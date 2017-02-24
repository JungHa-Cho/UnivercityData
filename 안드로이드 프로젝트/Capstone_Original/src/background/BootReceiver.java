/**
 * Booting 시 서비스 실행을 이한 브로드캐스트 리시버
 * 시스템이 부팅되면 안드로이드 OS에서 ACTION_BOOT_COMPLETED를 BroadCast하고 이는 
 * 이것을 받아서 Service를 실행시켜줌
 */
package background;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;

public class BootReceiver extends BroadcastReceiver{
	
	/**
	 * 부팅 메세지를 받았을때
	 * (non-Javadoc)
	 * @param Context, intent
	 * @see android.content.BroadcastReceiver#onReceive(android.content.Context, android.content.Intent)
	 */
	@Override
	public void onReceive(Context context, Intent intent) {
		// TODO Auto-generated method stub
		if(intent.getAction().equals(intent.ACTION_BOOT_COMPLETED))
		{
			SharedPreferences prefs = context.getSharedPreferences( "Variable" , android.content.Context.MODE_PRIVATE);
			if(prefs.getBoolean("ServiceCheck", true))
			{
				Intent i = new Intent(context, ListeningService.class);
				context.startService(i);
			}
		}
	}
}
