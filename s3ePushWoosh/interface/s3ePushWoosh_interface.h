/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */
/**
 * Definitions for functions types passed to/from s3eExt interface
 */
typedef  s3eResult(*s3ePushWooshRegister_t)(s3ePushWooshCallback cbid, s3eCallback fn, void* userData);
typedef  s3eResult(*s3ePushWooshUnRegister_t)(s3ePushWooshCallback cbid, s3eCallback fn);
typedef    s3eBool(*s3ePushWooshNotificationsAvailable_t)();
typedef  s3eResult(*s3ePushWooshNotificationRegister_t)();
typedef  s3eResult(*s3ePushWooshNotificationRegisterWithPWAppID_t)(const char * pushwooshAppId);
typedef     char *(*s3ePushWooshGetToken_t)();
typedef  s3eResult(*s3ePushWooshNotificationUnRegister_t)();
typedef  s3eResult(*s3ePushWooshNotificationSetIntTag_t)(const char * tagName, int tagValue);
typedef  s3eResult(*s3ePushWooshNotificationSetStringTag_t)(const char * tagName, const char * tagValue);
typedef  s3eResult(*s3ePushWooshNotificationSetBadgeNumber_t)(int badgeValue);
typedef  s3eResult(*s3ePushWooshClearLocalNotifications_t)();
typedef  s3eResult(*s3ePushWooshStartLocationTracking_t)();
typedef  s3eResult(*s3ePushWooshStopLocationTracking_t)();
typedef  s3eResult(*s3ePushWooshScheduleLocalNotification_t)(const char * message, int seconds, const char * userdata);
typedef  s3eResult(*s3ePushWooshSetAndroidNotificationMultiMode_t)(bool enable);

/**
 * struct that gets filled in by s3ePushWooshRegister
 */
typedef struct s3ePushWooshFuncs
{
    s3ePushWooshRegister_t m_s3ePushWooshRegister;
    s3ePushWooshUnRegister_t m_s3ePushWooshUnRegister;
    s3ePushWooshNotificationsAvailable_t m_s3ePushWooshNotificationsAvailable;
    s3ePushWooshNotificationRegister_t m_s3ePushWooshNotificationRegister;
    s3ePushWooshNotificationRegisterWithPWAppID_t m_s3ePushWooshNotificationRegisterWithPWAppID;
    s3ePushWooshGetToken_t m_s3ePushWooshGetToken;
    s3ePushWooshNotificationUnRegister_t m_s3ePushWooshNotificationUnRegister;
    s3ePushWooshNotificationSetIntTag_t m_s3ePushWooshNotificationSetIntTag;
    s3ePushWooshNotificationSetStringTag_t m_s3ePushWooshNotificationSetStringTag;
    s3ePushWooshNotificationSetBadgeNumber_t m_s3ePushWooshNotificationSetBadgeNumber;
    s3ePushWooshClearLocalNotifications_t m_s3ePushWooshClearLocalNotifications;
    s3ePushWooshStartLocationTracking_t m_s3ePushWooshStartLocationTracking;
    s3ePushWooshStopLocationTracking_t m_s3ePushWooshStopLocationTracking;
    s3ePushWooshScheduleLocalNotification_t m_s3ePushWooshScheduleLocalNotification;
    s3ePushWooshSetAndroidNotificationMultiMode_t m_s3ePushWooshSetAndroidNotificationMultiMode;
} s3ePushWooshFuncs;