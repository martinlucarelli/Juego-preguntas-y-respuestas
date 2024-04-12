#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include "pregunta.h"
#include "respuesta.h"


PreguntaPtr cargarPreguntaNula(){

    PreguntaPtr p=malloc(sizeof(struct Pregunta));

    p->nroPregunta=0;
    strcpy(p->pregunta,"VACIOO");//
    CargarRespuestasNulas(p->posibles,4);


    return p;
}
void mostarPregunta(PreguntaPtr p){

    printf("\n - %s", p->pregunta);//
    printf("\n");
    mostrarRespuestas(p->posibles,4);
    printf("\n");
}
void cargarPreguntasNulas(PreguntaPtr p[],int tam){

    for(int i=0;i<tam;i++){

        p[i]=cargarPreguntaNula();
    }
}
void mostrarPreguntas(PreguntaPtr p[],int tam){

    for(int i=0;i<tam;i++){

        mostarPregunta(p[i]);
    }
}
////////Archivo/////////////////////
void cargarPreguntaDeArchivo(PreguntaPtr pregunta[]){

    FILE * archivo;
    archivo=fopen("preguntas.txt","r");

    if(archivo==NULL){
        printf("\nNO ES POSIBLE ABRIR EL ARCHIVO");
    }
    int pos=0;
    while(!feof(archivo)){
        fscanf(archivo,"%d,%199[^,],%d,%99[^,],%d,%d,%d,%99[^,],%d,%d,%d,%99[^,],%d,%d,%d,%99[^,],%d,%d",
                      &(pregunta[pos]->nroPregunta), pregunta[pos]->pregunta,
                      &(pregunta[pos]->posibles[0]->nroRespuesta), pregunta[pos]->posibles[0]->respuesta,
                      &(pregunta[pos]->posibles[0]->nroRespuestaAsociada), &(pregunta[pos]->posibles[0]->correcta),
                      &(pregunta[pos]->posibles[1]->nroRespuesta), pregunta[pos]->posibles[1]->respuesta,
                      &(pregunta[pos]->posibles[1]->nroRespuestaAsociada), &(pregunta[pos]->posibles[1]->correcta),
                      &(pregunta[pos]->posibles[2]->nroRespuesta), pregunta[pos]->posibles[2]->respuesta,
                      &(pregunta[pos]->posibles[2]->nroRespuestaAsociada), &(pregunta[pos]->posibles[2]->correcta),
                      &(pregunta[pos]->posibles[3]->nroRespuesta), pregunta[pos]->posibles[3]->respuesta,
                      &(pregunta[pos]->posibles[3]->nroRespuestaAsociada), &(pregunta[pos]->posibles[3]->correcta));
        pos++;
    }

    fclose(archivo);
}
