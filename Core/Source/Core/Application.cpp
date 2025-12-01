#include "Application.hpp"

#include <iostream>
#include <assert.h>
#include <ranges>

namespace Core 
{
    static Application* s_application = nullptr;
    
    static void GLFWErrorCallback(int error, const char* description)
    {
        std::cerr << "[GLFW Error]: " << description << std::endl;
    }


    Application::Application(const ApplicationSpecification& appSpec) :
        m_specification(appSpec)
    {
        s_application = this;

        glfwSetErrorCallback(GLFWErrorCallback);
        glfwInit();

        if (m_specification.WindowSpec.Title.empty())
            m_specification.WindowSpec.Title = m_specification.Name;

        m_specification.WindowSpec.EventCallback = [this](Event& event){
            RaiseEvent(event);
        };

        m_window = std::make_shared<Window>(m_specification.WindowSpec);
        m_window->Create();

        // Renderer::Utils::InitOpenGLDebugMessageCallback();
    }


    Application::~Application()
    {
        m_window->Destroy();

        glfwTerminate();

        s_application = nullptr;
    }


    void Application::Run()
    {
        m_isRunning = true;

        float lastTime = GetTime();

        while (m_isRunning)
        {
            glfwPollEvents();

            if (m_window->ShouldClose())
            {
                Stop();     
                break;
            }

            float currentTime = GetTime();
            float timestep = glm::clamp(currentTime - lastTime, 0.001f, 0.1f);
            lastTime = currentTime;

            for (const std::unique_ptr<Layer>& layer : m_layerStack)
                layer->onUpdate(timestep);
                
            for (const std::unique_ptr<Layer>& layer : m_layerStack)
                layer->onRender();
            
            m_window->Update();
        }
    }


    void Application::Stop()
    {
        m_isRunning = false;
    }


    void Application::RaiseEvent(Event& event)
    {
        for (auto& layer : std::views::reverse(m_layerStack))
        {
            layer->onEvent(event);
            if (event.Handled)
                break;
        }
    }


    glm::vec2 Application::GetFrameBufferSize() const
	{
		return m_window->GetFrameBufferSize();
	}


    std::shared_ptr<Window> Application::GetWindow() const
    {
        return m_window;
    }


	Application& Application::Get()
	{
		assert(s_application);
		return *s_application;
	}


	float Application::GetTime()
	{
		return (float)glfwGetTime();
	}
}

