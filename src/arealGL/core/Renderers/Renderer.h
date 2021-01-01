#ifndef Renderer_h
#define Renderer_h

#include <map>
#include <vector>
#include <queue>
#include <memory>

#include "..\Entities\Renderable3D.h"
#include "../RenderData/RenderQuad.h"
#include "..\Entities\Camera.h"
#include "..\Buffers\FrameBuffer.h"
#include <glm\mat4x4.hpp>

namespace arealGL {

class Renderer {
public:
    virtual void submit(std::shared_ptr<Renderable3D> entity) = 0;
    
    virtual void render(const Camera& cam, const glm::mat4& projection) = 0;
    
    virtual void renderFBOtoDefaultScreen(const Shader& shader, const RenderQuad& renderQuad, const FrameBuffer& fbo) = 0;
    
};

}

#endif
