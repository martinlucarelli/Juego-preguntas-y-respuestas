#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include "Jugador.h"
#include "puntos.h"

struct Puntos{

    int actuales;
    int puntMax;
};

PuntosPtr cargarPuntosNulos(){
    PuntosPtr p= malloc(sizeof(struct Puntos));

    p->actuales=0;
    p->puntMax=0;

    return p;
}

void mostrarPuntosActuales(PuntosPtr p){

    printf("\nPuntaje----->  %d",p->actuales);
}

void mostrarPuntosMax(PuntosPtr p){

    printf("\n Puntaje total-----> %d",p->puntMax);
}

void iniciarPuntajeEn0(PuntosPtr p,int puntinicial){

    p->actuales=puntinicial;
    p->puntMax=puntinicial;

}

void setPuntajeActual(PuntosPtr p,int puntAct){

    p->actuales=puntAct;
}

void setPuntajeTotal(PuntosPtr p,int totPunt){

    p->puntMax=totPunt;
}

int getPuntajeActual(PuntosPtr p){

    return p->actuales;
}

int getPuntajeTotal(PuntosPtr p){

    return p->puntMax;
}
