#pragma once

class OutputImage {
public:
    OutputImage();
    ~OutputImage();

    void InitializeShaders();
    void InitializeFramebuffer();
    void ResizeFramebuffer(int width, int height);
    void RenderQuad();

    [[nodiscard]] unsigned int GetTextureID() const { return texture_id; }

private:
    unsigned int texture_id = 0;
    unsigned int FBO = 0, RBO = 0;
    unsigned int VAO = 0, VBO = 0, EBO = 0;
    unsigned int shaderProgram = 0;
    int framebuffer_width = 0;
    int framebuffer_height = 0;
};

