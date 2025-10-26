#pragma once
#include "../include/Window.h"
#include "../include/Node.h"
#include "../include/NodeGraph.h"

class UiManager {
public:
    static void ImGuiInit(const Window& window);
    static void ImguiCleanUp();

    static void AddNode(const Node& node);

    static void AddInputPin(int nodeId);
    static void AddOutputPin(int nodeId);

    static void RenderGraph(const NodeGraph& graph);



};
