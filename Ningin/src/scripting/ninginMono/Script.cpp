#include "Script.h"
#include "Mono.h"

Script::Script(ScriptClass* klass, MonoObject* obj) : klass(klass), obj(obj) {}

Script::Script() : klass(nullptr), obj(nullptr) {}

bool Script::HasStarted()
{
    return _hasStarted;
}

void Script::Start()
{
    InvokeMethod(obj, klass->startMethod, {});
    _hasStarted = true;
}

void Script::Update(float deltatime)
{
    InvokeMethod(obj, klass->updateMethod, {(void*)&deltatime});
}

void Script::LateUpdate(float deltatime)
{
    InvokeMethod(obj, klass->lateUpdateMethod, { (void*)&deltatime });
}

void Script::Destroy()
{
    InvokeMethod(obj, klass->destroyMethod, {});
}
