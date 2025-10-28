#pragma once
#include "UiManager.h"
#include "NodeGraph.h"
#include "Window.h"
#include "OutputImage.h"


class EditorContext {
public:

    EditorContext( NodeGraph& graph ,  UiManager& uiManager ,  Window& window ) : window(window), graph(graph), uiManager(uiManager) {
        graph.Init(this);
        uiManager.Init(this);
        window.Init(this);
        // Initialize legacy texture_id after OutputImage is constructed
        updateLegacyTextureId();
    };

     Window& window ;
     NodeGraph& graph;
     UiManager& uiManager;
     OutputImage outputImage;  // OutputImage instance managed by EditorContext

    // Getter for texture_id that delegates to OutputImage
    unsigned int getTextureId() const { return outputImage.GetTextureID(); }

    // Method to update output image size when window resizes
    void resizeOutput(int width, int height) { outputImage.ResizeFramebuffer(width, height); }

    // Method to render the output
    void renderOutput() { outputImage.RenderQuad(); }

    // Update legacy texture_id for backward compatibility
    void updateLegacyTextureId();

    // Legacy texture_id for backwards compatibility (delegates to OutputImage)
    unsigned int texture_id = 0;

};