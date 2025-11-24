#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "TangramPiece.h"
#include "Level.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

class Application;

enum class GameState {
    PLAYING,
    COMPLETED
};

class GameLayer {
public:
    GameLayer(const char* vertPath, const char* fragPath, Application* windowContext, Level* level);
    ~GameLayer();
    
    void OnRender();
    void OnUpdate(GLFWwindow* window);
    void OnMouseButtonEvent(int button, int action, int mods, double mouseX, double mouseY);
    void OnKeyEvent(int key, int scancode, int action, int mods);
    
    void ConvertScreenToNDC(double mouseX, double mouseY, float& outX, float& outY);
    void ConvertScreenToWorld(double mouseX, double mouseY, float& outX, float& outY);
    void UpdateViewMatrix();
    
    GameState GetGameState() const { return m_GameState; }
    void ResetLevel();
    
private:
    void InitializePieces();
    void RenderSilhouette();
    void RenderDynamicSilhouette();
    bool CheckSolution();
    
    Shader m_Shader;
    Renderer m_Renderer;
    
    std::vector<TangramPiece*> m_Pieces;
    TangramPiece* m_SelectedPiece;
    
    Level* m_CurrentLevel;
    Application* m_WindowContext;
    
    GameState m_GameState;
    
    glm::mat4 m_ViewMatrix;
    
    bool m_IsTranslating;
    bool m_IsPanning;
    
    double m_LastMouseX;
    double m_LastMouseY;
    double m_LastPanMouseX;
    double m_LastPanMouseY;
    
    float m_ZoomLevel;
    glm::vec3 m_PanOffset;
    
    // Silhouette rendering
    VertexArray* m_SilhouetteVAO;
    IndexBuffer* m_SilhouetteIBO;
    std::vector<float> m_SilhouetteVertices;
    std::vector<unsigned int> m_SilhouetteIndices;
};
