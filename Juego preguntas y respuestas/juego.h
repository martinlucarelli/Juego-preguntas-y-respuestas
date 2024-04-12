#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include "Jugador.h"



struct Juego{

    JugadorPtr jugadores;
};
typedef struct Juego * Juegoptr;

struct IndicesDeEmpate{

    int pos1;
    int pos2;
};
typedef struct IndicesDeEmpate * IndicesDeEmpateptr;

Juegoptr cargarJuego(int cantJugadores);

void mostrarJuego(Juegoptr j,int cantJugadores);

void limpiarConsola();

void presionarParaContinuar();

int responder();

void preguntarYResponder (int cantPreg,PreguntaPtr p[], JugadorPtr j,int pos);

void comenzarJuego(int cantjug,int cantpreg,Juegoptr juego);

void mostrarPuntajes(JugadorPtr j,int cantJug);

IndicesDeEmpateptr compararPuntajes(int cantjug, JugadorPtr j); //devuelve 0 si no hay empate, devuelve 1 si hay empate

IndicesDeEmpateptr cargarIndicesNulos();

void desempateOGanador(int cantjug,JugadorPtr j);

void preguntaDeDesempate(int pos1,int pos2, JugadorPtr j);



void reglas();

void bienvenida(MejoresJugadoresPtr m[]);

void fin();


#endif // JUEGO_H_INCLUDED
