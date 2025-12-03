#include "Layer.hpp"
#include "Application.hpp"

namespace Core
{

    /*void Layer::QueueTransition(std::unique_ptr<Layer> toLayer)
    {
        auto& layerStack = Application::Get().m_layerStack;

        for (auto& layer : layerStack)
        {
            if (layer.get() == this)
            {
                layer = std::move(toLayer);
                return;
            }
        }
    }*/

}