#ifndef Window_h
#define Window_h

#include <string>
#include <memory>
#include <windows.h> 

#include "..\..\Config.h"
#include "../IO/IO_Events.h"

namespace arealGL {
    
HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void GLAPIENTRY GlobalErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    // Print (red) Error in case of DEBUG_SEVERITY_HIGH, DEBUG_SEVERITY_MEDIUM, DEBUG_SEVERITY_LOW
    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
    {
        SetConsoleTextAttribute(hConsole, 4);
        std::cout << "[OpenGL Error](" << type << "): " << message << std::endl;
    }
    // Print (yellow) Warning in case of GL_DEBUG_SEVERITY_NOTIFICATION
    else
    {
        SetConsoleTextAttribute(hConsole, 6);
        std::cout << "[OpenGL Warning](" << type << "): " << message << std::endl;
    }

    // Reset the console text color to white
    SetConsoleTextAttribute(hConsole, 7);
}

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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        // create the OpenGL-Context-Window
        if(!fullscreen) { _window = glfwCreateWindow(width, height, titel.c_str(), nullptr, nullptr); }
        else { _window = glfwCreateWindow(width, height, titel.c_str(), glfwGetPrimaryMonitor(), nullptr); }
        glfwMakeContextCurrent(_window);

        // GLEW init only works after a OpenGL context was created
        glewExperimental = TRUE;
        if (glewInit() != GLEW_OK)
            return;

        // Setup global Error/Warning debug output
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GlobalErrorCallback, 0);

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
        // Get the actual window size values in pixels
        glfwGetFramebufferSize(_window, &_actualWidth, &_actualHeight);
    }
    
    inline void set_size(int width, int height) { _width = width; _height = height; glfwSetWindowSize(_window, width, height); }
    inline void set_position(int xpos, int ypos) { glfwSetWindowPos(_window, xpos, ypos); }
    inline void set_titel(const std::string& titel) { glfwSetWindowTitle(_window, titel.c_str()); }
    
    inline float width() const { return (float)this->_width; }
    inline float height() const { return (float)this->_height; }
    inline float actualWidth() const { return (float)this->_actualWidth; }
    inline float actualHeight() const { return (float)this->_actualHeight; }
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
