#pragma once

#define AddInternalCall(Name) mono_add_internal_call("NinginCore.InternalCalls::"#Name,Name)

#include <mono/metadata/metadata.h>
#include <mono/jit/jit.h>

void AddInternalCalls();
