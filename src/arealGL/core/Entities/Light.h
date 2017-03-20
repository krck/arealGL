// Light.h
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

#ifndef Light_h
#define Light_h

#include <vec3.hpp>

namespace arealGL {

class Light {
public:
    glm::vec3 direction;
    glm::vec3 color;
    glm::vec3 attenuation;      // Three values to define point-light-ness
    float intensity;
    
    Light(const glm::vec3& direction, const glm::vec3& color, float intensity)
    : direction(direction), color(color), attenuation(glm::vec3(1.0f, 0.0f, 0.0f)), intensity(intensity) { }
    
    Light(const glm::vec3& direction, const glm::vec3& color, const glm::vec3& attenuation, float intensity)
    : direction(direction), color(color), attenuation(attenuation), intensity(intensity) { }
    
    inline void setColor(const glm::vec3& color) { this->color = color; }
    inline void setColor(glm::vec3&& color) noexcept { this->color = std::move(color); }
    inline glm::vec3 getColor() const { return this->color; }
    
    inline void setDirection(const glm::vec3& direction) { this->direction = direction; }
    inline void setDirection(glm::vec3&& direction) noexcept { this->direction = std::move(direction); }
    inline glm::vec3 getDirection() const { return this->direction; }
    
    inline void setAttenuation(const glm::vec3& attenuation) { this->attenuation = attenuation; }
    inline void setAttenuation(glm::vec3&& attenuation) noexcept { this->attenuation = std::move(attenuation); }
    inline glm::vec3 getAttenuation() const { return this->attenuation; }
    
    inline void setIntensity(float intensity) { this->intensity = intensity; }
    inline float getIntensity() const { return this->intensity; }
    
};

}

#endif
