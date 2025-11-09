#pragma once
#include <vector>
#include "BufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shape.h"

class Polygon : public Shape{

public:

	Polygon(float x1, float y1, bool m_IsFilled);
	~Polygon();

	VertexArray& GetVAO() const;
	IndexBuffer& GetIBO() const; 
	void UpdateVertices(double mouseX, double mouseY);
	GLenum GetDrawnMode();
	void AddPoint(double x, double y);
    void FinalizeShape();
	void AddTessVertex(void* vertex_data);

private:

	std::vector<float> m_Vertices; 
	std::vector<unsigned int> m_Indices; 

	BufferLayout m_BufferLayout;

	VertexArray* m_VertexArray;
	IndexBuffer* m_IndexBuffer;

	float m_AnchorX;
	float m_AnchorY;

	bool m_ShapeIsFilled;
	bool m_IsFinalized;

	std::vector<float> m_TessVertices;
	std::vector<unsigned int> m_TessIndices;

};
