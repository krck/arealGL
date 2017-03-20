// Loader.h
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

#ifndef Loader_h
#define Loader_h

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <memory>

#include "Model.h"
#include "Types.h"
#include "Config.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace arealGL {

class Loader {
private:
    std::vector<Texture> textures_loaded;
    
public:
    // Load simple, untextured mesh from an .obj File
    std::shared_ptr<Model> LoadSimpleModelFromFile(const std::string& path) {
        std::vector<Mesh> meshes;
        std::vector<Vertex> tmpVertices;
        std::vector<uint> tmpIndices;
        // Parse the .obj file data
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
        if(scene != nullptr) {
            // Get the first mesh
            const aiMesh* mesh = scene->mMeshes[0];
            // Walk through each of the mesh's vertices
            for(uint i = 0; i < mesh->mNumVertices; i++) {
                Vertex tmpvec;
                tmpvec.position.x = mesh->mVertices[i].x;
                tmpvec.position.y = mesh->mVertices[i].y;
                tmpvec.position.z = mesh->mVertices[i].z;
                tmpvec.normal.x = mesh->mNormals[i].x;
                tmpvec.normal.y = mesh->mNormals[i].y;
                tmpvec.normal.z = mesh->mNormals[i].z;
                // default values as texture coords
                tmpvec.texcoords = glm::vec2(0.0f);
                tmpVertices.push_back(tmpvec);
            }
            // Now retrieve the corresponding vertex indices from the meshs faces
            for (uint i = 0; i < mesh->mNumFaces; i++) {
                aiFace face = mesh->mFaces[i];
                for (uint j = 0; j < face.mNumIndices; j++) {
                    tmpIndices.push_back(face.mIndices[j]);
                }
            }
        }
        meshes.push_back(Mesh(tmpVertices, tmpIndices, std::vector<Texture>(), (path.substr(0, path.rfind('/')))));
        return std::make_shared<Model>(meshes);
    }
    
    
    // Load complex Model: multiple Files, multiple Textures and Materials
    std::shared_ptr<Model> LoadComplexModelFromFile(const std::string& path) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
        if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout <<"ERROR::ASSIMP:: " <<importer.GetErrorString() <<std::endl;
            return nullptr;
        }
        // Retrieve the directory path of the filepath
        const std::string directory = path.substr(0, path.find_last_of('/'));
        std::vector<Mesh> tmpMeshes;
        // Process ASSIMP nodes recursively
        this->processNode(scene->mRootNode, scene, directory, tmpMeshes);
        // Create the loaded Model
        return std::make_shared<Model>(tmpMeshes);
    }
    
private:
    void processNode(aiNode* node, const aiScene* scene, const std::string& dir, std::vector<Mesh>& meshes) {
        // Process each mesh located at the current node
        for (uint i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(this->processMesh(mesh, scene, dir));
        }
        // After processing the meshes recursively process the childnodes
        for (uint i = 0; i < node->mNumChildren; i++) {
            this->processNode(node->mChildren[i], scene, dir, meshes);
        }
    }
    
    Mesh processMesh(aiMesh *mesh, const aiScene *scene, const std::string& dir) {
        std::vector<Vertex> tmpVertices;
        std::vector<uint> tmpIndices;
        std::vector<Texture> tmpTextures;
        
        // Get all of the mesh's vertices
        for (uint i = 0; i < mesh->mNumVertices; i++) {
            Vertex tmpvec;
            tmpvec.position.x = mesh->mVertices[i].x;
            tmpvec.position.y = mesh->mVertices[i].y;
            tmpvec.position.z = mesh->mVertices[i].z;
            tmpvec.normal.x = mesh->mNormals[i].x;
            tmpvec.normal.y = mesh->mNormals[i].y;
            tmpvec.normal.z = mesh->mNormals[i].z;
            if(mesh->mTextureCoords[0]) {
                tmpvec.texcoords.x = mesh->mTextureCoords[0][i].x;
                tmpvec.texcoords.y = mesh->mTextureCoords[0][i].y;
            } else {
                tmpvec.texcoords = glm::vec2(0.0f, 0.0f);
            }
            tmpVertices.push_back(tmpvec);
        }
        // Get all the the mesh's indices (by faces / triangles).
        for (uint i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (uint j = 0; j < face.mNumIndices; j++) {
                tmpIndices.push_back(face.mIndices[j]);
            }
        }
        // Process materials
        if(mesh->mMaterialIndex >= 0) {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            // We assume a convention for sampler names in the shaders.
            // Diffuse: texture_diffuseN
            // Specular: texture_specularN
            // Normal: texture_normalN
            // 1. Diffuse maps
            std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", dir);
            tmpTextures.insert(tmpTextures.end(), diffuseMaps.begin(), diffuseMaps.end());
            // 2. Specular maps
            std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", dir);
            tmpTextures.insert(tmpTextures.end(), specularMaps.begin(), specularMaps.end());
        }
        
        // Return a mesh object created from the extracted mesh data
        return Mesh(tmpVertices, tmpIndices, tmpTextures, dir);
    }
    
    // Process material textures of a given type and loads the textures if they're not loaded yet.
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, const std::string& dir) {
        std::vector<Texture> tmpTextures;
        
        for (uint i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);
            
            bool skip = false;
            
            for (GLuint j = 0; j < textures_loaded.size(); j++) {
                if(textures_loaded[j].path == str) {
                    tmpTextures.push_back(textures_loaded[j]);
                    skip = true;
                    break;
                }
            }
            // If texture hasn't been loaded already, load it
            if(!skip) {
                Texture tmpTex;
                tmpTex.texID = LoadTextureFromFile(str.C_Str(), dir);
                tmpTex.type = typeName;
                tmpTex.path = str;
                // Get the material reflection values (but store them as a single float)
                aiColor3D color (0.f,0.f,0.f);
                mat->Get(AI_MATKEY_COLOR_DIFFUSE,color);
                tmpTex.diffuseReflectivity = (color.r + color.g + color.b) / 3.0f;
                mat->Get(AI_MATKEY_COLOR_SPECULAR,color);
                tmpTex.spectralReflectivity = (color.r + color.g + color.b) / 3.0f;
                mat->Get(AI_MATKEY_COLOR_AMBIENT,color);
                tmpTex.ambientReflectivity = (color.r + color.g + color.b) / 3.0f;
                // Store it to ensure we won't unnecesery load duplicate textures
                tmpTextures.push_back(tmpTex);
                this->textures_loaded.push_back(tmpTex);
            }
        }
        return tmpTextures;
    }
    
    
    uint LoadTextureFromFile(const char* name, const std::string& directory) const {
        //Generate texture ID and load texture data
        const std::string filename = directory + '/' + std::string(name);
        uint textureID = 0;
        glGenTextures(1, &textureID);
        // get the texture data with the stb image lib
        int width = 0, height = 0, numComponents = 0;
        byte* imageData = stbi_load(filename.c_str(), &width, &height, &numComponents, 4);
        if (imageData == nullptr) { std::cerr <<" ERROR: loading texture " <<std::endl; }
        // Assign texture to ID
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        // Parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Activate MipMaping for the Texture
        if(MIP_MAPPING) {
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        // Activate Anisotropic Filtering for the Texture
        if(ANISOTROPIC_FILTERING) {
            GLfloat largest_supported_anisotropy;
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_supported_anisotropy);
        }
        // Cleanup
        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(imageData);
        return textureID;
    }
    
};

}

#endif
