#pragma once

#include <memory>
#include <string>


class Model
{
public:
    Model() {}
    Model(const std::string& path);

    static std::unique_ptr<Model> Create(const std::string& path);
};