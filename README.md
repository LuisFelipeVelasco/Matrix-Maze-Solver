# Matrix-Maze-Solver || Automatic Maze Navigation 🧭
A clean and educational C++ maze-solving project that models a grid-based labyrinth using matrices and object-oriented programming. The project focuses on logic, movement validation, and clear class responsibilities, making it ideal for learning data structures, algorithms, and C++ design.

# Features

🧩 Maze represented as a matrix (2D grid)

🤖 An Avatar that navigates the maze

✅ Valid and invalid movement detection

🧠 Logical separation of responsibilities using classes

👁️ Visual representation of the maze state

⚙️ Built with CMake for easy compilation

# Project Structure
```text
Matrix-Maze-Solver/
│── Avatar.h / Avatar.cpp        # Avatar logic and position handling
│── Movimiento.h / Movimiento.cpp # Movement rules and validation
│── Tablero.h / Tablero.cpp      # Maze (board) representation
│── Visual.h / Visual.cpp        # Maze visualization
│── main.cpp                     # Program entry point
│── CMakeLists.txt               # Build configuration
```

# Build & Run
Requirements:

Docker Desktop

VS code 

Extensión Dev Containers

steps:

```bash
git clone https://github.com/LuisFelipeVelasco/Matrix-Maze-Solver.git
cd Matrix-Maze-Solver
code .
```
In VS code:

1. Press Ctrl + Shift + P

2. Select Dev Containers: Reopen in Container (Docker Desktop must be running)

3. Press F5 (VS Code runs launch.json → tasks.json → Makefile → make all) 

4. Press F5 (VS Code runs launch.json → ${workspaceFolder}/main)

# Purpose of the Project 🎯

This project was created as a learning-focused implementation to practice:

Thinking in matrices

Designing reusable C++ classes

Applying logic to constrained movement problems

It is especially useful for computer science students or anyone strengthening their C++ fundamentals.
