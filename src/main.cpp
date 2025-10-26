
#include "../include/Window.h"
#include "../include/UiManager.h"
#include "../include/NodeGraph.h"


int main() {

    const Window window(1920,1080,"Shader Playground");
    NodeGraph graph ;
    graph.AddNode(2,2);
    graph.AddNode(2,3);
    graph.AddEdge(1,8);
    graph.AddEdge(1,2); // should give error ( both input pins)


    graph.PrintAllData();



    UiManager::ImGuiInit(window);
    while (window.isOpen()) {

        glfwPollEvents();
        UiManager::RenderGraph(graph);
        window.RenderFrame() ; // handles resizing and buffer swapping

    }

   UiManager::ImguiCleanUp();
    return 0;
}