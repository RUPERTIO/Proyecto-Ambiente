#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <stdio.h>
#include <random>
using namespace std;
random_device rd;

// Estructuras
struct BoolsCasilla
{
    bool J1 = false;
    bool J2 = false;
    bool J3 = false;
    bool J4 = false;
};
struct Casilla
{
    string NumCasilla;
    string TipoCasilla;
    Casilla *proxCasilla;
    BoolsCasilla *Jugadores;
};
struct jugador
{
    string NumJ;
    int inteligencia;
    int estrellas;
    int dinero;
    int vida;
    bool proteccion;
    Casilla *ubicacion;
    jugador *proxjg;
};

uniform_int_distribution<int> distDado(1, 4);
uniform_int_distribution<int> distCarta(1, 3);
uniform_int_distribution<int> distDesafio(1, 10);
uniform_int_distribution<int> distCatastrofe(1, 5);

int Dado()
{
    return distDado(rd);
}
int carta()
{
    return distCarta(rd);
}
int desafio()
{
    return distDesafio(rd);
}
int catastrofe()
{
    return distCatastrofe(rd);
}

bool listaVacia(Casilla *inicio)
{
    return inicio == NULL;
}
bool listaVaciajg(jugador *inicio)
{
    return inicio == NULL;
}

// Funciones
void mostrarjg(jugador *inicio)
{
    jugador *mover;

    if (!listaVaciajg(inicio))
    {
        mover = inicio;
        while (mover != NULL)
        {
            cout << mover->NumJ << " " << "->";
            mover = mover->proxjg;
        }
        cout << "NULL" << endl;
    }
    else
        cout << "Lista esta vacia" << endl;
}

Casilla *crearNodoMapa(string valor, string tipo)
{
    Casilla *nuevo = new Casilla;
    nuevo->NumCasilla = valor;
    nuevo->TipoCasilla = tipo;
    nuevo->proxCasilla = NULL;
    nuevo->Jugadores = new BoolsCasilla;
    return nuevo;
}
jugador *crearNodoJG(string numjg)
{
    jugador *nuevo = new jugador;
    nuevo->NumJ = numjg;
    nuevo->inteligencia = 1;
    nuevo->estrellas = 0;
    nuevo->dinero = 5;
    nuevo->vida = 4;
    bool proteccion = false;

    nuevo->proxjg = NULL;
    return nuevo;
}
void insertarUltimoJG(jugador **inicio, string num)
{
    jugador *nuevo = crearNodoJG(num);

    if (listaVaciajg(*inicio))
    {
        *inicio = nuevo;
    }
    else
    {
        jugador *auxiliar = *inicio;
        while (auxiliar->proxjg != NULL)
        {
            auxiliar = auxiliar->proxjg;
        }
        auxiliar->proxjg = nuevo;
    }
}

void insertarUltimoMapa(Casilla **mapa, string num, string tipo)
{
    Casilla *nuevo = crearNodoMapa(num, tipo);

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

void gotoxy(int x, int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void determinarColor(string tipoCasilla, int i, int j)
{

    int tamX = 6, tamY = 3;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (tipoCasilla == "Inicio")
    {
        SetConsoleTextAttribute(hConsole, 136);
    }
    else if (tipoCasilla == "dinero")
    {
        SetConsoleTextAttribute(hConsole, 238);
    }
    else if (tipoCasilla == "estudio")
    {
        SetConsoleTextAttribute(hConsole, 187);
    }
    else if (tipoCasilla == "desafio")
    {
        SetConsoleTextAttribute(hConsole, 153);
    }
    else if (tipoCasilla == "carta")
    {
        SetConsoleTextAttribute(hConsole, 221);
    }
    else if (tipoCasilla == "catastrofe")
    {
        SetConsoleTextAttribute(hConsole, 204);
    }
    else if (tipoCasilla == "vacio")
    {
        SetConsoleTextAttribute(hConsole, 255);
    }
    // porque j y i, colocar variables mas descritivas
    int m = j, n = i;

    while (m < j + tamY)
    {
        while (n < i + tamX)
        {
            gotoxy(n, m);
            cout << " ";
            n++;
        }
        n = i;
        m++;
    }
}

void imprimirTabla(Casilla *mapa)
{

    int valor = 36;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    float posiciones = valor / 4;
    int i = 1, j = 1;
    gotoxy(i * 6, j * 3);
    determinarColor(mapa->TipoCasilla, i * 6, j * 3);
    // cout << " ";
    while (i <= posiciones)
    {
        i++;
        gotoxy(i * 3, j * 2);
        mapa = mapa->proxCasilla;
        determinarColor(mapa->TipoCasilla, i * 6, j * 3);
        // cout << " ";
    }

    while (j <= posiciones)
    {
        j++;
        gotoxy(i * 3, j * 2);
        mapa = mapa->proxCasilla;
        determinarColor(mapa->TipoCasilla, i * 6, j * 3);
        // cout << " ";
    }

    while (i > 1)
    {
        i--;
        gotoxy(i * 3, j * 2);
        mapa = mapa->proxCasilla;
        determinarColor(mapa->TipoCasilla, i * 6, j * 3);
        // cout << " ";
    }

    while (j > 2)
    {
        j--;
        gotoxy(i * 3, j * 2);
        mapa = mapa->proxCasilla;
        determinarColor(mapa->TipoCasilla, i * 6, j * 3);
        // cout << " ";
    }
    SetConsoleTextAttribute(hConsole, 7);
}
void MostrarEstadisticas(jugador *lista, string TAB)
{
    cout << TAB << lista->NumJ << endl;
    cout << TAB << " Vida: " << lista->vida << endl;
    cout << TAB << " Inteligencia: " << lista->inteligencia << endl;
    cout << TAB << " Dinero:" << lista->dinero << endl;
    cout << TAB << " Estrellas: " << lista->estrellas << endl;
    if (lista->proteccion)
        cout << TAB << " Proteccion: Activa" << endl;
    else
        cout << TAB << " Proteccion: No disponible" << endl;
}
int contadorjg(jugador *lista)
{
    jugador *aux = lista;
    int contadorJG = 0;
    while (aux != NULL)
    {
        aux = aux->proxjg;
        contadorJG++;
    }
    return contadorJG;
}
void iniciarjugadores(Casilla **mapa, jugador *lista)
{
    cout << "3" << endl;
    (*mapa)->Jugadores->J1 = true;
    (*mapa)->Jugadores->J2 = true;
    int contadorJG = contadorjg(lista);
    if (contadorJG >= 3)
    {
        (*mapa)->Jugadores->J3 = true;
        if (contadorJG == 4)
        {
            (*mapa)->Jugadores->J4 = true;
        }
    }
}
void moverplayer1(jugador **j, int dado)
{
    int z = 0;
    (*j)->ubicacion->Jugadores->J1 = false;
    while (z != dado)
    {
        (*j)->ubicacion = (*j)->ubicacion->proxCasilla;
        z++;
    }
    (*j)->ubicacion->Jugadores->J1 = true;
}
void moverplayer2(jugador **j, int dado)
{
    int z = 0;
    (*j)->ubicacion->Jugadores->J2 = false;
    while (z != dado)
    {
        (*j)->ubicacion = (*j)->ubicacion->proxCasilla;
        z++;
    }
    (*j)->ubicacion->Jugadores->J2 = true;
}
void moverplayer3(jugador **j, int dado)
{
    int z = 0;
    (*j)->ubicacion->Jugadores->J3 = false;
    while (z != dado)
    {
        (*j)->ubicacion = (*j)->ubicacion->proxCasilla;
        z++;
    }
    (*j)->ubicacion->Jugadores->J3 = true;
}
void moverplayer4(jugador **j, int dado)
{
    int z = 0;
    (*j)->ubicacion->Jugadores->J4 = false;
    while (z != dado)
    {
        (*j)->ubicacion = (*j)->ubicacion->proxCasilla;
        z++;
    }
    (*j)->ubicacion->Jugadores->J4 = true;
}
void juego(jugador **listaPlayer, Casilla **mapa, bool &PartidaActiva, string TAB)
{
    jugador *aux = *listaPlayer;
    int dado;
    cin.get();

    while (PartidaActiva)
    {
        for (int i = 1; i <= contadorjg(*listaPlayer); i++)
        {
            system("cls");
            imprimirTabla(*mapa);
            cout << TAB << " TURNO JUGADOR " << i << endl;

            MostrarEstadisticas(aux, TAB);
            aux = aux->proxjg;
            cout << TAB << "Pulse una tecla para lanzar el dado \n";
            cin.get();
            dado = Dado();
            cout << dado;
            cin.get();
            if(i=1){
                moverplayer1(&aux,dado);
            }
        }

        PartidaActiva = false;
    }
}
int main()
{
    string TAB = "\t\t\t\t\t\t\t\t\t\t";
    bool PartidaActiva = true;
    jugador *ListaJG = NULL;
    Casilla *mapa = NULL;
    int i = 0;
    for (int z = 0; z < 200; z++)
    {
        distDado(rd);
        distCarta(rd);
        distCatastrofe(rd);
        distDesafio(rd);
    }
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
        // cout << tipo << endl;
        insertarUltimoMapa(&mapa, numerocasilla, tipo);
        i++;
        //  cout << i << endl;
    }
    archivo.close();
    // mostrarmapa(mapa);
    // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // SetConsoleTextAttribute(hConsole, 187);
    // cout << " ";
    // SetConsoleTextAttribute(hConsole, 15);
    // cin.get();

    int opcion, opcion2, opcion3, numjg = 0;
    while (opcion != 5)
    {
        system("cls");
        cout << "---------MONOPOLY AMBIENTAL---------" << endl;
        cout << "1) Iniciar Partida" << endl;
        cout << "2) Como jugar" << endl;
        cout << "3) Top Jugadores" << endl;
        cout << "4) Creditos " << endl;
        cout << "5) Salir" << endl;
        cout << "- Introduce una opcion >> ";
        cin >> opcion;



        // cout <<"hola";
        switch (opcion)
        {
        case 1:
            while (opcion2 != 3)
            {
                system("cls");
                cout << "---------MONOPOLY AMBIENTAL---------" << endl;
                cout << "1) Iniciar partida nueva" << endl;
                cout << "2) Cargar Partida" << endl;
                cout << "3) Regresar" << endl;
                cout << "- Introduce una opcion >> ";
                cin >> opcion2;
                switch (opcion2)
                {
                case 1:
                    while (numjg < 2 || numjg > 4)
                    {
                        cout << "Cuantos Jugadores van a jugar (2-4): ";
                        cin >> numjg;
                        if (numjg > 4 || numjg < 2)
                        {
                            cout << "cantidad invalida de jugadores\n";
                        }
                    }
                    for (int l = 1; l != numjg + 1; l++)
                    {
                        string a = to_string(l);
                        insertarUltimoJG(&ListaJG, a);
                    }
                    cout << "Se han cargado los jugadores\n";
                    opcion = 5;
                    opcion2 = 3;

                    break;

                default:
                    break;
                }
            }
            break;

        case 2:
            // ComoJugar();
            break;
        case 3:
            // TopJugadores();
            break;
        case 4:
            // creditos();
            break;
        case 5:
            break;
        default:
            break;
        }
    }
    cout << "1" << endl;
    iniciarjugadores(&mapa, ListaJG);
    system("cls");
    // imprimirTabla(mapa);
    cout << "2" << endl;
    juego(&ListaJG, &mapa, PartidaActiva, TAB);
    mostrarjg(ListaJG);
    cin.get();
    return 0;
}