#include "Visual.h"
#include <iostream>
#include <thread>
#include <chrono>


/*
========================================================================================
                        IMPLEMENTACIÓN DE LA CLASE VISUAL
========================================================================================
La clase Visual se encarga de mostrar la ejecucion del programa en consola, para qué cada
movimiento y accion del Avatar pueda ser visualizado

Se demuestra:
 - Uso de punteros para conocer la direccion del avatar en cualquier momento sin necesidad
   de copias.
 - Impresión de avisos por medio de for anidados y metodos
========================================================================================
*/

#ifdef _WIN32
    #include <windows.h>
#else
    #include <cstdlib>
#endif

Visual::Visual(int* posX, int* posY) {
    this->PosicionX = posX;
    this->PosicionY = posY;
    this->ContadorPasos = 0;
    this->UseAsciiFallback = false;
    EnableUtf8AndAnsi();
}

void Visual::EnableUtf8AndAnsi() {
#ifdef _WIN32
    // Intentar activar UTF-8 en salida y habilitar VT sequences (ANSI)
    if (!SetConsoleOutputCP(CP_UTF8)) {
        UseAsciiFallback = true;
        return;
    }
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) { UseAsciiFallback = true; return; }
    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode)) { UseAsciiFallback = true; return; }
    // Habilita procesamiento de secuencias ANSI
    if (!SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
        UseAsciiFallback = true;
        return;
    }
#else
    UseAsciiFallback = false;
#endif
}

void Visual::LimpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Visual::MostrarEncabezado() {
    if (UseAsciiFallback) {
        std::cout << "\n==== LABERINTO - AGENTE INTELIGENTE ====\n\n";
    } else {
        std::cout << "╔══════════════════════════════════════════════════════╗\n";
        std::cout << "║         LABERINTO - AGENTE INTELIGENTE               ║\n";
        std::cout << "║                 SMART EN ACCION                      ║\n";
        std::cout << "╚══════════════════════════════════════════════════════╝\n\n";
    }
}

void Visual::MostrarCelda(int valor, bool esPosicionActual, bool esSalida) {
    if (UseAsciiFallback) {
        if (esPosicionActual) std::cout << " S ";
        else if (esSalida) std::cout << " * ";
        else if (valor == 0) std::cout << " X ";
        else std::cout << " . ";
    } else {
        if (esPosicionActual) std::cout << " \033[1;32mS\033[0m ";
        else if (esSalida) std::cout << " \033[1;33m★\033[0m ";
        else if (valor == 0) std::cout << " \033[1;31mX\033[0m ";
        else std::cout << " \033[0;37m·\033[0m ";
    }
}

void Visual::MostrarLeyenda() {
    if (UseAsciiFallback) {
        std::cout << "\n  [S]=Soldado  [X]=Pared  [.] = Pasillo  [*]=Salida\n\n";
    } else {
        std::cout << "\n  ┌─────────────── LEYENDA ───────────────┐\n";
        std::cout << "  │  \033[1;32mS\033[0m = Soldado (Agente Inteligente)     │\n";
        std::cout << "  │  \033[1;31mX\033[0m = Vacio o Sin salida               │\n";
        std::cout << "  │  \033[0;37m·\033[0m = Pasillo (Camino disponible)      │\n";
        std::cout << "  │  \033[1;33m★\033[0m = Salida (Objetivo [9][9])         │\n";
        std::cout << "  └───────────────────────────────────────┘\n\n";
    }
}

void Visual::DibujarTablero(int (&matriz)[10][10]) {
    LimpiarPantalla();
    MostrarEncabezado();

    if (UseAsciiFallback) {
        for (int i = 0; i < 10; ++i) {
            std::cout << i << " ";
            for (int j = 0; j < 10; ++j) {
                bool esPosicionActual = (i == *PosicionX && j == *PosicionY);
                bool esSalida = (i == 9 && j == 9);
                MostrarCelda(matriz[i][j], esPosicionActual, esSalida);
            }
            std::cout << "\n";
        }
        std::cout << "   0 1 2 3 4 5 6 7 8 9\n\n";
        std::cout << " Pos: [" << *PosicionX << "][" << *PosicionY << "]  Movs: " << ContadorPasos << "\n\n";
        MostrarLeyenda();
        return;
    }

    std::cout << "       ┌";
    for (int j = 0; j < 10; j++) std::cout << "───";
    std::cout << "┐\n";

    for (int i = 0; i < 10; i++) {
        std::cout << "    " << i << "  │";
        for (int j = 0; j < 10; j++) {
            bool esPosicionActual = (i == *PosicionX && j == *PosicionY);
            bool esSalida = (i == 9 && j == 9);
            MostrarCelda(matriz[i][j], esPosicionActual, esSalida);
        }
        std::cout << "│\n";
    }

    std::cout << "       └";
    for (int j = 0; j < 10; j++) std::cout << "───";
    std::cout << "┘\n";

    std::cout << "         ";
    for (int j = 0; j < 10; j++) std::cout << j << "  ";
    std::cout << "\n";

    std::cout << "\n  ┌─────────────── ESTADO ────────────────┐\n";
    std::cout << "  │  Posición actual: [\033[1;36m" << *PosicionX << "\033[0m][\033[1;36m" << *PosicionY << "\033[0m]              │\n";
    std::cout << "  │  Movimientos realizados: \033[1;35m" << ContadorPasos << "\033[0m            │\n";
    std::cout << "  └───────────────────────────────────────┘\n";

    MostrarLeyenda();

}

void Visual::Delay(int milisegundos) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milisegundos));
}

void Visual::IncrementarPasos() {
    ContadorPasos++;
}

void Visual::MostrarVictoria() {
    LimpiarPantalla();
    if (UseAsciiFallback) {
        std::cout << "\n\n  ¡MISIÓN CUMPLIDA! Pos final: [9][9]  Movs: " << ContadorPasos << "\n\n";
    } else {
        std::cout << "\n\n";
        std::cout << "  ╔═══════════════════════════════════════════════════════╗\n";
        std::cout << "  ║          \033[1;32m¡MISIÓN CUMPLIDA!\033[0m                ║\n";
        std::cout << "  ║          Posición final: [\033[1;33m9\033[0m][\033[1;33m9\033[0m] \033[1;33m★\033[0m                   ║\n";
        std::cout << "  ║          Total de movimientos: \033[1;35m" << ContadorPasos << "\033[0m                 ║\n";
        std::cout << "  ╚═══════════════════════════════════════════════════════╝\n";
        std::cout << "\n\n";
    }
}
