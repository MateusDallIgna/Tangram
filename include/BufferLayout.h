#pragma once
#include <vector>
#include "LayoutElement.h"
#include "glad.h"
#include <GLFW/glfw3.h>

class BufferLayout{
public:
	
	BufferLayout() : m_Stride(0) {}

	void PushFloat(unsigned int count){
		m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_Stride += (count*sizeof(float));
	}

	//seting the getter for the VertexArray

	const std::vector<LayoutElement>& GetElements() const {
		return m_Elements;
	}

	unsigned int GetStride() const{
		return m_Stride;
	}

private:

	std::vector <LayoutElement> m_Elements;
	unsigned int m_Stride;
};

