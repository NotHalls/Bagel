#include <algorithm>

#include "LayerList.hpp"
#include "Layer.hpp"


LayerList::~LayerList()
{
    for(Layer* layer : m_layers)
    {
        layer->Destroy();
        delete layer;
    }
}

void LayerList::AddLayer(Layer* layer)
{
    m_layers.emplace(m_layers.begin() + LayerList::LayerList::m_index, layer);
    LayerList::LayerList::m_index++;
}

void LayerList::RemoveLayer(Layer* layer)
{
    auto itr = std::find(m_layers.begin(), m_layers.end(), layer);
    
    if(itr != m_layers.end())
    {
        layer->Destroy();
        m_layers.erase(itr);
        LayerList::m_index--;
    }
}