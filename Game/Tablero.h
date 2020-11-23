#ifndef TABLERO_H
#define TABLERO_H

class Tablero {
public:
    Tablero();
    Tablero(const Tablero& orig);
    void crearTablero();
    void liberarTablero();
    void limpiarTablero();
    void imprimirTablero();
    void establecerCasilla(int, char);
    char obtenerCasilla(int);
    char** obtenerMatriz();
    
    virtual ~Tablero();
private:
    char** tablero;
    int size;

};

#endif /* TABLERO_H */

