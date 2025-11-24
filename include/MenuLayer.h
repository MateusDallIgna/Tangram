#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Rectangle.h"
#include "LevelManager.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

class Application;

class MenuLayer {
public:
    MenuLayer(const char* vertPath, const char* fragPath, Application* windowContext, LevelManager* levelManager);
    ~MenuLayer();
    
    void OnRender();
    void OnUpdate(GLFWwindow* window);
    void OnMouseButtonEvent(int button, int action, int mods, double mouseX, double mouseY);
    void OnKeyEvent(int key, int scancode, int action, int mods);
    
    void ConvertScreenToNDC(double mouseX, double mouseY, float& outX, float& outY);
    void ConvertScreenToWorld(double mouseX, double mouseY, float& outX, float& outY);
    
    int GetSelectedLevel() const { return m_SelectedLevel; }
    void ResetSelection() { m_SelectedLevel = -1; }
    
private:
    void CreateLevelButtons();
    
    Shader m_Shader;
    Renderer m_Renderer;
    
    std::vector<Rectangle*> m_LevelButtons;
    LevelManager* m_LevelManager;
    Application* m_WindowContext;
    
    int m_SelectedLevel;
    int m_HoveredButton;
    
    glm::mat4 m_ViewMatrix;
};
