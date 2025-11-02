#pragma once

class Shader{

public:

	Shader(const char* VertexShader, const char* FragmentShader);	
	~Shader();

	void Bind();
	void Unbind();

private:

	unsigned int m_ID;
};

