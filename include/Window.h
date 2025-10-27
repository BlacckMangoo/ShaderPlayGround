#pragma once
#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class EditorContext;

class Window {
public:

    Window(int const width , int const height , std::string_view const  m_title ) : m_display_width(width), m_display_height(height) , m_title(m_title)
    {
      GLFWInit();
      CreateWindow(m_title);
    };

    ~Window();

    void Init(EditorContext *ctx) { m_ctx = ctx; }
    static void  GLFWInit();
    void CreateWindow( std::string_view title);
    void RenderFrame() const;

    [[nodiscard]] bool isOpen() const                      { return !glfwWindowShouldClose(m_window); }
    [[nodiscard]] GLFWwindow*  get_GLFW_Window() const     { return m_window; }


private:
    int const  m_display_width ;
    int const  m_display_height ;
    std::string_view const  m_title ;
    GLFWwindow* m_window{};
    EditorContext* m_ctx = nullptr;
};


