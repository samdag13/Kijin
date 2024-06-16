#include "base_window.h"

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
    Renderer Renderer;
};

BaseWindow::BaseWindow() : Pimpl(new pimpl)
{
}

BaseWindow::~BaseWindow()
{
    delete Pimpl;
}

void BaseWindow::Init(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{

    if (!glfwInit())
        return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Pimpl->Handle = glfwCreateWindow(width, height, title, monitor, share);
    Pimpl->Height = height;
    Pimpl->Width = width;
    if (!Pimpl->Handle)
        return;

    glfwMakeContextCurrent(Pimpl->Handle);
    glfwSetFramebufferSizeCallback(Pimpl->Handle, FbResizeCallback);
    glfwSwapInterval(1);

    // Verify that glew init succeeds, which makes the link between the openGL implementation of the hardware and the standard function calls.
    if (glewInit() != GLEW_OK)
    {
        return;
    }


    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // Setup Dear ImGui style

    ImGui::StyleColorsDark();

    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
    ImGui_ImplGlfw_InitForOpenGL(Pimpl->Handle, true);

    return;
}

// TODO: Load openGL functions with GLEW, include & compile glew
void BaseWindow::Draw()
{
    Pimpl->Renderer.Clear();
    // Giving the location and value, we are setting the uniform

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //Pimpl->Renderer.Draw();

    ImGui::Begin("Debug");

    // ImGui::SliderFloat3("Translation", &translate.x, 0.0f, 960.0f);
    // ImGui::SliderFloat3("Scaling", &scale.x, 0.0f, 10.0f);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap front and back buffers
    glfwSwapBuffers(Pimpl->Handle);
    return;
}

bool BaseWindow::ShouldClose()
{
    return glfwWindowShouldClose(Pimpl->Handle);
}

void BaseWindow::Close()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

void BaseWindow::PollEvents()
{
    glfwPollEvents();
}

void BaseWindow::FbResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, static_cast<GLint>(width), static_cast<GLint>(height));
}
