#include "Renderer.hpp"
#include "stb_image.h"

#include <iostream>


namespace Renderer
{
    Texture CreateTexture(int width, int height)
    {
        Texture tex;
        tex.Width = width;
        tex.Height = height;

        glCreateTextures(GL_TEXTURE_2D, 1, &tex.Handle);
        glTextureStorage2D(tex.Handle, 1, GL_RGBA32F, width, height);

        glTextureParameteri(tex.Handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(tex.Handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(tex.Handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(tex.Handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
        return tex;
    }

    Texture LoadTexture(const std::filesystem::path &path)
    {
        int width, height, channels;
        std::string filePath = path.string();

        stbi_set_flip_vertically_on_load(1);
        unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

        if (!data)
        {
            std::cerr << "Failed to load texture: " << filePath << "\n";
            return {};
        }

        GLenum format = channels == 4 ? GL_RGBA :
                        channels == 3 ? GL_RGB :
                        channels == 1 ? GL_RED : 0;

        Texture tex;
        tex.Width = width;
        tex.Height = height;

        glCreateTextures(GL_TEXTURE_2D, 1, &tex.Handle);

        glTextureSubImage2D(tex.Handle, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);

		glTextureParameteri(tex.Handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(tex.Handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(tex.Handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(tex.Handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glGenerateTextureMipmap(tex.Handle);
		stbi_image_free(data);

		return tex;
    }


    FrameBuffer CreateFrameBufferWithTexture(const Texture tex)
    {
        FrameBuffer result;

        glCreateFramebuffers(1, &result.Handle);

        if (!AttachTextureToFrameBuffer(result, tex))
        {
            glDeleteFramebuffers(1, &result.Handle);
            return {};
        }

        return result;
    }


    bool AttachTextureToFrameBuffer(FrameBuffer& frameBuffer, const Texture tex)
    {
        glNamedFramebufferTexture(frameBuffer.Handle, GL_COLOR_ATTACHMENT0, tex.Handle, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cerr << "Framebuffer is not complete!" << std::endl;
            return false;
        }

        frameBuffer.ColorAttachment = tex;
        return true;
    }


    void BlitFrameBufferToSwapchain(const FrameBuffer frameBuffer)
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer.Handle);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		glBlitFramebuffer(0, 0, frameBuffer.ColorAttachment.Width, frameBuffer.ColorAttachment.Height, // Source rect
			0, 0, frameBuffer.ColorAttachment.Width, frameBuffer.ColorAttachment.Height,               // Destination rect
			GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }

}