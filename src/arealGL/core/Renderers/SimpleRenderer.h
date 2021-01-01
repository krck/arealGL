#ifndef SimpleRenderer_h
#define SimpleRenderer_h

#include "Renderer.h"

namespace arealGL {

class SimpleRenderer : public Renderer {
private:
    std::queue<std::shared_ptr<Renderable3D>> renderables;
    
public:
    void submit(std::shared_ptr<Renderable3D> entity) {
        renderables.push(entity);
    }
    
    void render(const Camera& cam, const glm::mat4& projection) {
        while(!renderables.empty()) {
            auto entity = renderables.front();
            entity->shader->bind();
            entity->shader->setModelUniforms(entity->getTransformation(), cam.getView(), projection, entity->getColor());
            entity->shader->setLightUniforms();
            // render each mesh of the model
            for(const Mesh& mesh : *entity->model) {
                // Activate and bind all the textures
                mesh.texture.bindTexture();
                mesh.texture.bindNormalMap();
                entity->shader->setMaterialUniforms(mesh.texture.getMaterial().spectralReflectivity, mesh.texture.getMaterial().shineDamper);
                // Get the show on the road
                mesh.BindBuffer();
                glDrawElements(GL_TRIANGLES, (int)mesh.indices.size(), GL_UNSIGNED_INT, nullptr);
                mesh.UnbindBuffer();
                // Set everything back to defaults
                mesh.texture.unbindNormalMap();
                mesh.texture.unbindTexture();
            }
            entity->shader->unbind();
            renderables.pop();
        }
    }
    
    
    void renderFBOtoDefaultScreen(const Shader& shader, const RenderQuad& renderQuad, const FrameBuffer& fbo) {
        shader.bind();
        glBindVertexArray(renderQuad.getVAO());
        glBindTexture(GL_TEXTURE_2D, fbo.getTextureColorbuffer());
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        shader.unbind();
    }
    
};

}

#endif
