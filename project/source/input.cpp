#include "input.h"

namespace pad {

Input::KeyState::KeyState(const uint8_t state) noexcept : state(static_cast<State>(state)), frame(Input::s_currentFrame) {
   // Empty. 
}

bool Input::KeyState::operator==(const uint8_t state) const noexcept {
    return this->state == state;
}



bool Input::getKey(KeyCode key) noexcept {
    return s_keyStates[static_cast<int>(key)] == KeyState::PRESSED;
}

bool Input::getKeyDown(KeyCode key) noexcept {
    auto [state, frame] = s_keyStates[static_cast<int>(key)];
    return state==KeyState::PRESSED && frame==s_currentFrame;
}

bool Input::getKeyUp(KeyCode key) noexcept {
    auto [state, frame] = s_keyStates[static_cast<int>(key)];
    return state==KeyState::RELEASED && frame==s_currentFrame;
}

std::pair<double, double> Input::getMousePosition() noexcept {
    return s_mousePosition;
}

std::pair<double, double> Input::getMouseScrollDelta() noexcept {
    return s_mouseScrollDelta;
}

bool Input::getMouseButton(int button) noexcept {
    assert(("The parameter 'key', must be either 0 (Left), 1 (Right) or 2 (Middle)", 0 <= key && key <= 2));
    return s_keyStates[button] == KeyState::PRESSED;
}

bool Input::getMouseButtonDown(int button) noexcept {
    assert(("The parameter 'key', must be either 0 (Left), 1 (Right) or 2 (Middle)", 0 <= key && key <= 2));
    auto [state, frame] = s_keyStates[button];
    return state==KeyState::PRESSED && frame==s_currentFrame;
}

bool Input::getMouseButtonUp(int button) noexcept {
    assert(("The parameter 'key', must be either 0 (Left), 1 (Right) or 2 (Middle)", 0 <= key && key <= 2));
    auto [state, frame] = s_keyStates[button];
    return state==KeyState::RELEASED && frame==s_currentFrame;
}

void Input::attachToWindow(GLFWwindow* window) noexcept {
    if (s_window != nullptr) detachFromWindow();

    s_window = window;

    glfwSetKeyCallback(s_window, Input::handleKeyboardInput);
    glfwSetCursorPosCallback(s_window, Input::handleMousePositionInput);
    glfwSetMouseButtonCallback(s_window, Input::handleMouseButtonInput);
    glfwSetScrollCallback(s_window, Input::handleMouseScrollInput);
}

void Input::detachFromWindow() noexcept {
    glfwSetKeyCallback(s_window, nullptr);
    glfwSetCursorPosCallback(s_window, nullptr);
    glfwSetMouseButtonCallback(s_window, nullptr);
    glfwSetScrollCallback(s_window, nullptr);

    s_window = nullptr;
}

void Input::update() noexcept {
    s_currentFrame++;
    
    s_mouseScrollDelta.first = 0.0;
    s_mouseScrollDelta.second = 0.0;
    
    glfwPollEvents();
}

void Input::handleKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept {
    if (action == GLFW_REPEAT) return;
    s_keyStates[key] = action;
}

void Input::handleMousePositionInput(GLFWwindow* window, double x, double y) noexcept {
    s_mousePosition.first = x;
    s_mousePosition.second = y;
}

void Input::handleMouseButtonInput(GLFWwindow* window, int key, int action, int mods) noexcept {
    s_keyStates[key] = action;
}

void Input::handleMouseScrollInput(GLFWwindow* window, double xOffset, double yOffset) noexcept {
    s_mouseScrollDelta.first = xOffset;
    s_mouseScrollDelta.second = yOffset;
}

}
