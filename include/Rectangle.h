#pragma once
#include <vector>
#include "BufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shape.h"

class Rectangle : public Shape{

public:

	Rectangle(float x1, float y1, float x2, float y2);

	~Rectangle();

	VertexArray& GetVAO() const;
	IndexBuffer& GetIBO() const;

private:

	std::vector<float> m_Vertices; 
	std::vector<unsigned int> m_Indices; 

	BufferLayout m_BufferLayout;

	 VertexArray* m_VertexArray;
	 IndexBuffer* m_IndexBuffer;
};
