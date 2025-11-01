#ifndef PROYECTO_AGENTE_INTELIGENTE_AVATAR_H
#define PROYECTO_AGENTE_INTELIGENTE_AVATAR_H
#include <string>
/*
===============================================================================
                                TARJETA CRC
===============================================================================
Nombre de la clase:Avatar
Responsabilidades:
    - Definir un avatar con un nombre y la posición en la matriz
    - imprimir la posición actual del soldado
Colaboradores:
    - Tablero
    - Movimiento
===============================================================================
*/
class Avatar {
private:
    std::string Nombre{};
    int PosicionX{};
    int PosicionY{};
public:
    Avatar(std::string Nombre , int& PosicionX, int& PosicionY); // Paso por referencia
    std::string GetNombre();
    int& GetPosicionY() ;
    int& GetPosicionX() ;
    void SetPosicionX(int posicionX);
    void SetPosicionY(int posicionY);
    void Posicion();
};
#endif //PASO_MENSAJES_AVATAR_H