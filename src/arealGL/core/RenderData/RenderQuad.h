#ifndef RenderQuad_h
#define RenderQuad_h

// ---------------------------------------------------------
// CAN BE REPLACED, AS SOON AS 2D RENDER OBJECTS ARE A THING
// ---------------------------------------------------------

namespace arealGL {
    
class RenderQuad;
typedef std::vector<RenderQuad> Quads;
    
    
class RenderQuad {
private:
    const std::vector<float> quadVertices {
        // Positions   // TexCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
    };
    
    uint quadVAO, quadVBO;
    
public:
    RenderQuad() {
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * quadVertices.size()), &quadVertices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
        glBindVertexArray(0);
    }
    
    inline uint getVAO() const { return this->quadVAO; }
};
    
}

#endif
