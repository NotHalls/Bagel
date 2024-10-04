#pragma once

#include <vector>

#include "Object.hpp"


class ObjectList
{
private:
    std::vector<Object*> m_objects;
    uint32_t m_index = 0;


public:
    ObjectList() {}
    ~ObjectList();

    void AddObject(Object* object);
    void RemoveObject(Object* object);

    // these functions are used in the for-each loop
    // for-each calls the begin() and end()
    std::vector<Object*>::iterator begin()
    { return m_objects.begin(); }
    std::vector<Object*>::iterator end()
    { return m_objects.end(); }
};