#pragma once

#include "IndexBuffer.h"
#include "VertexArray.h"

class VertexArray;
class IndexBuffer;

class Shape {
public:
	virtual ~Shape(){}

	virtual VertexArray& GetVAO() const = 0;
	
	virtual IndexBuffer& GetIBO() const = 0;

	virtual void UpdateVertices(double mouseX, double mouseY) = 0;
};
