#ifndef Light_h
#define Light_h

#include "..\Misc\Color.h"
#include <glm\vec3.hpp>

namespace arealGL {

class Light {
private:
    glm::vec3 direction;
    Color color;
    glm::vec3 attenuation;      // Three values to define point-light-ness
    float intensity;
    
public:
    Light(const glm::vec3& direction, const Color& color, float intensity)
    : direction(direction), color(color), attenuation(glm::vec3(1.0f, 0.0f, 0.0f)), intensity(intensity) { }
    
    Light(const glm::vec3& direction, const Color& color, const glm::vec3& attenuation, float intensity)
    : direction(direction), color(color), attenuation(attenuation), intensity(intensity) { }
    
    inline void setColor(const Color& color) { this->color = color; }
    inline void setColor(Color&& color) noexcept { this->color = std::move(color); }
    inline Color getColor() const { return this->color; }
    
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
