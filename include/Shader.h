#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader{

public:

	Shader(const char* VertexShader, const char* FragmentShader);	
	~Shader();

	void Bind() const;
	void Unbind() const;
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);


private:

	unsigned int m_ID;
};

