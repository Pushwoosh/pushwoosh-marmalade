# Marmalade extension s3ePushWoosh #

Provides extension for Marmalade to receive and handle push notifications for iOS, Android and Windows Phone.

Example:
```cpp
int32 OnPushRegistered(char* token, void* userData)
{
    //TODO: handle push notifications registration here
    return 0;
}
 
int32 OnPushReceived(char* text, void* userData)
{
    //TODO: handle push notifications here
    //push notifications comes as JSON string payload:
    //    {"aps":{
    //            alert = "Hello from Pushwoosh!";
    //            sound = default;
    //        },
    //        "onStart":1
    //    }
    return 0;
}
 
int32 OnPushRegisterError(char* error, void* userData)
{
    //TODO: handle push registration error here
    return 0;
}

if (s3ePushWooshNotificationsAvailable())
{
    s3ePushWooshRegister(S3E_PUSHWOOSH_REGISTRATION_SUCCEEDED, (s3eCallback)&OnPushRegistered, 0);
    s3ePushWooshRegister(S3E_PUSHWOOSH_MESSAGE_RECEIVED, (s3eCallback)&OnPushReceived, 0);
    s3ePushWooshRegister(S3E_PUSHWOOSH_REGISTRATION_ERROR, (s3eCallback)&OnPushRegisterError, 0);
 
    s3ePushWooshNotificationRegister();
}
```

## Class summary
[s3eBool s3ePushWooshNotificationsAvailable() S3E_FALSE](#s3epushwooshnotificationsavailable)  
[s3eResult s3ePushWooshNotificationRegister() S3E_RESULT_SUCCESS](#s3epushwooshnotificationregister)  
[s3eResult s3ePushWooshNotificationRegisterWithPWAppID(const char * pushwooshAppId) S3E_RESULT_SUCCESS](#s3epushwooshnotificationregisterwithpwappid)  
[char * s3ePushWooshGetToken() 0](#s3epushwooshgettoken)  
[s3eResult s3ePushWooshNotificationUnRegister() S3E_RESULT_SUCCESS](#s3epushwooshnotificationunregister)  
[s3eResult s3ePushWooshNotificationSetIntTag(const char * tagName, int tagValue) S3E_RESULT_SUCCESS](#s3epushwooshnotificationsetinttag)  
[s3eResult s3ePushWooshNotificationSetStringTag(const char * tagName, const char * tagValue) S3E_RESULT_SUCCESS](#s3epushwooshnotificationsetstringtag)  
[s3eResult s3ePushWooshNotificationSetBadgeNumber(int badgeValue) S3E_RESULT_SUCCESS](#s3epushwooshnotificationsetbadgenumber)  
[s3eResult s3ePushWooshClearLocalNotifications() S3E_RESULT_SUCCESS](#s3epushwooshclearlocalnotifications)  
[s3eResult s3ePushWooshStartLocationTracking() S3E_RESULT_SUCCESS](#s3epushwooshstartlocationtracking)  
[s3eResult s3ePushWooshStopLocationTracking() S3E_RESULT_SUCCESS](#s3epushwooshstoplocationtracking)  
[s3eResult s3ePushWooshScheduleLocalNotification(const char * message, int seconds, const char * userdata) S3E_RESULT_SUCCESS](#s3epushwooshschedulelocalnotification)  
[s3eResult s3ePushWooshSetAndroidNotificationMultiMode(bool enable) S3E_RESULT_SUCCESS](#s3epushwooshsetandroidnotificationmultimode)  

## Enums

```cpp
enum s3ePushWooshCallback
{
	S3E_PUSHWOOSH_REGISTRATION_SUCCEEDED,
	S3E_PUSHWOOSH_REGISTRATION_ERROR,
	S3E_PUSHWOOSH_MESSAGE_RECEIVED,
	S3E_PUSHWOOSH_CALLBACK_MAX
};
```

### S3E_PUSHWOOSH_REGISTRATION_SUCCEEDED

Push registration success callback.

```cpp
    s3ePushWooshRegister(S3E_PUSHWOOSH_REGISTRATION_SUCCEEDED, (s3eCallback)&OnPushRegistered, 0);
```

### S3E_PUSHWOOSH_MESSAGE_RECEIVED

Push notification callback.

```cpp
    s3ePushWooshRegister(S3E_PUSHWOOSH_MESSAGE_RECEIVED, (s3eCallback)&OnPushReceived, 0);
```

### S3E_PUSHWOOSH_REGISTRATION_ERROR

Push registration failed callback.

```cpp
    s3ePushWooshRegister(S3E_PUSHWOOSH_REGISTRATION_ERROR, (s3eCallback)&OnPushRegisterError, 0);
```


## Functions

### s3ePushWooshNotificationsAvailable

Returns S3E_TRUE if PushWooshNotifications extension is available.

```cpp
s3eBool s3ePushWooshNotificationsAvailable() S3E_FALSE
```

---
### s3ePushWooshNotificationRegister

Registers for push notifications.

```cpp
s3eResult s3ePushWooshNotificationRegister() S3E_RESULT_SUCCESS
```

---
### s3ePushWooshNotificationRegisterWithPWAppID

Used by Windows Phone, as there is no way to pass appId through manifest. Will call default register function without parameters on other platforms!

```cpp
s3eResult s3ePushWooshNotificationRegisterWithPWAppID(const char * pushwooshAppId) S3E_RESULT_SUCCESS
```

---
### s3ePushWooshGetToken

Returns push notifications token if available.

```cpp
char * s3ePushWooshGetToken() 0
```

---
### s3ePushWooshNotificationUnRegister

Unregisters from push notifications.

```cpp
s3eResult s3ePushWooshNotificationUnRegister() S3E_RESULT_SUCCESS
```

---
### s3ePushWooshNotificationSetIntTag

Sets Integer Tag for the device.

```cpp
s3eResult s3ePushWooshNotificationSetIntTag(const char * tagName, int tagValue) S3E_RESULT_SUCCESS
```

---
### s3ePushWooshNotificationSetStringTag

Sets String Tag for the device.

```cpp
s3eResult s3ePushWooshNotificationSetStringTag(const char * tagName, const char * tagValue) S3E_RESULT_SUCCESS
```

---
### s3ePushWooshNotificationSetBadgeNumber

Sets badge value for iOS.

```cpp
s3eResult s3ePushWooshNotificationSetBadgeNumber(int badgeValue) S3E_RESULT_SUCCESS
```

---
### s3ePushWooshClearLocalNotifications

Clears all local notifications set. Android only.

```cpp
s3eResult s3ePushWooshClearLocalNotifications() S3E_RESULT_SUCCESS
```

---
### s3ePushWooshStartLocationTracking

Starts Geo Zone push notifications.

```cpp
s3eResult s3ePushWooshStartLocationTracking() S3E_RESULT_SUCCESS
```

---
### s3ePushWooshStopLocationTracking

Stops Geo Zone push notifications.

```cpp
s3eResult s3ePushWooshStopLocationTracking() S3E_RESULT_SUCCESS
```

---
### s3ePushWooshScheduleLocalNotification

Schedules local notification.
To differentiate between local and remote notifications: local notification will have "local":true parameter in the notification payload

```cpp
s3eResult s3ePushWooshScheduleLocalNotification(const char * message, int seconds, const char * userdata) S3E_RESULT_SUCCESS
```
* **message** - title of the message to display
* **seconds** - timeout to show the message
* **userdata** - optional paramater and can be null

---
### s3ePushWooshSetAndroidNotificationMultiMode

Sets Android multi-notification mode.

```cpp
s3eResult s3ePushWooshSetAndroidNotificationMultiMode(bool enable) S3E_RESULT_SUCCESS
```
