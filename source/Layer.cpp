#include "Layer.h" 
#include "Application.h"
#include "Rectangle.h"
#include <GLFW/glfw3.h>
#include <iostream>

Layer::Layer(const char* vertPath, const char* fragPath, Application* windowContext) : m_Shader(vertPath, fragPath), m_CurrentMode(0), m_CurrentDrawingShape(nullptr), m_WindowContext(windowContext){

};

void Layer::OnRender(){
	for(Shape* shape : m_Shape){
		m_Renderer.Draw(shape->GetVAO(),shape->GetIBO(), m_Shader);
	}
}

void Layer::ConvertScreenToNDC(double mouseX, double mouseY, float& outX, float& outY){

	float WindowWidth = m_WindowContext->GetWidth();
	float WindowHeight = m_WindowContext->GetHeight();
	
	outX = (mouseX / WindowWidth) * 2.0f - 1.0f;
	outY = 1 - (mouseY / WindowHeight) * 2.0f ;

}

void Layer::OnUpdate(GLFWwindow* window){
	if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){

		m_CurrentMode = 1;
		std::cout << "Mode 1: Drawn Rectangle Active" <<std::endl;

	}
	if (m_CurrentDrawingShape != nullptr){
		double mouseX, mouseY;
		float outX, outY;

		glfwGetCursorPos(window, &mouseX, &mouseY);
		ConvertScreenToNDC(mouseX, mouseY, outX, outY);
		m_CurrentDrawingShape->UpdateVertices(outX, outY);
		
	}
}

void Layer::OnMouseButtonEvent(int button, int action, int mods, double mouseX, double mouseY){

	float ndcX, ndcY;
	ConvertScreenToNDC(mouseX, mouseY, ndcX, ndcY);

	if (action == GLFW_PRESS){

		switch (m_CurrentMode) {

			case 1:{
					   m_CurrentDrawingShape = new Rectangle(ndcX, ndcY, ndcX, ndcY);
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
