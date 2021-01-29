#pragma once
#include <glad/glad.h>
#include <vector>
#include "ChunkController.h"
#include "Camera.h"
#include <glm\gtc\type_ptr.hpp>
namespace Renderer {
	static std::vector<std::tuple<uint32_t,uint32_t,uint32_t>> RendererQueue;

	void Init(void* msgCallbackFunc) {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			exit(-1);
		}
		// During init, enable debug output
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback((GLDEBUGPROC)msgCallbackFunc, 0);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glViewport(0, 0, 1280, 720);
	}

	void ClearScreen(std::initializer_list<float> color) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(*color.begin(), *(color.begin() + 1), *(color.begin() + 2), 1.0f);
	}
	void Render(const ChunkController& controller) {
		for (uint32_t z = 0; z < controller.GetSizeZ(); z++)
		{
			for (uint32_t x = 0; x < controller.GetSizeX(); x++)
			{
				auto va = controller.getChunkMeshes()[x][z].va;
				auto indexCount = controller.getChunkMeshes()[x][z].indexCount;
				glBindVertexArray(va);
				glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
			}
		}
	}
	void Submit(uint32_t va,uint32_t indexCount,uint32_t textureID = 0) {
		RendererQueue.push_back({ va,indexCount,textureID});
	}
	void Flush(uint32_t shaderID,Camera& camera,glm::mat4& model) {

		for (auto [va, indexCount, textureID] : RendererQueue) {
			if (textureID != 0) {
				glBindTexture(GL_TEXTURE_2D, textureID);
				glActiveTexture(GL_TEXTURE0);
			}

			glUseProgram(shaderID);

			camera.Upload(shaderID,"u_Projection","u_View");

			glBindVertexArray(va);
			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
		}
	}
}