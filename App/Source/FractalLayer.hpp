#pragma once
#define _DOUBLE_PRECISION_

#include "Core/Renderer/Renderer.hpp"
#include "Core/Renderer/Shader.hpp"
#include "Core/Application.hpp"
#include "Core/Layer.hpp"
#include "Core/CustomEvents.hpp"
#include "Core/ColorPalette.hpp"

#include <glm/glm.hpp>


class FractalLayer : public Core::Layer
{
public:
    FractalLayer(const char* path);
    virtual ~FractalLayer();

    virtual void onEvent(Core::Event& event) override;

    virtual void onUpdate(float ts) override;
    virtual void onRender() override;

private:
    uint32_t m_shader = 0;
    uint32_t m_vertexArray = 0;
    uint32_t m_vertexBuffer = 0;

    GLint m_loc_time, m_loc_resolution, m_loc_center, m_loc_zoom, m_loc_iterations, m_loc_palette;
    GLuint m_colorTexture = 0;

    float m_time = 0.0f;
    double m_zoom = 0.5;
    glm::dvec2 m_center = { -0.5, 0.0 };

    std::filesystem::path m_FragmentShaderPath;
    
    bool OnMouseScrollEvent(Core::MouseScrolledEvent& event);
    Core::ColorPalette m_palette;
};