//  Renderable2D.h
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

#ifndef Renderable2D_h
#define Renderable2D_h

#include "Entity.h"
#include "RenderQuad.h"
#include "Vec2.h"

namespace arealGL {
    
class Renderable2D : public Entity {
public:
    const std::shared_ptr<Quads> quads;
private:
    glm::vec2 position;
    glm::vec2 scale;
    
public:
    Renderable2D(std::shared_ptr<Quads> quads, std::shared_ptr<Shader> shader)
    : Entity(shader), quads(quads), position(glm::vec2()), scale(glm::vec2(1.0f)) { }
    
    Renderable2D(std::shared_ptr<Quads> quads, std::shared_ptr<Shader> shader, const glm::vec2& position, const Color& color)
    : Entity(shader, color), quads(quads), position(position), scale(glm::vec2(1.0f)) {
        execPosition();
    }
    
    Renderable2D(std::shared_ptr<Quads> quads, std::shared_ptr<Shader> shader, glm::vec2&& position, Color&& color)
    : Entity(shader, std::move(color)), quads(quads), position(std::move(position)), scale(glm::vec2(1.0f)) {
        execPosition();
    }
    
    Renderable2D(std::shared_ptr<Quads> quads, std::shared_ptr<Shader> shader, const glm::vec2& position, const glm::vec2& scale, const Color& color)
    : Entity(shader, color), quads(quads), position(position), scale(scale) {
        execPosition();
        execScale();
    }
    
    Renderable2D(std::shared_ptr<Quads> quads, std::shared_ptr<Shader> shader, glm::vec2&& position, glm::vec2&& scale, Color&& color)
    : Entity(shader, std::move(color)), quads(quads), position(std::move(position)), scale(std::move(scale)) {
        execPosition();
        execScale();
    }
    
    inline void changePosition(float dx, float dy) { this->position += glm::vec2(dx, dy); execPosition(); }
    inline void changePosition(const glm::vec2& dpos) { this->position += dpos; execPosition(); }
    inline void changeScale(float dsx, float dsy) { this->scale += glm::vec2(dsx, dsy); execScale(); }
    inline void changeScale(const glm::vec2& dscale) { this->scale += dscale; execScale(); }
    
    inline void setPosition(float x, float y) { this->position = glm::vec2(x, y); execPosition(); }
    inline void setPosition(const glm::vec2& position) { this->position = position; execPosition(); }
    inline void setPosition(glm::vec2&& position) noexcept { this->position = std::move(position); execPosition(); }
    inline void setScale(float x, float y) { this->scale = glm::vec2(x, y); execScale(); }
    inline void setScale(const glm::vec2& scale) { this->scale = scale; execScale(); }
    inline void setScale(glm::vec2&& scale) noexcept { this->scale = std::move(scale); execScale(); }
    
    inline glm::vec2 getPosition() const { return this->position; }
    inline glm::vec2 getScale() const { return this->scale; }
    
private:
    inline void execScale() { /* ... */ }
    inline void execPosition() { /* ... */ }
    
};
    
}

#endif
