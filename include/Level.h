#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>

struct PiecePosition {
    int pieceIndex;           // Index in the pieces array
    glm::vec2 position;       // Target position
    float rotation;           // Target rotation in radians
};

class Level {
public:
    Level(int levelNumber, const std::string& name, 
          const std::vector<glm::vec2>& silhouetteVertices,
          const std::vector<PiecePosition>& solution);
    
    int GetLevelNumber() const { return m_LevelNumber; }
    const std::string& GetName() const { return m_Name; }
    const std::vector<glm::vec2>& GetSilhouetteVertices() const { return m_SilhouetteVertices; }
    const std::vector<PiecePosition>& GetSolution() const { return m_Solution; }
    
private:
    int m_LevelNumber;
    std::string m_Name;
    std::vector<glm::vec2> m_SilhouetteVertices;  // Outline of target shape
    std::vector<PiecePosition> m_Solution;         // Solution piece positions
};
