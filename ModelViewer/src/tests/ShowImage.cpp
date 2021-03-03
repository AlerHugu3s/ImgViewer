#include "ShowImage.h"
#include "Variables.h"

test::ShowImage::ShowImage()       
	:positions{
	-400.0f , -400.0f, 0.0f, 0.0f,//0
	400.0f, -400.0f, 1.0f, 0.0f,//1
	400.0f, 400.0f , 1.0f, 1.0f,//2
	-400.0f , 400.0f , 0.0f, 1.0f //3
	},
	indices{ 
	0, 1, 2,
	2, 3, 0
	},
	shader(shaderPath),
	ib(indices, 6),
	texture(texturePath)
{
	VertexBuffer vb = VertexBuffer(positions, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);//每个VAO需要使用两个float类型的数据(Vector2)
	layout.Push<float>(2);//texture
	//为VAO绑定VartexBuffer和VertexBufferLayout
	va.AddBuffer(vb, layout);

	proj = glm::ortho(0.0f, (float)mode->width, 0.0f, (float)mode->height, -1.0f, 1.0f);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	shader.Bind();
	//shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

	texture.Bind(0);
	shader.SetUniform1i("u_Texture", 0);

	va.Unbind();
	vb.UnBind();
	ib.UnBind();
	shader.Unbind();
}

test::ShowImage::~ShowImage()
{
}

void test::ShowImage::OnUpdate(float deltaTime)
{
}

void test::ShowImage::OnRender()
{
	shader.Bind();
	//shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
	{
		model = glm::translate(glm::mat4(1.0f), translation);
		mvp = proj * view * model;
		shader.SetUniformMat4f("u_MVP", mvp);
		render.Draw(va, ib, shader);
	}
}

void test::ShowImage::OnImGuiRender()
{
	ImGui::Begin("TransformA");
	ImGui::Text("position");
	ImGui::SliderFloat("x", &translation.x, 0.0f, mode->width);
	ImGui::SliderFloat("y", &translation.y, 0.0f, mode->height);
	ImGui::SliderFloat("z", &translation.z, -1.0f, 1.0f);
	ImGui::End();
}


