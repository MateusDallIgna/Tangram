#include "Layer.h" 
#include "Rectangle.h"
#include <GLFW/glfw3.h>
#include <iostream>

Layer::Layer(const char* vertPath, const char* fragPath) : m_Shader(vertPath, fragPath), m_CurrentMode(0), m_CurrentDrawingShape(nullptr){
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
		m_CurrentMode = 1;
		std::cout << "Mode 1: Drawn Rectangle Active" <<std::endl;

	}
}

void Layer::OnMouseButtonEvent(int button, int action, int mods, double mouseX, double mouseY){
	if (action == GLFW_PRESS){

		switch (m_CurrentMode) {

			case 1:{
					   m_CurrentDrawingShape = new Rectangle(mouseX, mouseY, mouseX, mouseY);
					   m_Shape.push_back(m_CurrentDrawingShape);

					   break;
				   }

			case 2:{

					   break;
				   }

			case 3:{

					   break;
				   }

			case 4:{

					   break;
				   }

			case 5:{

					   break;
				   }
		}
	}
	if (action == GLFW_RELEASE){
		m_CurrentDrawingShape = nullptr;
	}

}

Layer::~Layer(){
	for(Shape* shape : m_Shape){
		delete shape;
	}
}
