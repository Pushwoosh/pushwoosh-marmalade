/*
C++ Shim implementation of the s3ePushWoosh extension's.

Not intended for modifications

These functions are called by C# to access native interface and from C++ to
access managed interface.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */

namespace s3ePushWooshExtension
{
// This is the interface which native code can use to talk to managed code.
[Windows::Foundation::Metadata::WebHostHidden]
public interface class IManagedS3Es3ePushWooshAPI : public s3e_native::IManagedS3EAPI
{
    // We shouldn't populate these defacto.  We should only add functions here as and when
    // necessary.
    bool s3ePushWooshNotificationsAvailable_managed();
    bool s3ePushWooshNotificationRegister_managed();
    bool s3ePushWooshNotificationRegisterWithPWAppID_managed(Platform::String^ pushwooshAppId);
    Platform::String^ s3ePushWooshGetToken_managed();
    bool s3ePushWooshNotificationUnRegister_managed();
    bool s3ePushWooshNotificationSetIntTag_managed(Platform::String^ tagName, int tagValue);
    bool s3ePushWooshNotificationSetStringTag_managed(Platform::String^ tagName, Platform::String^ tagValue);
    bool s3ePushWooshNotificationSetBadgeNumber_managed(int badgeValue);
    bool s3ePushWooshClearLocalNotifications_managed();
    bool s3ePushWooshStartLocationTracking_managed();
    bool s3ePushWooshStopLocationTracking_managed();
    bool s3ePushWooshScheduleLocalNotification_managed(Platform::String^ message, int seconds, Platform::String^ userdata);
    bool s3ePushWooshSetAndroidNotificationMultiMode_managed(bool enable);
};

// This is the class which managed code can use to talk to native code.
[Windows::Foundation::Metadata::WebHostHidden]
public ref class s3ePushWooshNativeInterface sealed : public s3e_native::INativeS3EAPI
{
    // We shouldn't populate these defacto.  We should only add functions here as and when
    // necessary.
public:
    s3ePushWooshNativeInterface() {}

	static void onPushTokenUpdated(Platform::String^ token);
	static void onPushReceived(Platform::String^ push);
    static void onPushTokenFailed(Platform::String^ error);
};


[Windows::Foundation::Metadata::WebHostHidden]
public ref class s3ePushWooshShim sealed 
{
public:

    s3ePushWooshShim();

    // We use two stage construction to avoid the use of exceptions.  We
    // don't want to ever register an API more than once (as it's a static
    // below).  If we did this initialization in the ctr then we'd either
    // have to fail silently or throw an exception.
     bool Init(IManagedS3Es3ePushWooshAPI^ managedAPI);

    // Unregisters the static interface.
     bool Terminate();

    // Need static getters as we can't have public members in the class.
    static IManagedS3Es3ePushWooshAPI^ GetInterface();
private:

    ~s3ePushWooshShim();

    // This is the unavoidable point where we need a static.  There's
    // no choice as we're converting to a C-API.
    static IManagedS3Es3ePushWooshAPI^ s_ManagedInterface;
};

// char* <-> Platform::String^ wrappers
static inline Platform::String^ UTF8ToString(const char* utf8str)
{
    return s3e_native::s3eAPIDataTypeWrapper::CStringToPlatformString(const_cast<char*>(utf8str));
}

static inline void StringToUTF8(char* utf8str, size_t size, Platform::String^ str)
{
    s3e_native::s3eAPIDataTypeWrapper::PlatformStringToCString(const_cast<char*>(utf8str), size, str);
}

}
