// Entity.h
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

#ifndef Entity_h
#define Entity_h

#include <memory>

#include "Model.h"
#include "Shader.h"
#include "Color.h"
#include <vec3.hpp>
#include <mat4x4.hpp>

namespace arealGL {

class Entity {
public:
    const std::shared_ptr<Shader> shader;
    const std::shared_ptr<Model> model;
private:
    // Entity transformation (could also be put in the shader program)
    glm::mat4 transform = glm::mat4();
    glm::vec3 position, rotation;
    float angle, scale;
    Color color;
    
public:
    Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader)
    : model(model), shader(shader), position(glm::vec3()), rotation(glm::vec3()), angle(0.0f), scale(1.0f), color(Color()) { }
    
    Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, const glm::vec3& position, const Color& color)
    : model(model), shader(shader), position(position), rotation(glm::vec3()), angle(0.0f), scale(1.0f), color(color) {
        execPosition();
    }
    
    Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, glm::vec3&& position, Color&& color)
    : model(model), shader(shader), position(std::move(position)), rotation(glm::vec3()), angle(0.0f), scale(1.0f), color(std::move(color)) {
        execPosition();
    }
    
    Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, const glm::vec3& position, float scale, const Color& color)
    : model(model), shader(shader), position(position), rotation(glm::vec3()), angle(0.0f), scale(scale), color((color)) {
        execPosition();
        execScale();
    }
    
    Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, glm::vec3&& position, float scale, Color&& color)
    : model(model), shader(shader), position(std::move(position)), rotation(glm::vec3()), angle(0.0f), scale(scale), color(std::move(color)) {
        execPosition();
        execScale();
    }
    
    Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, const glm::vec3& position,
           const glm::vec3& rotation, float angle, float scale, const Color& color)
    : model(model), shader(shader), position(position), rotation(rotation), angle(angle), scale(scale), color(color) {
        execPosition();
        execRotation();
        execScale();
    }
    
    Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, glm::vec3&& position,
           glm::vec3&& rotation, float angle, float scale, Color&& color)
    : model(model), shader(shader), position(std::move(position)), rotation(std::move(rotation)),
    angle(0.0f), scale(scale), color(std::move(color)) {
        execPosition();
        execRotation();
        execScale();
    }
    
    
    inline void changePosition(float dx, float dy, float dz) { this->position += glm::vec3(dx, dy, dz); execPosition(); }
    inline void changePosition(const glm::vec3& dpos) { this->position += dpos; execPosition(); }
    inline void changeRotation(float drx, float dry, float drz) { this->rotation += glm::vec3(drx, dry, drz); execRotation(); }
    inline void changeRotation(const glm::vec3& drota) { this->rotation += drota; execRotation(); }
    inline void changeAngle(float angle) { this->angle += angle; execRotation(); }
    inline void changeScale(float scale) { this->scale += scale; execScale(); }
    
    inline void setPosition(float x, float y, float z) { this->position = glm::vec3(x, y, z); execPosition(); }
    inline void setPosition(const glm::vec3& position) { this->position = position; execPosition(); }
    inline void setPosition(glm::vec3&& position) noexcept { this->position = std::move(position); execPosition(); }
    inline void setRotation(float x, float y, float z) { this->rotation = glm::vec3(x, y, z); execRotation(); }
    inline void setRotation(const glm::vec3& rotation) { this->rotation = rotation; execRotation(); }
    inline void setRotation(glm::vec3&& rotation) noexcept { this->rotation = std::move(rotation); execRotation(); }
    inline void setAngle(float angle) { this->angle = angle; execRotation(); }
    inline void setScale(float scale) { this->scale = scale; execScale(); }
    
    inline glm::vec3 getPosition() const { return this->position; }
    inline glm::vec3 getRotation() const { return this->rotation; }
    inline float getAngle() const { return this->angle; }
    inline float getScale() const { return this->scale; }
    
    inline void setColor(const Color& color) { this->color = color; }
    inline void setColor(Color&& color) noexcept { this->color = std::move(color); }
    inline Color getColor() const { return this->color; }
    
    inline glm::mat4 getTransformation() const { return this->transform; }
    
private:
    inline void execScale() { this->transform = glm::scale(this->transform, glm::vec3(this->scale)); }
    inline void execPosition() { this->transform = glm::translate(this->transform, this->position); }
    inline void execRotation() { this->transform = glm::rotate(this->transform, this->angle, this->rotation); }
    
};
    
}

#endif
