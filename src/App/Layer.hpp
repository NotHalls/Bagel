#pragma once

#include <string>


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
    virtual void Destroy() {}
};