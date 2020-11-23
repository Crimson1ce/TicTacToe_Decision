#include "InteligenciaArtificial.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::endl;

InteligenciaArtificial::InteligenciaArtificial(char caracter, char oponente) {
    this->caracter = caracter;
    this->oponente = oponente;
    this->primerTurno = true;
    this->ultimaJugada = 0;

    srand(time(0));

    /*  1 | 2 | 3 
     * ---+---+---
     *  4 | 5 | 6 
     * ---+---+---
     *  7 | 8 | 9 
     * 
     * si casilla1 + casilla2 == 10, son opuestas
     * 
     * si casilla1 + casilla2 == 7,  es una esquina superior  y una arista horizontal
     * si casilla1 + casilla2 == 9,  es una esquina izquierda y una arista vertical
     * si casilla1 + casilla2 == 11, es una esquina derecha   y una arista vertical
     * si casilla1 + casilla2 == 13, es una esquina inferior  y una arista horizontal
     *     si una casilla es esquina
     * 
     * si casilla1 + casilla2 == 
     * 
     */

    //tablero[(casilla-1)/3][(casilla-1)%3]

}

InteligenciaArtificial::InteligenciaArtificial(const InteligenciaArtificial& orig) {
}

InteligenciaArtificial::~InteligenciaArtificial() {
}

int InteligenciaArtificial::analizar(char** tablero) {
    int ret = 0;

    ret = buscarGanadoras(tablero, caracter);
    if (ret != 0) {
        return ret;
    }

    ret = buscarGanadoras(tablero, oponente);
    if (ret != 0) {
        siguiente = 0;
        return ret;
    }

    if (siguiente) {
        int aux = siguiente;
        siguiente = 0;
        return aux;
    }

    int casilla = 5;
    for (int lado : lados) { //Se verifica si el oponente jugó un lado, esquina, o centro.
        char c = obtenerCasilla(tablero, lado); // Funciona para cases 1 y 2
        if (c == oponente) {
            casilla = lado;
            break;
        }
    }
    for (int esq : esquinas) {
        char c = obtenerCasilla(tablero, esq);
        if (c == oponente) {
            casilla = esq;
            break;
        }
    }

    switch (casillasOcupadas(tablero)) {
            //Primer movimiento
        case 0:
            siguiente = 0;
            ultimaJugada = esquinas[rand() % 4];
            return ultimaJugada;
            //Primer turno de la inteligencia
        case 1:
            siguiente = 0;
            if (casilla == 5) { //Problema con esta decision
                ultimaJugada = esquinas[rand() % 4];
                return ultimaJugada;
            } else {
                ultimaJugada = 5;
                return 5;
            }
            cout << "\nNo debe llegar hasta aqui" << endl;
            break;
            //La inteligencia hizo el primer movimiento
            //Se verifica qué hizo el oponente
        case 2:
            if (contiene(lados, 4, casilla)) {
                if (sonAdyacentesHorizontales(ultimaJugada, casilla)
                        || sonAdyacentesHorizontales(ultimaJugada, casilla)) { //Si el oponente jugó una arista adyacente
                    for (int i = 0; i < 4; i++) {
                        if (!sonAdyacentesHorizontales(casilla, esquinas[i])
                                && !sonAdyacentesVerticales(casilla, esquinas[i])//Revisamos cada esquina, si no es adyacente a donde jugó el oponente
                                && !sonOpuestos(ultimaJugada, esquinas[i])) { //y tampoco es el opuesto de nuestra primera jugada

                            siguiente = obtenerOpuesta(ultimaJugada);
                            ultimaJugada = esquinas[i];
                            return esquinas[i];
                        }
                    }
                } else { //Si el oponente jugó una arista no adyacente
                    for (int i = 0; i < 4; i++) {
                        if (!sonAdyacentesHorizontales(casilla, esquinas[i])
                                && !sonAdyacentesVerticales(casilla, esquinas[i])
                                && esquinas[i] != ultimaJugada) { //Revisamos cada esquina, si no es adyacente a donde jugó el oponente

                            ultimaJugada = esquinas[i];
                            //                            cout << "La ultima jugada fue: " << ultimaJugada << endl;
                            siguiente = obtenerOpuesta(esquinas[i]);
                            //                            cout << "La proxima jugada sera: " << siguiente << endl;
                            return esquinas[i];
                        }
                    }
                }
            } else if (contiene(esquinas, 4, casilla)) { //Si el oponente jugó una esquina

                if (sonOpuestos(ultimaJugada, casilla)) { //Si jugó la esquina opuesta
                    for (int i = 0; i < 4; i++) {
                        if (!sonOpuestos(ultimaJugada, esquinas[i])) {
                            ultimaJugada = esquinas[i];
                            siguiente = obtenerOpuesta(esquinas[i]);
                            return esquinas[i];
                        }
                    }
                } else { // Si no jugó la esquina opuesta
                    siguiente = obtenerOpuesta(ultimaJugada);
                    ultimaJugada = obtenerOpuesta(casilla);
                    return ultimaJugada;
                }

            } else { //Si el oponente jugó el centro
                ultimaJugada = obtenerOpuesta(ultimaJugada);
                return ultimaJugada;
            }

            break;
        case 3:
            char c = obtenerCasilla(tablero, 5);
            if (c == caracter) { //Si se da el caso
                for (int esq : esquinas) {
                    if (obtenerCasilla(tablero, esq) == oponente && obtenerCasilla(tablero, obtenerOpuesta(esq)) == oponente) {
                        ultimaJugada = lados[rand() % 4];
                        return ultimaJugada;
                    }
                }
            } else if (c == oponente) {
                for (int esq : esquinas) {
                    if (obtenerCasilla(tablero, esq) == oponente && obtenerCasilla(tablero, obtenerOpuesta(esq)) == caracter) {
                        do {
                            ret = esquinas[rand()%4];
                        } while (obtenerCasilla(tablero,ret) != ' ');
                        return ret;
                    }
                }
            }

            break;
    }//Fin del switch

    ret = buscarAmenaza(tablero, oponente);
    if (ret >= 2) {
        return ret;
    }

    ret = buscarAmenaza(tablero, caracter);
    if (ret > 0) {
        return ret;
    }

    do {
        ret = rand() % 9 + 1;
    } while (obtenerCasilla(tablero,ret) != ' ');

    return ret;
}

int InteligenciaArtificial::buscarAmenaza(char** matriz, char car) {
    int amenazas[9] = {}; //{3, 2, 3, 2, 4, 2, 3, 2, 3};

    for (int i = 1; i <= 9; i++) { //Recorremos cada casilla
        if (obtenerCasilla(matriz, i) == ' ') { //Revisamos las que están desocupadas
            for (int k = 0; k < 8; k++) { //Y recorremos las jugadas ganadoras
                if (contiene(jugadasGanadoras[k], 3, i)) { // Verificamos si la casilla está en la jugada ganadora
                    for (int casilla : jugadasGanadoras[k]) { //Si lo está, revisamos las otras dos
                        if (casilla != i) {
                            char c = obtenerCasilla(matriz, casilla);
                            if (c != car && c != ' ') {
                                amenazas[i - 1]--;
                            } else if (c == car) {
                                amenazas[i - 1]++;
                            }
                        }
                    }
                }
            }
        }
    }

    int ret = 0;

    for (int i = 1; i < 9; i++) {
        if (amenazas[i] > amenazas[i - 1])
            ret = i;
    }

    //    if(amenazas[ret] < 2)
    //        return 0;

    return ret + 1;
}

bool InteligenciaArtificial::sonAdyacentesVerticales(int casilla1, int casilla2) {
    int x1 = (casilla1 - 1) / 3;
    int y1 = (casilla1 - 1) % 3;
    int x2 = (casilla2 - 1) / 3;
    int y2 = (casilla2 - 1) % 3;

    int dif = x1 > x2 ? x1 - x2 : x2 - x1;

    if (y1 == y2 && dif == 1) {
        return true;
    }
    return false;
}

bool InteligenciaArtificial::sonAdyacentesHorizontales(int casilla1, int casilla2) {
    int x1 = (casilla1 - 1) / 3;
    int y1 = (casilla1 - 1) % 3;
    int x2 = (casilla2 - 1) / 3;
    int y2 = (casilla2 - 1) % 3;

    int dif = y1 > y2 ? y1 - y2 : y2 - y1;

    if (x1 == x2 && dif == 1) {
        return true;
    }
    return false;
}

bool InteligenciaArtificial::sonOpuestos(int casilla1, int casilla2) {
    if (casilla1 == casilla2) {
        return false;
    }

    if (casilla1 + casilla2 == 10) {
        return true;
    }
    return false;
}

int InteligenciaArtificial::obtenerOpuesta(int casilla) {
    if (casilla < 1 || casilla > 9 || casilla == 5) {
        return 0;
    }
    return 10 - casilla;
}

int InteligenciaArtificial::obtenerCasillaSuperior(int casilla) {
    if (casilla < 4 || casilla > 9) {
        return 0;
    }
    return casilla - 3;
}

int InteligenciaArtificial::obtenerCasillaInferior(int casilla) {
    if (casilla < 1 || casilla > 6) {
        return 0;
    }
    return casilla + 3;
}

int InteligenciaArtificial::obtenerCasillaIzquierda(int casilla) {
    if (casilla < 1 || casilla > 9 || casilla % 3 == 1) {
        return 0;
    }
    return casilla - 1;
}

int InteligenciaArtificial::obtenerCasillaDerecha(int casilla) {
    if (casilla < 1 || casilla > 9 || casilla % 3 == 1) {
        return 0;
    }
    return casilla - 1;
}

bool InteligenciaArtificial::contiene(int arreglo[], int size, int numero) {
    if (size < 0)
        return false;
    for (int i = 0; i < size; i++) {
        if (arreglo[i] == numero)
            return true;
    }
    return false;
}

int InteligenciaArtificial::buscarGanadoras(char** tablero, char car) {
    for (int i = 0; i < 8; i++) {
        char x = obtenerCasilla(tablero, jugadasGanadoras[i][0]);
        char y = obtenerCasilla(tablero, jugadasGanadoras[i][1]);
        char z = obtenerCasilla(tablero, jugadasGanadoras[i][2]);

        if (x == y && x == car) { // (x == car && y == car)
            if (z == ' ')
                return jugadasGanadoras[i][2];
        } else if (x == z && x == car) { // (x == car && z == car)
            if (y == ' ')
                return jugadasGanadoras[i][1];
        } else if (y == z && y == car) { // (y == car && z == car)
            if (x == ' ')
                return jugadasGanadoras[i][0];
        }
    }
    return 0;
}

char InteligenciaArtificial::obtenerCasilla(char**& tablero, int casilla) {
    if (tablero != NULL)
        return tablero[(casilla - 1) / 3][(casilla - 1) % 3];
    return '.';
}

int InteligenciaArtificial::casillasOcupadas(char** matriz) {
    int c = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matriz[i][j] != ' ') {
                c++;
            }
        }
    }
    return c;
}