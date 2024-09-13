#include "Script.h"
#include "Mono.h"

Script::Script(ScriptClass* klass, MonoObject* obj) : klass(klass), obj(obj) {}

Script::Script() : klass(nullptr), obj(nullptr) {}

bool Script::IsStarted()
{
    return isStarted;
}

void Script::Start()
{
    InvokeMethod(obj, klass->startMethod, {});
    isStarted = true;
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
