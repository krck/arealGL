arealGL
========

arealGL is a (work in progress) open source graphics library written in C++ and based on OpenGL. It provides functions to create a window, render 2D and 3D objects, load .obj models and textures files, add custom OpenGL shaders and handle the keyboard and mouse IO. 

About
--------

The general idea is to create very simple interfaces, making the graphics library easy to use and minimising the lines of code needed, to draw some 2D or 3D objects on the screen.

Most of the basic functions are available, but its not even close to being finished.

Using
--------

- [GLFW](https://github.com/glfw/glfw) : Window and IO manager
- [Assimp](https://github.com/assimp/assimp) : Model loader
- [glm](https://github.com/g-truc/glm) :  Mathematics library (until the custom stuff is working)
- [STB lib](https://github.com/nothings/stb) : File “stb_image.h” to load texture and image files

Compiled with: LLVM 7.0 clang++ / Compiler flags: -Os -std=c++14


TODO (Basics)
--------

- [ ] Skybox
- [ ] Simple GUI rendering
- [ ] Font rendering
- [ ] Normal mapping
- [ ] Particle Effects
- [ ] Instancing / Buffer combinig
- [ ] Shadows
- [ ] FBOs and AA
- [ ] Ray picking
- [ ] Debug own maths classes

TODO (Big stuff)
--------

- [ ] Physics Engine
- [ ] GUI Framework
- [ ] Oculus VR Support


