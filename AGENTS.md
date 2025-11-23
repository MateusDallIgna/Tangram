# Agent Guidelines for Tangram Project

## 1. Build, Lint, and Test Commands

*   **Build:** `make`
*   **Run:** `make run`
*   **Clean:** `make clean`
*   **Rebuild:** `make rebuild`
*   **Linting:** Use `clang-format` for C++ code formatting. A `.clangd` file exists, suggesting `clangd` usage.
*   **Testing:** No explicit test framework or commands are configured. Manual testing or adding a dedicated test framework (e.g., Google Test) would be required for unit tests.

## 2. Code Style Guidelines

*   **Language Standard:** C++17 (`-std=c++17`).
*   **Formatting:** Adhere to `clang-format` style.
*   **Includes:**
    *   System libraries: `#include <library>`
    *   Project headers: `#include "Header.h"`
*   **Naming Conventions:**
    *   Classes: PascalCase (e.g., `Application`, `Renderer`).
    *   Functions: PascalCase (e.g., `Init`, `Draw`).
    *   Variables: camelCase or snake_case (infer from context if not explicit).
*   **Error Handling:** Use standard C++ error handling mechanisms (e.g., exceptions for exceptional cases, error codes for expected failures).
*   **Comments:** Add comments for complex logic or non-obvious design choices.

## 3. AI-Specific Rules

*   No specific Cursor or Copilot rules found in the repository.