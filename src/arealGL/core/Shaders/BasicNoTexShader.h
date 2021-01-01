#ifndef BasicNoTexShader_h
#define BasicNoTexShader_h

#include "Shader.h"

namespace arealGL {

class BasicNoTexShader : public Shader {
public:
    BasicNoTexShader() : Shader(SHADER_BASEPATH + "basicNoTexShader.vert", SHADER_BASEPATH + "basicNoTexShader.frag", true) {
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
    }
    
    void setModelUniforms(const glm::mat4& transform, const glm::mat4& view, const glm::mat4& projection, const Color& color) const override {
        uniformVec3("u_objectColor", color.getRGB());
        uniformMat4("u_transform", transform);
        uniformMat4("u_projection", projection);
        uniformMat4("u_view", view);
    }
    
};
    
}

#endif
