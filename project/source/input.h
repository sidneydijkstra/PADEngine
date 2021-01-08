/// @file input.h
/// @brief Header providing input functionality.
/// @author Sander Albers
/// @version 1.0.0
/// @date 08/01/2020

#ifndef PAD_ENGINE_UTILITY_INPUT_HEADER
#define PAD_ENGINE_UTILITY_INPUT_HEADER

#include <cassert>
#include <utility>

#include <GLFW/glfw3.h>

/* * * * * * * * * * * * * * * * * * *\
    TODO:
    1. Add documentation.
    2. Add JoyStick support.
    3. Add support for key mapping.
\* * * * * * * * * * * * * * * * * * */

class Core;

namespace pad {

enum class KeyCode {
    None = GLFW_KEY_UNKNOWN,
   
    Mouse0 = GLFW_MOUSE_BUTTON_1, Mouse1, Mouse2, Mouse3,
    Mouse4, Mouse5, Mouse6, Mouse7,

    MouseLeft = GLFW_MOUSE_BUTTON_1, MouseRight, MouseMiddle,

    Space = GLFW_KEY_SPACE,
    
    Apostrophe = GLFW_KEY_APOSTROPHE,
    
    Comma = GLFW_KEY_COMMA,
    Minus,
    Period,
    Slash,
    Alpha0, Alpha1, Alpha2, Alpha3, Alpha4,
    Alpha5, Alpha6, Alpha7, Alpha8, Alpha9,
    
    Semicolon = GLFW_KEY_SEMICOLON,
    Equals = GLFW_KEY_EQUAL,
    
    A = GLFW_KEY_A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    LeftBracket, Backslash, RightBracket,
    
    BackQuote = GLFW_KEY_GRAVE_ACCENT,
    
    World1 = GLFW_KEY_WORLD_1, World2 = GLFW_KEY_WORLD_2,
    
    Escape = GLFW_KEY_ESCAPE,
    Enter,
    Tab,
    Backspace,
    Insert,
    Delete,
    RightArrow, LeftArrow, DownArrow, UpArrow,
    PageUp, PageDown,
    Home,
    End,

    CapsLock = GLFW_KEY_CAPS_LOCK, ScrollLock, NumLock,
    PrintScreen,
    Pause,
    
    F1 = GLFW_KEY_F1, F2,  F3,  F4,  F5,
    F6,  F7,  F8,  F9,  F10,
    F11, F12, F13, F14, F15,
    F16, F17, F18, F19, F20,
    F21, F22, F23, F24, F25,
    
    KeyPad0 = GLFW_KEY_KP_0, KeyPad1, KeyPad2, KeyPad3, KeyPad4,
    KeyPad5, KeyPad6, KeyPad7, KeyPad8, KeyPad9,
    KeyPadPeriod,
    KeyPadDivide,
    KeyPadMultiply,
    KeyPadMinus,
    KeyPadPlus,
    KeyPadEnter,
    KeyPadEquals,
    
    LeftShift = GLFW_KEY_LEFT_SHIFT, LeftControl, LeftAlt,
    LeftSuper, LeftCommand = LeftSuper, LeftWindows = LeftSuper, LeftApple = LeftSuper,
    RightShift, RightControl, RightAlt,
    RightSuper, RightCommand = RightSuper, RightWindows = RightSuper, RightApple = RightSuper,
    Menu,

    LastKeyCode = Menu
};

class Input final {

public:

    friend class Core;

    Input(void) = delete;
    Input(const Input&) = delete;
    Input(Input&&) = delete;

    ~Input(void) = delete;

    /* TODO: Implement giving buttons a custom name/key mapping.
    static bool getButton() noexcept;
    static bool getButtonDown() noexcept;
    static bool getButtonUp() noexcept;
    */

    static bool getKey(KeyCode key) noexcept;
    static bool getKeyDown(KeyCode key) noexcept;
    static bool getKeyUp(KeyCode key) noexcept;

    static std::pair<double, double> getMousePosition() noexcept;
    static std::pair<double, double> getMouseScrollDelta() noexcept;

    static bool getMouseButton(int key) noexcept;
    static bool getMouseButtonDown(int key) noexcept;
    static bool getMouseButtonUp(int key) noexcept;

private:
    
    struct KeyState {
        enum State : uint8_t { PRESSED = GLFW_PRESS, RELEASED = GLFW_RELEASE };

        State state;
        int frame;

        KeyState(void) = default;
        KeyState(const uint8_t state) noexcept;
        
        bool operator==(uint8_t state) const noexcept;
    };

    inline static int currentFrame = 0;

    inline static GLFWwindow* window = nullptr;

    inline static KeyState* keyStates = new KeyState[static_cast<size_t>(KeyCode::LastKeyCode) + 1];
    
    inline static std::pair<double, double> mousePosition = std::make_pair(0.0, 0.0);
    inline static std::pair<double, double> mouseScrollDelta = std::make_pair(0.0, 0.0);

    static void attachToWindow(GLFWwindow* window) noexcept;
    static void detachFromWindow() noexcept;

    static void update() noexcept;

    static void handleKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept;
    static void handleMousePositionInput(GLFWwindow* window, double x, double y) noexcept;
    static void handleMouseButtonInput(GLFWwindow* window, int key, int action, int mods) noexcept;
    static void handleMouseScrollInput(GLFWwindow* window, double xOffset, double yOffset) noexcept;

};

}

/* Temporary using-directive. Remove when the whole engine uses the same namespace. */
using namespace pad;

#endif
