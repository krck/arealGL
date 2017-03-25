//  Types.h
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

#ifndef Types_h
#define Types_h

#include <chrono>

// arealGL Types
typedef unsigned char   byte;
typedef unsigned int    uint;
typedef unsigned short  ushort;
typedef unsigned long   ulong;
typedef std::chrono::high_resolution_clock::time_point  time_point;

// Basic Color definitions
#define CL_BLACK            Color(0.0f,0.0f,0.0f)
#define CL_WHITE            Color(1.0f,1.0f,1.0f)
#define CL_GRAY             Color(0.3f,0.3f,0.3f)
#define CL_RED              Color(1.0f,0.0f,0.0f)
#define CL_GREEN            Color(0.0f,1.0f,0.0f)
#define CL_BLUE             Color(0.0f,0.0f,1.0f)
#define CL_YELLOW           Color(1.0f,1.0f,0.0f)
#define CL_YELLOW_PALE      Color(1.0f,1.0f,0.8f)
#define CL_ORANGE           Color(1.0f,0.4f,0.0f)
#define CL_BROWN            Color(0.6f,0.3f,0.1f)
#define CL_PURPLE           Color(0.5f,0.0f,1.0f)
#define CL_AQUA             Color(0.0f,1.0f,1.0f)
#define CL_PINK             Color(0.9f,0.0f,0.9f)

#endif
