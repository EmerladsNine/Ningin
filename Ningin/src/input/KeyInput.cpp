#include "KeyInput.h"

std::unordered_map<int, bool> KeyInput::keys;

bool IsKeyDown(int key)
{
    bool result = false;
    auto it = KeyInput::keys.find(key);
    if (it != KeyInput::keys.end()) {
        result = KeyInput::keys[key];
    }
    return result;
}

void KeyInput::SetIsKeyDown(int key, bool isDown)
{
    keys.insert_or_assign(key, isDown);
}

void KeyInput::SetupKeyInputs(GLFWwindow* window)
{
    glfwSetKeyCallback(window, KeyInput::Callback);
}

void KeyInput::Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    SetIsKeyDown(key, action != GLFW_RELEASE);
}
