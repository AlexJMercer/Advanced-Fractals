#pragma once

#include "Event.hpp"

#include <memory>


namespace Core
{
    class Layer
    {
    public:
        virtual ~Layer() = default;
        
        virtual void onEvent(Event& event) {}
        
        virtual void onUpdate(float ts) {}
        virtual void onRender() {}

        template<std::derived_from<Layer> T, typename... Args>
		void TransitionTo(Args&&... args)
		{
			QueueTransition(std::move(std::make_unique<T>(std::forward<Args>(args)...)));
		}

    private:
        // void QueueTransition(std::unique_ptr<Layer> layer);
    };
}