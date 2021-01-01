#ifndef Texture_h
#define Texture_h

#include <string>

#include "..\..\Config.h"
#include "..\..\Types.h"

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
    Texture(uint textureID, uint normalID, uint specularID, const std::string& path)
    : textureDiffuse(textureID), normalMap(normalID), specularMap(specularID), path(path) { }
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
        if(normalMap) {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, normalMap);
        }
    }
    void unbindNormalMap() const {
        if(normalMap) {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
    
    void bindSpecularMap() const {
        if(specularMap) {
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, specularMap);
        }
    }
    void unbindSpecularMap() const {
        if(specularMap) {
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
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
