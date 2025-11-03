#include "Renderer.h" 
#include "Shader.h"
#include "VertexArray.h"
#include <GL/gl.h>

void Renderer::Draw(const VertexArray& vertexarray, const Shader& shader){
	
	shader.Bind();
	
	vertexarray.Bind();

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::Unbind(const VertexArray& vertexarray, const Shader& shader){
	
	shader.Unbind();
	
	vertexarray.Unbind();
}
