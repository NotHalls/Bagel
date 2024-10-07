#include <algorithm>

#include "ComponentList.hpp"
#include "Component.hpp"


ComponentList::~ComponentList()
{
    for(Component* component : m_Components)
    {
        component->Destroy();
        delete component;
    }
}

void ComponentList::AddComponent(Component* component)
{
    m_Components.emplace(m_Components.begin() + m_index, component);
    m_index++;
}

void ComponentList::RemoveComponent(Component* component)
{
    auto itr = std::find(m_Components.begin(), m_Components.end(), component);
    
    if(itr != m_Components.end())
    {
        component->Destroy();
        m_Components.erase(itr);
        m_index--;
    }
}