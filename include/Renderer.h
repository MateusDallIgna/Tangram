#pragma once
#include "VertexArray.h"
#include "Shader.h"

class Renderer{

public:

	void Draw(const VertexArray& VertexArray, const Shader& Shader);
	void Unbind(const VertexArray& vertexarray, const Shader& shader);

private:

};
