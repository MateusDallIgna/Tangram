# Tangram Puzzle Game

A traditional Tangram puzzle game built with OpenGL and C++. Arrange 7 geometric pieces to match target shapes across 10 creative levels!

## Features

- **10 Unique Levels**: Square, Triangle, Rectangle, Cow, Trapezoid, Elephant, Whale, Turtle, Horse, and Cat
- **7 Traditional Tangram Pieces**: 2 large triangles, 1 medium triangle, 2 small triangles, 1 square, and 1 parallelogram
- **Ghost Piece Visualization**: Semi-transparent overlays show exactly where each piece should go
- **Smart Auto-Snap**: Pieces automatically snap to correct position, rotation, and flip state when placed nearby
- **Colorful Pieces**: Each piece has a distinct color for easy identification
- **Visual Feedback**: Pieces turn green when correctly locked in place
- **Intuitive Controls**: Move, rotate, and flip pieces with mouse and keyboard
- **Position Capture Tool**: Press 'P' to capture current piece positions (for level creation)

## Building

### Using Makefile (Recommended)

```bash
make          # Build the program
make run      # Build and run the program
make clean    # Remove build artifacts
make rebuild  # Clean and rebuild
make help     # Show help message
```

The executable will be created in the root directory as `Tangram`.

### Manual Compilation

```bash
g++ source/main.cpp source/Application.cpp source/Renderer.cpp source/Shader.cpp \
    source/VertexArray.cpp source/IndexBuffer.cpp \
    source/Rectangle.cpp source/Triangle.cpp source/Circle.cpp source/Polygon.cpp \
    source/TangramTriangle.cpp source/TangramSquare.cpp source/TangramParallelogram.cpp \
    source/Level.cpp source/LevelManager.cpp source/GameLayer.cpp source/MenuLayer.cpp \
    source/glad.c \
    -I./include \
    -lglfw -lGL -lGLU -ldl -lpthread -lwayland-client -lwayland-cursor -lwayland-egl -lX11 \
    -std=c++17 -o Tangram
```

**Note**: Run the executable from the root directory so it can find the `shaders/` folder.

## Requirements

- g++ compiler (C++17 support)
- GLFW library
- OpenGL libraries
- Wayland libraries (for Wayland/Hyprland)
- X11 libraries (for X11 compatibility)

## Controls

### Menu
- **Left Click** - Select a level to play
- **Ctrl+Q** - Quit application

### Game

#### Piece Manipulation
- **Left Click & Drag** - Move piece
- **Q** - Rotate piece counter-clockwise
- **E** - Rotate piece clockwise
- **R** - Rotate piece 45 degrees
- **F** - Flip piece horizontally

#### View Controls
- **Z** - Zoom in
- **X** - Zoom out
- **Middle Mouse Button** - Pan (drag to move view)
- **Space + Drag Mouse** - Pan (hold space and drag)

#### Game Controls
- **C** - Check solution (verify if puzzle is solved)
- **P** - Print current piece positions (for level creation)
- **Ctrl+Q** - Quit to menu

## Running

After building, run the executable from the root directory:

```bash
./Tangram
```

The program will display the level selection menu. Click on any level button to start playing!

## Gameplay

1. **Select a Level**: Click on a level button in the menu
2. **See Ghost Pieces**: Semi-transparent gray pieces show target positions
3. **Arrange the Pieces**: Drag pieces close to their ghost positions
4. **Auto-Snap**: Pieces automatically snap and turn green when correctly placed
5. **Complete the Level**: When all 7 pieces are green, you've won!

### How Snapping Works

- **Position-Based**: Just drag pieces close to ghost positions (within 0.25 units)
- **Auto-Correction**: Rotation and flip state are automatically corrected
- **Visual Feedback**: Pieces turn green and lock when correctly placed
- **Locked Pieces**: Cannot be moved or rotated once locked

## Levels

1. **Square** - Classic 2x2 square formation
2. **Triangle** - Isosceles triangle
3. **Rectangle** - Wide rectangle
4. **Cow** - Creative animal shape
5. **Trapezoid** - Geometric trapezoid
6. **Elephant** - Majestic elephant silhouette
7. **Whale** - Sea creature
8. **Turtle** - Turtle with four legs
9. **Horse** - Standing horse
10. **Cat** - Sitting cat

## Project Structure

```
Tangram/
├── include/              # Header files
│   ├── Application.h     # Window and OpenGL management
│   ├── Shader.h          # Shader program management
│   ├── Renderer.h        # Rendering system
│   ├── Shape.h           # Base shape interface
│   ├── TangramPiece.h    # Tangram piece base class
│   ├── TangramTriangle.h # Triangle pieces
│   ├── TangramSquare.h   # Square piece
│   ├── TangramParallelogram.h # Parallelogram piece
│   ├── Level.h           # Level data structure
│   ├── LevelManager.h    # Level management
│   ├── GameLayer.h       # Game logic layer
│   └── MenuLayer.h       # Menu interface layer
├── source/               # Source files
├── shaders/              # GLSL shader files
├── Makefile              # Build configuration
└── README.md             # This file
```

## Technical Details

- **Graphics API**: OpenGL 3.3 Core Profile
- **Windowing**: GLFW
- **Math Library**: GLM (OpenGL Mathematics)
- **Rendering**: Vertex Array Objects (VAO) and Index Buffer Objects (IBO)
- **Shaders**: GLSL vertex and fragment shaders
- **Architecture**: Layer-based design with polymorphic shape system
- **Snapping System**: Position-based with auto-correction for rotation and flip
- **Ghost Rendering**: Semi-transparent overlays using shader uniform colors

## Development Tools

- **Position Capture ('P' key)**: Prints current piece positions in C++ format for easy level creation
- **Solution Checking ('C' key)**: Verifies all pieces are correctly locked

## Notes

- The program works with both Wayland Hyprland and X11
- Shader files must be in the `shaders/` directory relative to the executable
- All transformations use GLM transformation matrices
- Ghost pieces only appear for unlocked pieces
- Snapping tolerance: 0.25 units for position, auto-corrects rotation and flip

## Credits

Built using OpenGL, GLFW, and GLM. Inspired by the traditional Chinese Tangram puzzle.

Enjoy solving the puzzles! 🧩✨
