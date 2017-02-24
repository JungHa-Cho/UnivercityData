/**
 * 리스타트 리시버
 * 서비스가 죽었을때 다시 서비스를 실행
 */

package background;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.widget.Toast;

public class RestartReceiver extends BroadcastReceiver{
	
	static public final String ACTION_RESTART_SERVICE = "RestartReceiver.restart";

	/**
	 * 리스타트 리시버를 받았을때
	 * (non-Javadoc)
	 * @see android.content.BroadcastReceiver#onReceive(android.content.Context, android.content.Intent)
	 */
	@Override
	public void onReceive(Context context, Intent intent) {
		// TODO Auto-generated method stub
		if(intent.getAction().equals(ACTION_RESTART_SERVICE))
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
