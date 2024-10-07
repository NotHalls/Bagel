#pragma once

#include <string>


class Object
{
public:
    std::string ObjectName;


public:
    Object(const std::string& name)
        : ObjectName(name)
    {}
    virtual ~Object() {}

    virtual void Start() {}
    virtual void Update(float deltaTime) {}
    virtual void Destroy() {}
};