
#include "../include/Window.h"
#include "../include/UiManager.h"
#include "../include/NodeGraph.h"
#include <iostream>
#include "../include/EditorContext.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

int main() {

    Window window(1920,1080,"Shader Playground");
    NodeGraph graph ;
    UiManager uiManager;
    EditorContext ctx(graph, uiManager, window);

    int display_w, display_h;
    glfwGetFramebufferSize(window.get_GLFW_Window(), &display_w, &display_h);


    const char* vertexSrc = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aColor;
        out vec3 vColor;
        void main() {
            vColor = aColor;
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    const char* fragmentSrc = R"(
        #version 330 core
        in vec3 vColor;
        out vec4 FragColor;
        void main() {
            FragColor = vec4(vColor, 1.0);
        }
    )";

    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexSrc, nullptr);
    glCompileShader(vs);

    int success;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(vs, 512, nullptr, log);
        std::cerr << "Vertex shader error:\n" << log << "\n";

    }

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentSrc, nullptr);
    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(fs, 512, nullptr, log);
        std::cerr << "Fragment shader error:\n" << log << "\n";

    }

    unsigned int program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(program, 512, nullptr, log);
        std::cerr << "Shader link error:\n" << log << "\n";

    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    float vertices[] = {
        // positions         // colors
         0.0f,  0.5f, 0.0f,   1, 0, 0,
        -0.5f, -0.5f, 0.0f,   0, 1, 0,
         0.5f, -0.5f, 0.0f,   0, 0, 1
    };

    unsigned int VAO, VBO,FBO, RBO;
     unsigned int& texture_id = ctx.texture_id ;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, display_w, display_h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, display_w, display_h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);




    while (window.isOpen()) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);


        ImGui::NewFrame();
        ctx.uiManager.RenderGraph();

        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, display_w, display_h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, display_w, display_h);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);


        glfwGetFramebufferSize(window.get_GLFW_Window(), &display_w, &display_h);


        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glUseProgram(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);



        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        glfwSwapBuffers(window.get_GLFW_Window());

    }

   UiManager::ImguiCleanUp();
    return 0;
}