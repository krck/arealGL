#ifndef Keyboard_h
#define Keyboard_h

#include <queue>
#include <vector>

#include "..\..\Config.h"

namespace arealGL {

class KeyboardServer {
private:
    std::vector<bool> keystates;
    std::queue<int> keybuffer;
    
public:
    KeyboardServer() :keystates(KEY_CODES, false) { }
    
    void OnKeyPressed(int keycode) {
        keystates[keycode] = true;
        keybuffer.push(keycode);
        // keep only a number of key presses in the buffer
        if(keybuffer.size() == KEY_BUFFER_SZ) {
            keybuffer.pop();
        }
    }
    
    inline void OnKeyReleased(int keycode) { keystates[keycode] = false; }
    inline void RemoveFirstKey() { keybuffer.pop(); }
    inline void FlushBuffer() { std::queue<int>().swap(keybuffer); }
    
    inline bool getKeystate(int keycode) const { return keystates[keycode]; }
    inline size_t getBufferSize() const { return keybuffer.size(); }
    inline int getFirstKey() const { return keybuffer.front(); }
    
};


class KeyboardClient {
private:
    KeyboardServer& server;
    
public:
    KeyboardClient(KeyboardServer& kServer) :server(kServer) { }
    
    // Get constant Key presses
    inline bool KeyIsPressed(int keycode) const { return server.getKeystate(keycode); }
    
    // Get pressed Keys one by one
    int ReadKey() const {
        if(server.getBufferSize()) {
            const int keycode = server.getFirstKey();
            server.RemoveFirstKey();
            return keycode;
        } else {
            return 0;
        }
    }
    
    inline void FlushKeyBuffer() const { server.FlushBuffer(); }
    
    // Not copyable or assignable: Only one MouseClient allowed
    KeyboardClient& operator=(const KeyboardClient&) = delete;
    KeyboardClient() = delete;
    
};

}

#endif
