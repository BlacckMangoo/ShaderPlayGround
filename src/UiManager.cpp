#include "../include/UiManager.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imnodes.h>

void UiManager::ImGuiInit(const Window& window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Optional: Enable viewports (windows can be dragged outside main window)
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup ImNodes context
    ImNodes::CreateContext();

    // Setup Dear ImGui
    ImGui::StyleColorsDark();
    ImNodes::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.4f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.get_GLFW_Window(), true);
    ImGui_ImplOpenGL3_Init("#version 430");
}

void UiManager::ImguiCleanUp() {
    // Cleanup ImGui and ImNodes
    ImNodes::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}