#pragma once
#include "Test.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "Render.h"

#include <string.h>

#include <GL/glew.h>
#include "Render.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {
	static const std::string texturePath = "res/textures/testImg.png";
	static const std::string shaderPath = "res/shaders/SampleShader.shader";
	class ShowImage : public Test
	{
	public:
		ShowImage();
		~ShowImage();
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float positions[16];
		unsigned int indices[6];
		Shader shader;
		VertexArray va;
		IndexBuffer ib;
		glm::mat4 proj,view,model,mvp;
		Texture texture;
		glm::vec3 translation;
		Render render;
	};
}


