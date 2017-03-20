// Shader.h
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

#ifndef Shader_h
#define Shader_h

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "Light.h"
#include "Color.h"
#include "Config.h"

#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>

namespace arealGL {

class Shader {
public:
    uint programID;
    std::map<std::string, int> attributes;
    std::map<std::string, int> uniforms;
    // Error logging
    int success;
    char infoLog[1024];
    
public:
    Shader(const std::string& vertex, const std::string& fragment, bool isFile) {
        // create the shaders (load a shader from file or pass the string directly)
        uint vertexShader = createShader((isFile ? loadShader(vertex) : vertex), GL_VERTEX_SHADER);
        uint fragmentShader = createShader((isFile ? loadShader(fragment) : fragment), GL_FRAGMENT_SHADER);
        // Set up the overall shader program
        programID = glCreateProgram();
        glAttachShader(programID, vertexShader);
        glAttachShader(programID, fragmentShader);
        // Link the program and check for errors
        glLinkProgram(programID);
        glValidateProgram(programID);
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(programID, 1024, NULL, infoLog);
            std::cout <<"ERROR: SHADER LINKING\n" <<infoLog <<std::endl;
        }
        // The attached Shaders can be cleaned up
        glDetachShader(programID, vertexShader);
        glDetachShader(programID, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    
    // bind the shader to a program
    inline void bind() const { glUseProgram(programID); }
    inline void unbind() const { glUseProgram(0); }
    
    virtual void setModelUniforms(const glm::mat4& transform, const glm::mat4& view, const glm::mat4& projection, const Color& color) const = 0;
    virtual void setMaterialUniforms(float spectralReflectivity, float shineDamper) const { }
    virtual void setLightUniforms() const { }
    
    virtual ~Shader() { glDeleteProgram(programID); }
    
    
protected:
    void setAttribute(int index, const std::string name) {
        glBindAttribLocation(this->programID, index, name.c_str());
        this->attributes.insert(std::make_pair(name, index));
    }
    
    void setUniform(const std::string& name) {
        const int location = glGetUniformLocation(this->programID, name.c_str());
        this->uniforms.insert(std::make_pair(name, location));
    }
    
    // Apply basic uniform variables
    inline void uniformMat4(const std::string& name, const glm::mat4& mat) const { glUniformMatrix4fv(uniforms.at(name), 1, false, &mat[0][0]); }
    inline void uniformVec4(const std::string& name, const glm::vec4& vec) const { glUniform4fv(uniforms.at(name),1 , &vec[0] ); }
    inline void uniformVec3(const std::string& name, const glm::vec3& vec) const { glUniform3fv(uniforms.at(name),1 , &vec[0] ); }
    inline void uniformVec2(const std::string& name, const glm::vec2& vec) const { glUniform2fv(uniforms.at(name),1 , &vec[0] ); }
    inline void uniformFloat(const std::string& name, float val) const { glUniform1f(uniforms.at(name), val); }
    inline void uniformInt(const std::string& name, int val) const { glUniform1i(uniforms.at(name), val); }
    
    
private:
    // add an OpenGL shader from a file to the program
    uint createShader(const std::string& sh, const unsigned int& type) {
        const char* shader_source = sh.c_str();
        const int shader_length = (int)sh.length();
        uint shader = glCreateShader(type);
        glShaderSource(shader, 1, &shader_source, &shader_length);
        glCompileShader(shader);
        // Check for compile time errors
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout <<"ERROR: SHADER COMPILATION\n" <<infoLog <<std::endl;
        }
        return shader;
    }
    
    // function to read a shader file from harddrive
    std::string loadShader(const std::string& filename) const {
        std::string tmp = "";
        std::fstream file;
        file.open(filename, std::ifstream::in | std::ifstream::binary);
        if (file.is_open()) {
            try {
                file.seekg(0, std::ios::end);
                const size_t length = file.tellg();
                tmp.reserve(length);
                file.seekg(0, std::ios::beg);
                tmp.assign((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
            } catch (const std::ios_base::failure& e) {
                std::cerr << " Unable to read file \n" <<e.what() <<std::endl;
            }
        }
        file.close();;
        return tmp;
    }
    
};
    
}

#endif
