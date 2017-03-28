// Renderable3D.h
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

#ifndef Renderable3D_h
#define Renderable3D_h

#include "Entity.h"
#include "Mesh.h"
#include "Vec3.h"

namespace arealGL {
    
class Renderable3D : public Entity {
public:
    const std::shared_ptr<Model> model;
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    float angle;
    
public:    
    Renderable3D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader)
    : Entity(shader), model(model), position(glm::vec3()), rotation(glm::vec3()), scale(glm::vec3(1.0f)), angle(0.0f) { }
    
    Renderable3D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, const glm::vec3& position, const Color& color)
    : Entity(shader, color), model(model), position(position), rotation(glm::vec3()), scale(glm::vec3(1.0f)), angle(0.0f) {
        execPosition();
    }
    
    Renderable3D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, glm::vec3&& position, Color&& color)
    : Entity(shader, std::move(color)), model(model), position(std::move(position)), rotation(glm::vec3()), scale(glm::vec3(1.0f)), angle(0.0f) {
        execPosition();
    }
    
    Renderable3D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, const glm::vec3& position, const glm::vec3& scale, const Color& color)
    : Entity(shader, color), model(model), position(position), rotation(glm::vec3()), scale(scale), angle(0.0f) {
        execPosition();
        execScale();
    }
    
    Renderable3D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, glm::vec3&& position, glm::vec3&& scale, Color&& color)
    : Entity(shader, std::move(color)), model(model), position(std::move(position)), rotation(glm::vec3()), scale(std::move(scale)), angle(0.0f) {
        execPosition();
        execScale();
    }
    
    Renderable3D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, const glm::vec3& position,
           const glm::vec3& rotation, const glm::vec3& scale, float angle, const Color& color)
    : Entity(shader, color), model(model), position(position), rotation(rotation), scale(scale), angle(angle) {
        execPosition();
        execRotation();
        execScale();
    }
    
    Renderable3D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, glm::vec3&& position,
           glm::vec3&& rotation, glm::vec3&& scale, float angle, Color&& color)
    : Entity(shader, std::move(color)), model(model), position(std::move(position)), rotation(std::move(rotation)), scale(std::move(scale)), angle(angle) {
        execPosition();
        execRotation();
        execScale();
    }
    
    
    inline void changePosition(float dx, float dy, float dz) { this->position += glm::vec3(dx, dy, dz); execPosition(); }
    inline void changePosition(const glm::vec3& dpos) { this->position += dpos; execPosition(); }
    inline void changeRotation(float drx, float dry, float drz) { this->rotation += glm::vec3(drx, dry, drz); execRotation(); }
    inline void changeRotation(const glm::vec3& drota) { this->rotation += drota; execRotation(); }
    inline void changeScale(float dsx, float dsy, float dsz) { this->scale += glm::vec3(dsx, dsy, dsz); execScale(); }
    inline void changeScale(const glm::vec3& dscale) { this->scale += dscale; execScale(); }
    inline void changeAngle(float angle) { this->angle += angle; execRotation(); }
    
    inline void setPosition(float x, float y, float z) { this->position = glm::vec3(x, y, z); execPosition(); }
    inline void setPosition(const glm::vec3& position) { this->position = position; execPosition(); }
    inline void setPosition(glm::vec3&& position) noexcept { this->position = std::move(position); execPosition(); }
    inline void setRotation(float x, float y, float z) { this->rotation = glm::vec3(x, y, z); execRotation(); }
    inline void setRotation(const glm::vec3& rotation) { this->rotation = rotation; execRotation(); }
    inline void setRotation(glm::vec3&& rotation) noexcept { this->rotation = std::move(rotation); execRotation(); }
    inline void setScale(float x, float y, float z) { this->scale = glm::vec3(x, y, z); execScale(); }
    inline void setScale(const glm::vec3& scale) { this->scale = scale; execScale(); }
    inline void setScale(glm::vec3&& scale) noexcept { this->scale = std::move(scale); execScale(); }
    inline void setAngle(float angle) { this->angle = angle; execRotation(); }
    
    inline glm::vec3 getPosition() const { return this->position; }
    inline glm::vec3 getRotation() const { return this->rotation; }
    inline glm::vec3 getScale() const { return this->scale; }
    inline float getAngle() const { return this->angle; }
    
private:
    inline void execScale() { this->transform = glm::scale(this->transform, this->scale); }
    inline void execPosition() { this->transform = glm::translate(this->transform, this->position); }
    inline void execRotation() { this->transform = glm::rotate(this->transform, this->angle, this->rotation); }
    
};
    
}

#endif
