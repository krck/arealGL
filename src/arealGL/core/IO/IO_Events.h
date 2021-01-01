#ifndef IO_Events_h
#define IO_Events_h

#include "..\..\Config.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace arealGL {

static KeyboardServer key_server;
static MouseServer mouse_server;

class IOEvents {
private:
    const KeyboardClient key_client;
    const MouseClient mouse_client;
    
public:
    IOEvents() :key_client(KeyboardClient(key_server)), mouse_client(MouseClient(mouse_server)) { }
    
    // handle the keyboard input
    static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        switch (action) {
            case GLFW_PRESS:    key_server.OnKeyPressed(key);           break;
            case GLFW_RELEASE:  key_server.OnKeyReleased(key);          break;
        }
    }
    
    // handle mouse klicks
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
        switch (action) {
            case GLFW_PRESS:
                if(button == GLFW_MOUSE_BUTTON_LEFT) {          mouse_server.OnLeftPressed(); }
                else if( button == GLFW_MOUSE_BUTTON_RIGHT) {   mouse_server.OnRightPressed(); }
            case GLFW_RELEASE:
                if(button == GLFW_MOUSE_BUTTON_LEFT) {          mouse_server.OnLeftReleased(); }
                else if( button == GLFW_MOUSE_BUTTON_RIGHT) {   mouse_server.OnRightReleased(); }
        }
    }
    
    // handle mouse movement
    inline void mouse_motion(GLFWwindow* win) const { mouse_server.OnMouseMove(win); return; }
    
    // handle mouswheel / scrolling
    static inline void mouse_wheel_callback(GLFWwindow* window, double xoffset, double yoffset) { mouse_server.OnWheelMove(xoffset, yoffset); }
    
    // check if the mouse is inside the window
    static void mouse_inwindow_callback(GLFWwindow* window, int entered) {
        if(entered) { mouse_server.OnMouseEnter(); } else { mouse_server.OnMouseLeave(); }
    }
    
    
    const KeyboardClient& get_keyboard() const { return this->key_client; }
    const MouseClient& get_mouse() const { return this->mouse_client; }
    
};

}

#endif
