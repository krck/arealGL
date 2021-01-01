#ifndef RenderableGUI_h
#define RenderableGUI_h

#include "Entity.h"
#include "..\RenderData\RenderQuad.h"

namespace arealGL {
    
class RenderableGUI : public Entity {
public:
    const std::shared_ptr<RenderQuad> quad;
private:
    glm::vec2 position;
    glm::vec2 scale;
    
public:
    RenderableGUI(std::shared_ptr<RenderQuad> quad, std::shared_ptr<Shader> shader)
    : Entity(shader), quad(quad), position(glm::vec2()), scale(glm::vec2(1.0f)) { }
    
    RenderableGUI(std::shared_ptr<RenderQuad> quad, std::shared_ptr<Shader> shader, const glm::vec2& position, const Color& color)
    : Entity(shader, color), quad(quad), position(position), scale(glm::vec2(1.0f)) {
        execPosition();
    }
    
    RenderableGUI(std::shared_ptr<RenderQuad> quad, std::shared_ptr<Shader> shader, glm::vec2&& position, Color&& color)
    : Entity(shader, std::move(color)), quad(quad), position(std::move(position)), scale(glm::vec2(1.0f)) {
        execPosition();
    }
    
    RenderableGUI(std::shared_ptr<RenderQuad> quad, std::shared_ptr<Shader> shader, const glm::vec2& position, const glm::vec2& scale, const Color& color)
    : Entity(shader, color), quad(quad), position(position), scale(scale) {
        execPosition();
        execScale();
    }
    
    RenderableGUI(std::shared_ptr<RenderQuad> quad, std::shared_ptr<Shader> shader, glm::vec2&& position, glm::vec2&& scale, Color&& color)
    : Entity(shader, std::move(color)), quad(quad), position(std::move(position)), scale(std::move(scale)) {
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
