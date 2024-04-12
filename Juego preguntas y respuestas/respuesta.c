#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pregunta.h"
#include "respuesta.h"


RespuestaPtr CargarRespuestaNula(){

    RespuestaPtr r = malloc(sizeof(struct Respuesta));

    r->nroRespuesta= 0;
    strcpy(r->respuesta,"VACIO");
    r->nroRespuestaAsociada= 0;
    r->correcta= -1;

    return r;
}
void CargarRespuestasNulas(RespuestaPtr r[],int tam){

    for (int i=0;i<tam;i++){

        r[i]=CargarRespuestaNula();

    }
}
void mostrarRespuesta(RespuestaPtr r){

    printf("\n %d - %s", r->nroRespuesta, r->respuesta);
}

void mostrarRespuestas(RespuestaPtr r[],int tam){

    for(int i=0;i<tam;i++){

        mostrarRespuesta(r[i]);
    }
}
