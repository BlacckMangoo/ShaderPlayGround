
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


    // Initialize EditorContext which will initialize OutputImage
    // All framebuffer and shader setup is now handled by OutputImage

    // Initialize legacy texture_id for backward compatibility
    ctx.updateLegacyTextureId();





    while (window.isOpen()) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);


        ImGui::NewFrame();
        ctx.uiManager.RenderGraph();

        // Check if framebuffer size changed and resize if needed
        static int last_display_w = 0, last_display_h = 0;
        glfwGetFramebufferSize(window.get_GLFW_Window(), &display_w, &display_h);

        if (display_w != last_display_w || display_h != last_display_h) {
            // Resize OutputImage framebuffer when window size changes
            ctx.resizeOutput(display_w, display_h);
            ctx.updateLegacyTextureId(); // Update legacy texture_id

            last_display_w = display_w;
            last_display_h = display_h;
        }

        // Render the output using OutputImage
        ctx.renderOutput();



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