#ifndef FboShader_h
#define FboShader_h

#include "Shader.h"

namespace arealGL {
    
class FboShader : public Shader {
public:
    FboShader() : Shader(SHADER_BASEPATH + "fboShader.vert", SHADER_BASEPATH + "fboShader.frag", true) {
        // Set the Attributes
        setAttribute(0, "position");
        setAttribute(1, "texCoords");
    }
    
};
    
}

#endif
