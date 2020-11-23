#ifndef INTELIGENCIAARTIFICIAL_H
#define INTELIGENCIAARTIFICIAL_H

class InteligenciaArtificial {
public:
    InteligenciaArtificial(char,char);
    InteligenciaArtificial(const InteligenciaArtificial& orig);
    int analizar(char**);
    virtual ~InteligenciaArtificial();
private:
    int ARRIBA = 1;
    int ABAJO = 2;
    int IZQUIERDA = 3;
    int DERECHA = 4;
    
    char caracter;
    char oponente;
    
    int lados[4] = {2, 4, 6, 8};
    int esquinas[4] = {1, 3, 7, 9};
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
    bool primerTurno;
    int ultimaJugada;
    
    int siguiente = 0;
    int caso = 1;
    /* 1 = esquina X - Lado 0 - esquina adyacente X - Lado adyacente 0 - Centro X
     */
    
    bool contiene(int[],int,int);
    int casillasOcupadas(char**);
    
    int buscarGanadoras(char**,char);
    int buscarAmenaza(char**,char);
    
    bool sonAdyacentesVerticales(int,int);
    bool sonAdyacentesHorizontales(int,int);
    bool sonOpuestos(int,int);
    
    char obtenerCasilla(char**&,int);
    int obtenerOpuesta(int);
    int obtenerCasillaSuperior(int);
    int obtenerCasillaInferior(int);
    int obtenerCasillaIzquierda(int);
    int obtenerCasillaDerecha(int);
    
};

#endif /* INTELIGENCIAARTIFICIAL_H */
