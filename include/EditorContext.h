#pragma once
#include "UiManager.h"
#include "NodeGraph.h"
#include "Window.h"


class EditorContext {
public:

    EditorContext( NodeGraph& graph ,  UiManager& uiManager ,  Window& window ) : window(window), graph(graph), uiManager(uiManager) {
        graph.Init(this);
        uiManager.Init(this);
        window.Init(this);

    };

     Window& window ;
     NodeGraph& graph;
     UiManager& uiManager;

    unsigned int texture_id;

};