#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include "Jugador.h"
#include "Juego.h"
#include "pregunta.h"
#include "respuesta.h"
#include "puntos.h"




int main()
{
    srand(time(0));

    MejoresJugadoresPtr mejores[5];
    cargarMejoresJugadoresNulos(mejores);
    cargarMejoresJugDeArchivo(mejores);

    bienvenida(mejores);

    int cantPlayers=definirCantidadJugadores();
    Juegoptr juego= cargarJuego(cantPlayers);
    mostrarJuego(juego,cantPlayers);

    comenzarJuego(cantPlayers,TOTALPREG,juego);
    mostrarPuntajes(juego->jugadores,cantPlayers);
    desempateOGanador(cantPlayers,juego->jugadores);

    compararConGanador(mejores,juego->jugadores,cantPlayers);
    ordenarMejoresJugadores(mejores);
    guardarMejoresJugadores(mejores);

    fin();

    return 0;
}
