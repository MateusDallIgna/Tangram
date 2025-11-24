#include "MenuLayer.h"
#include "Application.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

MenuLayer::MenuLayer(const char* vertPath, const char* fragPath, Application* windowContext, LevelManager* levelManager)
    : m_Shader(vertPath, fragPath)
    , m_LevelManager(levelManager)
    , m_WindowContext(windowContext)
    , m_SelectedLevel(-1)
    , m_HoveredButton(-1)
    , m_ViewMatrix(glm::mat4(1.0f)) {
    
    CreateLevelButtons();
}

MenuLayer::~MenuLayer() {
    for (Rectangle* button : m_LevelButtons) {
        delete button;
    }
}

void MenuLayer::CreateLevelButtons() {
    // Create a grid of level buttons (2 columns, 5 rows for 10 levels)
    int levelCount = m_LevelManager->GetLevelCount();
    int columns = 2;
    int rows = (levelCount + columns - 1) / columns;
    
    float buttonWidth = 1.5f;
    float buttonHeight = 0.8f;
    float spacingX = 2.0f;
    float spacingY = 1.2f;
    
    float startX = -1.5f;
    float startY = 2.5f;
    
    for (int i = 0; i < levelCount; ++i) {
        int col = i % columns;
        int row = i / columns;
        
        float x = startX + col * spacingX;
        float y = startY - row * spacingY;
        
        // Create button as a rectangle
        // Color: light gray for unselected, will change on hover
        Rectangle* button = new Rectangle(
            x - buttonWidth / 2, y + buttonHeight / 2,
            x + buttonWidth / 2, y - buttonHeight / 2,
            true
        );
        button->SetColor(0.7f, 0.7f, 0.7f);  // Light gray
        
        m_LevelButtons.push_back(button);
    }
}

void MenuLayer::OnRender() {
    m_Shader.Bind();
    
    const glm::mat4& proj = m_WindowContext->GetProjectionMatrix();
    const glm::mat4& view = m_ViewMatrix;
    
    m_Shader.SetUniformMat4f("u_Projection", proj);
    m_Shader.SetUniformMat4f("u_View", view);
    
    // Render all level buttons
    for (size_t i = 0; i < m_LevelButtons.size(); ++i) {
        Rectangle* button = m_LevelButtons[i];
        
        // Highlight hovered button
        if ((int)i == m_HoveredButton) {
            button->SetColor(0.9f, 0.9f, 0.5f);  // Yellow highlight
        } else {
            button->SetColor(0.7f, 0.7f, 0.7f);  // Normal gray
        }
        
        const glm::mat4& model = button->GetModelMatrix();
        m_Shader.SetUniformMat4f("u_Model", model);
        m_Renderer.Draw(button->GetVAO(), button->GetIBO(), button->GetDrawnMode());
    }
}

void MenuLayer::OnUpdate(GLFWwindow* window) {
    // Check for mouse hover
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    
    float worldX, worldY;
    ConvertScreenToWorld(mouseX, mouseY, worldX, worldY);
    
    m_HoveredButton = -1;
    for (size_t i = 0; i < m_LevelButtons.size(); ++i) {
        if (m_LevelButtons[i]->IsInside(worldX, worldY)) {
            m_HoveredButton = i;
            break;
        }
    }
}

void MenuLayer::ConvertScreenToNDC(double mouseX, double mouseY, float& outX, float& outY) {
    int windowWidth, windowHeight;
    glfwGetWindowSize(m_WindowContext->GetWindow(), &windowWidth, &windowHeight);
    
    outX = (mouseX / (float)windowWidth) * 2.0f - 1.0f;
    outY = 1.0f - (mouseY / (float)windowHeight) * 2.0f;
}

void MenuLayer::ConvertScreenToWorld(double mouseX, double mouseY, float& outX, float& outY) {
    float ndcX, ndcY;
    ConvertScreenToNDC(mouseX, mouseY, ndcX, ndcY);
    
    glm::mat4 proj = m_WindowContext->GetProjectionMatrix();
    glm::mat4 view = m_ViewMatrix;
    glm::mat4 invVP = glm::inverse(proj * view);
    
    glm::vec4 worldPos = invVP * glm::vec4(ndcX, ndcY, 0.0f, 1.0f);
    outX = worldPos.x;
    outY = worldPos.y;
}

void MenuLayer::OnKeyEvent(int key, int /*scancode*/, int action, int mods) {
    if (!(action == GLFW_PRESS)) {
        return;
    }
    
    if (key == GLFW_KEY_Q && (mods & GLFW_MOD_CONTROL)) {
        std::cout << "Quitting application..." << std::endl;
        GLFWwindow* window = m_WindowContext->GetWindow();
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void MenuLayer::OnMouseButtonEvent(int button, int action, int /*mods*/, double mouseX, double mouseY) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        float worldX, worldY;
        ConvertScreenToWorld(mouseX, mouseY, worldX, worldY);
        
        // Check which button was clicked
        for (size_t i = 0; i < m_LevelButtons.size(); ++i) {
            if (m_LevelButtons[i]->IsInside(worldX, worldY)) {
                m_SelectedLevel = i;
                Level* level = m_LevelManager->GetLevel(i);
                if (level) {
                    std::cout << "Selected Level " << (i + 1) << ": " << level->GetName() << std::endl;
                }
                break;
            }
        }
    }
}
