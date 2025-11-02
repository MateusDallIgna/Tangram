#pragma once
#include "BufferLayout.h"

class VertexArray{

public:

	VertexArray();

    ~VertexArray();

	void Bind();
	void Unbind();
	void SetData(const void* data, unsigned int size, const BufferLayout* layout);


private:

	unsigned int m_VAOID;
	unsigned int m_VBOID;

};
