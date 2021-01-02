#ifndef FrameBuffer_h
#define FrameBuffer_h

#include "..\Window\Window.h"
#include "..\..\Config.h"
#include "..\..\Types.h"
#include "..\RenderData\Mesh.h"

namespace arealGL {
    
class FrameBuffer {
private:
    int width, height;
    uint FBO;
    uint textureAttachment;
    uint renderAttachment;
    
public:
    FrameBuffer(int width, int height, bool multisample) : width(width), height(height) {
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        if(multisample) {
            textureAttachment = createTextureAttachmentMultiSampled(width, height);
            renderAttachment = createRenderBufferAttachmentMultiSampled(width, height);
        } else {
            textureAttachment = createTextureAttachment(width, height);
            renderAttachment = createRenderBufferAttachment(width, height);
        }
        checkFrameBuffer();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    
    void setAsRenderTarget() const {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glViewport(0,0, width, height);
    }

    void resolveToWindow(const Window& window) {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, width, height, 0, 0, (int)window.width(), (int)window.height(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }
    
    void resolveToFBO(const FrameBuffer& fbo) {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, this->FBO);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo.getFBO());
        glBlitFramebuffer(0, 0, this->width, this->height, 0, 0, fbo.getWidth(), fbo.getHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }
    
    inline uint getTextureColorbuffer() const { return this->textureAttachment; }
    inline uint getFBO() const { return FBO; }
    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
    
private:
    uint createTextureAttachment(int width, int height) const {
        uint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
        return textureID;
    }
    
    uint createTextureAttachmentMultiSampled(int width, int height) const {
        uint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureID);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, MSAA, GL_RGBA, width, height, GL_TRUE);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureID, 0);
        return textureID;
    }
    
    uint createRenderBufferAttachment(int width, int height) const {
        uint depthBuffer;
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        return depthBuffer;
    }
    
    uint createRenderBufferAttachmentMultiSampled(int width, int height) const {
        uint depthBuffer;
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, MSAA, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        return depthBuffer;
    }
    
    void checkFrameBuffer() const {
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        }
    }
    
};
    
}

#endif
