#pragma once

#include "BufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

class VertexArray;
class IndexBuffer;

class Shape {
public:
	virtual ~Shape(){}

	//Render
	virtual VertexArray& GetVAO() const = 0;
	virtual IndexBuffer& GetIBO() const = 0;
	virtual GLenum GetDrawnMode() = 0;

	//Iteration
	virtual void UpdateVertices(double mouseX, double mouseY) = 0;
	virtual void AddPoint(double mouseX, double mouseY) = 0;
	virtual void FinalizeShape() = 0;

	//Selection An Color
	
	virtual bool IsInside(float ndcX, float ndcY) const = 0;
	virtual void SetColor(float r, float g, float b) = 0;
	

};
