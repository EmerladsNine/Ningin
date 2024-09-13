#include "DebugWrapper.h"
#include "../../../utills/Debug.h"

void DebugLogInfo(MonoString* message)
{
	char* messageCstr = mono_string_to_utf8(message);
	LogInfo(messageCstr);
}

void DebugLogError(MonoString* message)
{
	char* messageCstr = mono_string_to_utf8(message);
	LogInfo(messageCstr);
}

void DebugLogWarning(MonoString* message)
{
	char* messageCstr = mono_string_to_utf8(message);
	LogInfo(messageCstr);
}
