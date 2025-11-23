#include "Application.h"
#include "MenuLayer.h"
#include "GameLayer.h"
#include "LevelManager.h"
#include <glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

enum class AppState {
    MENU,
    GAME
};

// Global state for callbacks
struct AppContext {
    MenuLayer* menuLayer;
    GameLayer* gameLayer;
    AppState currentState;
    Application* app;
};

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    AppContext* context = (AppContext*)glfwGetWindowUserPointer(window);
    if (context != nullptr && context->app != nullptr) {
        context->app->OnResize(width, height);
    }
}

void MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods) {
    AppContext* context = (AppContext*)glfwGetWindowUserPointer(window);
    
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    
    if (context != nullptr) {
        if (context->currentState == AppState::MENU && context->menuLayer != nullptr) {
            context->menuLayer->OnMouseButtonEvent(button, action, mods, mouseX, mouseY);
        } else if (context->currentState == AppState::GAME && context->gameLayer != nullptr) {
            context->gameLayer->OnMouseButtonEvent(button, action, mods, mouseX, mouseY);
        }
    }
}

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    AppContext* context = (AppContext*)glfwGetWindowUserPointer(window);
    
    if (context != nullptr) {
        if (context->currentState == AppState::MENU && context->menuLayer != nullptr) {
            context->menuLayer->OnKeyEvent(key, scancode, action, mods);
        } else if (context->currentState == AppState::GAME && context->gameLayer != nullptr) {
            context->gameLayer->OnKeyEvent(key, scancode, action, mods);
        }
    }
}

void PrintMenuHelp() {
    std::cout << "\n========================================\n";
    std::cout << "   Tangram Puzzle Game - Menu\n";
    std::cout << "========================================\n\n";
    std::cout << "Click on a level button to start playing!\n";
    std::cout << "Ctrl+Q - Quit application\n\n";
    std::cout << "========================================\n\n";
}

void PrintGameHelp() {
    std::cout << "\n========================================\n";
    std::cout << "   Tangram Puzzle Game - Controls\n";
    std::cout << "========================================\n\n";
    
    std::cout << "PIECE MANIPULATION:\n";
    std::cout << "  Left Click - Select and drag piece\n";
    std::cout << "  Q - Rotate piece counter-clockwise\n";
    std::cout << "  E - Rotate piece clockwise\n";
    std::cout << "  F - Flip piece horizontally\n\n";
    
    std::cout << "VIEW CONTROLS:\n";
    std::cout << "  Z - Zoom in\n";
    std::cout << "  X - Zoom out\n";
    std::cout << "  Middle Mouse Button - Pan (drag to move view)\n";
    std::cout << "  Space + Drag Mouse - Pan (hold space and drag)\n\n";
    
    std::cout << "GAME CONTROLS:\n";
    std::cout << "  R - Reset level\n";
    std::cout << "  C - Check solution\n";
    std::cout << "  Ctrl+Q - Quit to menu\n\n";
    
    std::cout << "GOAL:\n";
    std::cout << "  Arrange all 7 Tangram pieces to match the gray outline!\n\n";
    
    std::cout << "========================================\n\n";
}

int main() {
    Application window(1280, 720, "Tangram Puzzle Game");
    window.Run();
    
    // Initialize level manager
    LevelManager levelManager;
    levelManager.LoadLevels();
    
    std::cout << "Loaded " << levelManager.GetLevelCount() << " levels!\n";
    
    // Create menu layer
    MenuLayer menuLayer("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl", &window, &levelManager);
    
    // App context for managing state
    AppContext context;
    context.menuLayer = &menuLayer;
    context.gameLayer = nullptr;
    context.currentState = AppState::MENU;
    context.app = &window;
    
    glfwSetWindowUserPointer(window.GetWindow(), &context);
    glfwSetMouseButtonCallback(window.GetWindow(), MouseButtonCallBack);
    glfwSetKeyCallback(window.GetWindow(), KeyCallBack);
    glfwSetFramebufferSizeCallback(window.GetWindow(), FramebufferSizeCallback);
    
    PrintMenuHelp();
    
    GameLayer* currentGameLayer = nullptr;
    
    while (!glfwWindowShouldClose(window.GetWindow())) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        if (context.currentState == AppState::MENU) {
            menuLayer.OnUpdate(window.GetWindow());
            menuLayer.OnRender();
            
            // Check if a level was selected
            int selectedLevel = menuLayer.GetSelectedLevel();
            if (selectedLevel >= 0) {
                Level* level = levelManager.GetLevel(selectedLevel);
                if (level != nullptr) {
                    // Switch to game state
                    if (currentGameLayer != nullptr) {
                        delete currentGameLayer;
                    }
                    currentGameLayer = new GameLayer(
                        "shaders/vertex_shader.glsl",
                        "shaders/fragment_shader.glsl",
                        &window,
                        level
                    );
                    context.gameLayer = currentGameLayer;
                    context.currentState = AppState::GAME;
                    menuLayer.ResetSelection();
                    
                    std::cout << "\n=== Starting Level " << (selectedLevel + 1) << ": " 
                              << level->GetName() << " ===\n";
                    PrintGameHelp();
                }
            }
        } else if (context.currentState == AppState::GAME) {
            if (currentGameLayer != nullptr) {
                currentGameLayer->OnUpdate(window.GetWindow());
                currentGameLayer->OnRender();
                
                // Check if level is completed
                if (currentGameLayer->GetGameState() == GameState::COMPLETED) {
                    std::cout << "\n=== Level Completed! Returning to menu... ===\n\n";
                    context.currentState = AppState::MENU;
                    PrintMenuHelp();
                }
            }
        }
        
        glfwSwapBuffers(window.GetWindow());
        glfwPollEvents();
    }
    
    // Cleanup
    if (currentGameLayer != nullptr) {
        delete currentGameLayer;
    }
    
    return 0;
}
