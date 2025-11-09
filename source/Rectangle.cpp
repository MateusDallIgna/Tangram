#include "Rectangle.h"
#include "BufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

Rectangle::Rectangle(float x1, float y1, float x2, float y2, bool m_IsFilled) : m_AnchorX(x1) , m_AnchorY(y1), m_ShapeIsFilled(m_IsFilled){

	m_Vertices = {
		x1,y1,0.0f,0.1f,0.5f,1.0f,
		x2,y1,1.0f,0.5f,0.0f,1.0f, 
		x2,y2,0.2f,0.8f,0.0f,1.0f,
		x1,y2,0.5f,0.8f,0.9f,1.0f
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

void Rectangle::UpdateVertices(double mouseX, double mouseY){


	m_Vertices = {
		(float)m_AnchorX, (float)m_AnchorY, 0.0f,0.1f,0.5f,1.0f,
		(float)mouseX, (float)m_AnchorY, 1.0f,0.5f,0.0f,1.0f,  
		(float)mouseX, (float)mouseY, 0.2f,0.8f,0.0f,1.0f,
		(float)m_AnchorX, (float)mouseY, 0.5f,0.8f,0.9f,1.0f
	};

	m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size()*sizeof(float) , &m_BufferLayout);

}

GLenum Rectangle::GetDrawnMode(){
	if(m_ShapeIsFilled){
		return GL_TRIANGLES;
	}
	else{
		return GL_LINE_LOOP;
	}

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


void Rectangle::AddPoint(double x, double y){}
void::Rectangle::FinalizeShape(){}
