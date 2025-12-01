#pragma once

#include "Event.hpp"
#include <format>

namespace Core
{
    //
    //  Window Events
    //

    class WindowClosedEvent : public Event
    {
    public:
        WindowClosedEvent() {}

        EVENT_CLASS_TYPE(WindowClose);
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(uint32_t width, uint32_t height) :
            m_width(width),
            m_height(height)
        {}

        inline uint32_t GetWidth() const { return m_width; }
        inline uint32_t GetHeight() const { return m_height; }

        EVENT_CLASS_TYPE(WindowResize);

    private:
        uint32_t m_width, m_height;
    };


    //
    //  Keyboard Events 
    //

    class KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() const { return m_keyCode; }
    
    protected:
        KeyEvent(int keyCode) :
            m_keyCode(keyCode)
        {}

        int m_keyCode;
    };



    //
    //  Mouse Events
    //

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(double xOffset, double yOffset) :
            m_xOffset(xOffset),
            m_yOffset(yOffset)
        {}

        inline double GetXOffset() const { return m_xOffset; }
        inline double GetYOffset() const { return m_yOffset; }

        std::string ToString() const override
		{
			return std::format("MouseScrolledEvent: {}, {}", m_xOffset, m_yOffset);
		}

        EVENT_CLASS_TYPE(MouseScrolled);
    
    private:
        double m_xOffset, m_yOffset;
    };
}