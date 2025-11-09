#include "Triangle.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include <algorithm>

Triangle::Triangle(float x1, float y1, float x2, float y2) : m_AnchorX(x1) , m_AnchorY(y1){

	float leftX = std::min(x1, x2);
    float rightX = std::max(x1, x2);
    float topY = std::max(y1, y2);
    float bottomY = std::min(y1, y2);

	m_Vertices = {
		(leftX+rightX)/2, topY, 0.0f,0.1f,0.5f,1.0f,
		leftX, bottomY, 1.0f,0.5f,0.0f,1.0f, 
        rightX, bottomY, 0.2f,0.8f,0.0f,1.0f
    };

    m_Indices = {
        0,1,2
    };

    m_BufferLayout.PushFloat(2);
    m_BufferLayout.PushFloat(4);

    m_VertexArray = new VertexArray();

    m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size()*sizeof(float) , &m_BufferLayout);

    m_IndexBuffer = new IndexBuffer(m_Indices.data(), m_Indices.size());
}

void Triangle::UpdateVertices(double mouseX, double mouseY){

	float x1 = (float)m_AnchorX;
    float y1 = (float)m_AnchorY;
    float x2 = (float)mouseX;
    float y2 = (float)mouseY;

    float leftX = std::min(x1, x2);
    float rightX = std::max(x1, x2);
    float topY = std::max(y1, y2);
    float bottomY = std::min(y1, y2);

	m_Vertices = {

        (leftX+rightX)/2, topY, 0.0f,0.1f,0.5f,1.0f,
        leftX, bottomY, 1.0f,0.5f,0.0f,1.0f,
        rightX, bottomY, 0.2f,0.8f,0.0f,1.0f

	};

	m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size()*sizeof(float) , &m_BufferLayout);
}

VertexArray& Triangle::GetVAO() const{
    return *m_VertexArray;
}

IndexBuffer& Triangle::GetIBO() const{
    return *m_IndexBuffer;
}

Triangle::~Triangle(){
    delete m_VertexArray;
    delete m_IndexBuffer;
}
