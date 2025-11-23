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

// Level 1: Simple Square
void LevelManager::CreateLevel1() {
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-1.0f, 1.0f),
        glm::vec2(-1.0f, -1.0f),
        glm::vec2(1.0f, -1.0f),
        glm::vec2(1.0f, 1.0f)
    };
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(0.0f, 0.5f), 0.0f},      // Large triangle 1
        {1, glm::vec2(0.0f, -0.5f), 0.0f},     // Large triangle 2
        {2, glm::vec2(0.5f, 0.0f), 0.0f},      // Medium triangle
        {3, glm::vec2(-0.5f, 0.5f), 0.0f},     // Small triangle 1
        {4, glm::vec2(-0.5f, -0.5f), 0.0f},    // Small triangle 2
        {5, glm::vec2(0.0f, 0.0f), 0.0f},      // Square
        {6, glm::vec2(0.5f, -0.5f), 0.0f}      // Parallelogram
    };
    
    m_Levels.push_back(new Level(1, "Square", silhouette, solution));
}

// Level 2: Triangle
void LevelManager::CreateLevel2() {
    std::vector<glm::vec2> silhouette = {
        glm::vec2(0.0f, 1.5f),
        glm::vec2(-1.5f, -1.0f),
        glm::vec2(1.5f, -1.0f)
    };
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(0.0f, 0.5f), 0.0f},
        {1, glm::vec2(-0.5f, -0.5f), 0.0f},
        {2, glm::vec2(0.5f, 0.0f), 0.0f},
        {3, glm::vec2(-0.3f, 0.3f), 0.0f},
        {4, glm::vec2(0.3f, -0.3f), 0.0f},
        {5, glm::vec2(0.0f, 0.0f), 0.0f},
        {6, glm::vec2(0.5f, -0.5f), 0.0f}
    };
    
    m_Levels.push_back(new Level(2, "Triangle", silhouette, solution));
}

// Level 3: Cat
void LevelManager::CreateLevel3() {
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-0.5f, 1.5f),   // Left ear
        glm::vec2(-1.0f, 1.0f),
        glm::vec2(-0.8f, 0.5f),   // Head
        glm::vec2(-1.2f, 0.0f),
        glm::vec2(-0.5f, -0.5f),  // Body
        glm::vec2(0.0f, -1.0f),
        glm::vec2(0.5f, -0.5f),
        glm::vec2(1.2f, 0.0f),
        glm::vec2(0.8f, 0.5f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.5f, 1.5f)     // Right ear
    };
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(-0.5f, 1.0f), 0.785f},  // Large triangle - left ear
        {1, glm::vec2(0.5f, 1.0f), -0.785f},  // Large triangle - right ear
        {2, glm::vec2(0.0f, 0.3f), 0.0f},     // Medium triangle - head
        {3, glm::vec2(-0.6f, -0.2f), 0.0f},   // Small triangle
        {4, glm::vec2(0.6f, -0.2f), 0.0f},    // Small triangle
        {5, glm::vec2(0.0f, -0.5f), 0.785f},  // Square - body
        {6, glm::vec2(0.0f, -1.0f), 0.0f}     // Parallelogram - tail
    };
    
    m_Levels.push_back(new Level(3, "Cat", silhouette, solution));
}

// Level 4: House
void LevelManager::CreateLevel4() {
    std::vector<glm::vec2> silhouette = {
        glm::vec2(0.0f, 1.5f),    // Roof peak
        glm::vec2(-1.0f, 0.5f),   // Left roof
        glm::vec2(-1.0f, -1.0f),  // Bottom left
        glm::vec2(1.0f, -1.0f),   // Bottom right
        glm::vec2(1.0f, 0.5f)     // Right roof
    };
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(-0.5f, 0.8f), 0.785f},  // Large triangle - left roof
        {1, glm::vec2(0.5f, 0.8f), -0.785f},  // Large triangle - right roof
        {2, glm::vec2(-0.3f, -0.3f), 0.0f},   // Medium triangle
        {3, glm::vec2(0.3f, 0.0f), 0.0f},     // Small triangle
        {4, glm::vec2(-0.5f, -0.7f), 0.0f},   // Small triangle
        {5, glm::vec2(0.3f, -0.5f), 0.0f},    // Square
        {6, glm::vec2(0.0f, -0.8f), 0.0f}     // Parallelogram
    };
    
    m_Levels.push_back(new Level(4, "House", silhouette, solution));
}

// Level 5: Bird
void LevelManager::CreateLevel5() {
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-1.5f, 0.5f),   // Beak
        glm::vec2(-0.8f, 0.8f),   // Head
        glm::vec2(-0.5f, 1.2f),
        glm::vec2(0.0f, 0.8f),    // Body
        glm::vec2(0.5f, 0.5f),
        glm::vec2(1.5f, 1.0f),    // Wing
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.5f, -0.5f),
        glm::vec2(0.0f, -1.0f),   // Tail
        glm::vec2(-0.5f, -0.5f),
        glm::vec2(-1.0f, 0.0f)
    };
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(0.8f, 0.6f), 0.785f},   // Large triangle - wing
        {1, glm::vec2(-0.3f, -0.5f), 0.0f},   // Large triangle - tail
        {2, glm::vec2(-0.8f, 0.5f), 0.0f},    // Medium triangle - beak
        {3, glm::vec2(-0.3f, 0.8f), 0.0f},    // Small triangle - head
        {4, glm::vec2(0.3f, 0.0f), 0.0f},     // Small triangle
        {5, glm::vec2(0.0f, 0.3f), 0.0f},     // Square - body
        {6, glm::vec2(0.5f, -0.3f), 0.0f}     // Parallelogram
    };
    
    m_Levels.push_back(new Level(5, "Bird", silhouette, solution));
}

// Level 6: Boat
void LevelManager::CreateLevel6() {
    std::vector<glm::vec2> silhouette = {
        glm::vec2(0.0f, 1.5f),    // Sail top
        glm::vec2(-0.5f, 0.5f),   // Sail
        glm::vec2(-1.5f, -0.5f),  // Hull left
        glm::vec2(-1.0f, -1.0f),
        glm::vec2(1.0f, -1.0f),
        glm::vec2(1.5f, -0.5f),   // Hull right
        glm::vec2(0.5f, 0.5f)
    };
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(0.0f, 0.8f), 0.0f},     // Large triangle - sail
        {1, glm::vec2(0.0f, -0.5f), 0.0f},    // Large triangle - hull
        {2, glm::vec2(-0.5f, 0.0f), 0.0f},    // Medium triangle
        {3, glm::vec2(0.5f, 0.3f), 0.0f},     // Small triangle
        {4, glm::vec2(-0.8f, -0.8f), 0.0f},   // Small triangle
        {5, glm::vec2(0.3f, -0.2f), 0.0f},    // Square
        {6, glm::vec2(0.8f, -0.7f), 0.0f}     // Parallelogram
    };
    
    m_Levels.push_back(new Level(6, "Boat", silhouette, solution));
}

// Level 7: Running Person
void LevelManager::CreateLevel7() {
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-0.3f, 1.5f),   // Head
        glm::vec2(-0.6f, 1.0f),
        glm::vec2(-0.8f, 0.5f),   // Body
        glm::vec2(-1.0f, 0.0f),
        glm::vec2(-0.5f, -0.5f),  // Legs
        glm::vec2(0.0f, -1.0f),
        glm::vec2(0.5f, -0.5f),
        glm::vec2(1.5f, 0.0f),    // Arms
        glm::vec2(1.0f, 0.5f),
        glm::vec2(0.5f, 1.0f),
        glm::vec2(0.3f, 1.5f)
    };
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(0.0f, 1.0f), 0.0f},     // Large triangle - head
        {1, glm::vec2(0.0f, -0.3f), 0.0f},    // Large triangle - body
        {2, glm::vec2(0.8f, 0.3f), 0.0f},     // Medium triangle - arm
        {3, glm::vec2(-0.5f, 0.5f), 0.0f},    // Small triangle
        {4, glm::vec2(0.3f, -0.8f), 0.0f},    // Small triangle - leg
        {5, glm::vec2(0.0f, 0.2f), 0.0f},     // Square
        {6, glm::vec2(-0.5f, -0.5f), 0.0f}    // Parallelogram - leg
    };
    
    m_Levels.push_back(new Level(7, "Running Person", silhouette, solution));
}

// Level 8: Fish
void LevelManager::CreateLevel8() {
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-1.5f, 0.0f),   // Tail
        glm::vec2(-0.8f, 0.5f),
        glm::vec2(-0.5f, 0.8f),   // Body
        glm::vec2(0.5f, 0.8f),
        glm::vec2(1.0f, 0.5f),    // Head
        glm::vec2(1.5f, 0.0f),
        glm::vec2(1.0f, -0.5f),
        glm::vec2(0.5f, -0.8f),
        glm::vec2(-0.5f, -0.8f),
        glm::vec2(-0.8f, -0.5f)
    };
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(0.5f, 0.3f), 0.0f},     // Large triangle - head
        {1, glm::vec2(-0.5f, 0.0f), 0.0f},    // Large triangle - body
        {2, glm::vec2(-1.0f, 0.0f), 0.785f},  // Medium triangle - tail
        {3, glm::vec2(0.0f, 0.5f), 0.0f},     // Small triangle
        {4, glm::vec2(0.0f, -0.5f), 0.0f},    // Small triangle
        {5, glm::vec2(0.8f, 0.0f), 0.0f},     // Square
        {6, glm::vec2(-0.3f, -0.3f), 0.0f}    // Parallelogram
    };
    
    m_Levels.push_back(new Level(8, "Fish", silhouette, solution));
}

// Level 9: Candle
void LevelManager::CreateLevel9() {
    std::vector<glm::vec2> silhouette = {
        glm::vec2(0.0f, 1.8f),    // Flame
        glm::vec2(-0.2f, 1.5f),
        glm::vec2(-0.3f, 1.0f),   // Candle top
        glm::vec2(-0.5f, 0.5f),
        glm::vec2(-0.5f, -0.5f),  // Candle body
        glm::vec2(-0.3f, -1.0f),
        glm::vec2(0.3f, -1.0f),
        glm::vec2(0.5f, -0.5f),
        glm::vec2(0.5f, 0.5f),
        glm::vec2(0.3f, 1.0f),
        glm::vec2(0.2f, 1.5f)
    };
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(0.0f, 1.3f), 0.0f},     // Large triangle - flame
        {1, glm::vec2(0.0f, 0.0f), 0.0f},     // Large triangle - body
        {2, glm::vec2(0.0f, -0.6f), 0.0f},    // Medium triangle - base
        {3, glm::vec2(-0.3f, 0.8f), 0.0f},    // Small triangle
        {4, glm::vec2(0.3f, 0.8f), 0.0f},     // Small triangle
        {5, glm::vec2(0.0f, 0.5f), 0.0f},     // Square
        {6, glm::vec2(0.0f, -0.3f), 0.0f}     // Parallelogram
    };
    
    m_Levels.push_back(new Level(9, "Candle", silhouette, solution));
}

// Level 10: Rabbit
void LevelManager::CreateLevel10() {
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-0.8f, 1.8f),   // Left ear
        glm::vec2(-1.0f, 1.2f),
        glm::vec2(-0.8f, 0.8f),   // Head
        glm::vec2(-1.2f, 0.3f),
        glm::vec2(-0.8f, -0.2f),  // Body
        glm::vec2(-0.5f, -0.8f),
        glm::vec2(0.0f, -1.2f),   // Legs
        glm::vec2(0.5f, -0.8f),
        glm::vec2(0.8f, -0.2f),
        glm::vec2(1.2f, 0.3f),
        glm::vec2(0.8f, 0.8f),
        glm::vec2(1.0f, 1.2f),
        glm::vec2(0.8f, 1.8f)     // Right ear
    };
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(-0.5f, 1.3f), 0.0f},    // Large triangle - left ear
        {1, glm::vec2(0.5f, 1.3f), 0.0f},     // Large triangle - right ear
        {2, glm::vec2(0.0f, 0.5f), 0.0f},     // Medium triangle - head
        {3, glm::vec2(-0.5f, 0.0f), 0.0f},    // Small triangle
        {4, glm::vec2(0.5f, 0.0f), 0.0f},     // Small triangle
        {5, glm::vec2(0.0f, -0.3f), 0.0f},    // Square - body
        {6, glm::vec2(0.0f, -0.9f), 0.0f}     // Parallelogram - legs
    };
    
    m_Levels.push_back(new Level(10, "Rabbit", silhouette, solution));
}
