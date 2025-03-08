#pragma once

#include <cstdint>
#include <vector>

#include "Layer.hpp"

class LayerList
{
private:
  std::vector<Layer *> m_layers;
  uint32_t m_index = 0;

public:
  LayerList() {}
  ~LayerList();

  void AddLayer(Layer *layer);
  void RemoveLayer(Layer *layer);

  // these functions are used in the for-each loop
  // for-each calls the begin() and end()
  std::vector<Layer *>::iterator begin() { return m_layers.begin(); }
  std::vector<Layer *>::iterator end() { return m_layers.end(); }
};