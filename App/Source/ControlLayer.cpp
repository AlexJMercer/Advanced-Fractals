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



ControlLayer::~ControlLayer()
{
}


void ControlLayer::onRender()
{
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 window_pos = ImVec2(0, 0);
    ImVec2 window_size = ImVec2(io.DisplaySize.x * 0.15f, io.DisplaySize.y * 0.50f);

    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.3f);

    ImGui::Begin("Fractal Controls", nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse
        // ImGuiWindowFlags_NoTitleBar
    );
    
    float zoom = static_cast<float>(m_fractalLayer->m_zoom);
    if (ImGui::SliderFloat("Zoom", &zoom, 0.0001f, 1.0f))
        m_fractalLayer->m_zoom = static_cast<double>(zoom);

    if (ImGui::Button("Reset Zoom"))
        m_fractalLayer->m_zoom = 0.5;
        
    ImGui::SliderInt("Iterations", &m_fractalLayer->m_iterations, 500, 30000);
    if (ImGui::Button("Reset Iterations"))
        m_fractalLayer->m_iterations = 500;
    
 
    ImGui::End();
}

