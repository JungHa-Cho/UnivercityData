/**
 * ����ŸƮ ���ù�
 * ���񽺰� �׾����� �ٽ� ���񽺸� ����
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
	 * ����ŸƮ ���ù��� �޾�����
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
