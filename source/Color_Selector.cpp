#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <glad.h>
#include <GLFW/glfw3.h>

//Function to read the shaders
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


//Set some consts
const int WIDTH = 800;
const int HEIGHT = 600;

int main (){
	
	//init the glfw
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Triangle", NULL, NULL);
	if (window == NULL){
		std::cout << "Failed on widow creation" << std::endl;
		glfwTerminate();
	}

	//set to use the current window
    glfwMakeContextCurrent(window);

	// initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to init GLAD" << std::endl;
		glfwTerminate();
	}
	//defining the cords of the vertices fo the trinagles
	float vertices[] = { 
		-0.5, -0.5, 0.0,  1.0, 0.0, 0.0, 
		 0.5, -0.5, 0.0,  0.0, 1.0, 0.0,
		 0.0,  0.5, 0.0,  0.0, 0.0, 1.0,
	};
	//creating the VBO and VAO,
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1,&VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Transfering the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//Setting the rules of the VAO for the positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	//Setting the rules of the VAO for the color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	//Activating the specific line of the config of the VAO
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//Reading the shaders content from the include files
    std::string vertexShader = readShaderFile("../include/shaders/vertex_shader.glsl");
    std::string fragmentShader = readShaderFile("../include/shaders/fragment_shader.glsl");

	const char *vertexShaderSource = vertexShader.c_str();
    const char *fragmentShaderSource = fragmentShader.c_str();

	//compiling the vertexShader
	unsigned int vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexshader);

	// Variáveis para checar o sucesso da compilação
	int success;
	char infoLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);

	// Se a compilação não foi bem sucedida
	if (!success)
	{
		// Pega o log de erro da OpenGL e o imprime
		glGetShaderInfoLog(vertexshader, 512, NULL, infoLog);
		std::cout << "ERRO::SHADER::VERTEX::COMPILACAO_FALHOU\n" << infoLog << std::endl;
	}

	//compiling the fragment shaders
	unsigned int fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentshader);

	//Make the Union of the shaders 
	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexshader);
	glAttachShader(shaderProgram, fragmentshader);

	glLinkProgram(shaderProgram);

	// Checa se a linkagem do programa de shader funcionou
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERRO::SHADER::PROGRAMA::LINKAGEM_FALHOU\n" << infoLog << std::endl;
	}

	//Clean the shaders that are alredy at the shaderProgram
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);

	//while loop
	while (!glfwWindowShouldClose(window)){
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);

	}
	glfwTerminate();

}
