package com.example.capstondesign;

import static com.example.capstondesign.CommonUtilities.SENDER_ID;
import static com.example.capstondesign.CommonUtilities.displayMessage;

import java.io.IOException;
import java.util.List;
import java.util.Locale;

import wifi.WifiScan;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningServiceInfo;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.location.Address;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.os.PowerManager;
import android.util.Log;
import android.view.MenuItem;
import android.widget.Toast;
import background.ListeningService;

import com.example.capstondesign.R;
import com.example.capstondesign.R.drawable;
import com.example.capstondesign.R.string;
import com.google.android.gcm.GCMBaseIntentService;

/**
 * GCM의 의 Service Receiver 클래스
 */
public class GCMIntentService extends GCMBaseIntentService {
	PowerManager.WakeLock mWakeLock;
	private static final String TAG = "GCMIntentService";
	
    public GCMIntentService() {
        super(SENDER_ID);
    }
 
	
    /**
     * Method called on device registered
     * 등록 요청이 들어왔을때
     **/
    @Override
    protected void onRegistered(Context context, String registrationId) {
        Log.i(TAG, "Device registered: regId = " + registrationId);
        displayMessage(context, "Your device registred with GCM");
        Log.d("NAME", MainActivity.name);
        ServerUtilities.register(context, MainActivity.name, MainActivity.email, registrationId);
    }

    /**
     * Method called on device un registred
     * 등록 해제 요청이 들어 왔을때
     * */
    @Override
    protected void onUnregistered(Context context, String registrationId) {
        Log.i(TAG, "Device unregistered");
        displayMessage(context, getString(R.string.gcm_unregistered));
        ServerUtilities.unregister(context, registrationId);
    }

    /**
     * Method called on Receiving a new message
     * 메세지를 수신 받았을때
     * */
    @Override
    protected void onMessage(Context context, Intent intent) {
        Log.i(TAG, "Received message");
        String message = intent.getExtras().getString("price");
        
        if(message.equals("11"))
        {
			/*ComponentName compName = new ComponentName("com.example.capstondesign", "com.example.capstondesign.EmergencyActivitiy"); 
		    Intent qwer = new Intent("android.intent.action.Tile");
		    qwer.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		    qwer.addCategory("android.intent.category.DEFAULT");
		    qwer.setComponent(compName);
		    
		    PowerManager powerManager = (PowerManager)getSystemService(Context.POWER_SERVICE);
		    mWakeLock = powerManager.newWakeLock(PowerManager.FULL_WAKE_LOCK, "WakeLock!!");
		    mWakeLock.acquire();
		    
		    WakeLocker.acquire(getApplicationContext());
			WakeLocker.release();
	        
		    startActivity(qwer);*/
		    
		    
		    ComponentName compName = new ComponentName("com.example.capstondesign", "com.example.capstondesign.EmergencyActivitiy"); 
		    Intent intent123 = new Intent("android.intent.action.Tile");
		    intent123.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		    intent123.addCategory("android.intent.category.DEFAULT");
		    intent123.setComponent(compName);
		    
		    PowerManager powerManager = (PowerManager)getSystemService(Context.POWER_SERVICE);
		    mWakeLock = powerManager.newWakeLock(PowerManager.FULL_WAKE_LOCK, "WakeLock!!");
		    mWakeLock.acquire();
		    
		    WakeLocker.acquire(getApplicationContext());
		    
		    Intent intent1 = new Intent("wake");
	        sendBroadcast(intent1);
	        
		    startActivity(intent123);
        }
        else
        {
        	displayMessage(context, message);
        	// notifies user
        	generateNotification(context, message);
        }
    }

    /**
     * Method called on receiving a deleted message
     * 
     * */
    @Override
    protected void onDeletedMessages(Context context, int total) {
        Log.i(TAG, "Received deleted messages notification");
        String message = getString(R.string.gcm_deleted, total);
        displayMessage(context, message);
        // notifies user
        generateNotification(context, message);
    }
    
    /**
     * Method called on Error
     * */
    @Override
    public void onError(Context context, String errorId) {
        Log.i(TAG, "Received error: " + errorId);
        displayMessage(context, getString(R.string.gcm_error, errorId));
    }

    @Override
    protected boolean onRecoverableError(Context context, String errorId) {
        // log message
        Log.i(TAG, "Received recoverable error: " + errorId);
        displayMessage(context, getString(R.string.gcm_recoverable_error,
                errorId));
        return super.onRecoverableError(context, errorId);
    }

    /**
     * Issues a notification to inform the user that server has sent a message.
     */
    private static void generateNotification(Context context, String message) {
        int icon = R.drawable.ic_launcher;
        long when = System.currentTimeMillis();
        NotificationManager notificationManager = (NotificationManager)
                context.getSystemService(Context.NOTIFICATION_SERVICE);
        Notification notification = new Notification(icon, message, when);
        
        String title = context.getString(R.string.app_name);
        
        Intent notificationIntent = new Intent(context, MainActivity.class);
        // set intent so it does not start a new activity
        notificationIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP |
                Intent.FLAG_ACTIVITY_SINGLE_TOP);
        PendingIntent intent =
                PendingIntent.getActivity(context, 0, notificationIntent, 0);
        notification.setLatestEventInfo(context, title, message, intent);
        notification.flags |= Notification.FLAG_AUTO_CANCEL;
        
        // Play default notification sound
        notification.defaults |= Notification.DEFAULT_SOUND;
        
        //notification.sound = Uri.parse("android.resource://" + context.getPackageName() + "your_sound_file_name.mp3");
        
        // Vibrate if vibrate is enabled
        notification.defaults |= Notification.DEFAULT_VIBRATE;
        notificationManager.notify(0, notification);      

    }
 }
