#include <iostream>
#include <fstream>
using namespace std;

struct Jugador
{
    int numero;
};
struct Casilla
{
    string NumCasilla;
    string TipoCasilla;
    Jugador *listaJugadores;
    Casilla *proxCasilla;
};
bool listaVacia(Casilla *inicio)
{
    return inicio == NULL;
}
void mostrarmapa(Casilla *inicio)
{
    Casilla *mover;

    if (!listaVacia(inicio))
    {
        mover = inicio;
        while (mover != NULL)
        {
            cout << mover->NumCasilla << " " << mover->TipoCasilla << " " << "->";
            mover = mover->proxCasilla;
        }
        cout << "NULL" << endl;
    }
    else
        cout << "Lista esta vacia" << endl;
}
Casilla *crearNodo(string valor, string tipo)
{
    Casilla *nuevo = new Casilla;
    nuevo->NumCasilla = valor;
    nuevo->TipoCasilla = tipo;
    nuevo->proxCasilla = NULL;
    return nuevo;
}

void insertarUltimoMapa(Casilla **mapa, string num, string tipo)
{
    Casilla *nuevo = crearNodo(num, tipo);

    if (listaVacia(*mapa))
    {
        *mapa = nuevo;
    }
    else
    {
        Casilla *auxiliar = *mapa;
        while (auxiliar->proxCasilla != NULL)
        {
            auxiliar = auxiliar->proxCasilla;
        }
        auxiliar->proxCasilla = nuevo;
    }
}

int main()
{
    Casilla *mapa = NULL;
    int i = 0;
    string numerocasilla;
    string tipo, auxiliarstr;
    ifstream archivo("mapa.txt");
    while (i != 36)
    {
        getline(archivo, auxiliarstr);
        numerocasilla = auxiliarstr;
        // cout << numerocasilla << endl;
        getline(archivo, auxiliarstr);
        tipo = auxiliarstr;
        //  cout << tipo << endl;
        insertarUltimoMapa(&mapa, numerocasilla, tipo);
        i++;
        //  cout << i << endl;
    }
    archivo.close();
    mostrarmapa(mapa);
    return 0;
}