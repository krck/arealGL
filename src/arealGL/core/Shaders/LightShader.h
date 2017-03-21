// LightShader.h
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

#ifndef LightShader_h
#define LightShader_h

#include "Shader.h"

namespace arealGL {

class LightShader : public Shader {
private:
    std::vector<Light> lights;
    
public:
    LightShader(const std::vector<Light>& lights) : Shader(SHADER_BASEPATH + "lightShader.vert", SHADER_BASEPATH + "lightShader.frag", true) {
        this->lights = lights;
        // Set the Attributes
        setAttribute(0, "position");
        setAttribute(1, "normal");
        setAttribute(2, "texCoords");
        // Set the Uniforms
        setUniform("u_transform");
        setUniform("u_projection");
        setUniform("u_view");
        setUniform("u_objectColor");
        setUniform("u_spectralReflectivity");
        setUniform("u_shineDamper");
        for(int i = 0; i < MAX_LIGHTS; i++) {
            setUniform("u_lightPosition[" + std::to_string(i) + "]");
            setUniform("u_lightColor[" + std::to_string(i) + "]");
            setUniform("u_intensity[" + std::to_string(i) + "]");
            setUniform("u_attenuation[" + std::to_string(i) + "]");
        }
    }
    
    void setModelUniforms(const glm::mat4& transform, const glm::mat4& view, const glm::mat4& projection, const Color& color) const override {
        uniformVec3("u_objectColor", color.getRGB());
        uniformMat4("u_transform", transform);
        uniformMat4("u_projection", projection);
        uniformMat4("u_view", view);
    }
    
    void setMaterialUniforms(float spectralReflectivity, float shineDamper) const override {
        uniformFloat("u_spectralReflectivity", spectralReflectivity);
        uniformFloat("u_shineDamper", shineDamper);
    }
    
    void setLightUniforms() const override {
        for(int i = 0; i < MAX_LIGHTS; i++) {
            if(i < lights.size()) {
                uniformVec3("u_lightPosition[" + std::to_string(i) + "]", lights[i].getDirection());
                uniformVec3("u_lightColor[" + std::to_string(i) + "]", lights[i].getColor().getRGB());
                uniformFloat("u_intensity[" + std::to_string(i) + "]", lights[i].getIntensity());
                uniformVec3("u_attenuation[" + std::to_string(i) + "]", lights[i].getAttenuation());
            } else {
                uniformVec3("u_lightPosition[" + std::to_string(i) + "]", glm::vec3(0.0f));
                uniformVec3("u_lightColor[" + std::to_string(i) + "]", glm::vec3(0.0f));
                uniformFloat("u_intensity[" + std::to_string(i) + "]", 1.0f);
                uniformVec3("u_attenuation[" + std::to_string(i) + "]", glm::vec3(1.0f, 0.0f, 0.0f));
            }
        }
    }
    
    inline void setLights(const std::vector<Light>& lights) { this->lights = lights; }
    inline void setLights(std::vector<Light>&& lights) noexcept { this->lights = std::move(lights); }
    
    inline void addLight(const Light& light) { this->lights.push_back(light); }
    inline void addLight(Light&& light) noexcept { this->lights.push_back(light); }
    
};

}

#endif
