#pragma once

#include <mono/metadata/metadata.h>
#include "ScriptClass.h"
#include "../scriptable.h"

class Script : public Scriptable
{
	public:
		Script(ScriptClass* klass , MonoObject* obj);
		Script();

		ScriptClass* klass;
		MonoObject* obj;
	
		bool IsStarted() override;
		void Start() override;
		void Update(float deltatime) override;
		void LateUpdate(float deltatime) override;
		void Destroy() override;

	private:
		bool isStarted = false;
};
