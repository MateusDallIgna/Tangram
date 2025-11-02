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
		std::cout << "ERRO::SHADER::VERTEX::COMPILACAO_FALHOU\n" << infoLog << std::endl;
	}
    
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(FragmentShader);

	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
		std::cout << "ERRO::SHADER::FRAGMENT::COMPILACAO_FALHOU\n" << infoLog << std::endl;
	}

    m_ID = glCreateProgram(); 
    glAttachShader(m_ID, VertexShader);
    glAttachShader(m_ID, FragmentShader);
    glLinkProgram(m_ID);

	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
		std::cout << "ERRO::SHADER::PROGRAMA::LINKAGEM_FALHOU\n" << infoLog << std::endl;
	}

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
}

void Shader::Bind() {
    glUseProgram(m_ID);
}

void Shader::Unbind() {
    glUseProgram(0);
}

Shader::~Shader() {
    glDeleteProgram(m_ID);
}
