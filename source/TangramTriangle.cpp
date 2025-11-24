#include "TangramTriangle.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

// Traditional Tangram triangle sizes (relative to unit square)
static const float LARGE_TRIANGLE_SIZE = 1.41421356f;
static const float MEDIUM_TRIANGLE_SIZE = 1.0f;
static const float SMALL_TRIANGLE_SIZE = 0.70710678f;

TangramTriangle::TangramTriangle(float x, float y, TriangleSize size, float r, float g, float b)
    : m_Size(size), m_ModelMatrix(glm::mat4(1.0f)), m_OriginalModelMatrix(glm::mat4(1.0f)) {
    
    float sizeValue;
    switch (size) {
        case TriangleSize::LARGE:
            sizeValue = LARGE_TRIANGLE_SIZE;
            break;
        case TriangleSize::MEDIUM:
            sizeValue = MEDIUM_TRIANGLE_SIZE;
            break;
        case TriangleSize::SMALL:
            sizeValue = SMALL_TRIANGLE_SIZE;
            break;
    }
    
    InitializeVertices(x, y, sizeValue);
    
    // Set color
    for (size_t i = 0; i < m_Vertices.size(); i += 6) {
        m_Vertices[i + 2] = r;
        m_Vertices[i + 3] = g;
        m_Vertices[i + 4] = b;
        m_Vertices[i + 5] = 1.0f;
    }
    
    m_OriginalVertices = m_Vertices;
    
    // Setup indices for a triangle
    m_Indices = {0, 1, 2};
    
    // Setup buffer layout
    m_BufferLayout.PushFloat(2);  // Position
    m_BufferLayout.PushFloat(4);  // Color
    
    // Create VAO and IBO
    m_VertexArray = new VertexArray();
    m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size() * sizeof(float), &m_BufferLayout);
    m_IndexBuffer = new IndexBuffer(m_Indices.data(), m_Indices.size());
}

void TangramTriangle::InitializeVertices(float x, float y, float size) {
    // Right isosceles triangle with right angle at bottom-left
    // Vertices: top, bottom-left, bottom-right
    m_Vertices = {
        x, y + size, 0.0f, 1.0f, 0.0f, 1.0f,           // Top vertex
        x, y, 0.0f, 1.0f, 0.0f, 1.0f,                  // Bottom-left vertex
        x + size, y, 0.0f, 1.0f, 0.0f, 1.0f            // Bottom-right vertex
    };
}

TangramTriangle::~TangramTriangle() {
    delete m_VertexArray;
    delete m_IndexBuffer;
}

VertexArray& TangramTriangle::GetVAO() const {
    return *m_VertexArray;
}

IndexBuffer& TangramTriangle::GetIBO() const {
    return *m_IndexBuffer;
}

GLenum TangramTriangle::GetDrawnMode() {
    return GL_TRIANGLES;
}

void TangramTriangle::UpdateVertices(double mouseX, double mouseY) {
    // Not used in Tangram game (pieces are pre-defined)
}

void TangramTriangle::AddPoint(double x, double y) {
    // Not used in Tangram game
}

void TangramTriangle::FinalizeShape() {
    // Not used in Tangram game
}

void TangramTriangle::SetColor(float r, float g, float b) {
    for (size_t i = 0; i < m_Vertices.size(); i += 6) {
        m_Vertices[i + 2] = r;
        m_Vertices[i + 3] = g;
        m_Vertices[i + 4] = b;
        m_Vertices[i + 5] = 1.0f;
    }
    m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size() * sizeof(float), &m_BufferLayout);
}

static float sign(float x1, float y1, float x2, float y2, float x3, float y3) {
    return (x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3);
}

bool TangramTriangle::IsInside(float ndcX, float ndcY) const {
    float v0_x = m_Vertices[0];
    float v0_y = m_Vertices[1];
    float v1_x = m_Vertices[6];
    float v1_y = m_Vertices[7];
    float v2_x = m_Vertices[12];
    float v2_y = m_Vertices[13];
    
    float d1 = sign(ndcX, ndcY, v0_x, v0_y, v1_x, v1_y);
    float d2 = sign(ndcX, ndcY, v1_x, v1_y, v2_x, v2_y);
    float d3 = sign(ndcX, ndcY, v2_x, v2_y, v0_x, v0_y);
    
    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);
    
    return !(has_neg && has_pos);
}

const glm::mat4& TangramTriangle::GetModelMatrix() const {
    return m_ModelMatrix;
}

void TangramTriangle::Translate(float dx, float dy) {
    if (m_IsLocked) return;
    glm::vec3 translationVector(dx, dy, 0.0f);
    m_ModelMatrix = glm::translate(glm::mat4(1.0f), translationVector) * m_ModelMatrix;
}

void TangramTriangle::Rotate(float angle) {
    if (m_IsLocked) return;
    
    float centerX = (m_Vertices[0] + m_Vertices[6] + m_Vertices[12]) / 3.0f;
    float centerY = (m_Vertices[1] + m_Vertices[7] + m_Vertices[13]) / 3.0f;
    
    glm::mat4 rotateMatrix = glm::mat4(1.0f);
    rotateMatrix = glm::translate(rotateMatrix, glm::vec3(centerX, centerY, 0.0f));
    rotateMatrix = glm::rotate(rotateMatrix, angle, glm::vec3(0.0f, 0.0f, 1.0f));
    rotateMatrix = glm::translate(rotateMatrix, glm::vec3(-centerX, -centerY, 0.0f));
    
    m_ModelMatrix = m_ModelMatrix * rotateMatrix;
}

void TangramTriangle::Scale(float sx, float sy) {
    // Not used in Tangram (pieces maintain fixed size)
}

float TangramTriangle::GetArea() const {
    float x1 = m_Vertices[0], y1 = m_Vertices[1];
    float x2 = m_Vertices[6], y2 = m_Vertices[7];
    float x3 = m_Vertices[12], y3 = m_Vertices[13];
    
    return std::abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0f);
}

float TangramTriangle::GetPerimeter() const {
    float x1 = m_Vertices[0], y1 = m_Vertices[1];
    float x2 = m_Vertices[6], y2 = m_Vertices[7];
    float x3 = m_Vertices[12], y3 = m_Vertices[13];
    
    float side1 = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    float side2 = std::sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    float side3 = std::sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
    
    return side1 + side2 + side3;
}

void TangramTriangle::Flip() {
    if (m_IsLocked) return;
    
    m_IsFlipped = !m_IsFlipped;
    
    // Flip horizontally by scaling x by -1
    float centerX = (m_Vertices[0] + m_Vertices[6] + m_Vertices[12]) / 3.0f;
    float centerY = (m_Vertices[1] + m_Vertices[7] + m_Vertices[13]) / 3.0f;
    
    glm::mat4 flipMatrix = glm::mat4(1.0f);
    flipMatrix = glm::translate(flipMatrix, glm::vec3(centerX, centerY, 0.0f));
    flipMatrix = glm::scale(flipMatrix, glm::vec3(-1.0f, 1.0f, 1.0f));
    flipMatrix = glm::translate(flipMatrix, glm::vec3(-centerX, -centerY, 0.0f));
    
    m_ModelMatrix = m_ModelMatrix * flipMatrix;
}

void TangramTriangle::ResetToOriginal() {
    m_ModelMatrix = m_OriginalModelMatrix;
    m_Vertices = m_OriginalVertices;
    m_IsFlipped = false;
    m_IsLocked = false;
}

PieceType TangramTriangle::GetPieceType() const {
    switch (m_Size) {
        case TriangleSize::LARGE:
            return PieceType::LARGE_TRIANGLE;
        case TriangleSize::MEDIUM:
            return PieceType::MEDIUM_TRIANGLE;
        case TriangleSize::SMALL:
            return PieceType::SMALL_TRIANGLE;
    }
    return PieceType::SMALL_TRIANGLE;
}

bool TangramTriangle::IsCorrectlyPlaced(const glm::vec2& targetPos, float targetRotation) const {
    glm::vec2 currentCenter = GetCenter();
    
    // Check position (with some tolerance)
    float positionTolerance = 0.2f;
    float distance = glm::length(currentCenter - targetPos);
    
    // For now, just check position
    // TODO: Add rotation checking if needed
    return distance < positionTolerance;
}

glm::vec2 TangramTriangle::GetCenter() const {
    // Apply model matrix to get world position
    glm::vec4 center(
        (m_Vertices[0] + m_Vertices[6] + m_Vertices[12]) / 3.0f,
        (m_Vertices[1] + m_Vertices[7] + m_Vertices[13]) / 3.0f,
        0.0f,
        1.0f
    );
    
    glm::vec4 worldCenter = m_ModelMatrix * center;
    return glm::vec2(worldCenter.x, worldCenter.y);
}

glm::vec2 TangramTriangle::GetLocalCenter() const {
    // For a right isosceles triangle with right angle at bottom-left
    // Vertices: top, bottom-left, bottom-right
    // Center is average of vertices
    // But we need to account for the fact that vertices are relative to (x,y)
    // The vertices are stored as absolute coordinates in m_Vertices
    
    return glm::vec2(
        (m_Vertices[0] + m_Vertices[6] + m_Vertices[12]) / 3.0f,
        (m_Vertices[1] + m_Vertices[7] + m_Vertices[13]) / 3.0f
    );
}

const std::vector<float>& TangramTriangle::GetVertices() const {
    return m_Vertices;
}
