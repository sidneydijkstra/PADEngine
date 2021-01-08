#include "input.h"

namespace pad {

Input::KeyState::KeyState(const uint8_t state) noexcept : state(static_cast<State>(state)), frame(Input::currentFrame) {
   // Empty. 
}

bool Input::KeyState::operator==(const uint8_t state) const noexcept {
    return this->state == state;
}



bool Input::getKey(KeyCode key) noexcept {
    return keyStates[static_cast<int>(key)] == KeyState::PRESSED;
}

bool Input::getKeyDown(KeyCode key) noexcept {
    auto [state, frame] = keyStates[static_cast<int>(key)];
    return state==KeyState::PRESSED && frame==currentFrame;
}

bool Input::getKeyUp(KeyCode key) noexcept {
    auto [state, frame] = keyStates[static_cast<int>(key)];
    return state==KeyState::RELEASED && frame==currentFrame;
}

std::pair<double, double> Input::getMousePosition() noexcept {
    return mousePosition;
}

std::pair<double, double> Input::getMouseScrollDelta() noexcept {
    return mouseScrollDelta;
}

bool Input::getMouseButton(int key) noexcept {
    assert(("The parameter 'key', must be either 0 (Left), 1 (Right) or 2 (Middle)", 0 <= key && key <= 2));
    return keyStates[key] == KeyState::PRESSED;
}

bool Input::getMouseButtonDown(int key) noexcept {
    assert(("The parameter 'key', must be either 0 (Left), 1 (Right) or 2 (Middle)", 0 <= key && key <= 2));
    auto [state, frame] = keyStates[key];
    return state==KeyState::PRESSED && frame==currentFrame;
}

bool Input::getMouseButtonUp(int key) noexcept {
    assert(("The parameter 'key', must be either 0 (Left), 1 (Right) or 2 (Middle)", 0 <= key && key <= 2));
    auto [state, frame] = keyStates[key];
    return state==KeyState::RELEASED && frame==currentFrame;
}

void Input::attachToWindow(GLFWwindow* window) noexcept {
    if (Input::window != nullptr) detachFromWindow();

    Input::window = window;

    glfwSetKeyCallback(window, Input::handleKeyboardInput);
    glfwSetCursorPosCallback(window, Input::handleMousePositionInput);
    glfwSetMouseButtonCallback(window, Input::handleMouseButtonInput);
    glfwSetScrollCallback(window, Input::handleMouseScrollInput);
}

void Input::detachFromWindow() noexcept {
    glfwSetKeyCallback(window, nullptr);
    glfwSetCursorPosCallback(window, nullptr);
    glfwSetMouseButtonCallback(window, nullptr);
    glfwSetScrollCallback(window, nullptr);

    Input::window = nullptr;
}

void Input::update() noexcept {
    currentFrame++;
    
    mouseScrollDelta.first = 0.0;
    mouseScrollDelta.second = 0.0;
    
    glfwPollEvents();
}

void Input::handleKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept {
    if (action == GLFW_REPEAT) return;

    keyStates[key] = action;
}

void Input::handleMousePositionInput(GLFWwindow* window, double x, double y) noexcept {
    mousePosition.first = x;
    mousePosition.second = y;
}

void Input::handleMouseButtonInput(GLFWwindow* window, int key, int action, int mods) noexcept {
    keyStates[key] = action;
}

void Input::handleMouseScrollInput(GLFWwindow* window, double xOffset, double yOffset) noexcept {
    mouseScrollDelta.first = xOffset;
    mouseScrollDelta.second = yOffset;
}

}
