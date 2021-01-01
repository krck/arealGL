#ifndef BasicShader_h
#define BasicShader_h

#include "Shader.h"

namespace arealGL {

class BasicShader : public Shader {
public:
    BasicShader() : Shader(SHADER_BASEPATH + "basicShader.vert", SHADER_BASEPATH + "basicShader.frag", true) {
        // Set the Attributes
        setAttribute(0, "position");
        setAttribute(1, "normal");
        setAttribute(2, "tangent");
        setAttribute(3, "texCoords");
        // Textures
        setUniform("texture_diffuse");
        // Set the Uniforms
        setUniform("u_transform");
        setUniform("u_projection");
        setUniform("u_view");
        setUniform("u_objectColor");
    }
    
    void setModelUniforms(const glm::mat4& transform, const glm::mat4& view, const glm::mat4& projection, const Color& color) const override {
        uniformVec3("u_objectColor", color.getRGB());
        uniformMat4("u_transform", transform);
        uniformMat4("u_projection", projection);
        uniformMat4("u_view", view);
    }
    
    void setMaterialUniforms(float spectralReflectivity, float shineDamper) const override {
        // Only set the Texture samplers
        uniformInt("texture_diffuse", 0);
    }
    
};
    
}

#endif
