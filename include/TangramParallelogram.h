#pragma once
#include "TangramPiece.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "BufferLayout.h"
#include <vector>
#include <glm/glm.hpp>

class TangramParallelogram : public TangramPiece {
public:
    TangramParallelogram(float x, float y, float size, float r, float g, float b);
    ~TangramParallelogram();
    
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
    virtual glm::vec2 GetCenter() const override;
    virtual glm::vec2 GetLocalCenter() const override;
    virtual const std::vector<float>& GetVertices() const override;
    float GetRotation() const override { return m_CurrentRotation; }
    
private:
    void InitializeVertices(float x, float y, float size);
    
    std::vector<float> m_Vertices;
    std::vector<float> m_OriginalVertices;
    std::vector<unsigned int> m_Indices;
    
    BufferLayout m_BufferLayout;
    VertexArray* m_VertexArray;
    IndexBuffer* m_IndexBuffer;
    
    glm::mat4 m_ModelMatrix;
    glm::mat4 m_OriginalModelMatrix;
    
    // Store original color for reset
    float m_OriginalR, m_OriginalG, m_OriginalB;
};
