#include "../include/UiManager.h"
#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imnodes.h>

#include "imgui_internal.h"
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




void UiManager::AddNode(Node& node)
{
    if (!node.initialized)
    {
        ImNodes::SetNodeScreenSpacePos(node.nodeId, node.position);
        node.initialized = true;
    }

    ImNodes::BeginNode(node.nodeId);

    // Node title bar
    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Node %d", node.nodeId);
    ImNodes::EndNodeTitleBar();

    // Inputs
    for (size_t i = 0; i < node.inputPins.size(); ++i)
    {
        std::string label = "In " + std::to_string(i + 1);
        ImNodes::BeginInputAttribute(node.inputPins[i]);
        ImGui::TextUnformatted(label.c_str());
        ImNodes::EndInputAttribute();
    }

    // Outputs
    for (size_t i = 0; i < node.outputPins.size(); ++i)
    {
        std::string label = "Out " + std::to_string(i + 1);
        ImNodes::BeginOutputAttribute(node.outputPins[i]);
        ImGui::Indent(40.0f); // visually offset output pins
        ImGui::TextUnformatted(label.c_str());
        ImNodes::EndOutputAttribute();
    }

    ImNodes::EndNode();

    // Sync position after dragging
    node.position = ImNodes::GetNodeScreenSpacePos(node.nodeId);
}


void UiManager::RenderGraph() {



 // set up docking space
    {
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

        static bool first_time = true;
        if (first_time) {
            first_time = false;


            ImGuiID dock_id_left, dock_id_right;
            ImGui::DockBuilderSplitNode(dock_space_id, ImGuiDir_Left, 0.5f, &dock_id_left, &dock_id_right);
            ImGui::DockBuilderDockWindow("node editor", dock_id_left);
            ImGui::DockBuilderDockWindow("shader output", dock_id_right);

            ImGui::DockBuilderFinish(dock_space_id);
        }



        ImGui::End();
    }


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

    bool openPopup = ImNodes::IsEditorHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right);
    ImNodes::EndNodeEditor();


    int stAtrr , endAttr ;
    if ( ImNodes::IsLinkCreated(&stAtrr, &endAttr)) {
        m_ctx->graph.AddEdge(stAtrr, endAttr);
        m_ctx->graph.PrintAllData();
    }


    if (openPopup)
        ImGui::OpenPopup("GraphPopup");

    if (ImGui::BeginPopup("GraphPopup")) {

        // --- Style overrides ---
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 12));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 6));
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6, 4));

        ImGui::Text("Create Node");
        ImGui::Separator();

        static int numInputs = 1;
        static int numOutputs = 1;

        ImGui::InputInt("Inputs", &numInputs);
        ImGui::InputInt("Outputs", &numOutputs);

        numInputs = std::max(0, numInputs);
        numOutputs = std::max(0, numOutputs);

        if (ImGui::Button("Add Node", ImVec2(-1, 0))) {  // full width button
            ImVec2 pos = ImGui::GetMousePos();
            m_ctx->graph.AddNode(numInputs, numOutputs, pos);
            ImGui::CloseCurrentPopup();
        }

        ImGui::PopStyleVar(3);
        ImGui::EndPopup();
    }


    ImGui::End();

    ImGui::Begin("shader output");
    ImGui::TextWrapped("This is where the generated shader code would be displayed.");

     const float window_width = ImGui::GetContentRegionAvail().x;
    const float window_height = ImGui::GetContentRegionAvail().y;

    ImVec2 pos = ImGui::GetCursorScreenPos();

    glViewport(0, 0, window_width, window_height);
    ImGui::GetWindowDrawList()->AddImage(
            (void *)m_ctx->texture_id,
            ImVec2(pos.x, pos.y),
            ImVec2(pos.x + window_width, pos.y + window_height),
            ImVec2(0, 1),
            ImVec2(1, 0)
        );

    ImGui::End();
    ImGui::Render();



};








