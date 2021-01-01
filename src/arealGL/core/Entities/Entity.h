#ifndef Entity_h
#define Entity_h

#include <memory>

#include "..\Shaders\Shader.h"
#include "..\Misc\Color.h"
#include <glm\mat4x4.hpp>

namespace arealGL {

class Entity {
public:
    const std::shared_ptr<Shader> shader;
protected:
    glm::mat4 transform;
    Color color;
    
public:
    Entity(std::shared_ptr<Shader> shader)
    : shader(shader), transform(glm::mat4()), color(Color()) { }
    
    Entity(std::shared_ptr<Shader> shader, const Color& color)
    : shader(shader), transform(glm::mat4()), color(color) { }
    
    Entity(std::shared_ptr<Shader> shader, Color&& color)
    : shader(shader), transform(glm::mat4()), color(std::move(color)) { }
    
    inline void setColor(const Color& color) { this->color = color; }
    inline void setColor(Color&& color) noexcept { this->color = std::move(color); }
    inline Color getColor() const { return this->color; }
    
    inline glm::mat4 getTransformation() const { return this->transform; }
    
};
    
}

#endif
