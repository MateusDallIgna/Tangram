#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

std::string readShaderFile(const std::string& filePath) {
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo do shader: " << filePath << std::endl;
        return "";
    }
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    return shaderStream.str();
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) { 

	int success;
	char infoLog[512];

    std::string VertexCode = readShaderFile(vertexPath);
    std::string FragmentCode = readShaderFile(fragmentPath);
    const char *vShaderCode = VertexCode.c_str();
    const char *fShaderCode = FragmentCode.c_str();

    unsigned int VertexShader, FragmentShader;
    
    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &vShaderCode, NULL);
    glCompileShader(VertexShader);

	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
		std::cout << "ERRO::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
    
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(FragmentShader);

	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
		std::cout << "ERRO::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

    m_ID = glCreateProgram(); 
    glAttachShader(m_ID, VertexShader);
    glAttachShader(m_ID, FragmentShader);
    glLinkProgram(m_ID);

	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
		std::cout << "ERRO::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
}

void Shader::Bind() const {
    glUseProgram(m_ID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

Shader::~Shader() {
    glDeleteProgram(m_ID);
}

int GetUniformLocation(unsigned int shaderID, const std::string& name) {
    int location = glGetUniformLocation(shaderID, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' Does't found" << std::endl;
    }
    return location;
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {

    int location = GetUniformLocation(m_ID, name);

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
