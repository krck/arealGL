// BatchRenderer.h
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

#ifndef BatchRenderer_h
#define BatchRenderer_h

#include "Renderer.h"

// --------------------------------------
// ----- BATCHED BY SHADERS FOR NOW -----
// --------------------------------------

namespace arealGL {

class BatchRenderer : public Renderer {
private:
    std::map<std::shared_ptr<Shader>, std::vector<std::shared_ptr<Entity>>> renderables;
    
public:
    void submit(std::shared_ptr<Entity> entity) {
        if(renderables.count(entity->shader) == 0) {
            std::vector<std::shared_ptr<Entity>> tmp { entity };
            renderables.insert(std::make_pair(entity->shader, tmp));
        } else {
            renderables[entity->shader].push_back(entity);
        }
    }
    
    void render(const Camera& cam, const glm::mat4& projection) {
        for(const auto& renderpair : this->renderables) {
            auto shader = renderpair.first;
            shader->bind();
            for(auto entity : renderpair.second) {
                shader->setLightUniforms();
                shader->setModelUniforms(entity->getTransformation(), cam.getView(), projection, entity->getColor());
                for(const Mesh& mesh : entity->model->meshes) {
                    // Activate and bind all the textures
                    for(auto i = 0; i < mesh.textures.size(); i++) {
                        glActiveTexture(GL_TEXTURE0 + i);
                        glBindTexture(GL_TEXTURE_2D, mesh.textures[i].texID);
                        shader->setMaterialUniforms(mesh.textures[i].spectralReflectivity, mesh.textures[i].shineDamper);
                    }
                    // Get the show on the road
                    glBindVertexArray(mesh.getVAO());
                    glDrawElements(GL_TRIANGLES, (int)mesh.indices.size(), GL_UNSIGNED_INT, nullptr);
                    glBindVertexArray(0);
                    // Set everything back to defaults
                    for (auto i = 0; i < mesh.textures.size(); i++){
                        glActiveTexture(GL_TEXTURE0 + i);
                        glBindTexture(GL_TEXTURE_2D, 0);
                    }
                }
            }
            shader->unbind();
        }
        renderables.clear();
    }
    
};
    
}

#endif
