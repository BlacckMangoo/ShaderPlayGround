
#include "../include/Window.h"
#include "../include/UiManager.h"
#include "../include/NodeGraph.h"

#include "../include/EditorContext.h"

int main() {

    Window window(1920,1080,"Shader Playground");
    NodeGraph graph ;
    UiManager uiManager;
    EditorContext ctx(graph, uiManager, window);

    while (window.isOpen()) {
        glfwPollEvents();
        ctx.uiManager.RenderGraph();
        window.RenderFrame() ; // handles resizing and buffer swapping
    }

   UiManager::ImguiCleanUp();
    return 0;
}