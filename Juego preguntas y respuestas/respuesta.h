#ifndef RESPUESTA_H_INCLUDED
#define RESPUESTA_H_INCLUDED

struct Respuesta{
    int nroRespuesta;
    char respuesta[100];
    int nroRespuestaAsociada;
    int correcta; //0 1
};
typedef struct Respuesta * RespuestaPtr;

RespuestaPtr CargarRespuestaNula();

void CargarRespuestasNulas(RespuestaPtr r[],int tam);

void mostrarRespuesta(RespuestaPtr r);

void mostrarRespuestas(RespuestaPtr r[], int tam);


#endif // RESPUESTA_H_INCLUDED
