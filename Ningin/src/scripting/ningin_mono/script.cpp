#include "script.h"

Script::Script() : klass(nullptr) , obj(nullptr)
{
}

Script::Script(ScriptClass* klass, MonoObject* obj) : klass(klass) ,  obj(obj) {}
