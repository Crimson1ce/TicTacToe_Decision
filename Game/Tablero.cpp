#include "Tablero.h"
#include <iostream>

using std::cout;
using std::endl;

Tablero::Tablero() {
    size = 3;
    tablero = NULL;
    crearTablero();
    limpiarTablero();
}

Tablero::Tablero(const Tablero& orig) {
}

Tablero::~Tablero() {
    liberarTablero();
}

void Tablero::crearTablero() {
    if (tablero != NULL) {
        liberarTablero();
    }
    //instanciar la matriz
    tablero = new char*[size];
    
    for (int i = 0; i < size; i++) {
        tablero[i] = new char[size];
    }

}

void Tablero::liberarTablero() {
    if (tablero != NULL) {
        for (int i = 0; i < size; i++) {
            if (tablero[i] != NULL) {
                delete [] tablero[i];
                tablero[i] = NULL;
            }
        }
        delete [] tablero;
        tablero = NULL;
    }
}

void Tablero::imprimirTablero() {
    if (tablero != NULL) {
        cout << "~~~~~~~~~~~" << endl;
        cout << " " << tablero[0][0] << " | " << tablero[0][1] << " | " << tablero[0][2] << endl;
        cout << "---+---+---" << endl;
        cout << " " << tablero[1][0] << " | " << tablero[1][1] << " | " << tablero[1][2] << endl;
        cout << "---+---+---" << endl;
        cout << " " << tablero[2][0] << " | " << tablero[2][1] << " | " << tablero[2][2] << endl;
    }
}

void Tablero::limpiarTablero() {
    if (tablero != NULL) {
        for (int i = 0; i < size; i++) {
            if (tablero[i] != NULL) {
                for (int j = 0; j < size; j++) {
                    tablero[i][j] = ' ';
                }
            }
        }
    }
}

void Tablero::establecerCasilla(int casilla, char caracter) {
    if (tablero != NULL)
        tablero[(casilla - 1) / 3][(casilla - 1) % 3] = caracter;
}

char Tablero::obtenerCasilla(int casilla) {
    if (tablero != NULL)
        return tablero[(casilla - 1) / 3][(casilla - 1) % 3];
    return '-';
}

char** Tablero::obtenerMatriz() {
    return tablero;
}
