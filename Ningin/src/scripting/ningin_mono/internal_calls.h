#pragma once
#include <mono/metadata/metadata.h>
#include <mono/jit/jit.h>

#define AddInternalCall(Name) mono_add_internal_call("Ningin.InternalCalls::"#Name,Name);

void AddInternalCalls();