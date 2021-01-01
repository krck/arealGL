// Keyboard.h
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
