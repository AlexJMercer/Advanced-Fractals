#pragma once

#include <imgui.h>

#include "Core/Layer.hpp"
#include "FractalLayer.hpp"

class FractalLayer;

class ControlLayer : public Core::Layer
{
public:
    ControlLayer();
    virtual ~ControlLayer();

    virtual void onUpdate(float ts) override {}
    virtual void onRender() override;

private:
    FractalLayer *m_fractalLayer;
};