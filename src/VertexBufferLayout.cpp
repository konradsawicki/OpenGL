
#include "VertexBufferLayout.h"

namespace yon {

template <>
void VertexBufferLayout::Push<float>(unsigned int count) {
  m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
  m_stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}

template <>
void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
  m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
  m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}

template <>
void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
  m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
  m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}

template <>
void VertexBufferLayout::Push<glm::vec3>(unsigned int count) {
  m_elements.push_back({ GL_FLOAT, 3 * count, GL_FALSE });
  m_stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * 3 * count;
}

}