#include "Renderer.h" 
#include "BufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include <GL/gl.h>

void Renderer::Draw(const VertexArray& vertexarray, const IndexBuffer& indexBuffer, const Shader& shader, GLenum DrawnMode){
	
	shader.Bind();
	
	vertexarray.Bind();

	indexBuffer.Bind();

	glDrawElements(DrawnMode,indexBuffer.GetCount(),GL_UNSIGNED_INT, (void*)0);
}

void Renderer::Unbind(const VertexArray& vertexarray, const IndexBuffer& indexBuffer, const Shader& shader){
	
	shader.Unbind();
	
	vertexarray.Unbind();

	indexBuffer.Unbind();

}
