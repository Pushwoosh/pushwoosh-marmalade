/*
 * Internal header for the s3ePushWoosh extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef S3EPUSHWOOSH_INTERNAL_H
#define S3EPUSHWOOSH_INTERNAL_H

#include "s3eTypes.h"
#include "s3ePushWoosh.h"
#include "s3ePushWoosh_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult s3ePushWooshInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult s3ePushWooshInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void s3ePushWooshTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void s3ePushWooshTerminate_platform();
s3eBool s3ePushWooshNotificationsAvailable_platform();

s3eResult s3ePushWooshNotificationRegister_platform();

s3eResult s3ePushWooshNotificationRegisterWithPWAppID_platform(const char * pushwooshAppId);

char * s3ePushWooshGetToken_platform();

s3eResult s3ePushWooshNotificationUnRegister_platform();

s3eResult s3ePushWooshNotificationSetIntTag_platform(const char * tagName, int tagValue);

s3eResult s3ePushWooshNotificationSetStringTag_platform(const char * tagName, const char * tagValue);

s3eResult s3ePushWooshClearLocalNotifications_platform();

s3eResult s3ePushWooshScheduleLocalNotification_platform(const char * message, int seconds, const char * userdata);

s3eResult s3ePushWooshSetAndroidNotificationMultiMode_platform(bool enable);

s3eResult s3ePushWooshStartLocationTracking_platform();

s3eResult s3ePushWooshStopLocationTracking_platform();

s3eResult s3ePushWooshNotificationSetBadgeNumber_platform(int badgeNumber);

s3eResult s3ePushWooshSetUserId_platform(const char * userId);

s3eResult s3ePushWooshPostEvent_platform(const char * event, const char * attributes);

#endif /* !S3EPUSHWOOSH_INTERNAL_H */