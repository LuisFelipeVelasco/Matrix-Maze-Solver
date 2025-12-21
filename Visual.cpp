#include "Visual.h"
#include <iostream>
#include <thread>
#include <chrono>


/*
========================================================================================
                        IMPLEMENTATION OF THE VISUAL CLASS
========================================================================================
The Visual class is responsible for displaying the program execution in console, so that
each movement and action of the Avatar can be visualized

Demonstrates:
 - Use of pointers to know the direction of the avatar at any time without need
   for copies.
 - Printing of messages through nested loops and methods
========================================================================================
*/

#ifdef _WIN32
    #include <windows.h>
#else
    #include <cstdlib>
#endif

Visual::Visual(int* posX, int* posY) {
    this->PositionX = posX;
    this->PositionY = posY;
    this->StepCounter = 0;
    this->UseAsciiFallback = false;
    EnableUtf8AndAnsi();
}

void Visual::EnableUtf8AndAnsi() {
#ifdef _WIN32
    // Try to enable UTF-8 in output and enable VT sequences (ANSI)
    if (!SetConsoleOutputCP(CP_UTF8)) {
        UseAsciiFallback = true;
        return;
    }
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) { UseAsciiFallback = true; return; }
    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode)) { UseAsciiFallback = true; return; }
    // Enable ANSI sequence processing
    if (!SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
        UseAsciiFallback = true;
        return;
    }
#else
    UseAsciiFallback = false;
#endif
}

void Visual::ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Visual::ShowHeader() {
    if (UseAsciiFallback) {
        std::cout << "\n==== MAZE - INTELLIGENT AGENT ====\n\n";
    } else {
        std::cout << "╔══════════════════════════════════════════════════════╗\n";
        std::cout << "║                MATRIX-MAZE-SOLVER                    ║\n";
        std::cout << "║                 SMART IN ACTION                      ║\n";
        std::cout << "╚══════════════════════════════════════════════════════╝\n\n";
    }
}

void Visual::ShowCell(int value, bool isCurrentPosition, bool isExit) {
    if (UseAsciiFallback) {
        if (isCurrentPosition) std::cout << " S ";
        else if (isExit) std::cout << " * ";
        else if (value == 0) std::cout << " X ";
        else std::cout << " . ";
    } else {
        if (isCurrentPosition) std::cout << " \033[1;32mS\033[0m ";
        else if (isExit) std::cout << " \033[1;33m★\033[0m ";
        else if (value == 0) std::cout << " \033[1;31mX\033[0m ";
        else std::cout << " \033[0;37m·\033[0m ";
    }
}

void Visual::ShowLegend() {
    if (UseAsciiFallback) {
        std::cout << "\n  [S]=Agent  [X]=Wall  [.] = Corridor  [*]=Exit\n\n";
    } else {
        std::cout << "\n  ┌─────────────── LEGEND ───────────────┐\n";
        std::cout << "  │  \033[1;32mS\033[0m = Agent (Intelligent)             │\n";
        std::cout << "  │  \033[1;31mX\033[0m = Wall or Dead End                │\n";
        std::cout << "  │  \033[0;37m·\033[0m = Corridor (Available Path)       │\n";
        std::cout << "  │  \033[1;33m★\033[0m = Exit (Goal [9][9])              │\n";
        std::cout << "  └──────────────────────────────────────┘\n\n";
    }
}

void Visual::DrawBoard(int (&matrix)[10][10]) {
    ClearScreen();
    ShowHeader();

    if (UseAsciiFallback) {
        for (int i = 0; i < 10; ++i) {
            std::cout << i << " ";
            for (int j = 0; j < 10; ++j) {
                bool isCurrentPosition = (i == *PositionX && j == *PositionY);
                bool isExit = (i == 9 && j == 9);
                ShowCell(matrix[i][j], isCurrentPosition, isExit);
            }
            std::cout << "\n";
        }
        std::cout << "   0 1 2 3 4 5 6 7 8 9\n\n";
        std::cout << " Pos: [" << *PositionX << "][" << *PositionY << "]  Moves: " << StepCounter << "\n\n";
        ShowLegend();
        return;
    }

    std::cout << "       ┌";
    for (int j = 0; j < 10; j++) std::cout << "───";
    std::cout << "┐\n";

    for (int i = 0; i < 10; i++) {
        std::cout << "    " << i << "  │";
        for (int j = 0; j < 10; j++) {
            bool isCurrentPosition = (i == *PositionX && j == *PositionY);
            bool isExit = (i == 9 && j == 9);
            ShowCell(matrix[i][j], isCurrentPosition, isExit);
        }
        std::cout << "│\n";
    }

    std::cout << "       └";
    for (int j = 0; j < 10; j++) std::cout << "───";
    std::cout << "┘\n";

    std::cout << "         ";
    for (int j = 0; j < 10; j++) std::cout << j << "  ";
    std::cout << "\n";

    std::cout << "\n  ┌─────────────── STATUS ────────────────┐\n";
    std::cout << "  │  Current Position: [\033[1;36m" << *PositionX << "\033[0m][\033[1;36m" << *PositionY << "\033[0m]             │\n";
    std::cout << "  │  Moves Performed: \033[1;35m" << StepCounter << "\033[0m                   │\n";
    std::cout << "  └───────────────────────────────────────┘\n";

    ShowLegend();

}

void Visual::Delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void Visual::IncrementSteps() {
    StepCounter++;
}

void Visual::ShowVictory() {
    ClearScreen();
    if (UseAsciiFallback) {
        std::cout << "\n\n  MISSION ACCOMPLISHED! Final Pos: [9][9]  Moves: " << StepCounter << "\n\n";
    } else {
        std::cout << "\n\n";
        std::cout << "  ╔═══════════════════════════════════════════════════════╗\n";
        std::cout << "  ║          \033[1;32mMISSION ACCOMPLISHED!\033[0m                        ║\n";
        std::cout << "  ║          Final Position: [\033[1;33m9\033[0m][\033[1;33m9\033[0m] \033[1;33m★\033[0m                     ║\n";
        std::cout << "  ║          Total Moves: \033[1;35m" << StepCounter << "\033[0m                               ║\n";
        std::cout << "  ╚═══════════════════════════════════════════════════════╝\n";
        std::cout << "\n\n";
    }
}
