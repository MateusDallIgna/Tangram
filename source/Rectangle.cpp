#include "Rectangle.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

Rectangle::Rectangle(float x1, float y1, float x2, float y2){

	m_Vertices = {
		x1,y1,0.0f,0.5f,0.5f,1.0f,
		x2,y1,1.0f,0.5f,0.0f,1.0f, 
		x2,y2,0.2f,0.8f,0.0f,1.0f,
		x1,y2,0.5f,0.8f,0.3f,1.0f
	};

	m_Indices = {
		0,1,2,
		2,3,0
	};

	m_BufferLayout.PushFloat(2);
	m_BufferLayout.PushFloat(4);

	m_VertexArray = new VertexArray();

	m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size()*sizeof(float) , &m_BufferLayout);

	m_IndexBuffer = new IndexBuffer(m_Indices.data(), m_Indices.size());

}

VertexArray& Rectangle::GetVAO() const{
	return *m_VertexArray;
}

IndexBuffer& Rectangle::GetIBO() const{
return *m_IndexBuffer;
}

Rectangle::~Rectangle(){
	delete m_VertexArray;
	delete m_IndexBuffer;
}


