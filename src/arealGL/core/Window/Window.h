//  Window.h
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

#ifndef Window_h
#define Window_h

#include <string>
#include <memory>

#include "glfw3.h"
#include "IO_Events.h"

namespace arealGL {
    
class Window {
    
private:
    int _width, _height, _fieldOfView = 45;
    int _actualWidth, _actualHeight;
    GLFWwindow* _window;
    std::unique_ptr<IOEvents> _io = nullptr;
    
public:
    Window(const std::string& titel, int width, int height, bool fullscreen) :_width(width), _height(height) {
        glfwInit();
        // settings needed for using OpenGL Version 410
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        // create the OpenGL-Context-Window
        if(!fullscreen) { _window = glfwCreateWindow(width, height, titel.c_str(), nullptr, nullptr); }
        else { _window = glfwCreateWindow(width, height, titel.c_str(), glfwGetPrimaryMonitor(), nullptr); }
        glfwMakeContextCurrent(_window);
        // Enable V-Sync
        glfwSwapInterval(1);
        // set some OpenGL options
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        // gamma correction (SRGB / expotential)
        // glEnable(GL_FRAMEBUFFER_SRGB);
        // check if these are still needed
        // GL DEPTH CLAMP
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        // glFrontFace(GL_CCW);
        // set input - output events
        _io = std::unique_ptr<IOEvents>(new IOEvents());
        glfwSetKeyCallback(_window, _io->keyboard_callback);
        glfwSetMouseButtonCallback(_window, _io->mouse_button_callback);
        glfwSetScrollCallback(_window, _io->mouse_wheel_callback);
        glfwSetCursorEnterCallback(_window, _io->mouse_inwindow_callback);
        // Disable cursor for unlimited mouse movement with the camera
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    
    inline void set_size(int width, int height) { _width = width; _height = height; glfwSetWindowSize(_window, width, height); }
    inline void set_position(int xpos, int ypos) { glfwSetWindowPos(_window, xpos, ypos); }
    inline void set_titel(const std::string& titel) { glfwSetWindowTitle(_window, titel.c_str()); }
    
    inline float width() const { return (float)this->_width; }
    inline float height() const { return (float)this->_height; }
    inline float fieldOfView() const { return (float)this->_fieldOfView; }
    inline bool closed() const { return glfwWindowShouldClose(_window); }
    
    inline const KeyboardClient& keyboardClient() const { return this->_io->get_keyboard(); }
    inline const MouseClient& mouseClient() const { return this->_io->get_mouse(); }
    
    inline void clear() const {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
    
    void update() {
        glfwPollEvents();
        _io->mouse_motion(_window);
        glfwSwapBuffers(_window);
    }
    
    void setAsRenderTarget() {
        // Set the default FrameBuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glfwGetFramebufferSize(_window, &_actualWidth, &_actualHeight);
        glViewport(0, 0, _actualWidth, _actualHeight);
    }

    ~Window() { glfwDestroyWindow(_window); glfwTerminate(); }
    
};
    
}

#endif
