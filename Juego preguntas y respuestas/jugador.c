#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include "Jugador.h"
#include "Juego.h"

JugadorPtr cargarJugadorTeclado (){
    JugadorPtr j=malloc(sizeof(struct Jugador));

    printf("\n ALIAS------> ");
    fflush(stdin);
    gets(j->alias);
    printf("\n DNI--------> ");
    scanf("%d",&j->dni);
    cargarPreguntasNulas(j->preguntas,TOTALPREG);
    cargarPreguntaDeArchivo(j->preguntas);
    j->puntaje=cargarPuntosNulos();
    return j;
}

JugadorPtr cargarJugadorNulo(){

    JugadorPtr j = malloc(sizeof(struct Jugador));

    strcpy(j->alias,"VACIO");
    j->dni= -1;
    cargarPreguntasNulas(j->preguntas,TOTALPREG);
    j->puntaje=cargarPuntosNulos();

    return j;

}
void mostrarJugador (JugadorPtr j){

    printf("\n=================================\n");
    printf("\n ALIAS --------> %s", j->alias);
    printf("\n DNI ----------> %d", j->dni);
    mostrarPuntosMax(j->puntaje);

}

int definirCantidadJugadores(){
    int cantJug;
    do{
    printf("\n INDICAR LA CANTIDAD DE JUGADORES (MAXIMO 4, MINIMO 2)----> ");
    scanf("%d", &cantJug);
    if(cantJug>4 || cantJug<2){
        printf("\n Lo siento solo pueden jugar 2,3 o 4 jugadores :(   intentalo de nuevo\n");//
    }

    }while(cantJug>4 || cantJug<2);

    return cantJug;
}
JugadorPtr crearVectorDeJugadores (int tam){

    JugadorPtr jugadores = malloc (tam * sizeof(struct Jugador));
    return jugadores;

}

void cargarVector (JugadorPtr j,int tam){

    for(int i=0;i<tam;i++){

         printf("\n JUGADOR %d", i+1);

        j[i]= *cargarJugadorTeclado();
    }
}

void mostrarVector (JugadorPtr j,int tam){

    for(int i=0;i<tam;i++){

        mostrarJugador(&j[i]);
    }
}

MejoresJugadoresPtr cargarMejorJugadorNulo(){

    MejoresJugadoresPtr m = malloc(sizeof(struct MejoresJugadores));

    m->dni=-1;
    m->puntaje=cargarPuntosNulos();
    strcpy(m->alias,"VACIO");

    return m;
}

void cargarMejoresJugadoresNulos(MejoresJugadoresPtr m[]){

    for(int i=0;i<5;i++){

        m[i]=cargarMejorJugadorNulo();
    }
}

void mostrarMejorJugador(MejoresJugadoresPtr m){

    if(m->dni != -1){
        int puntaje = getPuntajeTotal(m->puntaje);
        printf(" %s    |DNI: %d...................%d PUNTOS",m->alias,m->dni,puntaje);
    }

}

void mostrarMejoresJugadores(MejoresJugadoresPtr m[]){

    for(int i=0;i<5;i++){

        printf("\n %d",i+1);
        mostrarMejorJugador(m[i]);
    }
}

void cargarMejoresJugDeArchivo(MejoresJugadoresPtr m[]){

        FILE * archivo;
    archivo=fopen("mejoresJugadores.txt","r");

    if(archivo==NULL){
        printf("\nNO ES POSIBLE ABRIR EL ARCHIVO");
    }
    int pos=0;
    int puntaje;
    while(!feof(archivo)){

        fscanf(archivo,"%d,%199[^,],%d\n",&(m[pos]->dni),m[pos]->alias,&(puntaje));
        setPuntajeTotal(m[pos]->puntaje,puntaje);
        pos++;
    }

    fclose(archivo);
}

void ordenarMejoresJugadores(MejoresJugadoresPtr m[]){

    MejoresJugadoresPtr aux=cargarMejorJugadorNulo();
    int punt1,punt2;

    for(int i=0;i<5;i++){

        for(int j=0;j<4;j++){
            punt1 = getPuntajeTotal(m[j]->puntaje);
            punt2 = getPuntajeTotal(m[j+1]->puntaje);
            if(punt1 < punt2){

               aux=m[j];
               m[j]=m[j+1];
               m[j+1]=aux;
            }
        }
    }
}

void reemplazarConGanador(MejoresJugadoresPtr m, JugadorPtr j,int pos){

    strcpy(m->alias,j[pos].alias);
    m->dni=j->dni;
    int auxpunt=getPuntajeTotal(j[pos].puntaje);
    setPuntajeTotal(m->puntaje,auxpunt);
}

void compararConGanador(MejoresJugadoresPtr m[],JugadorPtr j,int cantJug){

    int max,aux,posganador;
    max=getPuntajeTotal(j[0].puntaje);
    posganador=0;

    for(int i=0;i<cantJug;i++){
        aux=getPuntajeTotal(j[i].puntaje);

        if(aux > max){
            max=aux;
            posganador=i;
        }
    }

    int puntAux= getPuntajeTotal(m[4]->puntaje);

    if(max > puntAux){

        reemplazarConGanador(m[4],j,posganador);
        printf("\n !!!!!!FELICIDADES!!!!!!!! <<<< %s >>>> entraste al top 5 ganadores",j[posganador].alias);
    }
}

void guardarMejoresJugadores(MejoresJugadoresPtr m[]){//

    FILE *archivo  = fopen("mejoresJugadores.txt","w");

    int auxpunt;
    for( int i = 0; i<5; i++){

        if(m[i]->dni != -1){

            auxpunt = getPuntajeTotal(m[i]->puntaje);
            fprintf(archivo, "%d,%s,%d\n",m[i]->dni,m[i]->alias,auxpunt);
        }
    }

    fclose(archivo);

}
