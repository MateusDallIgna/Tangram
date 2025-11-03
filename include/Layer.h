#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"

class Layer{
public:

	Layer(const char* vertPath, const char* fragPath);

	void OnRender();

private:
	VertexArray m_VertexArray;
	Shader m_Shader;
	Renderer m_Renderer;
};
