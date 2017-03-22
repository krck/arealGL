// game.cpp
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

#include <iostream>

#include "arealGL.h"

using namespace std;
using namespace arealGL;

int main() {
    
    Window window { "arealGL TEST", 1024, 768, false };
    const MouseClient& mouse = window.mouseClient();
    const KeyboardClient& keyboard = window.keyboardClient();
    Loader loader = Loader();
    BatchRenderer batchRender = BatchRenderer();
    FrameBuffer fboMSAA = FrameBuffer(window.width(), window.height(), true);
    FrameBuffer fboIntermediate = FrameBuffer(window.width(), window.height(), false);
    Camera camera;
    Timer timer;
    
    const glm::mat4 projection = glm::perspective(window.fieldOfView(), (window.width() / window.height()), 0.1f, 1000.0f);
    
    // Create Lights
    const Light sunLight = Light(glm::vec3(0.0f, 10.0f, -10.0f), CL_YELLOW_PALE, 0.8f);
    const Light leftLampLight = Light(glm::vec3(4.0f, 6.0f, 4.0f), CL_GREEN, glm::vec3(1.0f, 0.1f, 0.02f), 2.0f);
    const Light rightLampLight = Light(glm::vec3(-4.0f, 6.0f, 4.0f), CL_BLUE, glm::vec3(1.0f, 0.1f, 0.02f), 2.0f);
    const std::vector<Light> lights { sunLight, leftLampLight, rightLampLight };
    
    // Load Shaders
    std::shared_ptr<Shader> basicShader = std::make_shared<BasicShader>();
    std::shared_ptr<Shader> basicNoTexShader = std::make_shared<BasicNoTexShader>();
    std::shared_ptr<Shader> lightShader = std::make_shared<LightShader>(lights);
    std::shared_ptr<Shader> fboShader = std::make_shared<FboShader>();
    
    // Load Models
    std::shared_ptr<Model> sunModel = loader.LoadSimpleModelFromFile(MODEL_BASEPATH + "shpere.obj");
    std::shared_ptr<Model> nanosuitModel = loader.LoadComplexModelFromFile(MODEL_BASEPATH + "nanosuit/nanosuit.obj");
    std::shared_ptr<Model> boxModel = loader.LoadComplexModelFromFile(MODEL_BASEPATH + "cube/cube.obj");
    std::shared_ptr<Model> floorModel = loader.LoadComplexModelFromFile(MODEL_BASEPATH + "cube3/cube.obj");
    std::shared_ptr<Model> lampModel = loader.LoadComplexModelFromFile(MODEL_BASEPATH + "cube2/cube2.obj");
    // Simple quad model to render FBO texture on
    RenderQuad renderQuad;
    
    // Create Entities (and set the translations)
    std::shared_ptr<Entity> sun = std::make_shared<Entity>(sunModel, basicNoTexShader, glm::vec3(0.0f, 10.0f, -10.0f), CL_YELLOW_PALE);
    std::shared_ptr<Entity> nanosuit = std::make_shared<Entity>(nanosuitModel, lightShader, glm::vec3(0.0f, -0.45f, 0.0f), 0.25f, CL_WHITE);
    std::shared_ptr<Entity> box = std::make_shared<Entity>(boxModel, lightShader, glm::vec3(0.0f, 0.5f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 1.0f, CL_WHITE);
    std::shared_ptr<Entity> floor = std::make_shared<Entity>(floorModel, lightShader, glm::vec3(0.0f, -10.5f, 0.0f), CL_WHITE);
    std::shared_ptr<Entity> leftLamp = std::make_shared<Entity>(lampModel, basicShader, glm::vec3(4.0f, 6.0f, 4.0f), 0.2f, CL_GREEN);
    std::shared_ptr<Entity> rightLamp = std::make_shared<Entity>(lampModel, basicShader, glm::vec3(-4.0f, 6.0f, 4.0f), 0.2f, CL_BLUE);
    
    // MAIN LOOP
    while (!window.closed()) {
        timer.limitFPSstart();
        // window.clear();
        
        if(keyboard.KeyIsPressed(GLFW_KEY_A)) { camera.changePosition(MoveDirection::LEFT, 0.02f); }
        if(keyboard.KeyIsPressed(GLFW_KEY_D)) { camera.changePosition(MoveDirection::RIGHT, 0.02f); }
        if(keyboard.KeyIsPressed(GLFW_KEY_W)) { camera.changePosition(MoveDirection::FORWARD, 0.02f); }
        if(keyboard.KeyIsPressed(GLFW_KEY_S)) { camera.changePosition(MoveDirection::BACKWARD, 0.02f); }
        camera.changeLineOfSight(mouse.GetMouseX(), mouse.GetMouseY(), true);
        
        // spin the box
        box->setAngle(0.01f);
        
        batchRender.submit(sun);
        batchRender.submit(nanosuit);
        batchRender.submit(box);
        batchRender.submit(floor);
        batchRender.submit(leftLamp);
        batchRender.submit(rightLamp);
        
        // Render scene to the multisampled FrameBuffer
        fboMSAA.setAsRenderTarget();
        batchRender.render(camera, projection);
        // Combine multisampled scene into another FrameBuffer
        fboMSAA.resolveToFBO(fboIntermediate);
        // And render that to the actual Window
        window.setAsRenderTarget();
        batchRender.renderFBOtoDefaultScreen(*fboShader, renderQuad, fboIntermediate);
        
        const GLenum e (glGetError());
        if(e != GL_NO_ERROR) { std::cout <<" OpenGL ERROR: " <<e <<std::endl; }
        

        
        window.update();
        timer.calculateFPS();
        timer.limitFPSend();
        timer.printFPS();
    }
    
    return 0;
}
