package com.arellomobile.pushwoosh;

import android.app.Activity;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;

import java.util.HashMap;
import java.util.Map;

public class PushActivity extends Activity
{
	/**
	 * Called when the activity is first created.
	 */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		//bring the default activity into action
		Intent notifyIntent = new Intent();
		notifyIntent.setAction(Intent.ACTION_MAIN);
		notifyIntent.addCategory(Intent.CATEGORY_LAUNCHER);

        PackageManager manager = this.getPackageManager();
        Intent launchIntent = manager.getLaunchIntentForPackage(this.getPackageName());

		notifyIntent.setComponent(launchIntent.getComponent());
		
		notifyIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_RESET_TASK_IF_NEEDED);
		notifyIntent.putExtras(getIntent().getExtras());
        
		//if we are in background (INSTANCE available) s3ePushWooshNotificationRegister will not be called, therefore force to check for push notifications
    	if(s3ePushWoosh.INSTANCE != null) {
    	 	s3ePushWoosh.INSTANCE.checkMessage(notifyIntent);
    	}

   		this.startActivity(notifyIntent);
		
		finish();
	}
}
