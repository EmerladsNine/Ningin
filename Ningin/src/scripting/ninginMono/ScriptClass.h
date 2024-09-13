#pragma once

#include <mono/metadata/metadata.h>

class ScriptClass
{
	public:
		ScriptClass(MonoClass* klass);
		ScriptClass();

		MonoClass* klass;
		MonoMethod* startMethod;
		MonoMethod* updateMethod;
		MonoMethod* lateUpdateMethod;
		MonoMethod* destroyMethod;
};
