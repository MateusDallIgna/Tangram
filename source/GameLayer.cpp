#include "GameLayer.h"
#include "Application.h"
#include "TangramTriangle.h"
#include "TangramSquare.h"
#include "TangramParallelogram.h"
#include "BufferLayout.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GameLayer::GameLayer(const char* vertPath, const char* fragPath, Application* windowContext, Level* level)
    : m_Shader(vertPath, fragPath)
    , m_CurrentLevel(level)
    , m_WindowContext(windowContext)
    , m_SelectedPiece(nullptr)
    , m_GameState(GameState::PLAYING)
    , m_ViewMatrix(glm::mat4(1.0f))
    , m_IsTranslating(false)
    , m_IsPanning(false)
    , m_LastMouseX(0.0)
    , m_LastMouseY(0.0)
    , m_LastPanMouseX(0.0)
    , m_LastPanMouseY(0.0)
    , m_ZoomLevel(1.0f)
    , m_PanOffset(0.0f, 0.0f, 0.0f)
    , m_SilhouetteVAO(nullptr)
    , m_SilhouetteIBO(nullptr) {
    
    UpdateViewMatrix();
    InitializePieces();
    
    // Setup silhouette rendering
    const auto& silhouetteVerts = m_CurrentLevel->GetSilhouetteVertices();
    for (const auto& vert : silhouetteVerts) {
        m_SilhouetteVertices.push_back(vert.x);
        m_SilhouetteVertices.push_back(vert.y);
        m_SilhouetteVertices.push_back(0.5f);  // R
        m_SilhouetteVertices.push_back(0.5f);  // G
        m_SilhouetteVertices.push_back(0.5f);  // B
        m_SilhouetteVertices.push_back(0.3f);  // A (semi-transparent)
    }
    
    // Create indices for line loop
    for (size_t i = 0; i < silhouetteVerts.size(); ++i) {
        m_SilhouetteIndices.push_back(i);
    }
    
    BufferLayout silhouetteLayout;
    silhouetteLayout.PushFloat(2);  // Position
    silhouetteLayout.PushFloat(4);  // Color
    
    m_SilhouetteVAO = new VertexArray();
    m_SilhouetteVAO->SetData(m_SilhouetteVertices.data(), 
                             m_SilhouetteVertices.size() * sizeof(float), 
                             &silhouetteLayout);
    m_SilhouetteIBO = new IndexBuffer(m_SilhouetteIndices.data(), m_SilhouetteIndices.size());
}

GameLayer::~GameLayer() {
    for (TangramPiece* piece : m_Pieces) {
        delete piece;
    }
    delete m_SilhouetteVAO;
    delete m_SilhouetteIBO;
}

void GameLayer::InitializePieces() {
    // Create the 7 traditional Tangram pieces with different colors
    // Positioned on the right side of the screen initially
    
    float startX = 2.5f;
    float startY = 2.0f;
    float spacing = 0.8f;
    
    // 2 Large Triangles
    m_Pieces.push_back(new TangramTriangle(startX, startY, TriangleSize::LARGE, 1.0f, 0.0f, 0.0f));  // Red
    m_Pieces.push_back(new TangramTriangle(startX, startY - spacing, TriangleSize::LARGE, 0.0f, 1.0f, 0.0f));  // Green
    
    // 1 Medium Triangle
    m_Pieces.push_back(new TangramTriangle(startX, startY - spacing * 2, TriangleSize::MEDIUM, 0.0f, 0.0f, 1.0f));  // Blue
    
    // 2 Small Triangles
    m_Pieces.push_back(new TangramTriangle(startX, startY - spacing * 3, TriangleSize::SMALL, 1.0f, 1.0f, 0.0f));  // Yellow
    m_Pieces.push_back(new TangramTriangle(startX, startY - spacing * 4, TriangleSize::SMALL, 1.0f, 0.0f, 1.0f));  // Magenta
    
    // 1 Square
    m_Pieces.push_back(new TangramSquare(startX, startY - spacing * 5, 0.707f, 0.0f, 1.0f, 1.0f));  // Cyan
    
    // 1 Parallelogram
    m_Pieces.push_back(new TangramParallelogram(startX, startY - spacing * 6, 0.707f, 1.0f, 0.5f, 0.0f));  // Orange
}

void GameLayer::OnRender() {
    m_Shader.Bind();
    
    const glm::mat4& proj = m_WindowContext->GetProjectionMatrix();
    const glm::mat4& view = m_ViewMatrix;
    
    m_Shader.SetUniformMat4f("u_Projection", proj);
    m_Shader.SetUniformMat4f("u_View", view);
    
    // Render silhouette first (behind pieces)
    RenderSilhouette();
    
    // Render all Tangram pieces
    for (TangramPiece* piece : m_Pieces) {
        const glm::mat4& model = piece->GetModelMatrix();
        m_Shader.SetUniformMat4f("u_Model", model);
        m_Renderer.Draw(piece->GetVAO(), piece->GetIBO(), piece->GetDrawnMode());
    }
}

void GameLayer::RenderSilhouette() {
    glm::mat4 identityModel(1.0f);
    m_Shader.SetUniformMat4f("u_Model", identityModel);
    m_Renderer.Draw(*m_SilhouetteVAO, *m_SilhouetteIBO, GL_LINE_LOOP);
}

void GameLayer::ConvertScreenToNDC(double mouseX, double mouseY, float& outX, float& outY) {
    int windowWidth, windowHeight;
    glfwGetWindowSize(m_WindowContext->GetWindow(), &windowWidth, &windowHeight);
    
    outX = (mouseX / (float)windowWidth) * 2.0f - 1.0f;
    outY = 1.0f - (mouseY / (float)windowHeight) * 2.0f;
}

void GameLayer::ConvertScreenToWorld(double mouseX, double mouseY, float& outX, float& outY) {
    float ndcX, ndcY;
    ConvertScreenToNDC(mouseX, mouseY, ndcX, ndcY);
    
    const glm::mat4& proj = m_WindowContext->GetProjectionMatrix();
    glm::mat4 invProj = glm::inverse(proj);
    glm::mat4 invView = glm::inverse(m_ViewMatrix);
    
    glm::vec4 ndcPoint(ndcX, ndcY, 0.0f, 1.0f);
    glm::vec4 viewPoint = invProj * ndcPoint;
    glm::vec4 worldPoint = invView * viewPoint;
    
    if (worldPoint.w != 0.0f) {
        outX = worldPoint.x / worldPoint.w;
        outY = worldPoint.y / worldPoint.w;
    } else {
        outX = worldPoint.x;
        outY = worldPoint.y;
    }
}

void GameLayer::OnUpdate(GLFWwindow* window) {
    if (m_IsTranslating && m_SelectedPiece != nullptr) {
        double mouseX, mouseY;
        float outX, outY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        ConvertScreenToWorld(mouseX, mouseY, outX, outY);
        
        float dx = (float)(outX - m_LastMouseX);
        float dy = (float)(outY - m_LastMouseY);
        
        m_SelectedPiece->Translate(dx, dy);
        
        m_LastMouseX = outX;
        m_LastMouseY = outY;
    }
    
    if (m_IsPanning) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        
        double dx = mouseX - m_LastPanMouseX;
        double dy = mouseY - m_LastPanMouseY;
        
        float windowWidth = (float)m_WindowContext->GetWidth();
        float windowHeight = (float)m_WindowContext->GetHeight();
        const glm::mat4& proj = m_WindowContext->GetProjectionMatrix();
        
        float worldWidth = (proj[0][0] != 0.0f) ? (2.0f / proj[0][0]) : 10.0f;
        float worldHeight = (proj[1][1] != 0.0f) ? (2.0f / proj[1][1]) : 10.0f;
        
        float pixelToWorldScaleX = worldWidth / windowWidth;
        float pixelToWorldScaleY = worldHeight / windowHeight;
        
        float worldDx = (float)(dx * pixelToWorldScaleX) / m_ZoomLevel;
        float worldDy = (float)(-dy * pixelToWorldScaleY) / m_ZoomLevel;
        
        m_PanOffset.x -= worldDx;
        m_PanOffset.y -= worldDy;
        
        UpdateViewMatrix();
        
        m_LastPanMouseX = mouseX;
        m_LastPanMouseY = mouseY;
    }
}

void GameLayer::UpdateViewMatrix() {
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / m_ZoomLevel, 1.0f / m_ZoomLevel, 1.0f));
    glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(-m_PanOffset.x, -m_PanOffset.y, 0.0f));
    m_ViewMatrix = scaleMat * translateMat;
}

void GameLayer::OnKeyEvent(int key, int /*scancode*/, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
        m_IsPanning = false;
        std::cout << "Panning mode deactivated" << std::endl;
        return;
    }
    
    if (!(action == GLFW_PRESS)) {
        return;
    }
    
    switch (key) {
        case GLFW_KEY_Q: {
            if (mods & GLFW_MOD_CONTROL) {
                std::cout << "Quitting to menu..." << std::endl;
                GLFWwindow* window = m_WindowContext->GetWindow();
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            } else if (m_SelectedPiece != nullptr) {
                float rotationAngle = 0.1f;
                m_SelectedPiece->Rotate(rotationAngle);
                std::cout << "Rotated piece counter-clockwise" << std::endl;
            }
            break;
        }
        
        case GLFW_KEY_E: {
            if (m_SelectedPiece != nullptr) {
                float rotationAngle = -0.1f;
                m_SelectedPiece->Rotate(rotationAngle);
                std::cout << "Rotated piece clockwise" << std::endl;
            }
            break;
        }
        
        case GLFW_KEY_F: {
            if (m_SelectedPiece != nullptr) {
                m_SelectedPiece->Flip();
                std::cout << "Flipped piece" << std::endl;
            }
            break;
        }
        
        case GLFW_KEY_R: {
            ResetLevel();
            std::cout << "Level reset" << std::endl;
            break;
        }
        
        case GLFW_KEY_Z: {
            m_ZoomLevel *= 1.2f;
            if (m_ZoomLevel > 10.0f) m_ZoomLevel = 10.0f;
            UpdateViewMatrix();
            std::cout << "Zoomed in. Zoom level: " << m_ZoomLevel << std::endl;
            break;
        }
        
        case GLFW_KEY_X: {
            m_ZoomLevel /= 1.2f;
            if (m_ZoomLevel < 0.1f) m_ZoomLevel = 0.1f;
            UpdateViewMatrix();
            std::cout << "Zoomed out. Zoom level: " << m_ZoomLevel << std::endl;
            break;
        }
        
        case GLFW_KEY_SPACE: {
            GLFWwindow* window = m_WindowContext->GetWindow();
            double mouseX, mouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);
            m_IsPanning = true;
            m_LastPanMouseX = mouseX;
            m_LastPanMouseY = mouseY;
            std::cout << "Panning mode activated (drag mouse)" << std::endl;
            break;
        }
        
        case GLFW_KEY_C: {
            if (CheckSolution()) {
                std::cout << "CONGRATULATIONS! Level completed!" << std::endl;
                m_GameState = GameState::COMPLETED;
            } else {
                std::cout << "Not quite right yet. Keep trying!" << std::endl;
            }
            break;
        }
    }
}

void GameLayer::OnMouseButtonEvent(int button, int action, int mods, double mouseX, double mouseY) {
    float worldX, worldY;
    ConvertScreenToWorld(mouseX, mouseY, worldX, worldY);
    
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
        float ndcX, ndcY;
        ConvertScreenToNDC(mouseX, mouseY, ndcX, ndcY);
        std::cout << "DEBUG: Mouse Click - Screen(" << mouseX << ", " << mouseY << ")"
                  << " NDC(" << ndcX << ", " << ndcY << ")"
                  << " World(" << worldX << ", " << worldY << ")" << std::endl;
    }
    
    if (action == GLFW_RELEASE) {
        if (m_IsTranslating) {
            m_IsTranslating = false;
        }
        if (button == GLFW_MOUSE_BUTTON_MIDDLE && m_IsPanning) {
            m_IsPanning = false;
        }
    }
    
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
        m_IsPanning = true;
        double mouseX, mouseY;
        GLFWwindow* window = m_WindowContext->GetWindow();
        glfwGetCursorPos(window, &mouseX, &mouseY);
        m_LastPanMouseX = mouseX;
        m_LastPanMouseY = mouseY;
        return;
    }
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        m_SelectedPiece = nullptr;
        
        // Check pieces in reverse order (top to bottom in rendering)
        for (int i = m_Pieces.size() - 1; i >= 0; i--) {
            const glm::mat4& modelMatrix = m_Pieces[i]->GetModelMatrix();
            glm::mat4 invModel = glm::inverse(modelMatrix);
            glm::vec4 testPoint(worldX, worldY, 0.0f, 1.0f);
            glm::vec4 localPoint = invModel * testPoint;
            
            if (m_Pieces[i]->IsInside(localPoint.x, localPoint.y)) {
                m_SelectedPiece = m_Pieces[i];
                std::cout << "Selected piece " << i << std::endl;
                break;
            }
        }
        
        if (m_SelectedPiece != nullptr) {
            m_IsTranslating = true;
            m_LastMouseX = worldX;
            m_LastMouseY = worldY;
        }
    }
}

void GameLayer::ResetLevel() {
    for (TangramPiece* piece : m_Pieces) {
        piece->ResetToOriginal();
    }
    m_GameState = GameState::PLAYING;
    m_SelectedPiece = nullptr;
}

bool GameLayer::CheckSolution() {
    // Simple solution check - verify all pieces are roughly in correct positions
    // This is a simplified version - a full implementation would check rotations too
    
    const auto& solution = m_CurrentLevel->GetSolution();
    if (solution.size() != m_Pieces.size()) {
        return false;
    }
    
    int correctPieces = 0;
    for (const auto& targetPos : solution) {
        if (targetPos.pieceIndex >= 0 && targetPos.pieceIndex < (int)m_Pieces.size()) {
            TangramPiece* piece = m_Pieces[targetPos.pieceIndex];
            if (piece->IsCorrectlyPlaced(targetPos.position, targetPos.rotation)) {
                correctPieces++;
            }
        }
    }
    
    // All pieces must be correctly placed
    return correctPieces == (int)m_Pieces.size();
}
