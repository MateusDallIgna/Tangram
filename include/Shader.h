#pragma once

class Shader{

public:

	Shader(const char* VertexShader, const char* FragmentShader);	
	~Shader();

	void Bind() const;
	void Unbind() const;

private:

	unsigned int m_ID;
};

