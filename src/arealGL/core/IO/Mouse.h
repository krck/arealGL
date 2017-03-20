// Mouse.h
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

#ifndef Mouse_h
#define Mouse_h

namespace arealGL {

class MouseServer {
private:
    double x, y;
    double wheel_x, wheel_y;
    bool leftIsPressed;
    bool rightIsPressed;
    bool isInWindow;
    
public:
    MouseServer() :isInWindow(false), leftIsPressed(false), rightIsPressed(false), x(-1.0f), y(-1.0f) { }
    
    inline void OnMouseMove(GLFWwindow* win) { glfwGetCursorPos(win, &x, &y); }
    inline void OnWheelMove(double x, double y) { this->wheel_x = x; this->wheel_y = y; }
    inline void OnMouseLeave() { isInWindow = false; }
    inline void OnMouseEnter() { isInWindow = true; }
    inline void OnLeftPressed() { leftIsPressed = true; }
    inline void OnLeftReleased() { leftIsPressed = false; }
    inline void OnRightPressed() { rightIsPressed = true; }
    inline void OnRightReleased() { rightIsPressed = false; }
    inline void reset_wheel() { this->wheel_x = 0.0f; this->wheel_y = 0.0f; }
    inline bool IsInWindow() const { return isInWindow; }
    
    inline double getX() const { return this->x; }
    inline double getY() const { return this->y; }
    inline double getWheelX() const { return this->wheel_x; }
    inline double getWheelY() const { return this->wheel_y; }
    inline bool getLeftPressed() const { return this->leftIsPressed; }
    inline bool getRightPressed() const { return this->rightIsPressed; }
    inline bool getInWindow() const { return this->isInWindow; }
    
};


class MouseClient {
private:
    MouseServer& _server;
    
public:
    MouseClient(MouseServer& server) : _server(server) { }
    inline double GetMouseX() const { return _server.getX(); }
    inline double GetMouseY() const { return _server.getY(); }
    inline double GetWheelX() const { return _server.getWheelX(); }
    inline double GetWheelY() const { return _server.getWheelY(); }
    inline bool LeftIsPressed() const { return _server.getLeftPressed(); }
    inline bool RightIsPressed() const { return _server.getRightPressed(); }
    inline bool IsInWindow() const { return _server.getInWindow(); }
    inline void reset_wheel() { _server.reset_wheel(); }
    
    // Not copyable or assignable: Only one MouseClient allowed
    MouseClient& operator=(const MouseClient&) = delete;
    MouseClient() = delete;
    
};
    
}

#endif
