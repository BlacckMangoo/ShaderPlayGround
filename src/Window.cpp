//
// Created by lenovo on 25-10-2025.
//

#include "../include/Window.h"
#include <iostream>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
Window::~Window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}


void  Window::GLFWInit() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl ;
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::CreateWindow(const std::string_view  title) {
     m_window = glfwCreateWindow( m_display_width, m_display_height, title.data(), nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

    }
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();

    }

}

void Window::RenderFrame() const {
    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
    glfwSwapBuffers(m_window);
}
