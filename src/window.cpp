#include "window.h"

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"
#include "texture.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

struct pimpl
{
    GLFWwindow* Handle{ nullptr };
    int Width;
    int Height;
};

Window::Window() : Pimpl(new pimpl)
{
}

Window::~Window()
{
    delete Pimpl;
}

bool Window::Init(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{

    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Pimpl->Handle = glfwCreateWindow(width, height, title, monitor, share);

    if (!Pimpl->Handle)
        return false;

    glfwMakeContextCurrent(Pimpl->Handle);
    glfwSetFramebufferSizeCallback(Pimpl->Handle, FbResizeCallback);
    glfwSwapInterval(1);

    // Verify that glew init succeeds, which makes the link between the openGL implementation of the hardware and the standard function calls.
    if (glewInit() != GLEW_OK)
    {
        return false;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // Setup Dear ImGui style

    ImGui::StyleColorsDark();

    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
    ImGui_ImplGlfw_InitForOpenGL(Pimpl->Handle, true);

    return true;
}

// TODO: Load openGL functions with GLEW, include & compile glew
bool Window::Draw()
{

#pragma region geometry

    // Vertices position for our triangle
    float positions[] = {
        //
        // (100,100)     (200,100)
        //          *---*
        //          | / |
        //          *---*
        // (100,200)     (200,200)
        //
        //   pos: position row,
        //   tc: texture coordinate row
        //   pos,   pos,  pos,   tc,   tc
        -50.0f, -50.0f, 0.0f, 0.0f, 0.0f, // top left
        50.0f, -50.0f, 0.0f, 1.0f, 0.0f,  // top right
        50.0f, 50.0f, 0.0f, 1.0f, 1.0f,   // bottom right
        -50.0f, 50.0f, 0.0f, 0.0f, 1.0f   // bottom left
    };

    // Sequence of indices of vertices to draw each triangles that makes up the square
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0 };

#pragma endregion

#pragma region blending

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

#pragma endregion

#pragma region buffers

    VertexArray va;

    VertexBuffer vb(positions, 5 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

#pragma endregion

#pragma region MVP

    glm::mat4 proj = glm::ortho(0.0f, 960.0f,     // Left-most and right-most bounds (x-axis)
        0.0f, 540.0f,     // top-most and bottom-most bound (y-axis)
        -100.0f, 100.0f); // frustrum (z-axis)

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

#pragma endregion

#pragma region shader

    Shader shader("resources/shaders/basic_shader.glsl");
    shader.Bind();

    Texture texture("resources/textures/clouds.png");
    texture.Bind();

    shader.SetUniform1i("u_Texture", 0);

#pragma endregion

#pragma region unbind

    va.Unbind();
    vb.Unbind();
    ib.Unbind();

    shader.Unbind();
#pragma endregion

#pragma region Render

    Renderer renderer;

    glm::vec3 translate(200.f, 200.f, 0.f);
    glm::vec3 scale(1.f, 1.f, 1.f);
    while (!glfwWindowShouldClose(Pimpl->Handle))
    {
        /* Render here */

        renderer.Clear();
        // Giving the location and value, we are setting the uniform

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), translate);
        model = glm::scale(model, scale);

        glm::mat4 mvp = proj * view * model;

        shader.Bind();
        shader.SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(va, ib, shader);

        ImGui::Begin("Debug");

        ImGui::SliderFloat3("Translation", &translate.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Scaling", &scale.x, 0.0f, 10.0f);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap front and back buffers
        glfwSwapBuffers(Pimpl->Handle);

        // Event polling
        glfwPollEvents();
    }
#pragma endregion

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return false;
}

void Window::FbResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, static_cast<GLint>(width), static_cast<GLint>(height));
}
