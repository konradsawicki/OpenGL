#include <glad/glad.h>
#include "Core.h"

#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

namespace yon {

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const {
	glBindVertexArray(m_rendererID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}

}