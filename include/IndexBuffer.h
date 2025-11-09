#pragma once
class IndexBuffer{

public:

	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	unsigned int GetCount() const;
	void SetData(const unsigned int* data, unsigned int count);


private:
	unsigned int m_EBOId;
	unsigned int m_Count;
	
};
