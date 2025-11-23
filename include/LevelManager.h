#pragma once
#include "Level.h"
#include <vector>
#include <memory>

class LevelManager {
public:
    LevelManager();
    ~LevelManager();
    
    void LoadLevels();
    Level* GetLevel(int index);
    int GetLevelCount() const { return m_Levels.size(); }
    
private:
    std::vector<Level*> m_Levels;
    
    // Helper methods to create individual levels
    void CreateLevel1();
    void CreateLevel2();
    void CreateLevel3();
    void CreateLevel4();
    void CreateLevel5();
    void CreateLevel6();
    void CreateLevel7();
    void CreateLevel8();
    void CreateLevel9();
    void CreateLevel10();
};
