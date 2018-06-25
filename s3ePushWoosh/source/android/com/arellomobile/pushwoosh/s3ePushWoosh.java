/*
java implementation of the s3ePushWoosh extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
package com.arellomobile.pushwoosh;

import com.ideaworks3d.marmalade.LoaderAPI;
import com.ideaworks3d.marmalade.LoaderActivitySlave;

import com.ideaworks3d.marmalade.*;

import com.pushwoosh.PushManager;
import com.pushwoosh.BasePushMessageReceiver;
import com.pushwoosh.BaseRegistrationReceiver;
import com.pushwoosh.internal.utils.JsonUtils;
import com.pushwoosh.inapp.InAppFacade;
import com.pushwoosh.internal.utils.PWLog;

import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.app.Activity;

import android.widget.Toast;
import android.os.Bundle;
import java.util.HashMap;
import java.util.Map;

import org.json.JSONException;
import org.json.JSONObject;

class s3ePushWoosh extends LoaderActivitySlave
{
	private final static String TAG = "s3ePushWoosh";

	@Override
	protected void onPause()
	{
		unregisterReceivers();
	} 

	@Override
	protected void onResume()
	{
		registerReceivers();
	}
	public static s3ePushWoosh INSTANCE = null;
	boolean broadcastPush = true;

	PushManager pushManager = null;

	public s3ePushWoosh()
	{
		INSTANCE = this;
	}

	public boolean s3ePushWooshNotificationsAvailable()
	{
		return true;
	}
	public int s3ePushWooshNotificationRegister()
	{
		registerReceivers();
		
		ApplicationInfo ai = null;
		try {
			ai = LoaderActivity.m_Activity.getPackageManager().getApplicationInfo(LoaderActivity.m_Activity.getApplicationContext().getPackageName(), PackageManager.GET_META_DATA);
			
			broadcastPush = ai.metaData.getBoolean("PW_BROADCAST_PUSH", true);

			pushManager = PushManager.getInstance(LoaderActivity.m_Activity);
			pushManager.onStartup(LoaderActivity.m_Activity);
			pushManager.registerForPushNotifications();
		} catch (Exception e) {
			PWLog.exception(e);
		}

		checkMessage(LoaderActivity.m_Activity.getIntent());
		return 0;
	}
	public String s3ePushWooshGetToken()
	{
		return PushManager.getPushToken(LoaderActivity.m_Activity);
	}
	public int s3ePushWooshNotificationSetIntTag(String tagName, int tagValue)
	{
		Map<String, Object> tags = new HashMap<String, Object>();
		tags.put(tagName, new Integer(tagValue));
		
		PushManager.sendTags(LoaderActivity.m_Activity, tags, null);
		return 0;
	}
	public int s3ePushWooshNotificationSetStringTag(String tagName, String tagValue)
	{
		Map<String, Object> tags = new HashMap<String, Object>();
		tags.put(tagName, tagValue);
		
		PushManager.sendTags(LoaderActivity.m_Activity, tags, null);
		return 0;
	}
	public int s3ePushWooshNotificationUnRegister()
	{
		pushManager.unregisterForPushNotifications();
		return 0;
	}
	
	public int s3ePushWooshClearLocalNotifications()
	{
		PushManager.clearLocalNotifications(LoaderActivity.m_Activity);
		return 0;
	}
	public int s3ePushWooshScheduleLocalNotification(String message, int seconds, String userdata)
	{
		Bundle extras = new Bundle();
		if(userdata != null)
			extras.putString("u", userdata);
		
		PushManager.scheduleLocalNotification(LoaderActivity.m_Activity, message, extras, seconds);
		return 0;
	}

	public int s3ePushWooshSetAndroidNotificationMultiMode(int enable)
	{
		if(enable != 0)
			PushManager.setMultiNotificationMode(LoaderActivity.m_Activity);
		else
			PushManager.setSimpleNotificationMode(LoaderActivity.m_Activity);

		return 0;
	}

	public int s3ePushWooshStartLocationTracking()
	{
		PushManager.startTrackingGeoPushes(LoaderActivity.m_Activity);
		return 0;
	}

	public int s3ePushWooshStopLocationTracking()
	{
		PushManager.stopTrackingGeoPushes(LoaderActivity.m_Activity);
		return 0;
	}

	public int s3ePushWooshSetUserId(String userId)
	{
		pushManager.setUserId(LoaderActivity.m_Activity, userId);
		return 0;
	}

	public int s3ePushWooshPostEvent(String event, String attributes)
	{
		try
		{
			JSONObject json = new JSONObject(attributes);
			InAppFacade.postEvent(LoaderActivity.m_Activity, event, JsonUtils.jsonToMap(json));
		}
		catch (JSONException e)
		{
			PWLog.error(TAG, "Invalid attributes format", e);
			return 1;
		}

		return 0;
	}

	public void checkMessage(Intent intent)
	{
		if (null != intent)
		{
			if (intent.hasExtra(PushManager.PUSH_RECEIVE_EVENT))
			{
				//showMessage("push message is " + intent.getExtras().getString(PushManager.PUSH_RECEIVE_EVENT));
				onPushReceived(intent.getExtras().getString(PushManager.PUSH_RECEIVE_EVENT), "");
			}
			else if (intent.hasExtra(PushManager.REGISTER_EVENT))
			{
				//showMessage("register");
				onNotificationsRegistered(intent.getExtras().getString(PushManager.REGISTER_EVENT));
			}
			else if (intent.hasExtra(PushManager.UNREGISTER_EVENT))
			{
				//showMessage("unregister");
			}
			else if (intent.hasExtra(PushManager.REGISTER_ERROR_EVENT))
			{
				//showMessage("register error");
				onNotificationsRegisterError(intent.getExtras().getString(PushManager.REGISTER_ERROR_EVENT));
			}
			else if (intent.hasExtra(PushManager.UNREGISTER_ERROR_EVENT))
			{
				//showMessage("unregister error");
			}
		}
	}

	private void showMessage(final String message)
	{
		LoaderActivity.m_Activity.runOnUiThread(new Runnable() {
			public void run() {
				Toast.makeText(LoaderActivity.m_Activity, message, Toast.LENGTH_LONG).show();
			}
		});
	}
	
	public void registerReceivers()
	{
		unregisterReceivers();
		
		IntentFilter intentFilter = new IntentFilter(LoaderActivity.m_Activity.getPackageName() + ".action.PUSH_MESSAGE_RECEIVE");

		if(broadcastPush)
			LoaderActivity.m_Activity.registerReceiver(mReceiver, intentFilter);
		
		LoaderActivity.m_Activity.registerReceiver(mBroadcastReceiver, new IntentFilter(LoaderActivity.m_Activity.getPackageName() + "." + PushManager.REGISTER_BROAD_CAST_ACTION));		
	}
	
	public void unregisterReceivers()
	{
		try
		{
			LoaderActivity.m_Activity.unregisterReceiver(mReceiver);
		}
		catch (Exception e)
		{
			// pass.
		}
		
		try
		{
			LoaderActivity.m_Activity.unregisterReceiver(mBroadcastReceiver);
		}
		catch (Exception e)
		{
			//pass through
		}
	}
	
	private BroadcastReceiver mReceiver = new BasePushMessageReceiver()
	{
		@Override
		protected void onMessageReceive(Intent intent)
		{
			onPushReceived(intent.getStringExtra(JSON_DATA_KEY), "");
		}
	};
	
	BroadcastReceiver mBroadcastReceiver = new BaseRegistrationReceiver()
	{
		@Override
		public void onRegisterActionReceive(Context context, Intent intent)
		{
			checkMessage(intent);
		}
	};

	private static native void onNotificationsRegistered(String token);
	private static native void onNotificationsRegisterError(String message);
	private static native void onPushReceived(String text, String customData);
}
