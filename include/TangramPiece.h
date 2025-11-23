#pragma once
#include "Shape.h"
#include <glm/glm.hpp>

enum class PieceType {
    LARGE_TRIANGLE,
    MEDIUM_TRIANGLE,
    SMALL_TRIANGLE,
    SQUARE,
    PARALLELOGRAM
};

class TangramPiece : public Shape {
public:
    virtual ~TangramPiece() {}
    
    // Tangram-specific methods
    virtual void Flip() = 0;
    virtual void ResetToOriginal() = 0;
    virtual PieceType GetPieceType() const = 0;
    
    // Check if piece is in correct position (for solution validation)
    virtual bool IsCorrectlyPlaced(const glm::vec2& targetPos, float targetRotation) const = 0;
    
    // Get the center of the piece in world coordinates
    virtual glm::vec2 GetCenter() const = 0;
    
    // Lock/unlock piece (when correctly placed)
    void SetLocked(bool locked) { m_IsLocked = locked; }
    bool IsLocked() const { return m_IsLocked; }
    
protected:
    bool m_IsLocked = false;
    bool m_IsFlipped = false;
};
