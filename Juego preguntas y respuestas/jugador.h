#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#define TOTALPREG 61


#include "pregunta.h"
#include "puntos.h"

struct Jugador{
    int dni;
    char alias[25];
    PreguntaPtr preguntas[TOTALPREG];
    PuntosPtr puntaje;
};
typedef struct Jugador *JugadorPtr;

struct MejoresJugadores{
    int dni;
    char alias[25];
    PuntosPtr puntaje;
};
typedef struct MejoresJugadores *MejoresJugadoresPtr;

JugadorPtr cargarJugadorTeclado ();

JugadorPtr cargarJugadorNulo();

void mostrarJugador (JugadorPtr j);

int definirCantidadJugadores();

JugadorPtr crearVectorDeJugadores (int tam);

void cargarVector (JugadorPtr j,int tam);

void mostrarVector (JugadorPtr j,int tam);

/// MEJORES PUNTAJES

MejoresJugadoresPtr cargarMejorJugadorNulo();

void cargarMejoresJugadoresNulos(MejoresJugadoresPtr m[]);

void mostrarMejorJugador(MejoresJugadoresPtr m);

void mostrarMejoresJugadores(MejoresJugadoresPtr m[]);

void cargarMejoresJugDeArchivo(MejoresJugadoresPtr m[]);

void ordenarMejoresJugadores(MejoresJugadoresPtr m[]);

void guardarMejoresJugadores(MejoresJugadoresPtr m[]);

void compararConGanador(MejoresJugadoresPtr m[],JugadorPtr j,int cantJug);

void reemplazarConGanador(MejoresJugadoresPtr m, JugadorPtr j,int pos);



#endif // JUGADOR_H_INCLUDED
