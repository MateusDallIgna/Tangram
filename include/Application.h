#pragma once

struct GLFWwindow;

class Application{

public:

	Application(int windowWidth, int windowHeight, const char* title);

	~Application();

	void Run();
	GLFWwindow* GetWindow();

private:

	void InitGLFW();
	void InitGLAD();
	void CreateGLFWWindow();
	void MainLoop();
	void SetupGL();

	GLFWwindow* m_Window;
	int m_Width;
	int m_Height;
	const char* m_Title;

};
