#include "TangramParallelogram.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

static const float PARALLELOGRAM_SIZE = 1.0f;  // Base size

TangramParallelogram::TangramParallelogram(float x, float y, float size, float r, float g, float b)
    : m_ModelMatrix(glm::mat4(1.0f)), m_OriginalModelMatrix(glm::mat4(1.0f)) {
    
    InitializeVertices(x, y, PARALLELOGRAM_SIZE);
    
    // Set color
    for (size_t i = 0; i < m_Vertices.size(); i += 6) {
        m_Vertices[i + 2] = r;
        m_Vertices[i + 3] = g;
        m_Vertices[i + 4] = b;
        m_Vertices[i + 5] = 1.0f;
    }
    
    m_OriginalVertices = m_Vertices;
    
    // Setup indices for two triangles forming a parallelogram
    m_Indices = {0, 1, 2, 2, 3, 0};
    
    // Setup buffer layout
    m_BufferLayout.PushFloat(2);  // Position
    m_BufferLayout.PushFloat(4);  // Color
    
    // Create VAO and IBO
    m_VertexArray = new VertexArray();
    m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size() * sizeof(float), &m_BufferLayout);
    m_IndexBuffer = new IndexBuffer(m_Indices.data(), m_Indices.size());
}

void TangramParallelogram::InitializeVertices(float x, float y, float size) {
    // Parallelogram with 45-degree slant
    // Base width = size, height = size/2, offset = size/2
    float width = size;
    float height = size / 2.0f;
    float offset = size / 2.0f;
    
    m_Vertices = {
        x, y + height, 0.0f, 1.0f, 0.0f, 1.0f,              // Top-left
        x - offset, y, 0.0f, 1.0f, 0.0f, 1.0f,              // Bottom-left
        x - offset + width, y, 0.0f, 1.0f, 0.0f, 1.0f,      // Bottom-right
        x + width, y + height, 0.0f, 1.0f, 0.0f, 1.0f       // Top-right
    };
}

TangramParallelogram::~TangramParallelogram() {
    delete m_VertexArray;
    delete m_IndexBuffer;
}

VertexArray& TangramParallelogram::GetVAO() const {
    return *m_VertexArray;
}

IndexBuffer& TangramParallelogram::GetIBO() const {
    return *m_IndexBuffer;
}

GLenum TangramParallelogram::GetDrawnMode() {
    return GL_TRIANGLES;
}

void TangramParallelogram::UpdateVertices(double mouseX, double mouseY) {
    // Not used in Tangram game
}

void TangramParallelogram::AddPoint(double x, double y) {
    // Not used in Tangram game
}

void TangramParallelogram::FinalizeShape() {
    // Not used in Tangram game
}

void TangramParallelogram::SetColor(float r, float g, float b) {
    for (size_t i = 0; i < m_Vertices.size(); i += 6) {
        m_Vertices[i + 2] = r;
        m_Vertices[i + 3] = g;
        m_Vertices[i + 4] = b;
        m_Vertices[i + 5] = 1.0f;
    }
    m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size() * sizeof(float), &m_BufferLayout);
}

// Point-in-parallelogram test
bool TangramParallelogram::IsInside(float ndcX, float ndcY) const {
    // Use cross product method for quadrilateral
    auto sign = [](float x1, float y1, float x2, float y2, float x3, float y3) -> float {
        return (x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3);
    };
    
    float v0_x = m_Vertices[0], v0_y = m_Vertices[1];
    float v1_x = m_Vertices[6], v1_y = m_Vertices[7];
    float v2_x = m_Vertices[12], v2_y = m_Vertices[13];
    float v3_x = m_Vertices[18], v3_y = m_Vertices[19];
    
    // Check if point is on the same side of all edges
    float d1 = sign(ndcX, ndcY, v0_x, v0_y, v1_x, v1_y);
    float d2 = sign(ndcX, ndcY, v1_x, v1_y, v2_x, v2_y);
    float d3 = sign(ndcX, ndcY, v2_x, v2_y, v3_x, v3_y);
    float d4 = sign(ndcX, ndcY, v3_x, v3_y, v0_x, v0_y);
    
    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0) || (d4 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0) || (d4 > 0);
    
    return !(has_neg && has_pos);
}

const glm::mat4& TangramParallelogram::GetModelMatrix() const {
    return m_ModelMatrix;
}

void TangramParallelogram::Translate(float dx, float dy) {
    if (m_IsLocked) return;
    glm::vec3 translationVector(dx, dy, 0.0f);
    m_ModelMatrix = glm::translate(glm::mat4(1.0f), translationVector) * m_ModelMatrix;
}

void TangramParallelogram::Rotate(float angle) {
    if (m_IsLocked) return;
    
    float centerX = (m_Vertices[0] + m_Vertices[12]) / 2.0f;
    float centerY = (m_Vertices[1] + m_Vertices[7]) / 2.0f;
    
    glm::mat4 rotateMatrix = glm::mat4(1.0f);
    rotateMatrix = glm::translate(rotateMatrix, glm::vec3(centerX, centerY, 0.0f));
    rotateMatrix = glm::rotate(rotateMatrix, angle, glm::vec3(0.0f, 0.0f, 1.0f));
    rotateMatrix = glm::translate(rotateMatrix, glm::vec3(-centerX, -centerY, 0.0f));
    
    m_ModelMatrix = m_ModelMatrix * rotateMatrix;
}

void TangramParallelogram::Scale(float sx, float sy) {
    // Not used in Tangram
}

float TangramParallelogram::GetArea() const {
    // Area = base * height
    float base = std::sqrt(
        (m_Vertices[12] - m_Vertices[6]) * (m_Vertices[12] - m_Vertices[6]) +
        (m_Vertices[13] - m_Vertices[7]) * (m_Vertices[13] - m_Vertices[7])
    );
    float height = m_Vertices[1] - m_Vertices[7];
    return base * height;
}

float TangramParallelogram::GetPerimeter() const {
    float side1 = std::sqrt(
        (m_Vertices[6] - m_Vertices[0]) * (m_Vertices[6] - m_Vertices[0]) +
        (m_Vertices[7] - m_Vertices[1]) * (m_Vertices[7] - m_Vertices[1])
    );
    float side2 = std::sqrt(
        (m_Vertices[12] - m_Vertices[6]) * (m_Vertices[12] - m_Vertices[6]) +
        (m_Vertices[13] - m_Vertices[7]) * (m_Vertices[13] - m_Vertices[7])
    );
    return 2.0f * (side1 + side2);
}

void TangramParallelogram::Flip() {
    if (m_IsLocked) return;
    
    m_IsFlipped = !m_IsFlipped;
    
    // Flip horizontally
    float centerX = (m_Vertices[0] + m_Vertices[12]) / 2.0f;
    float centerY = (m_Vertices[1] + m_Vertices[7]) / 2.0f;
    
    glm::mat4 flipMatrix = glm::mat4(1.0f);
    flipMatrix = glm::translate(flipMatrix, glm::vec3(centerX, centerY, 0.0f));
    flipMatrix = glm::scale(flipMatrix, glm::vec3(-1.0f, 1.0f, 1.0f));
    flipMatrix = glm::translate(flipMatrix, glm::vec3(-centerX, -centerY, 0.0f));
    
    m_ModelMatrix = m_ModelMatrix * flipMatrix;
}

void TangramParallelogram::ResetToOriginal() {
    m_ModelMatrix = m_OriginalModelMatrix;
    m_Vertices = m_OriginalVertices;
    m_IsFlipped = false;
    m_IsLocked = false;
}

PieceType TangramParallelogram::GetPieceType() const {
    return PieceType::PARALLELOGRAM;
}

bool TangramParallelogram::IsCorrectlyPlaced(const glm::vec2& targetPos, float targetRotation) const {
    glm::vec2 currentCenter = GetCenter();
    
    float positionTolerance = 0.2f;
    float distance = glm::length(currentCenter - targetPos);
    
    return distance < positionTolerance;
}

glm::vec2 TangramParallelogram::GetCenter() const {
    glm::vec4 center(
        (m_Vertices[0] + m_Vertices[12]) / 2.0f,
        (m_Vertices[1] + m_Vertices[7]) / 2.0f,
        0.0f,
        1.0f
    );
    
    glm::vec4 worldCenter = m_ModelMatrix * center;
    return glm::vec2(worldCenter.x, worldCenter.y);
}

glm::vec2 TangramParallelogram::GetLocalCenter() const {
    // Parallelogram center is average of vertices
    // But we need to account for the fact that vertices are relative to (x,y)
    // The vertices are stored as absolute coordinates in m_Vertices
    
    return glm::vec2(
        (m_Vertices[0] + m_Vertices[6] + m_Vertices[12] + m_Vertices[18]) / 4.0f,
        (m_Vertices[1] + m_Vertices[7] + m_Vertices[13] + m_Vertices[19]) / 4.0f
    );
}

const std::vector<float>& TangramParallelogram::GetVertices() const {
    return m_Vertices;
}
