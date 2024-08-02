#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

namespace yon {

class VertexBufferLayout;
class VertexBuffer;

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_rendererID;

};

}

#endif