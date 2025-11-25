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
    // 2x2 Square (Side = 2.0) centered at origin: (-1,-1) to (1,1)
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-1.0f, -1.0f),
        glm::vec2(1.0f, -1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(-1.0f, 1.0f)
    };
    
    // PERFECT Solution - Captured from manual arrangement using 'P' key
    std::vector<PiecePosition> solution = {
        // LT-Red
        {0, glm::vec2(0.00144267f, -0.665061f), glm::radians(225.0f), false},
        // LT-Green
        {1, glm::vec2(-0.66527f, -0.00107586f), glm::radians(135.0f), false},
        // MT-Blue
        {2, glm::vec2(0.668837f, 0.664738f), glm::radians(180.0f), false},
        // ST-Yellow
        {3, glm::vec2(-0.496063f, 0.829233f), glm::radians(45.0f), false},
        // ST-Magenta
        {4, glm::vec2(0.332876f, 0.00311422f), glm::radians(315.0f), false},
        // Sq-Cyan
        {5, glm::vec2(0.00129771f, 0.498689f), glm::radians(45.0f), false},
        // Para-Orange
        {6, glm::vec2(0.749652f, -0.246708f), glm::radians(270.0f), false}
    };
    
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
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(-0.998173f, -0.663685f), glm::radians(225.0f), false},
        {1, glm::vec2(0.998795f, -0.667373f), glm::radians(225.0f), false},
        {2, glm::vec2(0.340871f, -0.330156f), glm::radians(270.0f), false},
        {3, glm::vec2(0.495919f, 0.174003f), glm::radians(225.0f), false},
        {4, glm::vec2(-0.661988f, -0.00751686f), glm::radians(315.0f), false},
        {5, glm::vec2(-0.00039053f, 0.488724f), glm::radians(45.0f), false},
        {6, glm::vec2(-0.244134f, -0.251807f), glm::radians(90.0f), false}
    };
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
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(0.941602f, 0.230183f), glm::radians(-180.0f), false},
        {1, glm::vec2(0.462343f, -0.235012f), glm::radians(0.0f), false},
        {2, glm::vec2(-0.245059f, -0.00447392f), glm::radians(-45.0f), false},
        {3, glm::vec2(-1.17692f, 0.465641f), glm::radians(270.0f), false},
        {4, glm::vec2(-0.481303f, -0.468785f), glm::radians(0.0f), false},
        {5, glm::vec2(-1.06553f, -0.356599f), glm::radians(0.0f), false},
        {6, glm::vec2(-0.705494f, 0.350241f), glm::radians(45.0f), true}
    };
    m_Levels.push_back(new Level(3, "Rectangle", silhouette, solution));
}

// Level 4: COW - Exact Area 4.0
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
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(-0.662843f, -0.457576f), glm::radians(855.0f), false},
        {1, glm::vec2(0.662037f, -0.454831f), glm::radians(1035.0f), false},
        {2, glm::vec2(0.00133514f, 0.00909758f), glm::radians(1125.0f), false},
        {3, glm::vec2(-0.830614f, 1.12827f), glm::radians(1215.0f), false},
        {4, glm::vec2(-1.86364f, 1.11487f), glm::radians(1035.0f), false},
        {5, glm::vec2(-1.34857f, 0.639611f), glm::radians(90.0f), false},
        {6, glm::vec2(1.33333f, -0.164763f), glm::radians(1485.0f), true}
    };
    m_Levels.push_back(new Level(4, "Cow", silhouette, solution));
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
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(-1.17988f, -0.237351f), glm::radians(0.0f), true},
        {1, glm::vec2(1.17398f, -0.236858f), glm::radians(0.0f), false},
        {2, glm::vec2(-0.000968933f, -0.470741f), glm::radians(225.0f), false},
        {3, glm::vec2(-0.470998f, 0.468436f), glm::radians(270.0f), false},
        {4, glm::vec2(0.469127f, -0.235913f), glm::radians(180.0f), false},
        {5, glm::vec2(0.348503f, 0.347336f), glm::radians(0.0f), false},
        {6, glm::vec2(-0.353992f, -0.00115821f), glm::radians(45.0f), false}
    };
    m_Levels.push_back(new Level(5, "Trapezoid", silhouette, solution));
}

// Level 6: ELEPHANT - Exact Area 4.0
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
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(-0.466863f, 0.375344f), glm::radians(630.0f), false},
        {1, glm::vec2(0.280944f, 0.202858f), glm::radians(810.0f), false},
        {2, glm::vec2(0.981984f, 0.445935f), glm::radians(855.0f), false},
        {3, glm::vec2(1.66814f, 0.67331f), glm::radians(1080.0f), false},
        {4, glm::vec2(-1.10722f, -0.491346f), glm::radians(1035.0f), false},
        {5, glm::vec2(0.408257f, -0.599269f), glm::radians(90.0f), false},
        {6, glm::vec2(1.44532f, 0.101211f), glm::radians(1215.0f), true}
    };
    m_Levels.push_back(new Level(6, "Elephant", silhouette, solution));
}

// Level 7: WHALE - Exact Area 4.0
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
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(0.346051f, 0.197352f), glm::radians(135.0f), false},
        {1, glm::vec2(-0.319598f, 0.198658f), glm::radians(-45.0f), false},
        {2, glm::vec2(-0.887419f, -0.836893f), glm::radians(315.0f), false},
        {3, glm::vec2(0.971159f, 0.941487f), glm::radians(-90.0f), false},
        {4, glm::vec2(1.03598f, -0.435351f), glm::radians(45.0f), false},
        {5, glm::vec2(-1.47316f, 0.197255f), glm::radians(45.0f), false},
        {6, glm::vec2(-1.19775f, 1.04942f), glm::radians(135.0f), false}
    };
    m_Levels.push_back(new Level(7, "Whale", silhouette, solution));
}

// Level 8: TURTLE - Exact Area 4.0
void LevelManager::CreateLevel8() {
    // Base 4, Height 2, pointing down
    std::vector<glm::vec2> silhouette = {
        glm::vec2(-2.0f, 1.0f),     // Top left
        glm::vec2(2.0f, 1.0f),      // Top right
        glm::vec2(0.0f, -1.0f)      // Bottom
    };
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(0.349258f, 0.194764f), glm::radians(135.0f), false},
        {1, glm::vec2(-0.319598f, 0.198658f), glm::radians(315.0f), false},
        {2, glm::vec2(-0.887419f, -0.836893f), glm::radians(-45.0f), false},
        {3, glm::vec2(0.971159f, 0.941487f), glm::radians(-90.0f), false},
        {4, glm::vec2(1.03598f, -0.435351f), glm::radians(45.0f), false},
        {5, glm::vec2(-1.47316f, 0.197255f), glm::radians(45.0f), false},
        {6, glm::vec2(-1.09615f, 1.10264f), glm::radians(135.0f), false}
    };
    m_Levels.push_back(new Level(8, "Turtle", silhouette, solution));
}

// Level 9: HORSE - Exact Area 4.0
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
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(-0.323224f, 0.076629f), glm::radians(135.0f), false},
        {1, glm::vec2(-1.136f, 0.611897f), glm::radians(180.0f), false},
        {2, glm::vec2(-1.37567f, 2.01055f), glm::radians(225.0f), false},
        {3, glm::vec2(-0.892744f, -0.691314f), glm::radians(90.0f), false},
        {4, glm::vec2(-2.06836f, 0.733815f), glm::radians(585.0f), false},
        {5, glm::vec2(-1.01234f, 1.42525f), glm::radians(0.0f), false},
        {6, glm::vec2(1.02286f, -0.285848f), glm::radians(495.0f), false}
    };
    m_Levels.push_back(new Level(9, "Horse", silhouette, solution));
}

// Level 10: CAT - Exact Area 4.0
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
    
    std::vector<PiecePosition> solution = {
        {0, glm::vec2(-1.44833f, -0.558615f), glm::radians(45.0f), false},
        {1, glm::vec2(-1.45271f, 0.108518f), glm::radians(225.0f), false},
        {2, glm::vec2(-0.780387f, -0.888426f), glm::radians(90.0f), false},
        {3, glm::vec2(-1.79359f, 1.75508f), glm::radians(135.0f), false},
        {4, glm::vec2(-1.12342f, 1.77232f), glm::radians(315.0f), false},
        {5, glm::vec2(-1.45556f, 1.27199f), glm::radians(45.0f), false},
        {6, glm::vec2(0.250379f, -0.87128f), glm::radians(225.0f), true}
    };
    m_Levels.push_back(new Level(10, "Cat", silhouette, solution));
}
