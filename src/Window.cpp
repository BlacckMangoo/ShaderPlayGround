
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


}
