#include "Circle.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include <cmath>

Circle::Circle(float x1, float y1, float x2, float y2, bool m_IsFilled) : m_AnchorX(x1) , m_AnchorY(y1), m_ShapeIsFilled(m_IsFilled){

	float sliceDegree = (10.0f * (float)M_PI) / 180.0f;

	m_Radius = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

	m_Vertices = {
		m_AnchorX, m_AnchorY, 0.0f,0.0f,1.0f,1.0f
	};

	for (int i = 0; i <36; i++){
		float currentDegree = float(i) * sliceDegree;
		
		float x = m_AnchorX + m_Radius * cos(currentDegree);
        float y = m_AnchorY + m_Radius * sin(currentDegree);

m_Vertices.push_back(x);
        m_Vertices.push_back(y);
        m_Vertices.push_back(0.0f);
        m_Vertices.push_back(0.0f);
        m_Vertices.push_back(1.0f);
        m_Vertices.push_back(1.0f);
	}


	//DEFINING THE INDICES FOR WHETHER THE CIRCLE IS FILLED OR NOT.//
	if(m_ShapeIsFilled){

		for (int i = 1 ; i < 36 ; i++){
			m_Indices.push_back(0);
			m_Indices.push_back(i);
			m_Indices.push_back(i+1);
		}
		m_Indices.push_back(0);
		m_Indices.push_back(36);
		m_Indices.push_back(1);
	}

	else{
		for(int i = 1; i <= 36; i++){
			m_Indices.push_back(i);
		}
		m_Indices.push_back(1);
	}
	//--------------------------------------------------------------//

    m_BufferLayout.PushFloat(2);
    m_BufferLayout.PushFloat(4);

    m_VertexArray = new VertexArray();

	m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size()*sizeof(float) , &m_BufferLayout);

    m_IndexBuffer = new IndexBuffer(m_Indices.data(), m_Indices.size());
}

void Circle::UpdateVertices(double mouseX, double mouseY){

	float sliceDegree = (10.0f * (float)M_PI) / 180.0f;

	m_Radius = sqrt((m_AnchorX - (float)mouseX)*(m_AnchorX - (float)mouseX) + (m_AnchorY - (float)mouseY)*(m_AnchorY - (float)mouseY));

	m_Vertices = {
		m_AnchorX, m_AnchorY, 0.0f,0.0f,1.0f,1.0f
	};

	for (int i = 0; i <36; i++){
		float currentDegree = float(i) * sliceDegree;
		
		float x = m_AnchorX + m_Radius * cos(currentDegree);
        float y = m_AnchorY + m_Radius * sin(currentDegree);

        m_Vertices.push_back(x);
        m_Vertices.push_back(y);
        m_Vertices.push_back(0.0f);
        m_Vertices.push_back(0.0f);
        m_Vertices.push_back(1.0f);
        m_Vertices.push_back(1.0f);
	}

	m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size()*sizeof(float) , &m_BufferLayout);

}


GLenum Circle::GetDrawnMode(){
	if(m_ShapeIsFilled){
		return GL_TRIANGLES;
	}
	else{
		return GL_LINE_LOOP;
	}

}

void Circle::SetColor(float r, float g, float b){
    
	for (size_t i = 0; i < m_Vertices.size(); i+=6){
        m_Vertices[i+2] = r;
        m_Vertices[i+3] = g;
        m_Vertices[i+4] = b;
		m_Vertices[i+5] = 1.0f;
    }
	m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size()*sizeof(float) , &m_BufferLayout);
}

bool Circle::IsInside(float ndcX, float ndcY) const{

	return (sqrt((m_AnchorX - ndcX)*(m_AnchorX - ndcX) + (m_AnchorY - ndcY)*(m_AnchorY - ndcY)) <= m_Radius);
}

VertexArray& Circle::GetVAO() const{
	return *m_VertexArray;
}

IndexBuffer& Circle::GetIBO() const{
	return *m_IndexBuffer;
} 

Circle::~Circle(){
	delete m_VertexArray;
	delete m_IndexBuffer;
}

void Circle::AddPoint(double x, double y){}

void Circle::FinalizeShape(){}
