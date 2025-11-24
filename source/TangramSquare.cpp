#include "TangramSquare.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

static const float SQUARE_SIZE = 0.70710678f;  // Matches small triangle leg (0.707)

TangramSquare::TangramSquare(float x, float y, float size, float r, float g, float b)
    : m_ModelMatrix(glm::mat4(1.0f)), m_OriginalModelMatrix(glm::mat4(1.0f)) {
    
    InitializeVertices(x, y, SQUARE_SIZE);
    
    // Set color
    for (size_t i = 0; i < m_Vertices.size(); i += 6) {
        m_Vertices[i + 2] = r;
        m_Vertices[i + 3] = g;
        m_Vertices[i + 4] = b;
        m_Vertices[i + 5] = 1.0f;
    }
    
    m_OriginalVertices = m_Vertices;
    
    // Setup indices for two triangles forming a square
    m_Indices = {0, 1, 2, 2, 3, 0};
    
    // Setup buffer layout
    m_BufferLayout.PushFloat(2);  // Position
    m_BufferLayout.PushFloat(4);  // Color
    
    // Create VAO and IBO
    m_VertexArray = new VertexArray();
    m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size() * sizeof(float), &m_BufferLayout);
    m_IndexBuffer = new IndexBuffer(m_Indices.data(), m_Indices.size());
}

void TangramSquare::InitializeVertices(float x, float y, float size) {
    // Square centered at (x, y)
    float halfSize = size / 2.0f;
    m_Vertices = {
        x - halfSize, y + halfSize, 0.0f, 1.0f, 0.0f, 1.0f,  // Top-left
        x - halfSize, y - halfSize, 0.0f, 1.0f, 0.0f, 1.0f,  // Bottom-left
        x + halfSize, y - halfSize, 0.0f, 1.0f, 0.0f, 1.0f,  // Bottom-right
        x + halfSize, y + halfSize, 0.0f, 1.0f, 0.0f, 1.0f   // Top-right
    };
}

TangramSquare::~TangramSquare() {
    delete m_VertexArray;
    delete m_IndexBuffer;
}

VertexArray& TangramSquare::GetVAO() const {
    return *m_VertexArray;
}

IndexBuffer& TangramSquare::GetIBO() const {
    return *m_IndexBuffer;
}

GLenum TangramSquare::GetDrawnMode() {
    return GL_TRIANGLES;
}

void TangramSquare::UpdateVertices(double mouseX, double mouseY) {
    // Not used in Tangram game
}

void TangramSquare::AddPoint(double x, double y) {
    // Not used in Tangram game
}

void TangramSquare::FinalizeShape() {
    // Not used in Tangram game
}

void TangramSquare::SetColor(float r, float g, float b) {
    for (size_t i = 0; i < m_Vertices.size(); i += 6) {
        m_Vertices[i + 2] = r;
        m_Vertices[i + 3] = g;
        m_Vertices[i + 4] = b;
        m_Vertices[i + 5] = 1.0f;
    }
    m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size() * sizeof(float), &m_BufferLayout);
}

bool TangramSquare::IsInside(float ndcX, float ndcY) const {
    // Get the four corners
    float minX = m_Vertices[0];
    float maxX = m_Vertices[12];
    float minY = m_Vertices[7];
    float maxY = m_Vertices[1];
    
    // Simple bounding box check (works for axis-aligned squares)
    return (ndcX >= minX && ndcX <= maxX && ndcY >= minY && ndcY <= maxY);
}

const glm::mat4& TangramSquare::GetModelMatrix() const {
    return m_ModelMatrix;
}

void TangramSquare::Translate(float dx, float dy) {
    if (m_IsLocked) return;
    glm::vec3 translationVector(dx, dy, 0.0f);
    m_ModelMatrix = glm::translate(glm::mat4(1.0f), translationVector) * m_ModelMatrix;
}

void TangramSquare::Rotate(float angle) {
    if (m_IsLocked) return;
    
    float centerX = (m_Vertices[0] + m_Vertices[12]) / 2.0f;
    float centerY = (m_Vertices[1] + m_Vertices[7]) / 2.0f;
    
    glm::mat4 rotateMatrix = glm::mat4(1.0f);
    rotateMatrix = glm::translate(rotateMatrix, glm::vec3(centerX, centerY, 0.0f));
    rotateMatrix = glm::rotate(rotateMatrix, angle, glm::vec3(0.0f, 0.0f, 1.0f));
    rotateMatrix = glm::translate(rotateMatrix, glm::vec3(-centerX, -centerY, 0.0f));
    
    m_ModelMatrix = m_ModelMatrix * rotateMatrix;
}

void TangramSquare::Scale(float sx, float sy) {
    // Not used in Tangram
}

float TangramSquare::GetArea() const {
    float sideLength = m_Vertices[12] - m_Vertices[0];
    return sideLength * sideLength;
}

float TangramSquare::GetPerimeter() const {
    float sideLength = m_Vertices[12] - m_Vertices[0];
    return 4.0f * sideLength;
}

void TangramSquare::Flip() {
    // Square is symmetric, so flip doesn't change appearance
    // But we track the state for consistency
    m_IsFlipped = !m_IsFlipped;
}

void TangramSquare::ResetToOriginal() {
    m_ModelMatrix = m_OriginalModelMatrix;
    m_Vertices = m_OriginalVertices;
    m_IsFlipped = false;
    m_IsLocked = false;
}

PieceType TangramSquare::GetPieceType() const {
    return PieceType::SQUARE;
}

bool TangramSquare::IsCorrectlyPlaced(const glm::vec2& targetPos, float targetRotation) const {
    glm::vec2 currentCenter = GetCenter();
    
    float positionTolerance = 0.2f;
    float distance = glm::length(currentCenter - targetPos);
    
    return distance < positionTolerance;
}

glm::vec2 TangramSquare::GetCenter() const {
    glm::vec4 center(
        (m_Vertices[0] + m_Vertices[12]) / 2.0f,
        (m_Vertices[1] + m_Vertices[7]) / 2.0f,
        0.0f,
        1.0f
    );
    
    glm::vec4 worldCenter = m_ModelMatrix * center;
    return glm::vec2(worldCenter.x, worldCenter.y);
}

glm::vec2 TangramSquare::GetLocalCenter() const {
    // Square center is average of vertices
    return glm::vec2(
        (m_Vertices[0] + m_Vertices[6] + m_Vertices[12] + m_Vertices[18]) / 4.0f,
        (m_Vertices[1] + m_Vertices[7] + m_Vertices[13] + m_Vertices[19]) / 4.0f
    );
}

const std::vector<float>& TangramSquare::GetVertices() const {
    return m_Vertices;
}
