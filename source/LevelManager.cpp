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

// Level 1: SQUARE - scaled to fit all 7 pieces
void LevelManager::CreateLevel1() {
    // Square outline - standard Tangram square size
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-1.5f, -1.5f),
        glm::vec2(1.5f, -1.5f),
        glm::vec2(1.5f, 1.5f),
        glm::vec2(-1.5f, 1.5f)
    };
    
    std::vector<PiecePosition> solution = {};
    
    m_Levels.push_back(new Level(1, "Square", silhouette, solution));
}

// Level 2: TRIANGLE - scaled to fit all pieces
void LevelManager::CreateLevel2() {
    // Triangle outline pointing up
    std::vector<glm::vec2> silhouette = {
        glm::vec2(0.0f, 2.0f),      // Top
        glm::vec2(-2.0f, -1.5f),    // Bottom left
        glm::vec2(2.0f, -1.5f)      // Bottom right
    };
    
    std::vector<PiecePosition> solution = {};
    
    m_Levels.push_back(new Level(2, "Triangle", silhouette, solution));
}

// Level 3: RECTANGLE - scaled properly
void LevelManager::CreateLevel3() {
    // Wide rectangle outline
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-2.5f, -1.0f),
        glm::vec2(2.5f, -1.0f),
        glm::vec2(2.5f, 1.0f),
        glm::vec2(-2.5f, 1.0f)
    };
    
    std::vector<PiecePosition> solution = {};
    
    m_Levels.push_back(new Level(3, "Rectangle", silhouette, solution));
}

// Level 4: HOUSE - scaled to fit all pieces
void LevelManager::CreateLevel4() {
    // House outline with triangular roof
    std::vector<glm::vec2> silhouette = {
        glm::vec2(0.0f, 2.0f),      // Roof peak
        glm::vec2(-1.5f, 0.5f),     // Left roof edge
        glm::vec2(-1.5f, -1.5f),    // Bottom left
        glm::vec2(1.5f, -1.5f),     // Bottom right
        glm::vec2(1.5f, 0.5f)       // Right roof edge
    };
    
    std::vector<PiecePosition> solution = {};
    
    m_Levels.push_back(new Level(4, "House", silhouette, solution));
}

// Level 5: BOAT - scaled properly
void LevelManager::CreateLevel5() {
    // Boat outline with sail
    std::vector<glm::vec2> silhouette = {
        glm::vec2(0.0f, 2.0f),      // Sail top
        glm::vec2(-0.75f, 0.0f),    // Sail left
        glm::vec2(-1.5f, -0.75f),   // Hull left
        glm::vec2(-0.75f, -1.5f),   // Hull bottom left
        glm::vec2(0.75f, -1.5f),    // Hull bottom right
        glm::vec2(1.5f, -0.75f),    // Hull right
        glm::vec2(0.75f, 0.0f)      // Sail right
    };
    
    std::vector<PiecePosition> solution = {};
    
    m_Levels.push_back(new Level(5, "Boat", silhouette, solution));
}

// Level 6: ARROW - scaled to fit
void LevelManager::CreateLevel6() {
    // Arrow pointing right
    std::vector<glm::vec2> silhouette = {
        glm::vec2(2.0f, 0.0f),      // Arrow tip
        glm::vec2(0.75f, 1.0f),     // Top of head
        glm::vec2(0.75f, 0.5f),     // Top of shaft
        glm::vec2(-1.5f, 0.5f),     // Shaft top left
        glm::vec2(-1.5f, -0.5f),    // Shaft bottom left
        glm::vec2(0.75f, -0.5f),    // Bottom of shaft
        glm::vec2(0.75f, -1.0f)     // Bottom of head
    };
    
    std::vector<PiecePosition> solution = {};
    
    m_Levels.push_back(new Level(6, "Arrow", silhouette, solution));
}

// Level 7: CAT - scaled properly
void LevelManager::CreateLevel7() {
    // Sitting cat outline
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-0.75f, 2.0f),    // Left ear
        glm::vec2(-0.5f, 1.5f),     // Head left
        glm::vec2(-1.0f, 0.0f),     // Body left
        glm::vec2(-0.75f, -1.5f),   // Bottom left
        glm::vec2(0.75f, -1.5f),    // Bottom right
        glm::vec2(1.0f, 0.0f),      // Body right
        glm::vec2(0.5f, 1.5f),      // Head right
        glm::vec2(0.75f, 2.0f),     // Right ear
        glm::vec2(0.0f, 1.75f)      // Head top
    };
    
    std::vector<PiecePosition> solution = {};
    
    m_Levels.push_back(new Level(7, "Cat", silhouette, solution));
}

// Level 8: BIRD - scaled to fit
void LevelManager::CreateLevel8() {
    // Flying bird outline
    std::vector<glm::vec2> silhouette = {
        glm::vec2(2.0f, 1.5f),      // Beak
        glm::vec2(0.75f, 0.75f),    // Head
        glm::vec2(1.0f, 0.0f),      // Right wing top
        glm::vec2(0.0f, 0.0f),      // Body center
        glm::vec2(-2.0f, -1.5f),    // Left wing tip
        glm::vec2(-0.75f, 0.0f),    // Left wing top
        glm::vec2(-1.5f, 0.75f)     // Tail
    };
    
    std::vector<PiecePosition> solution = {};
    
    m_Levels.push_back(new Level(8, "Bird", silhouette, solution));
}

// Level 9: FISH - scaled properly
void LevelManager::CreateLevel9() {
    // Fish swimming right
    std::vector<glm::vec2> silhouette = {
        glm::vec2(2.0f, 0.0f),      // Nose
        glm::vec2(1.0f, 0.75f),     // Top fin
        glm::vec2(0.0f, 1.0f),      // Top body
        glm::vec2(-1.0f, 0.75f),    // Tail top
        glm::vec2(-1.75f, 0.0f),    // Tail tip
        glm::vec2(-1.0f, -0.75f),   // Tail bottom
        glm::vec2(0.0f, -1.0f),     // Bottom body
        glm::vec2(1.0f, -0.75f)     // Bottom fin
    };
    
    std::vector<PiecePosition> solution = {};
    
    m_Levels.push_back(new Level(9, "Fish", silhouette, solution));
}

// Level 10: CANDLE - scaled to fit
void LevelManager::CreateLevel10() {
    // Candle with flame
    std::vector<glm::vec2> silhouette = {
        glm::vec2(0.0f, 2.0f),      // Flame tip
        glm::vec2(-0.5f, 1.5f),     // Flame left
        glm::vec2(-0.75f, 1.0f),    // Candle top left
        glm::vec2(-0.75f, -1.5f),   // Candle bottom left
        glm::vec2(0.75f, -1.5f),    // Candle bottom right
        glm::vec2(0.75f, 1.0f),     // Candle top right
        glm::vec2(0.5f, 1.5f)       // Flame right
    };
    
    std::vector<PiecePosition> solution = {};
    
    m_Levels.push_back(new Level(10, "Candle", silhouette, solution));
}
