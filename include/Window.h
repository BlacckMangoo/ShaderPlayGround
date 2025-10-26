#pragma once
#include <string>
#include <glad/glad.h>
#include "GLFW/glfw3.h"

class Window {

public:
      Window(int const width , int const height , std::string_view const  m_title ) : m_display_width(width), m_display_height(height) , m_title(m_title) {
      GLFWInit();
      CreateWindow(m_title);
    };
    ~Window();

    static void  GLFWInit();
    void CreateWindow( std::string_view title);

    [[nodiscard]] GLFWwindow*  get_GLFW_Window() const { return m_window; }


private:
    int const  m_display_width ;
    int const  m_display_height ;
    std::string_view const  m_title ;
    GLFWwindow* m_window{};
};


