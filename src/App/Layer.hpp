#pragma once

#include <string>

#include "Events/Events.hpp"


class Layer
{
public:
    std::string LayerName;


public:
    Layer(const std::string& name)
        : LayerName(name)
    {}
    virtual ~Layer() {}

    virtual void Start() {}
    virtual void Update(double deltaTime) {}
    virtual void ProcessEvent(Event& event) {}
    virtual void Destroy() {}
};