#include <cstdint>
#include <vector>

#include "BufferLayout.hpp"

BufferLayout::BufferLayout(const std::initializer_list<BufferAttrib> &layout)
    : m_bufferAttribs(layout)
{
  CalculateAttributes();
}

void BufferLayout::CalculateAttributes()
{
  for(auto &attrib : m_bufferAttribs)
  {
    attrib.Offset = m_stride;
    m_stride += attrib.Size;
  }
}