#ifndef _VERTEXBUFFERLAYOUT_H
#define _VERTEXBUFFERLAYOUT_H

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "Core.h"

#include <vector>

namespace yon {

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT: return sizeof(GLfloat);
			case GL_UNSIGNED_INT: return sizeof(GLuint);
			case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
public:
	VertexBufferLayout()
		: m_stride(0) {
	}

	template <typename T>
	void Push(unsigned int count) {
		//static_assert(false);
	}

	const std::vector<VertexBufferElement>& GetElements() const { return m_elements; }
	unsigned int GetStride() const { return m_stride; }

private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;
};

}

#endif