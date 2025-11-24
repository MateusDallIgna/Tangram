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
const float ROT_135 = 3.0f * PI / 4.0f;
const float ROT_180 = PI;
const float ROT_225 = 5.0f * PI / 4.0f;
const float ROT_270 = 3.0f * PI / 2.0f;
const float ROT_315 = 7.0f * PI / 4.0f;

// Level 1: SQUARE - Exact Area 4.0
void LevelManager::CreateLevel1() {
    // 2x2 Square centered at origin
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
    // Width 2.828, Height 1.414 (sqrt(8) x sqrt(2))
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

// Level 4: HOUSE - Exact Area 4.0
void LevelManager::CreateLevel4() {
    // Base 2x1 (Area 2), Roof Base 2 Height 2 (Area 2)
    std::vector<glm::vec2> silhouette = {
        glm::vec2(0.0f, 2.0f),      // Roof peak
        glm::vec2(-1.0f, 0.0f),     // Left roof edge
        glm::vec2(-1.0f, -1.0f),    // Bottom left
        glm::vec2(1.0f, -1.0f),     // Bottom right
        glm::vec2(1.0f, 0.0f)       // Right roof edge
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(4, "House", silhouette, solution));
}

// Level 5: BOAT - Approx Area 4.0
void LevelManager::CreateLevel5() {
    // Scaled down from previous version (factor ~0.7)
    std::vector<glm::vec2> silhouette = {
        glm::vec2(0.0f, 1.4f),      // Sail top
        glm::vec2(-0.5f, 0.0f),     // Sail left
        glm::vec2(-1.0f, -0.5f),    // Hull left
        glm::vec2(-0.5f, -1.0f),    // Hull bottom left
        glm::vec2(0.5f, -1.0f),     // Hull bottom right
        glm::vec2(1.0f, -0.5f),     // Hull right
        glm::vec2(0.5f, 0.0f)       // Sail right
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(5, "Boat", silhouette, solution));
}

// Level 6: ARROW - Approx Area 4.0
void LevelManager::CreateLevel6() {
    // Scaled down
    std::vector<glm::vec2> silhouette = {
        glm::vec2(1.4f, 0.0f),      // Arrow tip
        glm::vec2(0.5f, 0.7f),      // Top of head
        glm::vec2(0.5f, 0.35f),     // Top of shaft
        glm::vec2(-1.0f, 0.35f),    // Shaft top left
        glm::vec2(-1.0f, -0.35f),   // Shaft bottom left
        glm::vec2(0.5f, -0.35f),    // Bottom of shaft
        glm::vec2(0.5f, -0.7f)      // Bottom of head
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(6, "Arrow", silhouette, solution));
}

// Level 7: CAT - Approx Area 4.0
void LevelManager::CreateLevel7() {
    // Scaled down
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-0.5f, 1.4f),     // Left ear
        glm::vec2(-0.35f, 1.0f),    // Head left
        glm::vec2(-0.7f, 0.0f),     // Body left
        glm::vec2(-0.5f, -1.0f),    // Bottom left
        glm::vec2(0.5f, -1.0f),     // Bottom right
        glm::vec2(0.7f, 0.0f),      // Body right
        glm::vec2(0.35f, 1.0f),     // Head right
        glm::vec2(0.5f, 1.4f),      // Right ear
        glm::vec2(0.0f, 1.2f)       // Head top
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(7, "Cat", silhouette, solution));
}

// Level 8: BIRD - Approx Area 4.0
void LevelManager::CreateLevel8() {
    // Scaled down
    std::vector<glm::vec2> silhouette = {
        glm::vec2(1.4f, 1.0f),      // Beak
        glm::vec2(0.5f, 0.5f),      // Head
        glm::vec2(0.7f, 0.0f),      // Right wing top
        glm::vec2(0.0f, 0.0f),      // Body center
        glm::vec2(-1.4f, -1.0f),    // Left wing tip
        glm::vec2(-0.5f, 0.0f),     // Left wing top
        glm::vec2(-1.0f, 0.5f)      // Tail
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(8, "Bird", silhouette, solution));
}

// Level 9: FISH - Approx Area 4.0
void LevelManager::CreateLevel9() {
    // Scaled down
    std::vector<glm::vec2> silhouette = {
        glm::vec2(1.4f, 0.0f),      // Nose
        glm::vec2(0.7f, 0.5f),      // Top fin
        glm::vec2(0.0f, 0.7f),      // Top body
        glm::vec2(-0.7f, 0.5f),     // Tail top
        glm::vec2(-1.2f, 0.0f),     // Tail tip
        glm::vec2(-0.7f, -0.5f),    // Tail bottom
        glm::vec2(0.0f, -0.7f),     // Bottom body
        glm::vec2(0.7f, -0.5f)      // Bottom fin
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(9, "Fish", silhouette, solution));
}

// Level 10: CANDLE - Approx Area 4.0
void LevelManager::CreateLevel10() {
    // Scaled down
    std::vector<glm::vec2> silhouette = {
        glm::vec2(0.0f, 1.4f),      // Flame tip
        glm::vec2(-0.35f, 1.0f),    // Flame left
        glm::vec2(-0.5f, 0.7f),     // Candle top left
        glm::vec2(-0.5f, -1.0f),    // Candle bottom left
        glm::vec2(0.5f, -1.0f),     // Candle bottom right
        glm::vec2(0.5f, 0.7f),      // Candle top right
        glm::vec2(0.35f, 1.0f)      // Flame right
    };
    
    std::vector<PiecePosition> solution = {};
    m_Levels.push_back(new Level(10, "Candle", silhouette, solution));
}
