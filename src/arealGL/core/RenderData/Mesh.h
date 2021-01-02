#ifndef Mesh_h
#define Mesh_h

#include <string>
#include <sstream>
#include <vector>

#include "..\..\Types.h"
#include "..\..\Config.h"
#include "..\Entities\Camera.h"
#include "..\RenderData\Texture.h"

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>

namespace arealGL {
    
class Mesh;
typedef std::vector<Mesh> Model;
    
    
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec2 texcoords;
    
    Vertex() {}
    Vertex(const Vertex& rhs) = default;
    Vertex(Vertex&& rhs) noexcept = default;
    Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texcoords)
    : position(position), normal(normal), texcoords(texcoords) { }
    Vertex(glm::vec3&& position, glm::vec3&& normal, glm::vec2&& texcoords) noexcept
    : position(std::move(position)), normal(std::move(normal)), texcoords(std::move(texcoords)) { }
};


class Mesh {
public:
    const std::vector<Vertex> vertices;
    const std::vector<uint> indices;
    const Texture texture;
    const std::string directory;
private:
    uint VAO = 0, VBO = 0, EBO = 0;
    
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint>& indices,
         const Texture& texture, const std::string& directory)
    : vertices(vertices), indices(indices), texture(texture), directory(directory) {
        // Create the buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        // Load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, (sizeof(Vertex) * vertices.size()), &vertices[0], GL_STATIC_DRAW);
        // Set the vertex attribute pointers
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, normal));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, tangent));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, texcoords));
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(uint) * indices.size()), &indices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    inline void BindBuffer() const {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }
    
    inline void UnbindBuffer() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
};
    
}

#endif
