/*
C# implementation of the s3ePushWoosh extension.

Add win8-specific functionality here.

These functions are called via Shim class from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
using System.Windows.Controls;
using Microsoft.Phone.Controls;
using System.Windows.Media;


using s3e_native;
using s3ePushWooshExtension;
using System.Collections.Generic;
using PushSDK;
using PushSDK.Classes;
using Newtonsoft.Json;

namespace s3ePushWooshManaged
{
    public class s3ePushWooshManaged : IManagedS3Es3ePushWooshAPI, IManagedS3EEDKAPI
    {
        private PushSDK.NotificationService m_NotificationService = null;

        public bool ExtRegister(IS3EAPIManager apiManager, object mainPage)
        {
            try
            {
                // Keep a reference to the API Manager in order to call other
                // APIs.
                m_APIManager = apiManager;
                m_MainPage = mainPage as PhoneApplicationPage;
                m_MainPanel = VisualTreeHelper.GetChild(m_MainPage, 0) as Panel;

                // Add the managed API to the API Manager
                if (!m_APIManager.RegisterManagedAPI("s3ePushWoosh", this))
                    throw new System.Exception("Can't register Managed API");

                // Add the native API to the API manager.  Note that we don't own the native
                // interface, the API Manager does.  We want the two notions of managed and
                // native interface to be separate as there may be cases where we only want
                // one not the other.  It's only a matter of convenience that we create both
                // APIs in this ctr
                m_Native = new s3ePushWooshNativeInterface();
                if (!m_APIManager.RegisterNativeAPI("s3ePushWoosh", m_Native))
                    throw new System.Exception("Can't register Native API");

                // Create a Shim so we can pass the Managed interface down to native
                m_Shim = new s3ePushWooshShim();

                // Pass the managed interface down
                m_Shim.Init(this);
            }
            catch (System.Exception e)
            {
                m_APIManager = null;
                m_Shim = null;
                m_Native = null;
                System.Windows.MessageBox.Show("Failed to register s3ePushWoosh : " + e.Message);

                return false;
            }

            return true;
        }
        IS3EAPIManager m_APIManager = null;
        PhoneApplicationPage m_MainPage = null;
        // hint: add UI Elements as children of m_MainPanel
        Panel m_MainPanel = null;
        s3ePushWooshShim m_Shim = null;
        s3ePushWooshNativeInterface m_Native = null;

        // managed platform functionality


        public bool s3ePushWooshNotificationsAvailable_managed()
        {
            return true;
        }

        public bool s3ePushWooshNotificationRegister_managed()
        {
            if (m_NotificationService == null)
                return false;

            return false;
        }

        public bool s3ePushWooshNotificationRegisterWithPWAppID_managed(string pushwooshAppId)
        {
            string[] tileServers = { "https://cp.pushwoosh.com" };

            m_NotificationService =  NotificationService.GetCurrent(pushwooshAppId, "", tileServers);
            m_NotificationService.OnPushAccepted += m_NotificationService_OnPushAccepted;
            m_NotificationService.OnPushTokenReceived += m_NotificationService_OnPushTokenUpdated;
            m_NotificationService.OnPushTokenFailed += m_NotificationService_OnPushTokenFailed;

            m_NotificationService.SubscribeToPushService();
            return true;
        }

        public void m_NotificationService_OnPushTokenUpdated(object sender, string token)
        {
            s3ePushWooshNativeInterface.onPushTokenUpdated(token);
        }

        public void m_NotificationService_OnPushTokenFailed(object sender, string error)
        {
            s3ePushWooshNativeInterface.onPushTokenFailed(error);
        }

        public void m_NotificationService_OnPushAccepted(object sender, ToastPush push)
        {
            string pushString = JsonConvert.SerializeObject(push);
            s3ePushWooshNativeInterface.onPushReceived(pushString);
        }

        public string s3ePushWooshGetToken_managed()
        {
            if (m_NotificationService == null)
                return "";

            return m_NotificationService.PushToken;
        }

        public bool s3ePushWooshNotificationUnRegister_managed()
        {
            if (m_NotificationService == null)
                return false;

            m_NotificationService.UnsubscribeFromPushes(null, null);
            return true;
        }

        public bool s3ePushWooshNotificationSetIntTag_managed(string tagName, int tagValue)
        {
            if (m_NotificationService == null)
                return false;

            var tagsList = new List<KeyValuePair<string, object>>();

            object value;
            int iValue;
            tagsList.Add(new KeyValuePair<string, object>(tagName, tagValue));
            m_NotificationService.SendTag(tagsList, null, null);

            return true;
        }

        public bool s3ePushWooshNotificationSetStringTag_managed(string tagName, string tagValue)
        {
            if (m_NotificationService == null)
                return false;

            var tagsList = new List<KeyValuePair<string, object>>();

            object value;
            int iValue;
            tagsList.Add(new KeyValuePair<string, object>(tagName, tagValue));
            m_NotificationService.SendTag(tagsList, null, null);

            return true;
        }

        public bool s3ePushWooshNotificationSetBadgeNumber_managed(int badgeValue)
        {
            return false;
        }

        public bool s3ePushWooshClearLocalNotifications_managed()
        {
            return false;
        }

        public bool s3ePushWooshStartLocationTracking_managed()
        {
            if (m_NotificationService == null)
                return false;

            m_NotificationService.StartGeoLocation();
            return true;
        }

        public bool s3ePushWooshStopLocationTracking_managed()
        {
            if (m_NotificationService == null)
                return false;

            m_NotificationService.StopGeoLocation();
            return true;
        }

        public bool s3ePushWooshScheduleLocalNotification_managed(string message, int seconds, string userdata)
        {
            return false;
        }

        public bool s3ePushWooshSetAndroidNotificationMultiMode_managed(bool enable)
        {
            return false;
        }
    }
}
