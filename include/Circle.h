#pragma once
#include <vector>
#include "BufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shape.h"


class Circle : public Shape{

public:
	
	Circle(float x1, float y1, float x2, float y2);
	~Circle();

	VertexArray& GetVAO() const;
    IndexBuffer& GetIBO() const;
	void UpdateVertices(double mouseX, double mouseY);

private:

    std::vector<float> m_Vertices;
    std::vector<unsigned int> m_Indices;

    BufferLayout m_BufferLayout;

    VertexArray* m_VertexArray;
    IndexBuffer* m_IndexBuffer;

	float m_AnchorX;
    float m_AnchorY;
	float m_Radius;


};
