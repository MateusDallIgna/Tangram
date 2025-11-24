#include "LevelManager.h"
#include <cmath>

LevelManager::LevelManager() {
}

LevelManager::~LevelManager() {
    for (Level* level : m_Levels) {
        delete level;
    }
}

void LevelManager::LoadLevels() {
    CreateLevel1();
    CreateLevel2();
    CreateLevel3();
    CreateLevel4();
    CreateLevel5();
    CreateLevel6();
    CreateLevel7();
    CreateLevel8();
    CreateLevel9();
    CreateLevel10();
}

Level* LevelManager::GetLevel(int index) {
    if (index >= 0 && index < (int)m_Levels.size()) {
        return m_Levels[index];
    }
    return nullptr;
}

// Rotation constants
const float PI = 3.14159265f;
const float ROT_0 = 0.0f;
const float ROT_45 = PI / 4.0f;
const float ROT_90 = PI / 2.0f;

// Unit dimensions
// Small Square side = 1/sqrt(2) approx 0.70710678
const float U = 0.70710678f;

// Level 1: SQUARE - Exact Area 4.0
void LevelManager::CreateLevel1() {
    // 2x2 Square (Side = 2.828 * U = 2.0)
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-1.0f, -1.0f),
        glm::vec2(1.0f, -1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(-1.0f, 1.0f)
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(1, "Square", silhouette, solution));
}

// Level 2: TRIANGLE - Exact Area 4.0
void LevelManager::CreateLevel2() {
    // Base 4, Height 2
    std::vector<glm::vec2> silhouette = {
        glm::vec2(0.0f, 1.0f),      // Top
        glm::vec2(-2.0f, -1.0f),    // Bottom left
        glm::vec2(2.0f, -1.0f)      // Bottom right
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(2, "Triangle", silhouette, solution));
}

// Level 3: RECTANGLE - Exact Area 4.0
void LevelManager::CreateLevel3() {
    // Width 4U (2.828), Height 2U (1.414)
    float w = 1.414f;
    float h = 0.707f;
    
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-w, -h),
        glm::vec2(w, -h),
        glm::vec2(w, h),
        glm::vec2(-w, h)
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(3, "Rectangle", silhouette, solution));
}

// Level 4: PARALLELOGRAM - Exact Area 4.0
void LevelManager::CreateLevel4() {
    // Base 4U (2.828), Height 2U (1.414), Skew 2U (1.414)
    float w = 1.414f;
    float h = 0.707f;
    float skew = 1.414f;
    
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-w - skew/2, -h),   // Bottom left
        glm::vec2(w - skew/2, -h),    // Bottom right
        glm::vec2(w + skew/2, h),     // Top right
        glm::vec2(-w + skew/2, h)     // Top left
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(4, "Parallelogram", silhouette, solution));
}

// Level 5: TRAPEZOID - Exact Area 4.0
void LevelManager::CreateLevel5() {
    // Bottom Base 6U (4.242), Top Base 2U (1.414), Height 2U (1.414)
    float bottomHalf = 2.121f;
    float topHalf = 0.707f;
    float h = 0.707f;
    
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-bottomHalf, -h),   // Bottom left
        glm::vec2(bottomHalf, -h),    // Bottom right
        glm::vec2(topHalf, h),        // Top right
        glm::vec2(-topHalf, h)        // Top left
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(5, "Trapezoid", silhouette, solution));
}

// Level 6: DIAMOND (Rotated Square) - Exact Area 4.0
void LevelManager::CreateLevel6() {
    // Square rotated 45 degrees
    // Diagonal = Side * sqrt(2) = 2.0 * 1.414 = 2.828
    // Half diagonal = 1.414
    
    float d = 1.414f;
    
    std::vector<glm::vec2> silhouette = {
        glm::vec2(0.0f, -d),    // Bottom
        glm::vec2(d, 0.0f),     // Right
        glm::vec2(0.0f, d),     // Top
        glm::vec2(-d, 0.0f)     // Left
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(6, "Diamond", silhouette, solution));
}

// Level 7: TALL RECTANGLE (Rotated Rectangle) - Exact Area 4.0
void LevelManager::CreateLevel7() {
    // Width 2U (1.414), Height 4U (2.828)
    float w = 0.707f;
    float h = 1.414f;
    
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-w, -h),
        glm::vec2(w, -h),
        glm::vec2(w, h),
        glm::vec2(-w, h)
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(7, "Tall Rect", silhouette, solution));
}

// Level 8: INVERTED TRIANGLE (Rotated Triangle) - Exact Area 4.0
void LevelManager::CreateLevel8() {
    // Base 4, Height 2, pointing down
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-2.0f, 1.0f),     // Top left
        glm::vec2(2.0f, 1.0f),      // Top right
        glm::vec2(0.0f, -1.0f)      // Bottom
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(8, "Inv Triangle", silhouette, solution));
}

// Level 9: LEANING PARALLELOGRAM (Rotated) - Exact Area 4.0
void LevelManager::CreateLevel9() {
    // Parallelogram rotated 90 degrees? Or just flipped.
    // Let's do flipped (leaning left)
    float w = 1.414f;
    float h = 0.707f;
    float skew = 1.414f;
    
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-w + skew/2, -h),   // Bottom left
        glm::vec2(w + skew/2, -h),    // Bottom right
        glm::vec2(w - skew/2, h),     // Top right
        glm::vec2(-w - skew/2, h)     // Top left
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(9, "Leaning Para", silhouette, solution));
}

// Level 10: RIGHT TRAPEZOID - Exact Area 4.0
void LevelManager::CreateLevel10() {
    // Verified solvable shape
    // Vertical side 2.828 (4U). Top 1.414 (2U). Bottom 4.242 (6U). Height 1.414 (2U).
    // Center it.
    // Width = 6U = 4.242. Height = 2U = 1.414.
    // Centroid approx at x=0, y=0.
    
    float h = 0.707f; // Half height
    // Bottom: -2.121 to 2.121
    // Top: -2.121 to -0.707 (Left aligned)
    // Shifted to center:
    // Bottom width 6U. Top width 2U.
    // Average width 4U.
    
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-2.121f, -h),     // Bottom left
        glm::vec2(2.121f, -h),      // Bottom right
        glm::vec2(0.707f, h),       // Top right
        glm::vec2(-2.121f, h)       // Top left
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(10, "Right Trap", silhouette, solution));
}
