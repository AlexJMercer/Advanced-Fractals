#pragma once

#include "Event.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <functional>
#include <string>

namespace Core 
{
    struct WindowSpecification
    {
        std::string Title;
        uint32_t Width = 2560;
        uint32_t Height = 1440;
        bool isResizable = true;
        bool VSync = true;

        std::function<void(Event&)> EventCallback;
    };

    class Window
    {
    public:
        Window(const WindowSpecification& specs = WindowSpecification());
        ~Window();

        void Create();
        void Destroy();

        void Update();
        void RaiseEvent(Event& event);

        glm::vec2 GetFrameBufferSize() const;
        glm::vec2 GetMousePos() const;

        bool ShouldClose() const;

        GLFWwindow* GetHandle() const;

    private:
        WindowSpecification m_specification;
        GLFWwindow* m_handle = nullptr;
    };

}