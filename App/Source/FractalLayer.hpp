#pragma once

#include "Core/Renderer/Renderer.hpp"
#include "Core/Renderer/Shader.hpp"
#include "Core/Application.hpp"
#include "Core/Layer.hpp"
#include "Core/CustomEvents.hpp"

#include <glm/glm.hpp>


class FractalLayer : public Core::Layer
{
public:
    FractalLayer();
    virtual ~FractalLayer();

    virtual void onEvent(Core::Event& event) override;

    virtual void onUpdate(float ts) override;
    virtual void onRender() override;

private:
    uint32_t m_shader = 0;
    uint32_t m_vertexArray = 0;
    uint32_t m_vertexBuffer = 0;

    GLint m_loc_time, m_loc_resolution, m_loc_center, m_loc_zoom;

    float m_time = 0.0f;
    float m_zoom = 0.5f;
    glm::vec2 m_center = { -0.5f, 0.0f };
    
    bool OnMouseScrollEvent(Core::MouseScrolledEvent& event);

};