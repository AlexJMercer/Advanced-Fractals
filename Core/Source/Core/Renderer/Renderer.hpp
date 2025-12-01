#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <filesystem>


namespace Renderer
{

    struct Texture
    {
        GLuint Handle = 0;
        uint32_t Width = 0;
        uint32_t Height = 0;
    };


    struct FrameBuffer
    {
        GLuint Handle = 0;
        Texture ColorAttachment;
    };


    Texture CreateTexture(int width, int height);
    Texture LoadTexture(const std::filesystem::path &path);
    FrameBuffer CreateFrameBufferWithTexture(const Texture texture);
    bool AttachTextureToFrameBuffer(FrameBuffer &frameBuffer, const Texture texture);
    void BlitFrameBufferToSwapchain(FrameBuffer& frameBuffer);

}