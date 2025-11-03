#include "Layer.h" 

Layer::Layer(const char* vertPath, const char* fragPath) : m_Shader(vertPath, fragPath){

	float vertices[] = {
		-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 
		
		0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 
		
		0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f 
	};

	BufferLayout buffer;
	buffer.PushFloat(2);
	buffer.PushFloat(4);
	
	m_VertexArray.SetData(vertices, sizeof(vertices), &buffer);

};

void Layer::OnRender(){
	m_Renderer.Draw(m_VertexArray, m_Shader);
}

 
