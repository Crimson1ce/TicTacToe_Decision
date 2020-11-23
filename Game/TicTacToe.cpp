#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>

#include "Tablero.h"
#include "InteligenciaArtificial.h"

using namespace std;

bool verificarGanador(char**, char);
bool verificarEmpate(char**);
bool verificarCasilla(char**, int);
bool verificarFinDelJuego(char, char[], char**);

int jugadasGanadoras[8][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
    {1, 4, 7},
    {2, 5, 8},
    {3, 6, 9},
    {1, 5, 9},
    {3, 5, 7}
};

int main(int argc, char** argv) {
    char jugador1[15];
    char jugador2[15] = "Markus 3478";

    int casilla1 = 0;
    int casilla2 = 0;

    cout << "Ingrese el nombre del Jugador: ";
    cin.getline(jugador1, 15, '\n');
//    cout << "Ingrese el nombre del Jugador 2: ";
//    cin.getline(jugador2, 15, '\n');

    int turno = 0;

    InteligenciaArtificial intel('0', 'X');
    
    srand(time(0));
    if (rand() % 2) {
        cout << endl << "Empieza " << jugador1 << " con 'X'! "<< endl;
    } else {
        cout << endl << "Empieza " << jugador2 << " con '0'! "<< endl;
        turno = 1;
    }
    cout << endl;

    Tablero tablero;

    tablero.imprimirTablero();
    while (true) {

        if (turno == 0) {
            cout << "\nEs el turno de " << jugador1 << " (X)\n";
            do {
                cout << "Ingresa una casilla para jugar (1-9): ";
                cin >> casilla1; //Aqui
            } while (!verificarCasilla(tablero.obtenerMatriz(), casilla1));

            tablero.establecerCasilla(casilla1, 'X');
            tablero.imprimirTablero();
            
            if (verificarFinDelJuego('X',jugador1,tablero.obtenerMatriz())){
                break;
            }

            turno = 1;
        }

        if (turno == 1) {
            cout << "\nEs el turno de " << jugador2 << ", la Inteligencia (0)\n";
            do {
                cout << "Ingresa una casilla para jugar (1-9): ";
                casilla2 = intel.analizar(tablero.obtenerMatriz());
                cout << casilla2 << endl;
            } while (!verificarCasilla(tablero.obtenerMatriz(), casilla2));
            tablero.establecerCasilla(casilla2, '0');

            tablero.imprimirTablero();

            if (verificarFinDelJuego('0',jugador2,tablero.obtenerMatriz())){
                break;
            }
            
            turno = 0;
        }
    }
    
    cout << "\nPresione ENTER para finalizar.\n";
    cin.ignore();
    cin.get();
    return 0;
}

bool verificarGanador(char** matriz, char jugador) {
    for (int i = 0; i < 8; i++) {
        int x = jugadasGanadoras[i][0];
        int y = jugadasGanadoras[i][1];
        int z = jugadasGanadoras[i][2];

        if (matriz[(x - 1) / 3][(x - 1) % 3] == jugador &&
                matriz[(y - 1) / 3][(y - 1) % 3] == jugador &&
                matriz[(z - 1) / 3][(z - 1) % 3] == jugador) {
            return true;
        }
    }
    return false;
}

bool verificarEmpate(char** matriz) {
    bool flag = true;
    for (int i = 1; i <= 9; i++) {
        if (matriz[(i - 1) / 3][(i - 1) % 3] == ' ') {
            flag = false;
            break;
        }
    }
    return flag;
}

bool verificarCasilla(char** matriz, int casilla) {
    if (casilla > 0 && casilla < 10) {
        if (matriz[(casilla - 1) / 3][(casilla - 1) % 3] == ' ')
            return true;
    }
    return false;
}

bool verificarFinDelJuego(char caracter, char jugador[], char** matriz) {
    if (verificarGanador(matriz, caracter)) {
        cout << "\nEl ganador es " << jugador << "! Felicidades!" << endl;
        return true;
    } else if (verificarEmpate(matriz)) {
        cout << "\nHay un empate!" << endl;
        return true;
    }
    return false;
}