#include "Layer.h" 
#include "Application.h"
#include "Circle.h"
#include "Polygon.h"
#include "Rectangle.h"
#include <GLFW/glfw3.h>
#include "Triangle.h"
#include <iostream>
#include <algorithm>

Layer::Layer(const char* vertPath, const char* fragPath, Application* windowContext) : m_Shader(vertPath, fragPath), m_CurrentMode(0), m_CurrentDrawingShape(nullptr), m_WindowContext(windowContext), m_IsFilled(true),m_ViewMatrix(glm::mat4(1.0f)), m_IsTranslating(false), m_LastMouseX(0.0), m_LastMouseY(0.0){

};

void Layer::OnRender(){

	m_Shader.Bind();

	const glm::mat4& proj = m_WindowContext->GetProjectionMatrix();
	const glm::mat4& view = m_ViewMatrix; 

	m_Shader.SetUniformMat4f("u_Projection", proj);
	m_Shader.SetUniformMat4f("u_View", view);

	for(Shape* shape : m_Shape){
		const glm::mat4& model = shape->GetModelMatrix();

		m_Shader.SetUniformMat4f("u_Model", model);
		m_Renderer.Draw(shape->GetVAO(),shape->GetIBO(),shape->GetDrawnMode());
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

		case GLFW_KEY_K:{

			if (m_SelectedShape.empty()){ 
				break; 
			}
			for (Shape* shape : m_SelectedShape) {
				shape->SetColor(0.0f, 0.0f, 0.0f); 
			}
			std::cout << "The color of the selected objects has been changed to BLACK." << std::endl;
			break;
		}

		case GLFW_KEY_R:{

			if (m_SelectedShape.empty()){ 
				break; 
			}
			for (Shape* shape : m_SelectedShape) {
				shape->SetColor(1.0f, 0.0f, 0.0f); 
			}
			std::cout << "The color of the selected objects has been changed to RED." << std::endl;
			break;
		}

		case GLFW_KEY_G:{

			if (m_SelectedShape.empty()){ 
				break; 
			}
			for (Shape* shape : m_SelectedShape) {
				shape->SetColor(0.0f, 1.0f, 0.0f); 
			}
			std::cout << "The color of the selected objects has been changed to GREEN." << std::endl;
			break;
		}

		case GLFW_KEY_B:{

			if (m_SelectedShape.empty()){ 
				break; 
			}
			for (Shape* shape : m_SelectedShape) {
				shape->SetColor(0.0f, 0.0f, 1.0f); 
			}
			std::cout << "The color of the selected objects has been changed to BLUE." << std::endl;
			break;
		}

		case GLFW_KEY_BACKSPACE:{

			if(!(m_SelectedShape.empty())){
				for(Shape* shapeToDelete : m_SelectedShape){
					m_Shape.erase(std::remove(m_Shape.begin(), m_Shape.end(), shapeToDelete), m_Shape.end());
					delete shapeToDelete;
				}
				m_SelectedShape.clear();
				std::cout << "Selected shapes erased" <<std::endl;
				break;
			}
			std::cout << "Nothig Selected to be Ereased" <<std::endl;
			break;
		}

		case GLFW_KEY_0:{
            m_CurrentMode = 0;
			std::cout << "Mode 0: Select Mode Active" <<std::endl;
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
	}
}

void Layer::OnMouseButtonEvent(int button, int action, int mods, double mouseX, double mouseY){

	float ndcX, ndcY;
	ConvertScreenToNDC(mouseX, mouseY, ndcX, ndcY);

	if (action == GLFW_RELEASE){
		if(m_IsTranslating){
            m_IsTranslating = false;
		}
    }

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


	if (action != GLFW_PRESS){
		m_CurrentDrawingShape = nullptr;
		return;
	}

	switch (m_CurrentMode) {

		case 0:{
				   if(!(mods & GLFW_MOD_CONTROL)){
					   m_SelectedShape.clear();
				   }

				   for(int i = m_Shape.size() - 1; i >= 0; i--)
					   if(m_Shape[i]->IsInside(ndcX, ndcY)){
						   m_SelectedShape.push_back(m_Shape[i]);
						   std::cout << "The " << i<<"rd last form created has been selected" <<std::endl; 
						   break;
					   }

				   if (!m_SelectedShape.empty()) {
					   m_IsTranslating = true;

					   m_LastMouseX = ndcX; 
					   m_LastMouseY = ndcY;
				   }

				   break; 
			   }

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

Layer::~Layer(){
	for(Shape* shape : m_Shape){
		delete shape;
	}
}
