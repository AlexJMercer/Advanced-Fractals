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

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_window->GetHandle(), true);
        ImGui_ImplOpenGL3_Init("#version 130");
        // Renderer::Utils::InitOpenGLDebugMessageCallback();
    }


    Application::~Application()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        
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

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

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

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
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



    void Application::TakeScreenshot(const std::string &path)
    {
        glm::vec2 frameSize = s_application->GetFrameBufferSize();

        std::vector<uint8_t> pixelArray(frameSize.x * frameSize.y * 3);

        glReadBuffer(GL_FRONT);
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadPixels(
            0, 0, 
            frameSize.x, frameSize.y,
            GL_RGB, GL_UNSIGNED_BYTE,
            pixelArray.data()
        );

        if (stbi_write_png(path.c_str(), frameSize.x, frameSize.y, 3, pixelArray.data(), frameSize.x * 3))
            std::cout << "Image printed\n";
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

