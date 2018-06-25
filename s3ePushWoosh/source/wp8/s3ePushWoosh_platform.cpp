/*
 * wp8-specific implementation of the s3ePushWoosh extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include <crtdbg.h>

#define _CRT_PERROR_DEFINED
#include <wrl/client.h>
#include <wrl/module.h>
#undef _CRT_PERROR_DEFINED

#include "s3ePushWoosh_internal.h"

#include "s3ePushWoosh_shim.h"
#include "IwDebug.h"

using namespace s3ePushWooshExtension;

s3eResult s3ePushWooshInit_platform()
{
    if (s3ePushWooshShim::GetInterface() == nullptr)
    {
        IwTrace(PUSHWOOSH, ("No IManagedS3Es3ePushWooshAPI interface. Managed part of s3ePushWoosh extension failed to register."));
        return S3E_RESULT_ERROR;
    }

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3ePushWooshTerminate_platform()
{
    // Add any platform-specific termination code here
}

s3eBool s3ePushWooshNotificationsAvailable_platform()
{
    return (s3eBool)s3ePushWooshShim::GetInterface()->s3ePushWooshNotificationsAvailable_managed();
}

// This is a error to call this function on Windows Phone. Call the function with Pushwoosh App Id instead.
s3eResult s3ePushWooshNotificationRegister_platform()
{
    IwTrace(PUSHWOOSH, ("This is a error to call s3ePushWooshNotificationRegister function on Windows Phone. Call the function s3ePushWooshNotificationRegisterWithPWAppID with Pushwoosh App Id instead."));
    return S3E_RESULT_ERROR;
}

s3eResult s3ePushWooshNotificationRegisterWithPWAppID_platform(const char * pushwooshAppId)
{
    Platform::String^ pushwooshAppId_string = UTF8ToString(pushwooshAppId);
    if (!s3ePushWooshShim::GetInterface()->s3ePushWooshNotificationRegisterWithPWAppID_managed(pushwooshAppId_string))
        return S3E_RESULT_ERROR;
    return S3E_RESULT_SUCCESS;
}

char g_nativeToken[4096];

char * s3ePushWooshGetToken_platform()
{
    Platform::String^ token = s3ePushWooshShim::GetInterface()->s3ePushWooshGetToken_managed();

    memset(g_nativeToken, 0, 4096);
    StringToUTF8(g_nativeToken, 4096, token);

    return g_nativeToken;
}

s3eResult s3ePushWooshNotificationUnRegister_platform()
{
    if (!s3ePushWooshShim::GetInterface()->s3ePushWooshNotificationUnRegister_managed())
        return S3E_RESULT_ERROR;
    return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshNotificationSetIntTag_platform(const char * tagName, int tagValue)
{
    Platform::String^ tagName_string = UTF8ToString(tagName);
    if (!s3ePushWooshShim::GetInterface()->s3ePushWooshNotificationSetIntTag_managed(tagName_string, tagValue))
        return S3E_RESULT_ERROR;
    return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshNotificationSetStringTag_platform(const char * tagName, const char * tagValue)
{
    Platform::String^ tagName_string = UTF8ToString(tagName);
    Platform::String^ tagValue_string = UTF8ToString(tagValue);
    if (!s3ePushWooshShim::GetInterface()->s3ePushWooshNotificationSetStringTag_managed(tagName_string, tagValue_string))
        return S3E_RESULT_ERROR;
    return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshNotificationSetBadgeNumber_platform(int badgeValue)
{
    if (!s3ePushWooshShim::GetInterface()->s3ePushWooshNotificationSetBadgeNumber_managed(badgeValue))
        return S3E_RESULT_ERROR;
    return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshClearLocalNotifications_platform()
{
    if (!s3ePushWooshShim::GetInterface()->s3ePushWooshClearLocalNotifications_managed())
        return S3E_RESULT_ERROR;
    return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshStartLocationTracking_platform()
{
    if (!s3ePushWooshShim::GetInterface()->s3ePushWooshStartLocationTracking_managed())
        return S3E_RESULT_ERROR;
    return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshStopLocationTracking_platform()
{
    if (!s3ePushWooshShim::GetInterface()->s3ePushWooshStopLocationTracking_managed())
        return S3E_RESULT_ERROR;
    return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshScheduleLocalNotification_platform(const char * message, int seconds, const char * userdata)
{
    Platform::String^ message_string = UTF8ToString(message);
    Platform::String^ userdata_string = UTF8ToString(userdata);
    if (!s3ePushWooshShim::GetInterface()->s3ePushWooshScheduleLocalNotification_managed(message_string, seconds, userdata_string))
        return S3E_RESULT_ERROR;
    return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshSetAndroidNotificationMultiMode_platform(bool enable)
{
    if (!s3ePushWooshShim::GetInterface()->s3ePushWooshSetAndroidNotificationMultiMode_managed(enable))
        return S3E_RESULT_ERROR;
    return S3E_RESULT_SUCCESS;
}
