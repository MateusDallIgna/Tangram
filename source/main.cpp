#include "Application.h"
#include "BufferLayout.h"
#include "Layer.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include <glad.h>
#include <GLFW/glfw3.h>

int main(){
	Application window (1280, 720 , "My_Window");
	window.Run();

	// VertexArray vertexArray;
	// vertexArray.SetData(vertices, sizeof(vertices), &buffer);
	// Shader shader ("../include/shaders/vertex_shader.glsl", "../include/shaders/fragment_shader.glsl");
	// Renderer renderer;

	Layer layer ("../include/shaders/vertex_shader.glsl", "../include/shaders/fragment_shader.glsl");

	while(!glfwWindowShouldClose(window.GetWindow())){
		glClear(GL_COLOR_BUFFER_BIT);

		// renderer.Draw(vertexArray, shader);
		layer.OnRender();
		layer.OnUpdate(window.GetWindow());

		glfwSwapBuffers(window.GetWindow());

		glfwPollEvents();
	}

return 0;
}
