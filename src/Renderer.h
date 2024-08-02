#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace yon {

class Renderer {
public:
  void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
  void Clear() const;
};

}

#endif