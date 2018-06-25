/*
 * iphone-specific implementation of the s3ePushWoosh extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3ePushWoosh_internal.h"
#import "../../Pushwoosh/PushNotificationManager.h"
#include "s3eEdk.h"
#include "s3eEdk_iphone.h"
#include "IwDebug.h"
#include <string>

static std::string g_pushToken;
static std::string g_errorMessage;
static std::string g_pushPayload;

@implementation UIApplication(InternalPushRuntime)

- (NSObject<PushNotificationDelegate> *)getPushwooshDelegate {
	return (NSObject<PushNotificationDelegate> *)[UIApplication sharedApplication];
}

- (BOOL) pushwooshUseRuntimeMagic {
	return YES;
}

//succesfully registered for push notifications
- (void) onDidRegisterForRemoteNotificationsWithDeviceToken:(NSString *)token
{
	g_pushToken = [token UTF8String];
	s3eEdkCallbacksEnqueue(S3E_EXT_PUSHWOOSH_HASH, S3E_PUSHWOOSH_REGISTRATION_SUCCEEDED, (char *)g_pushToken.c_str());
}

//failed to register for push notifications
- (void) onDidFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
	g_errorMessage = [[error description] UTF8String];
	s3eEdkCallbacksEnqueue(S3E_EXT_PUSHWOOSH_HASH, S3E_PUSHWOOSH_REGISTRATION_ERROR, (char *)g_errorMessage.c_str());
}

//handle push notification, display alert, if this method is implemented onPushAccepted will not be called, internal message boxes will not be displayed
- (void) onPushAccepted:(PushNotificationManager *)pushManager withNotification:(NSDictionary *)pushNotification onStart:(BOOL)onStart
{
	NSMutableDictionary *pushNotificationMutable = [pushNotification mutableCopy];
	[pushNotificationMutable setObject:[NSNumber numberWithBool:onStart] forKey:@"onStart"];
	
	NSData *jsonData = [NSJSONSerialization dataWithJSONObject:pushNotificationMutable options:0 error:nil];
	NSString *jsonRequestData = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];

	NSLog(@"PushNotification payload: %@", jsonRequestData);
	
	g_pushPayload = [jsonRequestData UTF8String];
	s3eEdkCallbacksEnqueue(S3E_EXT_PUSHWOOSH_HASH, S3E_PUSHWOOSH_MESSAGE_RECEIVED, (char *)g_pushPayload.c_str());
}

@end

s3eResult s3ePushWooshInit_platform()
{
	IwTrace(Device, ("Pushwoosh InitPlatform"));

	[PushNotificationManager pushManager].delegate = (NSObject<PushNotificationDelegate> *)[UIApplication sharedApplication];
	[[PushNotificationManager pushManager] sendAppOpen];

	return S3E_RESULT_SUCCESS;
}

void s3ePushWooshTerminate_platform()
{
	// Add any platform-specific termination code here
}

s3eBool s3ePushWooshNotificationsAvailable_platform()
{
	IwTrace(Device, ("Pushwoosh Available platform"));
	return S3E_TRUE;
}

s3eResult s3ePushWooshNotificationRegister_platform()
{
	IwTrace(Device, ("Pushwoosh Register platform"));
	[[PushNotificationManager pushManager] registerForPushNotifications];

	//check for notifications on startup
	if(!g_pushPayload.empty())
	{
		s3eEdkCallbacksEnqueue(S3E_EXT_PUSHWOOSH_HASH, S3E_PUSHWOOSH_MESSAGE_RECEIVED, (char *)g_pushPayload.c_str());
	}
	
	return S3E_RESULT_SUCCESS;
}

// on iOS Pushwoosh App Id comes from Info.plist
s3eResult s3ePushWooshNotificationRegisterWithPWAppID_platform(const char * pushwooshAppId)
{
	return s3ePushWooshNotificationRegister_platform();
}

char * s3ePushWooshGetToken_platform()
{
	IwTrace(Device, ("Pushwoosh GetToken"));

	return (char *)[[[PushNotificationManager pushManager] getPushToken] UTF8String];
}

s3eResult s3ePushWooshNotificationUnRegister_platform()
{
	[[PushNotificationManager pushManager] unregisterForPushNotifications];
	return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshStartLocationTracking_platform()
{
	[[PushNotificationManager pushManager] startLocationTracking];
	return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshStopLocationTracking_platform()
{
	[[PushNotificationManager pushManager] stopLocationTracking];
	return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshNotificationSetBadgeNumber_platform(int badgeValue) {
	[UIApplication sharedApplication].applicationIconBadgeNumber = badgeValue;
	return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshNotificationSetIntTag_platform(const char * tagName, int tagValue)
{
	NSString *tagNameStr = [[NSString alloc] initWithUTF8String:tagName];
	NSDictionary * dict = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithInt:tagValue], tagNameStr, nil];
	[[PushNotificationManager pushManager] setTags:dict];

	return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshNotificationSetStringTag_platform(const char * tagName, const char * tagValue)
{
	NSString *tagNameStr = [[NSString alloc] initWithUTF8String:tagName];
	NSString *tagValueStr = [[NSString alloc] initWithUTF8String:tagValue];
	
	NSDictionary *dict = [NSDictionary dictionaryWithObjectsAndKeys:tagValueStr, tagNameStr, nil];
	[[PushNotificationManager pushManager] setTags:dict];

	return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshClearLocalNotifications_platform()
{
	return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshScheduleLocalNotification_platform(const char * message, int seconds, const char * userdata)
{
	NSLog(@"s3ePushWooshScheduleLocalNotification_platform: %@, %d", @(message), seconds);

	UILocalNotification* notification = [[UILocalNotification alloc] init];
	notification.fireDate = [NSDate dateWithTimeIntervalSinceNow: seconds];
	notification.alertBody = @(message);
	notification.soundName = UILocalNotificationDefaultSoundName;

	[[UIApplication sharedApplication] scheduleLocalNotification:notification];

	return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshSetAndroidNotificationMultiMode_platform(bool enable)
{
	return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshSetUserId_platform(const char * userId)
{
	NSString *userIdStr = [[NSString alloc] initWithUTF8String:userId];

	[[PushNotificationManager pushManager] setUserId:userIdStr];
}

s3eResult s3ePushWooshPostEvent_platform(const char * event, const char * attributes)
{
	NSString *eventStr = [[NSString alloc] initWithUTF8String:event];
	NSString *attributesStr = [[NSString alloc] initWithUTF8String:attributes];

	NSDictionary *json = [NSJSONSerialization JSONObjectWithData:[attributesStr dataUsingEncoding:NSUTF8StringEncoding] options:0 error:nil];
	if ([json isKindOfClass:[NSDictionary class]]) {
		[[PushNotificationManager pushManager] postEvent:eventStr withAttributes:json];
	}
	else {
		NSLog(@"Invalid postEvent attribute argument: %@", json);
		return S3E_RESULT_ERROR;
	}

	return S3E_RESULT_SUCCESS;
}
