#include "Core/ColorPalette.hpp"
#include "ControlLayer.hpp"

#include <glm/glm.hpp>
#include <iostream>




ControlLayer::ControlLayer() :
    m_fractalLayer(Core::Application::Get().GetLayer<FractalLayer>())
{
    if (!m_fractalLayer)
    {
        std::cerr << "Fractal Layer is not found!" << std::endl;
        return;
    }
}



void ControlLayer::onRender()
{
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 window_pos = ImVec2(0, 0);
    ImVec2 window_size = ImVec2(io.DisplaySize.x * 0.15f, io.DisplaySize.y * 1.0f);

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.4f);

    ImGui::Begin("Fractal Controls", nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse
    );
    
    
    float zoom = static_cast<float>(m_fractalLayer->m_zoom);
    if (ImGui::SliderFloat("Zoom", &zoom, 0.0001f, 1.0f))
        m_fractalLayer->m_zoom = static_cast<double>(zoom);

    if (ImGui::Button("Reset Zoom"))
        m_fractalLayer->m_zoom = 0.5;
        
    ImGui::Spacing();
    
    ImGui::SliderInt("Iterations", &m_fractalLayer->m_iterations, 5, 20000);
    if (ImGui::Button("Reset Iterations"))
    m_fractalLayer->m_iterations = 500;
    
    ImGui::Spacing();

    Core::pixel_t& start = m_fractalLayer->m_palette.m_startColor;
    Core::pixel_t& end = m_fractalLayer->m_palette.m_endColor;

    bool updated = false;
    float stColor[3] = { start.red / 255.0f, start.green / 255.0f, start.blue / 255.0f };
    float enColor[3] = { end.red   / 255.0f, end.green   / 255.0f, end.blue   / 255.0f };

    updated |= ImGui::ColorPicker3("Start Color", stColor);

    ImGui::Spacing();

    updated |= ImGui::ColorPicker3("End Color", enColor);

    if (updated)
    {
        start.red   = static_cast<uint8_t>(stColor[0] * 255.0f);
        start.green = static_cast<uint8_t>(stColor[1] * 255.0f);
        start.blue  = static_cast<uint8_t>(stColor[2] * 255.0f);

        end.red     = static_cast<uint8_t>(enColor[0] * 255.0f);
        end.green   = static_cast<uint8_t>(enColor[1] * 255.0f);
        end.blue    = static_cast<uint8_t>(enColor[2] * 255.0f);

        m_fractalLayer->m_palette.generateGradient();
        m_fractalLayer->updatePaletteTexture();
    }
 
    ImGui::End();
}

