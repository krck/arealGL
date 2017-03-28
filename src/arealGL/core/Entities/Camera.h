// Camera.h
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

#ifndef Camera_h
#define Camera_h

#include <vec3.hpp>
#include <gtx/transform.hpp>

#include "math.h"

namespace arealGL {

enum class MoveDirection { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

class Camera {
private:
    const glm::vec3 worldUp;
    glm::vec3 position;
    glm::vec3 front, up, right;
    float pitch, yaw;
    float lastX, lastY;
    float mouseSens, moveSpeed;
    
public:
    Camera() : worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), lastX(0.0f), lastY(0.0f) {
        position = glm::vec3();
        front = glm::vec3(0.0f, 0.0f, -1.0f);
        up = glm::vec3(0.0f, 1.0f, 0.0f);
        right = glm::vec3();
        pitch = 0.0f;
        yaw = -90.0f;
        mouseSens = 0.5f;
        moveSpeed = 3.0f;
        
    }
    
    Camera(const glm::vec3& pos, const glm::vec3& front, const glm::vec3& up) : worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), lastX(0.0f), lastY(0.0f) {
        this->position = pos;
        this->front = front;
        this->up = up;
        right = glm::vec3();
        pitch = 0.0f;
        yaw = -90.0f;
        mouseSens = 0.5f;
        moveSpeed = 3.0f;
    }
    
    
    inline void changePosition(MoveDirection dir, float deltaTime) {
        const float velocity = moveSpeed * deltaTime;
        switch(dir) {
            case MoveDirection::FORWARD:    position += (front * velocity);   break;
            case MoveDirection::BACKWARD:   position -= (front * velocity);   break;
            case MoveDirection::RIGHT:      position += (right * velocity);   break;
            case MoveDirection::LEFT:       position -= (right * velocity);   break;
            case MoveDirection::UP:         position += (up * velocity);      break;
            case MoveDirection::DOWN:       position -= (up * velocity);      break;
        }
    }
    
    // Processes input received from the mouse input system
    void changeLineOfSight(const int xpos, const int ypos, bool constrain) {
        const float xoffset = (xpos - lastX) * mouseSens;
        const float yoffset = (lastY - ypos) * mouseSens;
        lastX = xpos;
        lastY = ypos;
        yaw   += xoffset;
        pitch += yoffset;
        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrain) {
            if (pitch > 89.0f) { pitch = 89.0f; }
            if (pitch < -89.0f) { pitch = -89.0f; }
        }
        // Update Front, Right and Up Vectors using the updated Eular angles
        updateCamVecs();
    }
    
    
    inline glm::mat4 getView() const { return glm::lookAt(this->position, (this->position + this->front), this->up);
    }
    
    inline void setPosition(const glm::vec3& position) { this->position = position; }
    inline void setPosition(glm::vec3&& position) noexcept { this->position = std::move(position); }
    inline glm::vec3 getPosition() const { return this->position; }
    
    inline void setMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }
    inline float getMoveSpeed() const { return this->moveSpeed; }
    inline void setMouseSensitivity(float mouseSensitivity) { this->mouseSens = mouseSensitivity; }
    inline float getMouseSensitivity() const { return this->mouseSens; }
    
    inline glm::vec3 getLeft() const { return glm::normalize(glm::cross(up, front)); }
    inline glm::vec3 getRight() const { return glm::normalize(glm::cross(front, up)); }
    
    
private:
    inline float radians(float degrees) const { return (degrees * 0.0174533f); }
    
    void updateCamVecs() {
        glm::vec3 tmp;
        tmp.x = cos(radians(this->yaw)) * cos(radians(this->pitch));
        tmp.y = sin(radians(this->pitch));
        tmp.z = sin(radians(this->yaw)) * cos(radians(this->pitch));
        this->front = glm::normalize(tmp);
        this->right = glm::normalize(glm::cross(this->front, this->worldUp));
        this->up = glm::normalize(glm::cross(this->right, this->front));
    }
    
};
    
}

#endif
