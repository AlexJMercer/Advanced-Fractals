#pragma once

#include "stb_image_write.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glad/gl.h>

#include "Layer.hpp"
#include "Window.hpp"
#include "Event.hpp"

#include <vector>
#include <memory>



namespace Core
{
    struct ApplicationSpecification
    {
        std::string Name = "App";
        WindowSpecification WindowSpec;
    };


    class Application
    {
    public:
        Application(const ApplicationSpecification& appSpec = ApplicationSpecification());
        ~Application();
        
        void Run();
        void Stop();
        
        void RaiseEvent(Event& event);

        template<typename TLayer, typename... Args>
        requires(std::is_base_of_v<Layer, TLayer>)
        void PushLayer(Args&&... args)
        {
            m_layerStack.push_back(std::make_unique<TLayer>(std::forward<Args>(args)...));
        }
        

        template<typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
        TLayer* GetLayer()
        {
            for (const auto& layer : m_layerStack)
            {
                if (auto castedLayer = dynamic_cast<TLayer*>(layer.get()))
                    return castedLayer;
                
            }
            return nullptr;
        }


        template<typename TLayer>
        void RemoveLayer()
        {
            m_layerStack.erase(
                std::remove_if(m_layerStack.begin(), m_layerStack.end(),
                    [](const std::unique_ptr<Layer>& layer){
                        return dynamic_cast<TLayer*>(layer.get()) != nullptr;
                    }),
                    m_layerStack.end()
            );
        }


        void TakeScreenshot(const std::string& path);

        glm::vec2 GetFrameBufferSize() const;

        std::shared_ptr<Window> GetWindow() const;

        static Application& Get();
        static float GetTime();

        
    private:
        ApplicationSpecification m_specification;

        std::shared_ptr<Window> m_window;
        bool m_isRunning = false;

        std::vector<std::unique_ptr<Layer>> m_layerStack;
        friend class Layer;
    };
}