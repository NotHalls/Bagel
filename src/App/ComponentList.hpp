#pragma once

#include <vector>

#include "Component.hpp"


class ComponentList
{
private:
    std::vector<Component*> m_Components;
    uint32_t m_index = 0;


public:
    ComponentList() {}
    ~ComponentList();

    void AddComponent(Component* Component);
    void RemoveComponent(Component* Component);

    // these functions are used in the for-each loop
    // for-each calls the begin() and end()
    std::vector<Component*>::iterator begin()
    { return m_Components.begin(); }
    std::vector<Component*>::iterator end()
    { return m_Components.end(); }
};