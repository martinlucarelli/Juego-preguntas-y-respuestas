#ifndef PUNTOS_H_INCLUDED
#define PUNTOS_H_INCLUDED

struct Puntos;

typedef struct Puntos * PuntosPtr;

PuntosPtr cargarPuntosNulos();

void mostrarPuntosActuales(PuntosPtr p);

void mostrarPuntosMax(PuntosPtr p);

void iniciarPuntajeEn0 (PuntosPtr p,int puntinicial);

void setPuntajeActual(PuntosPtr p,int puntAct);

void setPuntajeTotal(PuntosPtr p,int totPunt);

int getPuntajeActual(PuntosPtr p);

int getPuntajeTotal(PuntosPtr p);






#endif // PUNTOS_H_INCLUDED
