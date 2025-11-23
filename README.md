# Tangram Puzzle Game

A traditional Tangram puzzle game built with OpenGL and C++. Arrange 7 geometric pieces to match target silhouettes across 10 challenging levels!

## Features

- **10 Unique Levels**: Square, Triangle, Cat, House, Bird, Boat, Running Person, Fish, Candle, and Rabbit
- **7 Traditional Tangram Pieces**: 2 large triangles, 1 medium triangle, 2 small triangles, 1 square, and 1 parallelogram
- **Colorful Pieces**: Each piece has a distinct color for easy identification
- **Intuitive Controls**: Move, rotate, and flip pieces with mouse and keyboard
- **View Controls**: Zoom and pan to get the perfect view
- **Level Selection Menu**: Simple text-based menu for choosing levels

## Building

### Using Makefile (Recommended)

The easiest way to build is using the provided Makefile:

```bash
make          # Build the program
make run      # Build and run the program
make clean    # Remove build artifacts
make help     # Show help message
```

The executable will be created in the root directory as `Tangram`.

### Manual Compilation

If you prefer to compile manually:

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

**Note**: When compiling manually, make sure to:
- Compile from the root directory (or adjust paths accordingly)
- Run the executable from the root directory so it can find the `shaders/` folder
- Include the `-std=c++17` flag for C++17 features

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
- **Left Click** - Select and drag piece
- **Q** - Rotate piece counter-clockwise
- **E** - Rotate piece clockwise
- **F** - Flip piece horizontally

#### View Controls
- **Z** - Zoom in
- **X** - Zoom out
- **Middle Mouse Button** - Pan (drag to move view)
- **Space + Drag Mouse** - Pan (hold space and drag)

#### Game Controls
- **R** - Reset level (return all pieces to starting positions)
- **C** - Check solution (verify if puzzle is solved)
- **Ctrl+Q** - Quit to menu

## Running

After building, run the executable from the root directory:

```bash
./Tangram
```

The program will display the level selection menu. Click on any level button to start playing!

## Gameplay

1. **Select a Level**: Click on a level button in the menu
2. **Arrange the Pieces**: The 7 Tangram pieces will appear on the right side of the screen
3. **Match the Silhouette**: Move, rotate, and flip pieces to match the gray outline on the left
4. **Check Your Solution**: Press 'C' to verify if you've solved the puzzle correctly
5. **Complete the Level**: When all pieces are correctly placed, you'll return to the menu

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

## Levels

1. **Square** - Simple warm-up level
2. **Triangle** - Basic geometric shape
3. **Cat** - Cute feline silhouette
4. **House** - Classic house shape
5. **Bird** - Flying bird in profile
6. **Boat** - Sailboat on water
7. **Running Person** - Human figure in motion
8. **Fish** - Swimming fish
9. **Candle** - Lit candle
10. **Rabbit** - Bunny with long ears

## Technical Details

- **Graphics API**: OpenGL 3.3 Core Profile
- **Windowing**: GLFW
- **Math Library**: GLM (OpenGL Mathematics)
- **Rendering**: Vertex Array Objects (VAO) and Index Buffer Objects (IBO)
- **Shaders**: GLSL vertex and fragment shaders
- **Architecture**: Layer-based design with polymorphic shape system

## Notes

- The program is designed to work with Wayland Hyprland but also supports X11
- Shader files must be in the `shaders/` directory relative to where the executable is run
- All transformations (rotate, translate, flip) are applied using transformation matrices
- The solution checking system uses position-based validation with tolerance

## Credits

Built using OpenGL, GLFW, and GLM. Inspired by the traditional Chinese Tangram puzzle.

Enjoy solving the puzzles! 🧩
