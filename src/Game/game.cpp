#include <iostream>
#include <array>
#include <time.h>

#include "..\arealGL\arealGL.h"
#include "..\arealGL\core\IO\Mouse.h"
#include "..\arealGL\core\IO\Keyboard.h"

using namespace std;
using namespace arealGL;

int main() {
    
    Window window { "arealGL TEST", 1920, 1080, false };
    const MouseClient& mouse = window.mouseClient();
    const KeyboardClient& keyboard = window.keyboardClient();
    Loader loader = Loader();
    BatchRenderer batchRender = BatchRenderer();
    FrameBuffer fboMSAA = FrameBuffer(window.width(), window.height(), true);
    FrameBuffer fboIntermediate = FrameBuffer(window.width(), window.height(), false);
    Camera camera;
    
    const glm::mat4 projection = glm::perspective(window.fieldOfView(), (window.width() / window.height()), 0.1f, 1000.0f);
    
    // Check installed OpenGL Version
    std::cout << glGetString(GL_VERSION) << std::endl;

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
    std::shared_ptr<Model> nanosuitModel = loader.LoadComplexModelFromFile(MODEL_BASEPATH + "nanosuit\\nanosuit.obj");
    std::shared_ptr<Model> boxModel = loader.LoadComplexModelFromFile(MODEL_BASEPATH + "cube\\cube.obj");
    std::shared_ptr<Model> floorModel = loader.LoadComplexModelFromFile(MODEL_BASEPATH + "cube3\\cube.obj");
    std::shared_ptr<Model> lampModel = loader.LoadComplexModelFromFile(MODEL_BASEPATH + "cube2\\cube2.obj");
    // Simple quad model to render FBO texture on
    RenderQuad renderQuad;
    
    // Create Entities (and set the translations)
    std::shared_ptr<Renderable3D> sun = std::make_shared<Renderable3D>(sunModel, basicNoTexShader, glm::vec3(0.0f, 10.0f, -10.0f), CL_YELLOW_PALE);
    std::shared_ptr<Renderable3D> nanosuit = std::make_shared<Renderable3D>(nanosuitModel, lightShader, glm::vec3(0.0f, -0.45f, 0.0f), glm::vec3(0.25f), CL_WHITE);
    std::shared_ptr<Renderable3D> floor = std::make_shared<Renderable3D>(floorModel, lightShader, glm::vec3(0.0f, -10.5f, 0.0f), CL_WHITE);
    std::shared_ptr<Renderable3D> leftLamp = std::make_shared<Renderable3D>(lampModel, basicShader, glm::vec3(4.0f, 6.0f, 4.0f), glm::vec3(0.2f), CL_GREEN);
    std::shared_ptr<Renderable3D> rightLamp = std::make_shared<Renderable3D>(lampModel, basicShader, glm::vec3(-4.0f, 6.0f, 4.0f), glm::vec3(0.2f), CL_BLUE);
    std::shared_ptr<Renderable3D> box = std::make_shared<Renderable3D>(boxModel, lightShader, glm::vec3(0.0f, 0.5f, 4.0f),
                                                                       glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 1.0f, CL_WHITE);
    
    // MAIN LOOP
    while (!window.closed()) {
        //window.clear();
        
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

        // Check for Errors
        const GLenum e = glGetError();
        if(e != GL_NO_ERROR) { std::cout <<" OpenGL ERROR: " <<e <<std::endl; }
        
        // Handle Window Events
        // Swap Display buffer
        window.update();
    }
    
    return 0;
}
