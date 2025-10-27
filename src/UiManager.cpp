#include "../include/UiManager.h"
#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imnodes.h>

#include "../include/EditorContext.h"
#include "../include/Utils.h"

class Node ;


void UiManager::UiInit() {


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
    ImGui_ImplGlfw_InitForOpenGL(m_ctx->window.get_GLFW_Window(), true);
    ImGui_ImplOpenGL3_Init("#version 430");
}

void UiManager::ImguiCleanUp() {
    // Cleanup ImGui and ImNodes
    ImNodes::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UiManager::AddInputPin(int nodeId) {
    ImNodes::BeginInputAttribute(nodeId);
    ImGui::Text("Input Pin");
    ImNodes::EndInputAttribute();
}

void UiManager::AddOutputPin(int nodeId) {
    ImNodes::BeginOutputAttribute(nodeId);
    ImGui::Text("Output Pin");
    ImNodes::EndOutputAttribute();
}


void UiManager::AddNode(const Node& node) {
    ImNodes::SetNodeScreenSpacePos(node.nodeId,node.position);

    ImNodes::BeginNode(node.nodeId);

    for ( auto& inputPinId: node.inputPins) {
        AddInputPin(inputPinId);
    }

    for ( auto& outputPin: node.outputPins) {
        AddOutputPin(outputPin);
    }

    ImNodes::EndNode();

}

void UiManager::RenderGraph() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", nullptr, window_flags);
    ImGui::PopStyleVar(3);


    const ImGuiID dock_space_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dock_space_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

    ImGui::End();
    ImGui::Begin("node editor");
    ImNodes::BeginNodeEditor();

    for ( auto& node : m_ctx->graph.nodes) {
        // get mouse position in screen space
        ImVec2 mousePos = ImGui::GetMousePos();
        UiManager::AddNode(node.second);
    }
    for ( const auto& adj : m_ctx->graph.adjList) {
        for ( const auto& connectedPinId : adj.second) {
            ImNodes::Link(GenerateId(), adj.first, connectedPinId);
        }
    }

    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
        ImGui::OpenPopup("GraphPopup");

    if (ImGui::BeginPopup("GraphPopup")) {
        if (ImGui::MenuItem("Add Node")) { m_ctx->graph.AddNode(1,4,ImGui::GetMousePos()) ;}
        ImGui::EndPopup();
    }


    ImNodes::EndNodeEditor();

    ImGui::End();
    // Rendering
    ImGui::Render();
}








