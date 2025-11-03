#include "Layer.h" 
#include "Rectangle.h"
#include <GLFW/glfw3.h>
#include <iostream>

Layer::Layer(const char* vertPath, const char* fragPath) : m_Shader(vertPath, fragPath){
//    Usaremos coordenadas "chumbadas" (hardcoded) por enquanto.
    Rectangle* rect = new Rectangle(-0.5f, -0.5f, 0.5f, 0.5f);

    // 2. Adicionar o ponteiro para este novo retângulo à nossa lista.
    m_Shape.push_back(rect);
};

void Layer::OnRender(){
	for(Shape* shape : m_Shape){
		m_Renderer.Draw(shape->GetVAO(),shape->GetIBO(), m_Shader);
	}
}

void Layer::OnUpdate(GLFWwindow* window){
	if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
		std::cout << "Mode 1: Drawn Rectangle Active" <<std::endl;
	}
}

Layer::~Layer(){
	for(Shape* shape : m_Shape){
		delete shape;
	}
}

 
	
