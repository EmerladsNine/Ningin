#include "ScriptClass.h"

ScriptClass::ScriptClass() : klass(nullptr) , startMethod(nullptr), updateMethod(nullptr),
	lateUpdateMethod(nullptr), destroyMethod(nullptr) {}

ScriptClass::ScriptClass(MonoClass* klass) : klass(klass), startMethod(nullptr),
	updateMethod(nullptr), lateUpdateMethod(nullptr), destroyMethod(nullptr) {}
