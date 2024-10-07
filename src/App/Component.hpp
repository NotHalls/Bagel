#pragma once

#include <string>


class Component
{
public:
    std::string ComponentName;


public:
    Component(const std::string& name)
        : ComponentName(name)
    {}
    virtual ~Component() {}

    virtual void Start() {}
    virtual void Update(double deltaTime) {}
    virtual void Destroy() {}
};