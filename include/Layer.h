#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Shape.h"
#include <GLFW/glfw3.h>
#include <vector>

class Layer{
public:

	Layer(const char* vertPath, const char* fragPath);
    ~Layer();

	void OnRender();
	void OnUpdate(GLFWwindow* window);
	void OnMouseButtonEvent(int button, int action, int mods, double mouseX, double mouseY);

private:
	Shader m_Shader;
	Renderer m_Renderer;
	std::vector<Shape*> m_Shape;
	int m_CurrentMode;
	Shape* m_CurrentDrawingShape;

};

