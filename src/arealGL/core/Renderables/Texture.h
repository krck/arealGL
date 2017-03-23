//  FrameBuffer.h
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

#ifndef Texture_h
#define Texture_h

#include <string>

#include "Types.h"

namespace arealGL {

struct Material {
    float ambientReflectivity;
    float diffuseReflectivity;
    float spectralReflectivity;
    float shineDamper = 10.0f;
};


class Texture {
private:
    Material material;
    std::string path;
    uint textureDiffuse;
    uint normalMap;
    uint specularMap;
    
public:
    Texture(const Texture& rhs) = default;
    Texture(Texture&& rhs) noexcept = default;
    Texture(uint textureID, const std::string& path) : textureDiffuse(textureID), path(path) { }
    Texture(uint textureID, uint normalID, const std::string& path) : textureDiffuse(textureID), normalMap(normalID), path(path) { }
    Texture(uint textureID, uint normalID, uint specularID, const std::string& path)
    : textureDiffuse(textureID), normalMap(normalID), specularMap(specularID), path(path) { }
    
    Texture(uint textureID, const Material& mat, const std::string& path)
    : textureDiffuse(textureID), material(mat), path(path) { }
    Texture(uint textureID, uint normalID, const Material& mat, const std::string& path)
    : textureDiffuse(textureID), normalMap(normalID), material(mat), path(path) { }
    Texture(uint textureID, uint normalID, uint specularID, const Material& mat, const std::string& path)
    : textureDiffuse(textureID), normalMap(normalID), specularMap(specularID), material(mat), path(path) { }
    
    Texture& operator=(const Texture& rhs) = default;
    Texture& operator=(Texture&& rhs) = default;
    
    void bindTexture() const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureDiffuse);
    }
    void unbindTexture() const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void bindNormalMap() const {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normalMap);
    }
    void unbindNormalMap() const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void bindSpecularMap() const {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, specularMap);
    }
    void unbindSpecularMap() const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    inline void setAmbientReflectivity(float aRef) { this->material.ambientReflectivity = aRef; }
    inline void setDiffuseReflectivity(float dRef) { this->material.diffuseReflectivity = dRef; }
    inline void setSpectralReflectivity(float sRef) { this->material.spectralReflectivity = sRef; }
    inline void setShineDamper(float sDamp) { this->material.shineDamper = sDamp; }
    
    inline Material getMaterial() const { return this->material; }
    inline std::string getPath() const { return this->path; }

};

}

#endif
