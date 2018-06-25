/*
 * android-specific implementation of the s3ePushWoosh extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3ePushWoosh_internal.h"

#include <memory>
#include <string>

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_s3ePushWooshNotificationsAvailable;
static jmethodID g_s3ePushWooshNotificationRegister;
static jmethodID g_s3ePushWooshGetToken;
static jmethodID g_s3ePushWooshNotificationUnRegister;
static jmethodID g_s3ePushWooshNotificationSetIntTag;
static jmethodID g_s3ePushWooshNotificationSetStringTag;
static jmethodID g_s3ePushWooshClearLocalNotifications;
static jmethodID g_s3ePushWooshScheduleLocalNotification;
static jmethodID g_s3ePushWooshSetAndroidNotificationMultiMode;
static jmethodID g_s3ePushWooshStartLocationTracking;
static jmethodID g_s3ePushWooshStopLocationTracking;
static jmethodID g_s3ePushWooshSetUserId;
static jmethodID g_s3ePushWooshPostEvent;


JNIEXPORT void JNICALL native_onNotificationsRegistered(JNIEnv* env, jclass clazz, jstring token);
JNIEXPORT void JNICALL native_onNotificationsRegisterError(JNIEnv* env, jclass clazz, jstring message);
JNIEXPORT void JNICALL native_onPushReceived(JNIEnv* env, jclass clazz, jstring text, jstring customData);



s3eResult s3ePushWooshInit_platform()
{
	
	
	
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("com/arellomobile/pushwoosh/s3ePushWoosh");
    if (!cls)
        goto fail;

    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    // Get all the extension methods
    g_s3ePushWooshNotificationsAvailable = env->GetMethodID(cls, "s3ePushWooshNotificationsAvailable", "()Z");
    if (!g_s3ePushWooshNotificationsAvailable)
        goto fail;

    g_s3ePushWooshNotificationRegister = env->GetMethodID(cls, "s3ePushWooshNotificationRegister", "()I");
    if (!g_s3ePushWooshNotificationRegister)
        goto fail;

    g_s3ePushWooshGetToken = env->GetMethodID(cls, "s3ePushWooshGetToken", "()Ljava/lang/String;");
    if (!g_s3ePushWooshGetToken)
        goto fail;

    g_s3ePushWooshNotificationUnRegister = env->GetMethodID(cls, "s3ePushWooshNotificationUnRegister", "()I");
    if (!g_s3ePushWooshNotificationUnRegister)
        goto fail;

    g_s3ePushWooshNotificationSetIntTag = env->GetMethodID(cls, "s3ePushWooshNotificationSetIntTag", "(Ljava/lang/String;I)I");
    if (!g_s3ePushWooshNotificationSetIntTag)
        goto fail;

    g_s3ePushWooshNotificationSetStringTag = env->GetMethodID(cls, "s3ePushWooshNotificationSetStringTag", "(Ljava/lang/String;Ljava/lang/String;)I");
    if (!g_s3ePushWooshNotificationSetStringTag)
        goto fail;

    g_s3ePushWooshClearLocalNotifications = env->GetMethodID(cls, "s3ePushWooshClearLocalNotifications", "()I");
    if (!g_s3ePushWooshClearLocalNotifications)
        goto fail;

    g_s3ePushWooshScheduleLocalNotification = env->GetMethodID(cls, "s3ePushWooshScheduleLocalNotification", "(Ljava/lang/String;ILjava/lang/String;)I");
    if (!g_s3ePushWooshScheduleLocalNotification)
        goto fail;

    g_s3ePushWooshSetAndroidNotificationMultiMode = env->GetMethodID(cls, "s3ePushWooshSetAndroidNotificationMultiMode", "(I)I");
    if (!g_s3ePushWooshSetAndroidNotificationMultiMode)
        goto fail;

    g_s3ePushWooshStartLocationTracking = env->GetMethodID(cls, "s3ePushWooshStartLocationTracking", "()I");
    if (!g_s3ePushWooshStartLocationTracking)
        goto fail;

    g_s3ePushWooshStopLocationTracking = env->GetMethodID(cls, "s3ePushWooshStopLocationTracking", "()I");
    if (!g_s3ePushWooshStopLocationTracking)
        goto fail;

	g_s3ePushWooshSetUserId = env->GetMethodID(cls, "s3ePushWooshSetUserId", "(Ljava/lang/String;)I");
    if (!g_s3ePushWooshSetUserId)
        goto fail;

    g_s3ePushWooshPostEvent = env->GetMethodID(cls, "s3ePushWooshPostEvent", "(Ljava/lang/String;Ljava/lang/String;)I");
    if (!g_s3ePushWooshPostEvent)
        goto fail;
	
    static const JNINativeMethod jnm[] = {
        {"onNotificationsRegistered", "(Ljava/lang/String;)V", (void *)&native_onNotificationsRegistered},
        {"onNotificationsRegisterError", "(Ljava/lang/String;)V", (void *)&native_onNotificationsRegisterError},
        {"onPushReceived", "(Ljava/lang/String;Ljava/lang/String;)V", (void *)&native_onPushReceived }
    };

    env->RegisterNatives(cls, jnm, sizeof(jnm) / sizeof(jnm[0]));

    IwTrace(PUSHWOOSH, ("PUSHWOOSH init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;

fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(s3ePushWoosh, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void s3ePushWooshTerminate_platform()
{
    // Add any platform-specific termination code here
}

s3eBool s3ePushWooshNotificationsAvailable_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eBool)env->CallBooleanMethod(g_Obj, g_s3ePushWooshNotificationsAvailable);
}

s3eResult s3ePushWooshNotificationRegister_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_s3ePushWooshNotificationRegister);
}

// on Android Pushwoosh App Id and ProjectId comes from AndroidManifest.xml
s3eResult s3ePushWooshNotificationRegisterWithPWAppID_platform(const char * pushwooshAppId)
{
    return s3ePushWooshNotificationRegister_platform();
}

struct AutoJniStringBuffer
{
    AutoJniStringBuffer(JNIEnv* env, jstring string) : env(env), string(string)
    {
        buffer = env->GetStringUTFChars(string, 0);
    }

    ~AutoJniStringBuffer()
    {
        env->ReleaseStringUTFChars(string, buffer);
    }

    const char* buffer;
private:
    JNIEnv* env;
    jstring string;
};

std::string g_pushToken;
std::string g_errorMessage;
std::string g_pushPayload;

char * s3ePushWooshGetToken_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
	jstring jtoken = (jstring)env->CallObjectMethod(g_Obj, g_s3ePushWooshGetToken);
	
	AutoJniStringBuffer tokenBuffer(env, jtoken);
	g_pushToken = tokenBuffer.buffer;
    return (char *)g_pushToken.c_str();
}


JNIEXPORT void JNICALL native_onNotificationsRegistered(JNIEnv* env, jclass clazz, jstring token)
{
    IwTrace(PUSHWOOSH, ("PUSHWOOSH: registered for notifications"));
    {
        AutoJniStringBuffer tokenBuffer(env, token);    
        g_pushToken = std::string(tokenBuffer.buffer);
    }

	s3eEdkCallbacksEnqueue(S3E_EXT_PUSHWOOSH_HASH, S3E_PUSHWOOSH_REGISTRATION_SUCCEEDED, (char *)g_pushToken.c_str());
}

JNIEXPORT void JNICALL native_onNotificationsRegisterError(JNIEnv* env, jclass clazz, jstring message) 
{
	AutoJniStringBuffer messageBuffer(env, message);
    g_errorMessage = std::string(messageBuffer.buffer);
	
	s3eEdkCallbacksEnqueue(S3E_EXT_PUSHWOOSH_HASH, S3E_PUSHWOOSH_REGISTRATION_ERROR, (char *)g_errorMessage.c_str());
}

JNIEXPORT void JNICALL native_onPushReceived(JNIEnv* env, jclass clazz, jstring text, jstring customData)
{
    {
        AutoJniStringBuffer textBuffer(env, text);
        g_pushPayload = std::string(textBuffer.buffer);
    }

	s3eEdkCallbacksEnqueue(S3E_EXT_PUSHWOOSH_HASH, S3E_PUSHWOOSH_MESSAGE_RECEIVED, (char *)g_pushPayload.c_str());
}
s3eResult s3ePushWooshNotificationUnRegister_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_s3ePushWooshNotificationUnRegister);
}

s3eResult s3ePushWooshNotificationSetIntTag_platform(const char * tagName, int tagValue)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring tagName_jstr = env->NewStringUTF(tagName);
    return (s3eResult)env->CallIntMethod(g_Obj, g_s3ePushWooshNotificationSetIntTag, tagName_jstr, tagValue);
}

s3eResult s3ePushWooshNotificationSetStringTag_platform(const char * tagName, const char * tagValue)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring tagName_jstr = env->NewStringUTF(tagName);
    jstring tagValue_jstr = env->NewStringUTF(tagValue);
    return (s3eResult)env->CallIntMethod(g_Obj, g_s3ePushWooshNotificationSetStringTag, tagName_jstr, tagValue_jstr);
}

s3eResult s3ePushWooshClearLocalNotifications_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_s3ePushWooshClearLocalNotifications);
}

s3eResult s3ePushWooshScheduleLocalNotification_platform(const char * message, int seconds, const char * userdata)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring message_jstr = env->NewStringUTF(message);
    jstring userdata_jstr = userdata ? env->NewStringUTF(userdata) : 0;
    return (s3eResult)env->CallIntMethod(g_Obj, g_s3ePushWooshScheduleLocalNotification, message_jstr, seconds, userdata_jstr);
}

s3eResult s3ePushWooshSetAndroidNotificationMultiMode_platform(bool enable)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_s3ePushWooshSetAndroidNotificationMultiMode, enable);
}

s3eResult s3ePushWooshStartLocationTracking_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_s3ePushWooshStartLocationTracking);
}

s3eResult s3ePushWooshStopLocationTracking_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (s3eResult)env->CallIntMethod(g_Obj, g_s3ePushWooshStopLocationTracking);
}

s3eResult s3ePushWooshNotificationSetBadgeNumber_platform(int badgeNumber)
{
    return S3E_RESULT_SUCCESS;
}

s3eResult s3ePushWooshSetUserId_platform(const char * userId)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring userId_jstr = env->NewStringUTF(userId);
    return (s3eResult)env->CallIntMethod(g_Obj, g_s3ePushWooshSetUserId, userId_jstr);
}

s3eResult s3ePushWooshPostEvent_platform(const char * event, const char * attributes)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring event_jstr = env->NewStringUTF(event);
    jstring attributes_jstr = env->NewStringUTF(attributes);
    return (s3eResult)env->CallIntMethod(g_Obj, g_s3ePushWooshPostEvent, event_jstr, attributes_jstr);
}
