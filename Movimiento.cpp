#include "Tablero.h"
#include "Movimiento.h"
#include "Visual.h"
#include <string>
#include <iostream>
#include <vector>
/*
===============================================================================
                        IMPLEMENTACIÓN DE LA CLASE MOVIMIENTO
===============================================================================
La clase Movimiento representa las acciones que puede realizar el avatar,
modificando sus coordenadas para simular su desplazamiento

Se demuestra:
 - Paso de objetos por referencia
 - Asociar una posición existente del tablero (por referencia)
 - Cambiar la posición actual moviendo en distintas direcciones
 - Integración con la clase Visual para mostrar el progreso
===============================================================================
*/

Movimiento::Movimiento(int& x, int& y) : PosicionX(x), PosicionY(y) {}

std::string Movimiento::Moverse() {
    // Crear objeto Visual pasando punteros a las posiciones
    Visual vista(&PosicionX, &PosicionY);
    
    // Obtener referencia a la matriz del tablero
    int (&matriz)[10][10] = Tablero::GetMatrizStatic();
    
    // Mostrar estado inicial del laberinto
    vista.DibujarTablero(matriz); // se llama
    vista.Delay(2000);  // Pausa de 2 segundos al inicio
    
    while (PosicionY != 9 || PosicionX != 9) { // ejecutar hasta que logre llegar a la salida
        //Las variables der,izq,arr,abj para que direccion alrededor del avatar hay un camino sin salida o un vacio
        bool der = DetectarVacioDerecha(matriz);
        bool izq = DetectarVacioIzquierda(matriz);
        bool arr = DetectarVacioArriba(matriz);
        bool abj = DetectarVacioAbajo(matriz);

        if (der && izq && arr) {
            // Bloqueado a la derecha, izquierda y arriba: moverse abajo
            matriz[PosicionX][PosicionY]=0;
            PosicionX++;
            if (!UltimosMovimientos.empty()) { // si ya han habido movimientos realizados
                UltimosMovimientos.pop_back(); // borra el último movimiento
            }
        }
        else if (der && izq && abj) {
            // Bloqueado a la derecha, izquierda y abajo: moverse arriba
            matriz[PosicionX][PosicionY]=0;
            PosicionX--;
            if (!UltimosMovimientos.empty()) {
                UltimosMovimientos.pop_back();
            }
        }
        else if (der && abj && arr) {
            // Bloqueado a la derecha, abajo y arriba: moverse a la izquierda
            matriz[PosicionX][PosicionY]=0;
            PosicionY--;
            if (!UltimosMovimientos.empty()) {
                UltimosMovimientos.pop_back();
            }
        }
        else if (izq && abj && arr) {
            // Bloqueado a la izquierda, abajo y arriba: moverse a la derecha
            matriz[PosicionX][PosicionY]=0;
            PosicionY++;
            if (!UltimosMovimientos.empty()) {
                UltimosMovimientos.pop_back();
            }
        }

        else if(izq && der){// Bloqueado por derecha e izquierda
            if (!UltimosMovimientos.empty()) { // si ya se ha registrado un movimiento :
                if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Arr") {PosicionX--; UltimosMovimientos.emplace_back("Arr");  } //si el último movimiento fue hacia arriba entonces continua arriba
                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Abj") {PosicionX++;UltimosMovimientos.emplace_back("Abj");}
            }
            else { // si no se ha registrado ningun movimiento , toma una decision al azar y subela al vector
                int opcion= rand() % 2;
                if (opcion==1) {PosicionX--; UltimosMovimientos.emplace_back("Arr"); std::cout<<"Arr";}
                else {PosicionX++;UltimosMovimientos.emplace_back("Abj");}
            }
        }
        else if(der && arr) {// Bloqueado por derecha y por arriba
            if (!UltimosMovimientos.empty()) {
                if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Der") {PosicionX++; UltimosMovimientos.emplace_back("Abj");  }
                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Arr") {PosicionY--;UltimosMovimientos.emplace_back("Izq");}
            }
            else {
                int opcion= rand() % 2;
                if (opcion==1) {PosicionY--;UltimosMovimientos.emplace_back("Izq");}
                else {PosicionX++; UltimosMovimientos.emplace_back("Abj");}
            }

        }
        else if(der && abj) {// Bloqueado por derecha y por abajo
            if (!UltimosMovimientos.empty()) {
                if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Der") {PosicionX--; UltimosMovimientos.emplace_back("Arr");  }
                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Abj") {PosicionY--;UltimosMovimientos.emplace_back("Izq");}
            }
            else {
                int opcion= rand() % 2;
                if (opcion==1) {PosicionY--;UltimosMovimientos.emplace_back("Izq");}
                else {PosicionX--; UltimosMovimientos.emplace_back("Arr");}
            }

        }
        else if(izq && arr) {      // Bloqueado por izquierda y por arriba
            if (!UltimosMovimientos.empty()) {
                if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Izq") {PosicionX++; UltimosMovimientos.emplace_back("Abj");  }
                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Arr") {PosicionY++;UltimosMovimientos.emplace_back("Der");}
            }

            else {
                int opcion= rand() % 2;
                if (opcion==1) {PosicionY++;UltimosMovimientos.emplace_back("Der");}
                else {PosicionX++; UltimosMovimientos.emplace_back("Abj");  }
            }

        }
        else if(izq && abj) {  // Bloqueado por izquierda y por abajo
            if (!UltimosMovimientos.empty()) {
                if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Izq") {PosicionX--; UltimosMovimientos.emplace_back("Arr");  }
                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Abj") {PosicionY++;UltimosMovimientos.emplace_back("Der");}
            }

            else {
                int opcion= rand() % 2;
                if (opcion==1) {PosicionY++;UltimosMovimientos.emplace_back("Der");}
                else {PosicionX--; UltimosMovimientos.emplace_back("Arr");}
            }

        }
        else if(arr && abj) { // Bloqueado por arriba y por abajo
            if (!UltimosMovimientos.empty()) { // si el vector de ultimos movimientos no esta vacio entonces ejecuta lo de adentro
                if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Izq") {PosicionY--; UltimosMovimientos.emplace_back("Izq");  } // si ademas el ultimo movimiento viene por la izquierda entonces si o si siga por la izquierda
                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Der") {PosicionY++;UltimosMovimientos.emplace_back("Der");} // si ademas el ultimo movimiento viene por la derecha encontonces si o si siga por la derecha
            }

            else {
                int opcion= rand() % 2;
                if (opcion==1) {PosicionY++;UltimosMovimientos.emplace_back("Der");}
                else {PosicionY--; UltimosMovimientos.emplace_back("Izq");  }
            }

        }


        else if(arr){   // Bloqueado por arriba: decidir entre bajar, izquierda o derecha
            if (!UltimosMovimientos.empty()) {
                if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Arr") {
                    int opcion= rand() % 2;
                    if (opcion==1) {PosicionY++;UltimosMovimientos.emplace_back("Der");}
                    else {PosicionY--; UltimosMovimientos.emplace_back("Izq");  }
                }

                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Der") {
                    int opcion= rand() % 2;
                    if (opcion==1) {PosicionY++;UltimosMovimientos.emplace_back("Der");}
                    else {PosicionX++; UltimosMovimientos.emplace_back("Abj");  }

                }

                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Izq") {
                    int opcion= rand() % 2;
                    if (opcion==1) {PosicionY--;UltimosMovimientos.emplace_back("Izq");}
                    else {PosicionX++; UltimosMovimientos.emplace_back("Abj");}
                }
            }
            else {
                int opcion= rand() % 3;
                if (opcion==1) {PosicionX++; UltimosMovimientos.emplace_back("Abj");  }
                else if (opcion==2) {PosicionY++;UltimosMovimientos.emplace_back("Der");}
                else {PosicionY--;UltimosMovimientos.emplace_back("Izq");}
            }

        }
        else if(abj)  {// Bloqueado por abajo: decidir entre subir, izquierda o derecha
            if (!UltimosMovimientos.empty()) {

                if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Abj") {
                    int opcion= rand() % 2;
                    if (opcion==1) {PosicionY++;UltimosMovimientos.emplace_back("Der");}
                    else {PosicionY--; UltimosMovimientos.emplace_back("Izq");  }
                }

                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Der") {
                    int opcion= rand() % 2;
                    if (opcion==1) {PosicionY++;UltimosMovimientos.emplace_back("Der");}
                    else {PosicionX--; UltimosMovimientos.emplace_back("Arr");}
                }

                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Izq") {
                    int opcion= rand() % 2;
                    if (opcion==1) {PosicionY--;UltimosMovimientos.emplace_back("Izq");}
                    else {PosicionX--; UltimosMovimientos.emplace_back("Arr");}
                }

            }

            else {
                int opcion= rand() % 3;
                if (opcion==1) {PosicionX--; UltimosMovimientos.emplace_back("Arr");  }
                else if (opcion==2) {PosicionY--;UltimosMovimientos.emplace_back("Izq");}
                else {PosicionY++;UltimosMovimientos.emplace_back("Der");}
            }

        }
        else if(der){   // Bloqueado por derecha: decidir entre otras tres direcciones
            if (!UltimosMovimientos.empty()) {
                if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Arr") {
                    int opcion= rand() % 2;
                    if (opcion==1) {PosicionY--;UltimosMovimientos.emplace_back("Izq");}
                    else {PosicionX--; UltimosMovimientos.emplace_back("Arr");}
                }
                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Abj") {
                    int opcion= rand() % 2;
                    if (opcion==1) {PosicionY--;UltimosMovimientos.emplace_back("Izq");}
                    else {PosicionX++; UltimosMovimientos.emplace_back("Abj");}
                }

                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Der") {
                    int opcion= rand() % 2;
                    if (opcion==1) {PosicionX--; UltimosMovimientos.emplace_back("Arr");  }
                    else {PosicionX++;UltimosMovimientos.emplace_back("Abj");}
                }

            }

            else {
                int opcion= rand() % 3;
                if (opcion==1) {PosicionX++; UltimosMovimientos.emplace_back("Abj");  }
                else if (opcion==2) {PosicionX--; UltimosMovimientos.emplace_back("Arr");  }
                else {PosicionY--;UltimosMovimientos.emplace_back("Izq");}
            }
            }

        else if(izq){  // Bloqueado por izquierda: decidir entre otras tres direcciones
            if (!UltimosMovimientos.empty()) {
                if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Abj") {
                    int opcion= rand() % 2;
                    if (opcion==1) {PosicionY++;UltimosMovimientos.emplace_back("Der");}
                    else {PosicionX++; UltimosMovimientos.emplace_back("Abj");  }
                }

                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Arr") {
                    int opcion= rand() % 2;
                    if (opcion==1) {PosicionY++;UltimosMovimientos.emplace_back("Der");}
                    else {PosicionX--; UltimosMovimientos.emplace_back("Arr");}

                }

                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Izq") {
                    int opcion= rand() % 2;
                    if (opcion==1) {PosicionX--; UltimosMovimientos.emplace_back("Arr");  }
                    else {PosicionX++;UltimosMovimientos.emplace_back("Abj");}
                }
            }

            else {
                int opcion= rand() % 3;
                if (opcion==1) {PosicionX++; UltimosMovimientos.emplace_back("Abj");  }
                else if (opcion==2) {PosicionX--; UltimosMovimientos.emplace_back("Arr");}
                else {PosicionY++;UltimosMovimientos.emplace_back("Der");}
            }

        }

        else { // el avatar no esta bloqueado alrededor , por ende puede tomar cualquier decision
            if (!UltimosMovimientos.empty()) {
                if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Abj") {
                    int opcion= rand() % 3;
                    if (opcion==1) {PosicionY++;UltimosMovimientos.emplace_back("Der");}
                    else if (opcion==2){PosicionX++; UltimosMovimientos.emplace_back("Abj");  }
                    else {PosicionY--;UltimosMovimientos.emplace_back("Izq");}
                }

                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Arr") {
                    int opcion= rand() % 3;
                    if (opcion==1) {PosicionY++;UltimosMovimientos.emplace_back("Der");}
                    else if (opcion==2){PosicionX--; UltimosMovimientos.emplace_back("Arr");  }
                    else {PosicionY--;UltimosMovimientos.emplace_back("Izq");}
                }

                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Der") {
                    int opcion= rand() % 3;
                    if (opcion==1) {PosicionY++;UltimosMovimientos.emplace_back("Der");}
                    else if (opcion==2){PosicionX--; UltimosMovimientos.emplace_back("Arr");  }
                    else {PosicionX++;UltimosMovimientos.emplace_back("Abj");}
                }

                else if (UltimosMovimientos[UltimosMovimientos.size()-1]=="Izq") {
                    int opcion= rand() % 3;
                    if (opcion==1) {PosicionY--;UltimosMovimientos.emplace_back("Izq");}
                    else if (opcion==2){PosicionX--; UltimosMovimientos.emplace_back("Arr");  }
                    else {PosicionX++;UltimosMovimientos.emplace_back("Abj");}
                }

            }
            else {
                int opcion= rand() % 4;
                if (opcion==1) {PosicionX++; UltimosMovimientos.emplace_back("Abj");  }
                else if (opcion==2) {PosicionX--; UltimosMovimientos.emplace_back("Arr");  }
                else if (opcion==3) {PosicionY++;UltimosMovimientos.emplace_back("Der");}
                else {PosicionY--;UltimosMovimientos.emplace_back("Izq");}
            }

        }
        // ACTUALIZAR VISUALIZACIÓN después de cada movimiento
        vista.IncrementarPasos();
        vista.DibujarTablero(matriz);
        vista.Delay(500);  // Medio segundo entre movimientos
    }
    // Mostrar mensaje de victoria
    vista.MostrarVictoria();
    return "COMPLETADO";
}

// ====== Funciones de detección individuales ======

bool Movimiento::DetectarVacioDerecha(int (&matriz)[10][10]) {
    if (PosicionY < 9) {
        return matriz[PosicionX][PosicionY + 1] == 0;
    }
    return true; // fuera del tablero = obstáculo
}

bool Movimiento::DetectarVacioIzquierda(int (&matriz)[10][10]) {
    if (PosicionY > 0) {
        return matriz[PosicionX][PosicionY - 1] == 0;
    }
    return true;
}

bool Movimiento::DetectarVacioArriba(int (&matriz)[10][10]) {
    if (PosicionX > 0) {
        return matriz[PosicionX - 1][PosicionY] == 0;
    }
    return true;
}

bool Movimiento::DetectarVacioAbajo(int (&matriz)[10][10]) {
    if (PosicionX < 9) {
        return matriz[PosicionX + 1][PosicionY] == 0;
    }
    return true;
}