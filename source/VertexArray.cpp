#include "VertexArray.h"
#include "BufferLayout.h"
#include "LayoutElement.h"

VertexArray::VertexArray(){
	glGenVertexArrays(1, &m_VAOID);
	glGenBuffers(1, &m_VBOID);
	
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_VAOID);
	glDeleteBuffers(1, &m_VBOID);
}

void VertexArray::Bind() const{
	glBindVertexArray(m_VAOID);
	glBindBuffer(GL_ARRAY_BUFFER,m_VBOID);
}

void VertexArray::Unbind() const{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

//Reminder for myself here we use void* as a generic pointer that can point at any type of data, like float or int.
void VertexArray::SetData(const void* data, unsigned int size, const BufferLayout* layout){
	glBindVertexArray(m_VAOID);
	glBindBuffer(GL_ARRAY_BUFFER,m_VBOID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	
	unsigned int offset = 0;
	unsigned int index = 0;

	for(LayoutElement element : layout->GetElements()){

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.count, element.type, element.normalized, layout->GetStride(), (const void*)(intptr_t)offset);

		offset += element.count * sizeof(float);
		index++;

	}
	glBindVertexArray(0);
}

