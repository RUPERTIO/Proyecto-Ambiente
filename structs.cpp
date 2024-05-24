#include <iostream>
using namespace std;
struct stats
{
    int dinero;
    int inteligencia;
    int vida;
    int estrellas;
    bool proteccion;
};
struct jugador
{
    char letra;
    stats *prox;
    jugador *proxjg;
};
struct mapa
{
    mapa *prox;
}

Inicio
    Struct Casilla
{
    Int 1 ;
    String vacio ;
    Jugador *listaJugadores;
    Casilla *proxCasilla
}
Vacio
    Struct Casilla
{
    Int 11,20,29;
    String vacio;
    Jugador *listaJugadores;
    Casilla *proxCasilla
}
Dinero 
    Struct Casilla
{
    Int 2,6,9,12,18,21,27,30,36;
    String Dinero;
    Jugador *listaJugadores;
    Casilla *proxCasilla
}
estudio
    Struct Casilla
{
    Int 3,7,13,16,22,25,31,34;
    String vacio;
    Jugador *listaJugadores;
    Casilla *proxCasilla
}
Desafio
    Struct Casilla
{
    Int 4,8,14,17,23,26,32,35;
    String vacio;
    Jugador *listaJugadores;
    Casilla *proxCasilla
}
Carta
    Struct Casilla
{
    Int 5,15,24,33;
    String vacio;
    Jugador *listaJugadores;
    Casilla *proxCasilla
}
Catastrofe
    Struct Casilla
{
    Int 10, 19, 28;
    String vacio;
    Jugador *listaJugadores;
    Casilla *proxCasilla
}
void
crearjugador(jugador **listaPlayer)
{
    int cantidad = 0;
    cout << "b" << endl;

    while ((cantidad <= 1) || (cantidad >= 5))
    {
        cout << "Indique cantidad de jugares(min 2, max 4): ";
        cin >> cantidad;
        if (cantidad > 1 && cantidad < 5)
            break;
        cout << endl
             << "cantidad invalida de jugadores" << endl;
    }
}

void insertarUltimo(Nodo **inicio, int valor)
{
    Nodo *nuevo = crearNodo(valor);

    if (listaVacia(*inicio))
    {
        *inicio = nuevo;
    }
    else
    {
        Nodo *auxiliar = *inicio;
        while (auxiliar->prox != NULL)
        {
            auxiliar = auxiliar->prox;
        }
        auxiliar->prox = nuevo;
    }
}

void CrearMapa(Mapa **mapa)
{
}

int main()
{
    jugador *ListaJG = NULL;
    crearjugador(&ListaJG);
    cout << "a";
    return 0;
}
