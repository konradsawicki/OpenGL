#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Vertex.h"
#include "Camera.h"

static const int width = 1280;
static const int height = 720;
static const float AspectRatio = (float)width / height;

static Camera camera(60.0f, AspectRatio, 0.1f, 10.0f);

static double mouse_xpos, mouse_ypos;
static void UpdateMouseInput(GLFWwindow* window, double xpos, double ypos)
{
    camera.Rotate(glm::vec2(xpos, ypos));
}

static void UpdateKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if ((key == GLFW_KEY_W || key == GLFW_KEY_S || key == GLFW_KEY_A || key == GLFW_KEY_D) && action == GLFW_REPEAT)
        camera.Translate(key);
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, UpdateMouseInput);
    glfwSetKeyCallback(window, UpdateKeyboardInput);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "gladLoadGLLoader error!\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST); // Enable depth buffer

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        Vertex vertices[] = {
        glm::vec3(-1.0f, +1.0f, +1.0f), // 0
        glm::vec3(+1.0f, +0.0f, +0.0f),

        glm::vec3(+1.0f, +1.0f, +1.0f), // 1
        glm::vec3(+0.0f, +1.0f, +0.0f),

        glm::vec3(+1.0f, +1.0f, -1.0f), // 2
        glm::vec3(+0.0f, +0.0f, +1.0f),

        glm::vec3(-1.0f, +1.0f, -1.0f), // 3
        glm::vec3(+1.0f, +1.0f, +1.0f),

        glm::vec3(-1.0f, +1.0f, -1.0f), // 4
        glm::vec3(+1.0f, +0.0f, +1.0f),

        glm::vec3(+1.0f, +1.0f, -1.0f), // 5
        glm::vec3(+0.0f, +0.5f, +0.2f),

        glm::vec3(+1.0f, -1.0f, -1.0f), // 6
        glm::vec3(+0.8f, +0.6f, +0.4f),

        glm::vec3(-1.0f, -1.0f, -1.0f), // 7
        glm::vec3(+0.3f, +1.0f, +0.5f),

        glm::vec3(+1.0f, +1.0f, -1.0f), // 8
        glm::vec3(+0.2f, +0.5f, +0.2f),

        glm::vec3(+1.0f, +1.0f, +1.0f), // 9
        glm::vec3(+0.9f, +0.3f, +0.7f),

        glm::vec3(+1.0f, -1.0f, +1.0f), // 10
        glm::vec3(+0.3f, +0.7f, +1.0f),

        glm::vec3(+1.0f, -1.0f, -1.0f), // 11
        glm::vec3(+0.5f, +0.7f, +0.5f),

        glm::vec3(-1.0f, +1.0f, +1.0f), // 12
        glm::vec3(+0.7f, +0.8f, +0.2f),

        glm::vec3(-1.0f, +1.0f, -1.0f), // 13
        glm::vec3(+0.5f, +0.7f, +0.3f),

        glm::vec3(-1.0f, -1.0f, -1.0f), // 14
        glm::vec3(+0.4f, +0.7f, +0.7f),

        glm::vec3(-1.0f, -1.0f, +1.0f), // 15
        glm::vec3(+0.2f, +0.5f, +1.0f),

        glm::vec3(+1.0f, +1.0f, +1.0f), // 16
        glm::vec3(+0.6f, +1.0f, +0.7f),

        glm::vec3(-1.0f, +1.0f, +1.0f), // 17
        glm::vec3(+0.6f, +0.4f, +0.8f),

        glm::vec3(-1.0f, -1.0f, +1.0f), // 18
        glm::vec3(+0.2f, +0.8f, +0.7f),

        glm::vec3(+1.0f, -1.0f, +1.0f), // 19
        glm::vec3(+0.2f, +0.7f, +1.0f),

        glm::vec3(+1.0f, -1.0f, -1.0f), // 20
        glm::vec3(+0.8f, +0.3f, +0.7f),

        glm::vec3(-1.0f, -1.0f, -1.0f), // 21
        glm::vec3(+0.8f, +0.9f, +0.5f),

        glm::vec3(-1.0f, -1.0f, +1.0f), // 22
        glm::vec3(+0.5f, +0.8f, +0.5f),

        glm::vec3(+1.0f, -1.0f, +1.0f), // 23
        glm::vec3(+0.9f, +1.0f, +0.2f),
        };

        unsigned int indices[] = {
            0,   1,  2,  0,  2,  3, // Top
            4,   5,  6,  4,  6,  7, // Front
            8,   9, 10,  8, 10, 11, // Right
            12, 13, 14, 12, 14, 15, // Left
            16, 17, 18, 16, 18, 19, // Back
            20, 22, 21, 20, 23, 22, // Bottom
        };

        VertexArray va;
        VertexBuffer vb(vertices, sizeof(vertices)/*4 * 2 * sizeof(float)*/);
        VertexBufferLayout layout;
        layout.Push<glm::vec3>(1);
        layout.Push<glm::vec3>(1);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, sizeof(indices) / sizeof(*indices));

        Shader shader("res/shaders/Basic.shader");

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;
        float angle = 0.0f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();
         

            glm::mat4 TranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
            glm::mat4 RotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 1.0f));
            glm::mat4 ModelToWorldMatrix = TranslationMatrix * RotationMatrix;     

            glm::mat4 TransformationMatrix = camera.GetProjectionMatrix() * camera.GetViewMatrix() * ModelToWorldMatrix;

            shader.Bind();
            shader.SetUniformMat4("TransformationMatrix", TransformationMatrix);

            renderer.Draw(va, ib, shader);

            if (angle > 360.0f)
            {
                angle = 0.0f;
            }
            //angle += 0.01f;

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}