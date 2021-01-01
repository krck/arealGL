// IO_Events.h
/*************************************************************************************
 *  arealGL (OpenGL graphics library)                                                *
 *-----------------------------------------------------------------------------------*
 *  Copyright (c) 2015, Peter Baumann                                                *
 *  All rights reserved.                                                             *
 *                                                                                   *
 *  Redistribution and use in source and binary forms, with or without               *
 *  modification, are permitted provided that the following conditions are met:      *
 *    1. Redistributions of source code must retain the above copyright              *
 *       notice, this list of conditions and the following disclaimer.               *
 *    2. Redistributions in binary form must reproduce the above copyright           *
 *       notice, this list of conditions and the following disclaimer in the         *
 *       documentation and/or other materials provided with the distribution.        *
 *    3. Neither the name of the organization nor the                                *
 *       names of its contributors may be used to endorse or promote products        *
 *       derived from this software without specific prior written permission.       *
 *                                                                                   *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND  *
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED    *
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
 *  DISCLAIMED. IN NO EVENT SHALL PETER BAUMANN BE LIABLE FOR ANY                    *
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES       *
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;     *
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND      *
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS    *
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                     *
 *                                                                                   *
 *************************************************************************************/

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
