#ifndef BatchRenderer_h
#define BatchRenderer_h

#include "Renderer.h"

// --------------------------------------
// ----- BATCHED BY SHADERS FOR NOW -----
// --------------------------------------

namespace arealGL {

class BatchRenderer : public Renderer {
private:
	std::map<std::shared_ptr<Shader>, std::vector<std::shared_ptr<Renderable3D>>> renderables;

public:
	void submit(std::shared_ptr<Renderable3D> entity) {
		if (renderables.count(entity->shader) == 0) {
			std::vector<std::shared_ptr<Renderable3D>> tmp{ entity };
			renderables.insert(std::make_pair(entity->shader, tmp));
		}
		else {
			renderables[entity->shader].push_back(entity);
		}
	}

	void render(const Camera& cam, const glm::mat4& projection) {
		for (const auto& renderpair : this->renderables) {
			auto shader = renderpair.first;
			shader->bind();
			for (auto entity : renderpair.second) {
				shader->setLightUniforms();
				shader->setModelUniforms(entity->getTransformation(), cam.getView(), projection, entity->getColor());
				for (const Mesh& mesh : *entity->model) {
					mesh.BindBuffer();
					// Activate and bind all the textures
					mesh.texture.bindTexture();
					mesh.texture.bindNormalMap();
					// Get the show on the road
					shader->setMaterialUniforms(mesh.texture.getMaterial().spectralReflectivity, mesh.texture.getMaterial().shineDamper);
					glDrawElements(GL_TRIANGLES, (int)mesh.indices.size(), GL_UNSIGNED_INT, nullptr);
					// Set everything back to defaults
					mesh.texture.unbindNormalMap();
					mesh.texture.unbindTexture();
					mesh.UnbindBuffer();
				}
			}
			shader->unbind();
		}
		renderables.clear();
	}


	void renderFBOtoDefaultScreen(const Shader& shader, const RenderQuad& renderQuad, const FrameBuffer& fbo) {
		shader.bind();
		glBindVertexArray(renderQuad.getVAO());
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, fbo.getTextureColorbuffer());
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		shader.unbind();
	}

};

}

#endif
