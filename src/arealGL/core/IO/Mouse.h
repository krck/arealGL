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
