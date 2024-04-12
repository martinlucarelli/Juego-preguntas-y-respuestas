#ifndef PREGUNTA_H_INCLUDED
#define PREGUNTA_H_INCLUDED

#include "respuesta.h"

struct Pregunta{

    int nroPregunta;
    char pregunta[350];//
    RespuestaPtr posibles[4];

};
typedef struct Pregunta * PreguntaPtr;

PreguntaPtr cargarPreguntaNula();

void mostarPregunta(PreguntaPtr p);

void mostrarPreguntas(PreguntaPtr p[],int tam);

void cargarPreguntasNulas(PreguntaPtr p[],int tam);

void cargarPreguntaDeArchivo(PreguntaPtr pregunta[]);


#endif // PREGUNTA_H_INCLUDED
