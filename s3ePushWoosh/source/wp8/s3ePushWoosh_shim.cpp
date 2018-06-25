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
#include "s3ePushWoosh_shim.h"
#include "s3ePushWoosh_internal.h"
#include "s3eEdk.h"
#include <memory.h>
#include "IwDebug.h"

using namespace s3ePushWooshExtension;


IManagedS3Es3ePushWooshAPI^ s3ePushWooshShim::s_ManagedInterface = nullptr;

s3ePushWooshShim::s3ePushWooshShim()
{
}

s3ePushWooshShim::~s3ePushWooshShim()
{
    Terminate();
}

bool s3ePushWooshShim::Init(IManagedS3Es3ePushWooshAPI^ managedAPI)
{
    // It's an error to do this twice.
    if (s_ManagedInterface)
        return false;

    s_ManagedInterface = managedAPI;
    return true;
}

bool s3ePushWooshShim::Terminate()
{
    // It's an error to do this twice.
    if (!s_ManagedInterface)
        return false;

    s_ManagedInterface = nullptr;
    return true;
}

IManagedS3Es3ePushWooshAPI^ s3ePushWooshShim::GetInterface()
{
    return s_ManagedInterface;
}

char nativeToken[4096];
char nativePush[4096];
char nativeError[4096];

void s3ePushWooshNativeInterface::onPushTokenUpdated(Platform::String^ token)
{
    memset(nativeToken, 0, 4096);
    StringToUTF8(nativeToken, 4096, token);

	s3eEdkCallbacksEnqueue(S3E_EXT_PUSHWOOSH_HASH, S3E_PUSHWOOSH_REGISTRATION_SUCCEEDED, nativeToken);
}

void s3ePushWooshNativeInterface::onPushTokenFailed(Platform::String^ error)
{
    memset(nativeError, 0, 4096);
    StringToUTF8(nativeError, 4096, error);

    s3eEdkCallbacksEnqueue(S3E_EXT_PUSHWOOSH_HASH, S3E_PUSHWOOSH_REGISTRATION_ERROR, nativeError);
}

void s3ePushWooshNativeInterface::onPushReceived(Platform::String^ push)
{
    memset(nativePush, 0, 4096);
    StringToUTF8(nativePush, 4096, push);

	s3eEdkCallbacksEnqueue(S3E_EXT_PUSHWOOSH_HASH, S3E_PUSHWOOSH_MESSAGE_RECEIVED, nativePush);
}
