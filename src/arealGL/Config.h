#ifndef Config_h
#define Config_h

#define GLEW_STATIC
#include <GLEW/glew.h>

#include <GLFW/glfw3.h>
#include <glm\glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image\stb_image.h>

#define SHADER_BASEPATH         std::string("C:\\Users\\PeterUser\\Documents\\GitHub\\arealGL\\resources\\Shaders\\")
#define MODEL_BASEPATH          std::string("C:\\Users\\PeterUser\\Documents\\GitHub\\arealGL\\resources\\Models\\")

#define MAX_LIGHTS              4

#define KEY_CODES               512
#define KEY_BUFFER_SZ           4

#define MIP_MAPPING             true
#define ANISOTROPIC_FILTERING   true

#define MSAA                    8       // 0 - 2 - 4 - 8

#define FRAME_SAMPLES           10
#define FPS_MAX                 100.0f

#endif
