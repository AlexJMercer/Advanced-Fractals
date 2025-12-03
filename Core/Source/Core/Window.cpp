#include "Window.hpp"
#include "CustomEvents.hpp"

#include <glad/gl.h>
#include <iostream>

namespace Core
{

    Window::Window(const WindowSpecification& specs) :
        m_specification(specs)
    {}

    
    Window::~Window()
    {
        Destroy();
    }

    
    void Window::Create()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        m_handle = glfwCreateWindow(m_specification.Width, m_specification.Height,
                        m_specification.Title.c_str(), nullptr, nullptr);

        if (!m_handle)
        {
            std::cerr << "Failed to create GLFW Window!\n";
            return;
        }

        glfwMakeContextCurrent(m_handle);
        gladLoadGL(glfwGetProcAddress);

        glfwSwapInterval(m_specification.VSync ? 1 : 0);
        glfwSetWindowUserPointer(m_handle, this);


        // glfwSetWindowCloseCallback(m_handle, [](GLFWwindow* handle){
        //     Window &window = *((Window*)glfwGetWindowUserPointer(handle));

        //     WindowClosedEvent event;
        //     window.RaiseEvent(event);
        // });
        
        // glfwSetWindowSizeCallback(m_handle, [](GLFWwindow* handle, int width, int height){
        //     Window &window = *((Window*)glfwGetWindowUserPointer(handle));

        //     WindowResizeEvent event((uint32_t)width, (uint32_t)height);
        //     window.RaiseEvent(event);
        // });

        glfwSetScrollCallback(m_handle, [](GLFWwindow* window, double xOffset, double yOffset){
            Window &userWindow = *((Window*)glfwGetWindowUserPointer(window));
            
            MouseScrolledEvent event(xOffset, yOffset);
            userWindow.RaiseEvent(event);
        });

        glfwSetKeyCallback(m_handle, [](GLFWwindow* window, int key, int scanCode, int action, int mods){
            Window &userWindow = *((Window*)glfwGetWindowUserPointer(window));

            switch (action)
            {
                case GLFW_PRESS:
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, action == GLFW_REPEAT);
                    userWindow.RaiseEvent(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    userWindow.RaiseEvent(event);
                    break;
                }
            }
        });

    }

    
    void Window::Destroy()
    {
        if (m_handle)
            glfwDestroyWindow(m_handle);

        m_handle = nullptr;
    }


    void Window::Update()
    {
        glfwSwapBuffers(m_handle);
    }


    void Window::RaiseEvent(Event& event)
    {
        if (m_specification.EventCallback)
            m_specification.EventCallback(event);
    }


    glm::vec2 Window::GetFrameBufferSize() const
    {
        int width, height;
        glfwGetFramebufferSize(m_handle, &width, &height);
        return { width, height };
    }


    glm::vec2 Window::GetMousePos() const
    {
        double x, y;
        glfwGetCursorPos(m_handle, &x, &y);
        return { static_cast<float>(x), static_cast<float>(y) };
    }


    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_handle) != 0;
    }


    GLFWwindow* Window::GetHandle() const
    {
        return m_handle;
    }
}