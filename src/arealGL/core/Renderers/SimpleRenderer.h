// SimpleRenderer.h
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

#ifndef SimpleRenderer_h
#define SimpleRenderer_h

#include "Renderer.h"

namespace arealGL {

class SimpleRenderer : public Renderer {
private:
    std::queue<std::shared_ptr<Entity>> renderables;
    
public:
    void submit(std::shared_ptr<Entity> entity) {
        renderables.push(entity);
    }
    
    void render(const Camera& cam, const glm::mat4& projection) {
        while(!renderables.empty()) {
            auto entity = renderables.front();
            entity->shader->bind();
            entity->shader->setModelUniforms(entity->getTransformation(), cam.getView(), projection, entity->getColor());
            entity->shader->setLightUniforms();
            // render each mesh of the model
            for(const Mesh& mesh : entity->model->meshes) {
                // Activate and bind all the textures
                mesh.texture.bindTexture();
                mesh.texture.bindNormalMap();
                entity->shader->setMaterialUniforms(mesh.texture.getMaterial().spectralReflectivity, mesh.texture.getMaterial().shineDamper);
                // Get the show on the road
                glBindVertexArray(mesh.getVAO());
                glDrawElements(GL_TRIANGLES, (int)mesh.indices.size(), GL_UNSIGNED_INT, nullptr);
                glBindVertexArray(0);
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
