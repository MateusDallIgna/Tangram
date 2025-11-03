#pragma once
#include "BufferLayout.h"
#include "VertexArray.h"
#include <vector>

class Shape{

public:

private:
	std::vector<float> m_vertices;
	BufferLayout m_BufferLayout;
	VertexArray m_VertexArray ;

};
