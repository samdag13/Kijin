#pragma once
#include "vertex_buffer.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int RendererID;

public:
	VertexArray();
	~VertexArray();
	void Bind() const;
	void Unbind() const;

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};