#include "IndexBuffer.h"
#include "BufferLayout.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_Count(count){

	glGenBuffers(1, &m_EBOId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*count, data, GL_STATIC_DRAW);
};

IndexBuffer::~IndexBuffer(){
	glDeleteBuffers(1, &m_EBOId);
}

void IndexBuffer::Bind() const{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOId);
}

void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::GetCount() const{
	return m_Count;
}
