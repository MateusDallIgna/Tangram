#pragma once
#include "BufferLayout.h"

class VertexArray{

public:

	VertexArray();

    ~VertexArray();

	void Bind() const;
	void Unbind() const;
	void SetData(const void* data, unsigned int size, const BufferLayout* layout);


private:

	unsigned int m_VAOID;
	unsigned int m_VBOID;

};
