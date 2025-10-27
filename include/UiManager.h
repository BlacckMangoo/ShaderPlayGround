#pragma once
#include "../include/Window.h"
#include "../include/Node.h"
#include "../include/NodeGraph.h"
#include "imgui.h"
class EditorContext;

class UiManager {
public:

     void Init(EditorContext* ctx) { this->m_ctx = ctx; UiInit() ;}

     static void AddNode(Node &node);
     void UiInit();
    void RenderGraph();

    static void ImguiCleanUp();

private:
    EditorContext* m_ctx = nullptr  ;

};
