#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Shape.h"
#include <GLFW/glfw3.h>
#include <vector>

class Application;

class Layer{
public:

	Layer(const char* vertPath, const char* fragPath, Application* windowContext);
    ~Layer();

	void OnRender();
	void OnUpdate(GLFWwindow* window);
	void OnMouseButtonEvent(int button, int action, int mods, double mouseX, double mouseY);
	void OnKeyEvent(int key, int scancode, int action, int mods);
	void ConvertScreenToNDC(double mouseX, double mouseY, float& outX, float& outY);

private:

	Shader m_Shader;
	Renderer m_Renderer;

	std::vector<Shape*> m_Shape;
	std::vector<Shape*> m_SelectedShape;

	int m_CurrentMode;

	Shape* m_CurrentDrawingShape;
	Application* m_WindowContext;

	bool m_IsFilled;

};

