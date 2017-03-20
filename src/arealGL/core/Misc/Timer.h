// Timer.h
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

#ifndef Timer_h
#define Timer_h

#include <chrono>
#include <string>
#include <iostream>
#include <thread>

#include "Config.h"
#include "Types.h"

namespace arealGL {

class Timer {
private:
    float fps;
    float frameTimeAverage;
    int frameTimes[FRAME_SAMPLES];
    int currentFrame;
    int prevTicks;
    int currentTicks;
    time_point startTicks;
    
public:
    Timer() : prevTicks(std::chrono::high_resolution_clock::now().time_since_epoch().count()), currentFrame(0) {}
    
    void calculateFPS() {
        const time_point tp = std::chrono::high_resolution_clock::now();
        currentTicks = std::chrono::time_point_cast<std::chrono::milliseconds>(tp).time_since_epoch().count();
        frameTimes[currentFrame % FRAME_SAMPLES] = (currentTicks - prevTicks);
        prevTicks = currentTicks;
        frameTimeAverage = 0;
        for (int i = 0; i < FRAME_SAMPLES; i++) { frameTimeAverage += frameTimes[i]; }
        frameTimeAverage /= FRAME_SAMPLES;
        // calculate frames per second (dont divide by zero)
        frameTimeAverage > 0 ? fps = 1000.0f / frameTimeAverage : fps = 60.0f;
        currentFrame++;
        return;
    }
    
    inline void printFPS() const { std::cout <<"FPS: " <<(int)fps <<std::endl; }
    
    inline void limitFPSstart() { startTicks = std::chrono::high_resolution_clock::now(); }
    void limitFPSend() const {
        const time_point endTicks = std::chrono::high_resolution_clock::now();
        const float start = std::chrono::time_point_cast<std::chrono::milliseconds>(startTicks).time_since_epoch().count();
        const float end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTicks).time_since_epoch().count();
        const float frameTicks = end - start;
        // Limit the FPS by delaying the main loop
        if(1000.0f / FPS_MAX > 0) {
            const int limit = (1000.0f / FPS_MAX) - frameTicks;
            std::this_thread::sleep_for(std::chrono::milliseconds(limit));
        }
    }
    
};

}

#endif
