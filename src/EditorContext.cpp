#include "../include/EditorContext.h"

// The constructor is already defined in the header file
// We could add additional initialization here if needed

// Update the legacy texture_id whenever the OutputImage texture changes
void EditorContext::updateLegacyTextureId() {
    texture_id = outputImage.GetTextureID();
}
