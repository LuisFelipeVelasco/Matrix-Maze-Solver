#include <iostream>
#include <string>
#include "Tablero.h"
#include "Avatar.h"
#include <exception>
#include <cassert>
/*
Proyecto: Paso-de-Mensajes-Main

Curso: Fundamentos de Programación Orientada a Objetos (FPOO)

Autores:
Felipe velasco - 2517245
Jerónimo imbachi - 2517760
Leonardo rosero - 2518313-3743
Alejandro velez - 2521169-3743
Julio Cesar Urbano Noguera- 2517931

Resumen:
Este programa es un algoritmo cuyo protagonista es un objeto de la clase avatar y que recorre las coordenadas de una matriz que representa un laberinto.
Los Vacios y Espacios sin salida se representan como 0 y los Espacios Libres como 1
Meta: Llegar a la salida ubicada en la celda [9,9]
*/

int main()
{
    std::cout << "===== DEBUGGER INICIADO =====" << std::endl;

    // === TABLERO ===
    std::cout << "[DEBUG] Creando objeto Tablero (Laberinto)..." << std::endl;
    Tablero Laberinto;
    std::cout << "[DEBUG] Definiendo posición inicial..." << std::endl;
    Laberinto.Definirposicion();
    int PosicionX = Laberinto.GetTableroX();
    int PosicionY = Laberinto.GetTableroY();
    std::cout << "[INFO] Posición inicial obtenida: X=" << PosicionX << " , Y=" << PosicionY << std::endl;
    // Validación con assert
    assert(PosicionX >= 0 && "ERROR: PosicionX no puede ser negativa");
    assert(PosicionY >= 0 && "ERROR: PosicionY no puede ser negativa");
    // === AVATAR ===
    std::cout << "\n[DEBUG] Creando Avatar 'Smart'..." << std::endl;
    Avatar AgenteI("Smart", PosicionX, PosicionY);
    std::cout << "[DEBUG] Mostrando posición inicial del Avatar..." << std::endl;
    
    // Verificar consistencia
    assert(AgenteI.GetPositionX() == PosicionX && "ERROR: Posicion X del Avatar no coincide con la del Tablero");
    assert(AgenteI.GetPositionY() == PosicionY && "ERROR: Posicion Y del Avatar no coincide con la del Tablero");

    // === MOVIMIENTO ===
    std::cout << "\n[DEBUG] Inicializando módulo de Movimiento..." << std::endl;
    std::cout << "[DEBUG] Ejecutando método Moverse()..." << std::endl;
    try
    {
        AgenteI.Moverse();
        std::cout << "[OK] Movimiento ejecutado sin errores." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "[EXCEPTION] Error durante el movimiento: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "[EXCEPTION] Error desconocido durante el movimiento." << std::endl;
    }

    // === FINAL ===
    std::cout << "\n===== DEBUGGER FINALIZADO =====" << std::endl;
    AgenteI.Moverse();
    return 0;
}