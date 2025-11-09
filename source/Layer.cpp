#include "Layer.h" 
#include "Application.h"
#include "Circle.h"
#include "Polygon.h"
#include "Rectangle.h"
#include <GLFW/glfw3.h>
#include "Triangle.h"
#include <iostream>

Layer::Layer(const char* vertPath, const char* fragPath, Application* windowContext) : m_Shader(vertPath, fragPath), m_CurrentMode(0), m_CurrentDrawingShape(nullptr), m_WindowContext(windowContext), m_IsFilled(true){

};

void Layer::OnRender(){

	for(Shape* shape : m_Shape){
		m_Renderer.Draw(shape->GetVAO(),shape->GetIBO(), m_Shader, shape->GetDrawnMode());
	}
}

void Layer::ConvertScreenToNDC(double mouseX, double mouseY, float& outX, float& outY){

	float WindowWidth = m_WindowContext->GetWidth();
	float WindowHeight = m_WindowContext->GetHeight();
	
	outX = (mouseX / WindowWidth) * 2.0f - 1.0f;
	outY = 1 - (mouseY / WindowHeight) * 2.0f ;

}

void Layer::OnUpdate(GLFWwindow* window){

	if (m_CurrentDrawingShape != nullptr){
		double mouseX, mouseY;
		float outX, outY;

		glfwGetCursorPos(window, &mouseX, &mouseY);
		ConvertScreenToNDC(mouseX, mouseY, outX, outY);
		m_CurrentDrawingShape->UpdateVertices(outX, outY);
		
	}
}

void Layer::OnKeyEvent(int key, int scancode, int action, int mods){

	if (!(action == GLFW_PRESS)){
        return;
    }

	switch (key) {

		case GLFW_KEY_F:{
			m_IsFilled = !m_IsFilled;
			if(!m_IsFilled){
				std::cout << "Fill Mode: Deactivate" <<std::endl;
				return;
			}
			std::cout << "Fill Mode: Activated" <<std::endl;
			break;
		}

        case GLFW_KEY_1:{
            m_CurrentMode = 1;
            std::cout << "Mode 1: Drawn Rectangle Active" <<std::endl;
            break;
        }

        case GLFW_KEY_2:{
            m_CurrentMode = 2;
            std::cout << "Mode 2: Drawn Triangle Active" <<std::endl;
            break;
        }

		case GLFW_KEY_3: {
			m_CurrentMode = 3;
			std::cout << "Mode 3: Drawn Cirvle Active" <<std::endl;
			break;
		}

        case GLFW_KEY_4: {
            m_CurrentMode = 4;
            std::cout << "Mode 4: Drawn Polygon Active" <<std::endl;
            break;
        }

		case GLFW_KEY_ESCAPE:{
            m_CurrentMode = 0;
            break;
		}
	
	}
    
}

void Layer::OnMouseButtonEvent(int button, int action, int mods, double mouseX, double mouseY){

	float ndcX, ndcY;
	ConvertScreenToNDC(mouseX, mouseY, ndcX, ndcY);

	if (m_CurrentMode == 4){
		if(action != GLFW_PRESS){
			return;
		}
		if(button != GLFW_MOUSE_BUTTON_LEFT){
			m_CurrentDrawingShape = nullptr;
			return;
		}
		if(m_CurrentDrawingShape){
			m_CurrentDrawingShape->AddPoint(ndcX, ndcY);
		}
		else{
			m_CurrentDrawingShape = new Polygon(ndcX,ndcY, m_IsFilled);
			m_Shape.push_back(m_CurrentDrawingShape);
		}
		return;
	}


	if(action == GLFW_PRESS){

		switch (m_CurrentMode) {

			case 1:{
					   m_CurrentDrawingShape = new Rectangle(ndcX, ndcY, ndcX, ndcY, m_IsFilled);
					   m_Shape.push_back(m_CurrentDrawingShape);

					   break;
				   }

			case 2:{
					   m_CurrentDrawingShape = new Triangle(ndcX, ndcY, ndcX, ndcY, m_IsFilled);
					   m_Shape.push_back(m_CurrentDrawingShape);

					   break;
				   }

			case 3:{
					   m_CurrentDrawingShape = new Circle(ndcX, ndcY , ndcX, ndcY, m_IsFilled);
					   m_Shape.push_back(m_CurrentDrawingShape);

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
	else if (action == GLFW_RELEASE){
		m_CurrentDrawingShape = nullptr;
	}
}

Layer::~Layer(){
	for(Shape* shape : m_Shape){
		delete shape;
	}
}
