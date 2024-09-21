#pragma once

#include "../shader/Shader.h"
#include <vector>

using namespace std;

class UBO {
	public:
		UBO(vector<Shader> shadersUniforms, const string uboName, unsigned long long uniformSize);
		UBO();

		void SetUBOFloatPtr(unsigned long long uniformSize, unsigned long long offset, float* ptr);
		void SetUBOIntPtr(unsigned long long uniformSize, unsigned long long offset, int* ptr);

		GLuint getId();

	private:
		void GenUBO(unsigned long long uniformSize);

		GLuint _ubo;
};