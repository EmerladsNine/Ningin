#pragma once
#include <mono/metadata/metadata.h>
class ScriptClass
{
public:
	MonoClass* klass;
	MonoMethod* startMethod;
	MonoMethod* updateMethod;
	MonoMethod* lateUpdateMethod;
	MonoMethod* destroyMethod;
	ScriptClass();
	ScriptClass(MonoClass* klass);
};