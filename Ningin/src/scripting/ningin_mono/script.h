#pragma once
#include <mono/metadata/metadata.h>
#include "script_class.h"
class Script
{
public:
	ScriptClass* klass;
	MonoObject* obj;
	Script();
	Script(ScriptClass* klass , MonoObject* obj);
};