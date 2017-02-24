/**
 * Booting �� ���� ������ ���� ��ε�ĳ��Ʈ ���ù�
 * �ý����� ���õǸ� �ȵ���̵� OS���� ACTION_BOOT_COMPLETED�� BroadCast�ϰ� �̴� 
 * �̰��� �޾Ƽ� Service�� ���������
 */
package background;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;

public class BootReceiver extends BroadcastReceiver{
	
	/**
	 * ���� �޼����� �޾�����
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
