#pragma once

#include <mono/jit/jit.h>

void DebugLogInfo(MonoString* message);

void DebugLogError(MonoString* message);

void DebugLogWarning(MonoString* message);
