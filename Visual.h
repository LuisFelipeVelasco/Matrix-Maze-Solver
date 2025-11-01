#ifndef PROYECTO_AGENTE_INTELIGENTE_VISUAL_H
#define PROYECTO_AGENTE_INTELIGENTE_VISUAL_H
/*
===============================================================================
                                TARJETA CRC
===============================================================================
Nombre de la clase:Visual
Responsabilidades:
    - Mostrar la ejecucion del algoritmo en consola
Colaboradores:
    - Tablero
    - Movimiento
===============================================================================
*/
class Visual {
private:
    int* PosicionX;
    int* PosicionY;
    int ContadorPasos;
    bool UseAsciiFallback; // fallback si la consola no soporta UTF-8/ANSI

    void LimpiarPantalla();
    void MostrarCelda(int valor, bool esPosicionActual, bool esSalida);
    void MostrarEncabezado();
    void MostrarLeyenda();
    void EnableUtf8AndAnsi(); // habilita UTF-8 y ANSI en Windows

public:
    Visual(int* posX, int* posY);
    void DibujarTablero(int (&matriz)[10][10]);
    void Delay(int milisegundos);
    void IncrementarPasos();
    void MostrarVictoria();
};

#endif //PROYECTO_AGENTE_INTELIGENTE_VISUAL_H
