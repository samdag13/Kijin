#include "window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

struct pimpl
{
    GLFWwindow *handle{nullptr};
    int width;
    int height;
};

window::window() : Pimpl(new pimpl)
{
}

window::~window()
{
    delete Pimpl;
}

bool window::init(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
{

    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Pimpl->handle = glfwCreateWindow(width, height, title, monitor, share);

    if (!Pimpl->handle)
        return false;

    glfwMakeContextCurrent(Pimpl->handle);
    glfwSetFramebufferSizeCallback(Pimpl->handle, fb_resize_callback);
    glfwSwapInterval(1);

    // Verify that glew init succeeds, which makes the link between the openGL implementation of the hardware and the standard function calls.
    if (glewInit() != GLEW_OK)
    {
        return false;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // Setup Dear ImGui style

    ImGui::StyleColorsDark();

    ImGui_ImplOpenGL3_Init((char *)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
    ImGui_ImplGlfw_InitForOpenGL(Pimpl->handle, true);

    return true;
}

// TODO: Load openGL functions with GLEW, include & compile glew
bool window::run()
{

    glm::vec3 translate(200.f, 200.f, 0.f);
    glm::vec3 scale(1.f, 1.f, 1.f);
    while (!glfwWindowShouldClose(Pimpl->handle))
    {
        /*Render here*/

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Begin("Debug");

        ImGui::SliderFloat3("Translation", &translate.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Scaling", &scale.x, 0.0f, 10.0f);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap front and back buffers
        glfwSwapBuffers(Pimpl->handle);

        // Event polling
        glfwPollEvents();
    }
    glfwTerminate();
    return false;
}

void window::fb_resize_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, static_cast<GLint>(width), static_cast<GLint>(height));
}
