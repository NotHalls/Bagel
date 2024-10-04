#include <algorithm>

#include "ObjectList.hpp"
#include "Object.hpp"


ObjectList::~ObjectList()
{
    for(Object* obj : m_objects)
        delete obj;
}

void ObjectList::AddObject(Object* object)
{
    m_objects.emplace(m_objects.begin() + m_index, object);
    m_index++;
}

void ObjectList::RemoveObject(Object* object)
{
    auto itr = std::find(m_objects.begin(), m_objects.end(), object);
    
    if(itr != m_objects.end())
    {
        m_objects.erase(itr);
        m_index--;
    }
}