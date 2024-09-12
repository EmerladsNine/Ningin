#include "script.h"

bool Script::IsStarted()
{
    return isStarted;
}

void Script::Start()
{
    isStarted = true;
}

void Script::Update(float deltatime)
{

}

void Script::LateUpdate(float deltatime)
{

}

void Script::Destroy()
{

}

Script::Script() : klass(nullptr) , obj(nullptr)
{
}

Script::Script(ScriptClass* klass, MonoObject* obj) : klass(klass) ,  obj(obj) {}
