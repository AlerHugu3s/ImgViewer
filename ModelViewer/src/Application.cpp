#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <string>

#include "Render.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())    return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 450, "hello world", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    //更改主线程刷新调用时间
    //glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "ERROR!" << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,//0
             0.5f, -0.5f, 1.0f, 0.0f,//1
             0.5f,  0.5f, 1.0f, 1.0f,//2
            -0.5f,  0.5f, 0.0f, 1.0f //3
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        }; 

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        //设置VAO
        VertexArray va;
        //设置VAO对应的VertexBuffer
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        //设置需要VAO需要使用的VertexBufferLayout
        VertexBufferLayout layout;
        layout.Push<float>(2);//每个VAO需要使用两个float类型的数据(Vector2)
        layout.Push<float>(2);//texture
        //为VAO绑定VartexBuffer和VertexBufferLayout
        va.AddBuffer(vb,layout);

        //设置IndexBuffer
        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(-1.6f, 1.6f, -0.9f, 0.9f, -1.0f, 1.0f);
        
        Shader shader("res/shaders/SampleShader.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        shader.SetUniformMat4f("u_MVP", proj);

        Texture texture("res/textures/testImg.png");
        texture.Bind(0);
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        vb.UnBind();
        ib.UnBind();
        shader.Unbind();

        Render renderer;

        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        float r = 0.0f;
        float increment = 0.001f;

        while (!glfwWindowShouldClose(window))
        {
            /* Render Here */
            renderer.Clear();

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            renderer.Draw(va,ib,shader);

            if (r > 1.0f)
                increment = -0.001f;
            else if (r < 0.0f)
                increment = 0.001f;
            r += increment;

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}
