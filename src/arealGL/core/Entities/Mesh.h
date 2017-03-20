// Mesh.h
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

#ifndef Mesh_h
#define Mesh_h

#include <string>
#include <sstream>
#include <vector>

#include "Types.h"
#include "Config.h"
#include "Camera.h"

#include <vec2.hpp>
#include <vec3.hpp>
#include "Importer.hpp"

namespace arealGL {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoords;
};

// Doubles as Material struct
struct Texture {
    uint texID;
    std::string type;
    aiString path;
    // Material values
    float ambientReflectivity;
    float spectralReflectivity;
    float diffuseReflectivity;
    float shineDamper = 10.0f;
};

class Mesh {
public:
    const std::vector<Vertex> vertices;
    const std::vector<uint> indices;
    const std::vector<Texture> textures;
    const std::string directory;
private:
    uint VAO = 0, VBO = 0, EBO = 0;
    
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint>& indices,
         const std::vector<Texture>& textures, const std::string& directory)
    : vertices(vertices), indices(indices), textures(textures), directory(directory) {
        // Create the buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        // Load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, (sizeof(Vertex) * vertices.size()), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(uint) * indices.size()), &indices[0], GL_STATIC_DRAW);
        // Set the vertex attribute pointers
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, normal));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, texcoords));
        glBindVertexArray(0);
    }
    
    inline uint getVAO() const { return this->VAO; }
    
};
    
}

#endif
