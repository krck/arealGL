#ifndef LightNoTexShader_h
#define LightNoTexShader_h

#include "Shader.h"

namespace arealGL {

class LightNoTexShader : public Shader {
private:
    std::vector<Light> lights;
    
public:
    LightNoTexShader(const std::vector<Light>& lights) : Shader(SHADER_BASEPATH + "lightNoTexShader.vert", SHADER_BASEPATH + "lightNoTexShader.frag", true) {
        this->lights = lights;
        // Set the Attributes
        setAttribute(0, "position");
        setAttribute(1, "normal");
        setAttribute(2, "tangent");
        setAttribute(3, "texCoords");
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
            } else {
                uniformVec3("u_lightPosition[" + std::to_string(i) + "]", glm::vec3(0.0f));
                uniformVec3("u_lightColor[" + std::to_string(i) + "]", glm::vec3(0.0f));
                uniformFloat("u_intensity[" + std::to_string(i) + "]", 1.0f);
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
