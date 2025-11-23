#include "Level.h"

Level::Level(int levelNumber, const std::string& name,
             const std::vector<glm::vec2>& silhouetteVertices,
             const std::vector<PiecePosition>& solution)
    : m_LevelNumber(levelNumber)
    , m_Name(name)
    , m_SilhouetteVertices(silhouetteVertices)
    , m_Solution(solution) {
}
