# Matrix-Maze-Solver || Automatic Maze Navigation 🧭
A clean and educational C++ maze-solving project that models a grid-based labyrinth using matrices and object-oriented programming. The project focuses on logic, movement validation, and clear class responsibilities, making it ideal for learning data structures, algorithms, and C++ design.

![Image](https://github.com/user-attachments/assets/48f6c961-ffaf-4e7c-9a3a-f6f344cd1efe)

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
│
├── Avatar.h                 # Defines the avatar entity and its attributes
├── Avatar.cpp               # Implements avatar behavior and movement
│
├── Board.h                  # Maze (matrix) representation and rules
├── Board.cpp                # Implements board logic and validations
│
├── Visual.h                 # Interface for maze visualization
├── Visual.cpp               # Console-based rendering of the maze
│
├── main.cpp                 # Program entry point
│
├── Makefile                 # Build automation using Make
├── README.md                # Project documentation
│
├── tests/                   # Unit and integration tests
│   └── test_main.cpp        # Main test file
│
├── .vscode/                 # VS Code configuration
│   ├── launch.json
│   └── tasks.json
│
├── .devcontainer/           # Development container configuration
│   ├── devcontainer.json
│   └── Dockerfile
```

# Build & Run
Requirements:

Docker Desktop ,VS code , Extensión Dev Containers

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

# Run Tests:

```bash
Make google-test
```

# Purpose of the Project 🎯

This project was created as a learning-focused implementation to practice:

Thinking in matrices

Applying logic to constrained movement problems

It is especially useful for computer science students or anyone strengthening their C++ fundamentals.
