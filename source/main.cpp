#include "Application.h"
#include "BufferLayout.h"
#include "Layer.h"
#include <glad.h>
#include <GLFW/glfw3.h>

void MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods){
	Layer* layer = (Layer*)glfwGetWindowUserPointer(window);

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if (layer != nullptr){
		layer->OnMouseButtonEvent(button, action, mods, mouseX, mouseY);

	}
}

int main(){
	Application window (1280, 720 , "My_Window");
	window.Run();

	Layer layer ("../include/shaders/vertex_shader.glsl", "../include/shaders/fragment_shader.glsl", &window);

	glfwSetWindowUserPointer(window.GetWindow(), &layer);

	glfwSetMouseButtonCallback(window.GetWindow(), MouseButtonCallBack);

	while(!glfwWindowShouldClose(window.GetWindow())){
		glClear(GL_COLOR_BUFFER_BIT);

		// renderer.Draw(vertexArray, shader);
		layer.OnUpdate(window.GetWindow());
		layer.OnRender();

		glfwSwapBuffers(window.GetWindow());

		glfwPollEvents();
	}

return 0;
}
