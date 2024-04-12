#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include <math.h>
#include "Jugador.h"
#include "Juego.h"
#include "puntos.h"

Juegoptr cargarJuego(int cantJugadores){

    Juegoptr j= malloc(sizeof(struct Juego));

    j->jugadores=crearVectorDeJugadores(cantJugadores);
    cargarVector(j->jugadores,cantJugadores);
    return j;
}
void mostrarJuego(Juegoptr j,int cantJugadores){

    mostrarVector(j->jugadores,cantJugadores);
}

void limpiarConsola(int segundosAntesDeLimpiar){

    sleep(segundosAntesDeLimpiar);
    system("cls");
}

void presionarParaContinuar(){

    getch();
}

int responder(){
    int respuestaUsuario;

    do{
    printf("\n Elegi una opcion (1,2,3,4)------> ");
    scanf("%d", &respuestaUsuario);
    if(respuestaUsuario < 1 || respuestaUsuario > 4){

        printf("\n Las unicas opciones son 1,2,3,4.");
    }
    }while(respuestaUsuario < 1 || respuestaUsuario > 4);

    return respuestaUsuario;
}

void preguntarYResponder (int cantPreg,PreguntaPtr p[], JugadorPtr j,int pos){

    int indices[cantPreg];
    for(int i=0;i<cantPreg;i++){
        indices[i]=i;
    }
    for(int i=cantPreg-1;i>0;i--){
        int j=rand() % (i+1);
        int temp=indices[i];
        indices[i]=indices[j];
        indices[j]=temp;
    }
    ///
    int x=0;
    int tiempolimite=10;
    clock_t tiempoinicial,tiempoactual;
    int tiempotranscurrido=0;


    tiempoinicial=clock();

    while(tiempotranscurrido < tiempolimite && x==0){



    for(int i=0;i<cantPreg;i++){

        tiempolimite = 10;
        tiempotranscurrido = 0;
        tiempoinicial=clock();
        int aleat= indices[i];
       mostarPregunta(p[aleat]);

       printf("\nResponde en %d segundos: ", tiempolimite - tiempotranscurrido);
       int  respueta=responder();
       int indiceRespuesta = respueta -1;


           tiempoactual=clock();
           tiempotranscurrido= (int)(tiempoactual - tiempoinicial)/ CLOCKS_PER_SEC;
            if(tiempotranscurrido >= tiempolimite){

                printf("\n RESPONDISTE FUERA DE TIEMPO!!!!!! ");
                mostrarPuntosActuales(j[pos].puntaje);
                break;
            }



       if(p[aleat]->posibles[indiceRespuesta]->correcta){

            printf("\n RESPUESTA CORRECTA!!!! ");
            setPuntajeActual(j[pos].puntaje, getPuntajeActual(j[pos].puntaje) + 10);
            if(tiempotranscurrido < 4){
                printf("\n Respondiste en menos de 4 segundos!!!, sumas 5 puntos extra \n");
                setPuntajeActual(j[pos].puntaje, getPuntajeActual(j[pos].puntaje) + 5);
            }
            mostrarPuntosActuales(j[pos].puntaje);
            printf("\n\n");
       }
       else{
            printf("\n RESPUESTA INCORRECTA :(  ");
            mostrarPuntosActuales(j[pos].puntaje);
            x=1;
            break;
       }
    }
    }

    setPuntajeTotal(j[pos].puntaje,(getPuntajeActual(j[pos].puntaje)));

}

void comenzarJuego(int cantjug,int cantpreg,Juegoptr juego){
    limpiarConsola(2);
    printf("\n Presione cualquier tecla para comenzar");
    presionarParaContinuar();
    limpiarConsola(1);
    for(int i=0;i<cantjug;i++){
        printf("\n                                                                      <<<<<<<<<<<<<<<<<<<<<<<<< TURNO DE: %s >>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n\n",juego->jugadores[i].alias);
        preguntarYResponder(cantpreg,juego->jugadores->preguntas,juego->jugadores,i);

        limpiarConsola(2);
        if(i<cantjug-1){
        printf("\n Turno del siguiente jugador. presiona cualquier tecla para comenzar");
        presionarParaContinuar();

        }
    }
}

void mostrarPuntajes(JugadorPtr j,int cantJug){

    limpiarConsola(3);

    for(int i=0;i<cantJug;i++){

        int puntMaxAux= getPuntajeTotal(j[i].puntaje);
        printf("\n %s ------> %d puntos", j[i].alias,puntMaxAux);
    }
}

IndicesDeEmpateptr cargarIndicesNulos(){

    IndicesDeEmpateptr i = malloc(sizeof(struct IndicesDeEmpate));

    i->pos1=-1;
    i->pos2=-1;

    return i;
}

IndicesDeEmpateptr compararPuntajes(int cantjug, JugadorPtr j){
    int indice=0;
    int max=getPuntajeTotal(j[0].puntaje);

    for(int i=0;i<cantjug;i++){
        int aux=getPuntajeTotal(j[i].puntaje);
        if(aux > max){
            max=aux;
            indice=i;
        }
    }

    IndicesDeEmpateptr indices = cargarIndicesNulos();
    indices->pos1=indice;


    int cont=0;
    int indice2;
    for(int i=0;i<cantjug;i++){
        int aux=getPuntajeTotal(j[i].puntaje);
        if(aux == max){
            cont=cont+1;
            if(cont > 1){
                indice2=i;
                indices->pos2=indice2;
            }

        }
    }

    return indices;

}

void preguntaDeDesempate(int pos1,int pos2, JugadorPtr j){

    int num1,num2,num3,respuesta;
    int x=0;
    int rtajug1,rtajug2;

    while(x==0){

        num1= rand() % 90+ 10;
        num2=rand() % 90+ 10;
        num3=rand() % 2+ 2;
        respuesta= num1+num2*num3;
        printf("\n Cual es el resultado de: %d + %d * %d",num1,num2,num3);

        printf("\n Respuesta de %s-----> ",j[pos1].alias);
        scanf("%d",&rtajug1);
        printf("\n Respuesta de %s-----> ",j[pos2].alias);
        scanf("%d",&rtajug2);

        printf("\n RESPUESTA CORRECTA ------------------------------> %d <------------------------------------", respuesta);

        int diferenciajug1= abs(respuesta - rtajug1);
        int diferenciajug2= abs(respuesta - rtajug2);

        if(rtajug1== respuesta && rtajug2==respuesta){

            printf("\n AMBAS RESPUESTAS SON CORRECTAS!!\n Hay empate nuevamente, presione cualquier tecla para una nueva pregunta de desempate.");
            presionarParaContinuar();
            limpiarConsola(1);
        }else if(rtajug1==respuesta){

            printf("\n %s RESPONDIO CORRECTAMENTE!!!!!",j[pos1].alias);
            setPuntajeTotal(j[pos1].puntaje,(getPuntajeTotal(j[pos1].puntaje)+5));
            x=1;
        }else if(rtajug2==respuesta){

            printf("\n %s RESPONDIO CORRECTAMENTE!!!!!",j[pos2].alias);
            setPuntajeTotal(j[pos2].puntaje,(getPuntajeTotal(j[pos2].puntaje)+5));

            x=1;
        }else{

            if(diferenciajug1<diferenciajug2){

                printf("\n %s ESTA MAS CERCA DE LA RESPUESTA CORRECTA!!!!!!!",j[pos1].alias);
                setPuntajeTotal(j[pos1].puntaje,(getPuntajeTotal(j[pos1].puntaje)+5));
                x=1;
            }else if(diferenciajug2<diferenciajug1){

                printf("\n %s ESTA MAS CERCA DE LA RESPUESTA CORRECTA!!!!!!!",j[pos2].alias);
                setPuntajeTotal(j[pos2].puntaje,(getPuntajeTotal(j[pos2].puntaje)+5));
                x=1;
            }else{

                printf("\n LAS DOS RESPUESTAS ESTAN A IGUAL DIFERENCIA DEL LA RESPUESTA CORRECTA!!\n Hay empate nuevamente, presione cualquier tecla para una nueva pregunta de desempate. ");
                presionarParaContinuar();
                limpiarConsola(1);
            }
        }
    }
}

void desempateOGanador(int cantjug,JugadorPtr j){

    IndicesDeEmpateptr i= compararPuntajes(cantjug,j);


    if(i->pos2 == -1){
        limpiarConsola(2);
        for(int k=0;k<2;k++){
            printf("\n-----------------------------------------------------------------------------------------------FIN DEL JUEGO------------------------------------------------------------\n");
            system("color 4");
            printf("\n\n\n\n======================================================================================== EL GANADOR ES %s ================================================ ", j[i->pos1].alias);

            limpiarConsola(1);
            printf("\n-----------------------------------------------------------------------------------------------FIN DEL JUEGO------------------------------------------------------------\n");
            system("color 1");
            printf("\n\n\n\n======================================================================================== EL GANADOR ES %s ================================================ ", j[i->pos1].alias);

            limpiarConsola(1);
            printf("\n-----------------------------------------------------------------------------------------------FIN DEL JUEGO------------------------------------------------------------\n");
            system("color 2");
            printf("\n\n\n\n======================================================================================== EL GANADOR ES %s ================================================ ", j[i->pos1].alias);
            limpiarConsola(1);
        }

    }else{
        printf("\n-----------------------------------------------------------------------------------------------!!!EMPATE!!!-------------------------------------------------------------\n");
        printf("\n SE DEBE RESPONDER UNA PREGUNTA MATEMATICA ENTRE %s Y %s",j[i->pos1].alias,j[i->pos2].alias);
        printf("\n\n AVISO!. La pregunta debe ser ingresada por teclado por los jugadores, en caso de ninguna respuesta sea correcta ganara el que se aproxime mas al resultado. Exitos...");
        printf("\n\n Listos??. presionen una tecla para continuar...");
        presionarParaContinuar();
        limpiarConsola(1);
        preguntaDeDesempate(i->pos1,i->pos2,j);
        desempateOGanador(cantjug,j);
    }
}

void reglas(){

    printf("\n-----------------------------------------------------------------------------REGLAS------------------------------------------------------------------------------------\n");
    printf("\n\n .SE TRATA DE UN JUEGO MULTIJUGADOR DONDE LA CANTIDAD MINIMA DE JUGADORES ES 2 Y LA MAXIMA 4");
    printf("\n\n .SE LE HARAN PREGUNTAS A LOS JUGADORES Y ESTOS DEBEN ELEGIR ENTRE 4 OPCIONES(con las telcas 1,2,3,4)");
    printf("\n\n .LOS TURNOS PARA RESPONDER VAN A SER SEGUN EL ORDEN QUE INGRESARON SUS DATOS, EL QUE SE REGISTRO PRIMERO RESPONDE PRIMERO,ETC");
    printf("\n\n .EL JUGADOR QUE TIENE EL TURNO DE RESPONDER SEGUIRA JUGANDO MIENTRAS RESPONDA CORRECTAMENTE DENTRO DEL TIEMPO");
    printf("\n\n .TODOS LOS JUGADORES TIENEN 10 SEGUNDOS PARA RESPONDER, EL TIEMPO TRANSCURRIDO NO ES MOSTRADO EN PANTALLA Y AUNQUE PASEN LOS 10 SEGUNDOs EL JUGADOR\n  PODRA RESPONDER, PERO SU RESPUESTA SE TOMARA COMO 'fuera de tiempo' AUNQUE SEA CORRRECTA");
    printf("\n\n .POR CADA RESPUESTA CORRECTA EL JUGADOR SUMA 10 PUNTOS. SI EL JUGADOR RESPONDE EN MENOS DE 4 SEGUNDOS SUMARA 5 PUNTOS EXTRA");
    printf("\n\n .EN CASO DE QUE DOS JUGADORES TERMINEN CON EL MISMO PUNTAJE ESTOS DEBERAN RESPONDER UNA PREGUNTA MATEMATICA DE DESEMPATE QUE LA RESPUESTA DEBE SER INGRESADA\n  POR TECLADO Y SE TOMARA COMO CORRECTA LA QUE ACIERTE O EN SU DEFECTO, LA QUE SE ACERQUE MAS AL RESULTADO\n\n" );
    printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void bienvenida(MejoresJugadoresPtr m[]){
    int opcion;
    printf("\n\n ---------------------------------------------------------BIENVENIDOS AL JUEGO DE PREGUNTAS Y RESPUESTAS---------------------------------------------------------------\n\n");
    printf("\n .Presione 1 para ver las reglas\n .Presione 2 para ver el top 5 de ganadores\n .Presione 3 para comenzar a jugar ");
    scanf("%d",&opcion);

    switch (opcion){

        case 1:
            reglas();
            printf("\n .Presione 1 para ver las reglas\n .Presione 2 para ver el top 5 de ganadores\n .Presione 3 para comenzar a jugar ");
            scanf("%d",&opcion);
            limpiarConsola(1);
        case 2:
            mostrarMejoresJugadores(m);
            printf("\n\n\n .Presione 1 para ver las reglas\n .Presione 2 para ver el top 5 de ganadores\n .Presione 3 para comenzar a jugar ");
            scanf("%d",&opcion);
            limpiarConsola(1);
        case 3:
            limpiarConsola(1);
            break;

        default:
            printf("\n OPCION NO VALIDA, eliga 1,2,3");
            printf("\n .Presione 1 para ver las reglas\n .Presione 2 para ver el top 5 de ganadores\n .Presione 3 para comenzar a jugar ");
            scanf("%d",&opcion);
    }
}

void fin(){


    printf("\n\n\n");
    printf("\n========================================================================================================================================================================\n");
    printf("\n======================================================================= GRACIAS POR JUGAR ==============================================================================\n");
    printf("\n========================================================================================================================================================================\n");
}
