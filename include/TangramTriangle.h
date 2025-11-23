#pragma once
#include "TangramPiece.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "BufferLayout.h"
#include <vector>
#include <glm/glm.hpp>

enum class TriangleSize {
    LARGE,
    MEDIUM,
    SMALL
};

class TangramTriangle : public TangramPiece {
public:
    TangramTriangle(float x, float y, TriangleSize size, float r, float g, float b);
    ~TangramTriangle();
    
    // Shape interface implementation
    VertexArray& GetVAO() const override;
    IndexBuffer& GetIBO() const override;
    GLenum GetDrawnMode() override;
    
    void UpdateVertices(double mouseX, double mouseY) override;
    void AddPoint(double x, double y) override;
    void FinalizeShape() override;
    
    void SetColor(float r, float g, float b) override;
    bool IsInside(float ndcX, float ndcY) const override;
    
    const glm::mat4& GetModelMatrix() const override;
    void Translate(float dx, float dy) override;
    void Rotate(float angle) override;
    void Scale(float sx, float sy) override;
    
    float GetArea() const override;
    float GetPerimeter() const override;
    
    // TangramPiece interface implementation
    void Flip() override;
    void ResetToOriginal() override;
    PieceType GetPieceType() const override;
    bool IsCorrectlyPlaced(const glm::vec2& targetPos, float targetRotation) const override;
    glm::vec2 GetCenter() const override;
    
private:
    void InitializeVertices(float x, float y, float size);
    
    std::vector<float> m_Vertices;
    std::vector<float> m_OriginalVertices;
    std::vector<unsigned int> m_Indices;
    
    BufferLayout m_BufferLayout;
    VertexArray* m_VertexArray;
    IndexBuffer* m_IndexBuffer;
    
    TriangleSize m_Size;
    glm::mat4 m_ModelMatrix;
    glm::mat4 m_OriginalModelMatrix;
};
