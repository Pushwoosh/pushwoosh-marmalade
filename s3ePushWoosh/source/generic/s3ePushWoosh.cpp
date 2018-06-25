/*
Generic implementation of the s3ePushWoosh extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "s3ePushWoosh_internal.h"
s3eResult s3ePushWooshInit()
{
    //Add any generic initialisation code here
    return s3ePushWooshInit_platform();
}

void s3ePushWooshTerminate()
{
    //Add any generic termination code here
    s3ePushWooshTerminate_platform();
}

s3eBool s3ePushWooshNotificationsAvailable()
{
	return s3ePushWooshNotificationsAvailable_platform();
}

s3eResult s3ePushWooshNotificationRegister()
{
	return s3ePushWooshNotificationRegister_platform();
}

s3eResult s3ePushWooshNotificationRegisterWithPWAppID(const char * pushwooshAppId)
{
	return s3ePushWooshNotificationRegisterWithPWAppID_platform(pushwooshAppId);
}

char * s3ePushWooshGetToken()
{
	return s3ePushWooshGetToken_platform();
}

s3eResult s3ePushWooshNotificationUnRegister()
{
	return s3ePushWooshNotificationUnRegister_platform();
}

s3eResult s3ePushWooshNotificationSetIntTag(const char * tagName, int tagValue)
{
	return s3ePushWooshNotificationSetIntTag_platform(tagName, tagValue);
}

s3eResult s3ePushWooshNotificationSetStringTag(const char * tagName, const char * tagValue)
{
	return s3ePushWooshNotificationSetStringTag_platform(tagName, tagValue);
}

s3eResult s3ePushWooshClearLocalNotifications()
{
	return s3ePushWooshClearLocalNotifications_platform();
}

s3eResult s3ePushWooshStartLocationTracking()
{
	return s3ePushWooshStartLocationTracking_platform();
}

s3eResult s3ePushWooshStopLocationTracking()
{
	return s3ePushWooshStopLocationTracking_platform();
}


s3eResult s3ePushWooshScheduleLocalNotification(const char * message, int seconds, const char * userdata)
{
	return s3ePushWooshScheduleLocalNotification_platform(message, seconds, userdata);
}

s3eResult s3ePushWooshSetAndroidNotificationMultiMode(bool enable)
{
	return s3ePushWooshSetAndroidNotificationMultiMode_platform(enable);
}

s3eResult s3ePushWooshNotificationSetBadgeNumber(int badgeValue) {
    return s3ePushWooshNotificationSetBadgeNumber_platform(badgeValue);
}

s3eResult s3ePushWooshSetUserId(const char * userId)
{
	return s3ePushWooshSetUserId_platform(userId);
}

s3eResult s3ePushWooshPostEvent(const char * event, const char * attributes)
{
	if (!attributes) {
		attributes = "{}";
	}

	return s3ePushWooshPostEvent_platform(event, attributes);
}
