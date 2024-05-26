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

struct Desafio
{
    int nivel;
    int pregNivel;
    string nombre;
    string pregunta1;
    string pregunta2;
    Desafio *siguiente;
};

struct Catastrofe
{
    int nivel = 10;
    string nombre;
    string pregunta1;
    string pregunta2;
    Catastrofe *proxCatastrofe;
};

struct Inteligencia
{
    string pregunta;
    string respuesta1;
    string respuesta2;
    Inteligencia *proxInteligencia;
};

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
    int vuelta;
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

bool listaVaciaDesafios(Desafio *inicio)
{
    return inicio == NULL;
}

bool listaVaciaCatastrofe(Catastrofe *inicio)
{
    return inicio == NULL;
}

bool listaVaciaInteligencia(Inteligencia *inicio)
{
    return inicio == NULL;
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

Desafio *crearDesafio(int nivel, int pregunta, string nombre, string pregunta1, string pregunta2)
{
    Desafio *nuevo = new Desafio;
    nuevo->nivel = nivel;
    nuevo->pregNivel = pregunta;
    nuevo->nombre = nombre;
    nuevo->pregunta1 = pregunta1;
    nuevo->pregunta2 = pregunta2;
    nuevo->siguiente = NULL;
    return nuevo;
}

Catastrofe *crearCatastrofe(string nombre, string pregunta1, string pregunta2)
{
    Catastrofe *nuevo = new Catastrofe;
    nuevo->nombre = nombre;
    nuevo->pregunta1 = pregunta1;
    nuevo->pregunta2 = pregunta2;
    nuevo->proxCatastrofe = NULL;
    return nuevo;
}

Inteligencia *crearInteligencia(string pregunta, string respuesta1, string respuesta2)
{
    Inteligencia *nuevo = new Inteligencia;
    nuevo->pregunta = pregunta;
    nuevo->respuesta1 = respuesta1;
    nuevo->respuesta2 = respuesta2;
    nuevo->proxInteligencia = NULL;
    return nuevo;
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
jugador *crearNodoJG(string numjg, Casilla *mapa)
{
    jugador *nuevo = new jugador;
    nuevo->NumJ = numjg;
    nuevo->inteligencia = 1;
    nuevo->estrellas = 0;
    nuevo->dinero = 5;
    nuevo->vida = 4;
    nuevo->vuelta = 1;
    bool proteccion = false;
    nuevo->ubicacion = mapa;
    nuevo->proxjg = NULL;
    return nuevo;
}

void insertarUltimoDesafio(Desafio **inicio, int nivel, int pregNivel, string nombre, string pregunta1, string pregunta2)
{
    Desafio *nuevo = crearDesafio(nivel, pregNivel, nombre, pregunta1, pregunta2);
    nuevo->nivel = nivel;
    nuevo->pregNivel = pregNivel;
    nuevo->nombre = nombre;
    nuevo->pregunta1 = pregunta1;
    nuevo->pregunta2 = pregunta2;
    nuevo->siguiente = NULL;

    if (listaVaciaDesafios(*inicio))
    {
        *inicio = nuevo;
    }
    else
    {
        Desafio *aux = *inicio;
        while (aux->siguiente != NULL)
        {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }
}

void insertarUltimoCatastrofe(Catastrofe **inicio, string nombre, string pregunta1, string pregunta2)
{
    Catastrofe *nuevo = crearCatastrofe(nombre, pregunta1, pregunta2);

    if (listaVaciaCatastrofe(*inicio))
    {
        *inicio = nuevo;
    }
    else
    {
        Catastrofe *aux = *inicio;
        while (aux->proxCatastrofe != NULL)
        {
            aux = aux->proxCatastrofe;
        }
        aux->proxCatastrofe = nuevo;
    }
}

void insertarUltimoInteligencia(Inteligencia **inicio, string pregunta, string respuesta1, string respuesta2)
{
    Inteligencia *nuevo = crearInteligencia(pregunta, respuesta1, respuesta2);

    if (listaVaciaInteligencia(*inicio))
    {
        *inicio = nuevo;
    }
    else
    {
        Inteligencia *aux = *inicio;
        while (aux->proxInteligencia != NULL)
        {
            aux = aux->proxInteligencia;
        }
        aux->proxInteligencia = nuevo;
    }
}

void insertarUltimoJG(jugador **inicio, string num, Casilla *mapa)
{
    jugador *nuevo = crearNodoJG(num, mapa);

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

void cargarDatos(Desafio **desafios, Catastrofe **catastrofes, Inteligencia **inteligencia, Casilla **mapa)
{
    ifstream archivoEntrada("Listas.txt");

    if (archivoEntrada.is_open())
    {
        string cantidad;

        getline(archivoEntrada, cantidad);

        int i = 0;
        while (i < stoi(cantidad))
        {
            string nivel, pregNivel, nombre, pregunta1,pregunta2;
            getline(archivoEntrada, nivel);
            getline(archivoEntrada, pregNivel);
            getline(archivoEntrada, nombre);
            getline(archivoEntrada, pregunta1);
            getline(archivoEntrada, pregunta2);

            int numNivel = stoi(nivel);
            int numPregNivel = stoi(pregNivel);

            insertarUltimoDesafio(*&desafios, numNivel, numPregNivel, nombre, pregunta1, pregunta2);
            i++;
        }

        i = 0;
        getline(archivoEntrada, cantidad);
        while (i < stoi(cantidad))
        {
            string nombre, pregunta1, pregunta2;
            getline(archivoEntrada, nombre);
            getline(archivoEntrada, pregunta1);
            getline(archivoEntrada, pregunta2);

            insertarUltimoCatastrofe(*&catastrofes, nombre, pregunta1, pregunta2);
            i++;
        }

        i = 0;
        getline(archivoEntrada, cantidad);
        while (i < stoi(cantidad))
        {
            string pregunta, respuesta1, respuesta2;
            getline(archivoEntrada, pregunta);
            getline(archivoEntrada, respuesta1);
            getline(archivoEntrada, respuesta2);

            insertarUltimoInteligencia(*&inteligencia, pregunta, respuesta1, respuesta2);
            i++;
        }

        i = 0;
        getline(archivoEntrada, cantidad);
        while (i < stoi(cantidad))
        {
            string numCasilla, TipoCasilla;
            getline(archivoEntrada, numCasilla);
            getline(archivoEntrada, TipoCasilla);

            insertarUltimoMapa(*&mapa, numCasilla, TipoCasilla);
            i++;
        }
        archivoEntrada.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo Listas.txt" << endl;
    }
}


//Funcion para mover el cursor a una posicion especifica
void gotoxy(int x, int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

//Funcion para imprimir al jugador si se encuentra en esa casilla
void imprimirJugador(BoolsCasilla *listJugadores, int i, int j)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (listJugadores->J1)
    {
        gotoxy(i + 1, j + 1);
        SetConsoleTextAttribute(hConsole, 160);
        cout << "1";
    }
    if (listJugadores->J2)
    {
        gotoxy(i + 2, j + 1);
        SetConsoleTextAttribute(hConsole, 160);
        cout << "2";
    }
    if (listJugadores->J3)
    {
        gotoxy(i + 3, j + 1);
        SetConsoleTextAttribute(hConsole, 160);
        cout << "3";
    }
    if (listJugadores->J4)
    {
        gotoxy(i + 4, j + 1);
        SetConsoleTextAttribute(hConsole, 160);
        cout << "4";
    }
}

//Funcion para determinar el color de la casilla segun el tipo de casilla
void determinarColor(string tipoCasilla, int i, int j, BoolsCasilla *jugadores, bool catastrofeActivo)
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
        if (catastrofeActivo){
            SetConsoleTextAttribute(hConsole, 204);
        } else {
            SetConsoleTextAttribute(hConsole, 119);
        }
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
    imprimirJugador(jugadores, i, j);
}

//Funcion para imprimir el tablero del juego, solo funciona para
void imprimirTabla(Casilla *mapa, bool catastrofeActivo)
{

    int valor = 36;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //Se divide el valor del total de las casillas entre 4
    //Para saber cuantas veces tiene que recorrer el mapa por cada lado
    float posiciones = valor / 4;


    int i = 1, j = 1;
    gotoxy(i * 6, j * 3);
    determinarColor(mapa->TipoCasilla, i * 6, j * 3, mapa->Jugadores, catastrofeActivo);
    while (i <= posiciones)
    {
        i++;
        gotoxy(i * 3, j * 2);
        mapa = mapa->proxCasilla;
        determinarColor(mapa->TipoCasilla, i * 6, j * 3, mapa->Jugadores, catastrofeActivo);
    }

    while (j <= posiciones)
    {
        j++;
        gotoxy(i * 3, j * 2);
        mapa = mapa->proxCasilla;
        determinarColor(mapa->TipoCasilla, i * 6, j * 3, mapa->Jugadores, catastrofeActivo);
    }

    while (i > 1)
    {
        i--;
        gotoxy(i * 3, j * 2);
        mapa = mapa->proxCasilla;
        determinarColor(mapa->TipoCasilla, i * 6, j * 3, mapa->Jugadores, catastrofeActivo);
    }

    while (j > 2)
    {
        j--;
        gotoxy(i * 3, j * 2);
        mapa = mapa->proxCasilla;
        determinarColor(mapa->TipoCasilla, i * 6, j * 3, mapa->Jugadores, catastrofeActivo);
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
void moverplayer1(jugador *j, int dado, int *vueltaJuego)
{
    int z = 0;
    j->ubicacion->Jugadores->J1 = false;
    while (z != dado)
    {
        j->ubicacion = j->ubicacion->proxCasilla;
        if (j->ubicacion->TipoCasilla == "Inicio")
        {
            cin.get();
            j->vuelta++;
            if (j->vuelta > *vueltaJuego)
            {
                *vueltaJuego = *vueltaJuego + 1;
            }
        }
        z++;
    }
    j->ubicacion->Jugadores->J1 = true;
}
void moverplayer2(jugador **j, int dado, int *vueltaJuego)
{
    int z = 0;
    (*j)->ubicacion->Jugadores->J2 = false;
    while (z != dado)
    {
        (*j)->ubicacion = (*j)->ubicacion->proxCasilla;
        if ((*j)->ubicacion->TipoCasilla == "Inicio")
        {
            cin.get();
            (*j)->vuelta++;
            if ((*j)->vuelta > *vueltaJuego)
            {
                *vueltaJuego = *vueltaJuego + 1;
            }
        }
        z++;
    }
    (*j)->ubicacion->Jugadores->J2 = true;
}
void moverplayer3(jugador **j, int dado, int *vueltaJuego)
{
    int z = 0;
    (*j)->ubicacion->Jugadores->J3 = false;
    while (z != dado)
    {
        (*j)->ubicacion = (*j)->ubicacion->proxCasilla;
        if ((*j)->ubicacion->TipoCasilla == "Inicio")
        {
            cin.get();
            (*j)->vuelta++;
            if ((*j)->vuelta > *vueltaJuego)
            {
                *vueltaJuego = *vueltaJuego + 1;
            }
        }
        z++;
    }
    (*j)->ubicacion->Jugadores->J3 = true;
}
void moverplayer4(jugador **j, int dado, int *vueltaJuego)
{
    int z = 0;
    (*j)->ubicacion->Jugadores->J4 = false;
    while (z != dado)
    {
        (*j)->ubicacion = (*j)->ubicacion->proxCasilla;
        if ((*j)->ubicacion->TipoCasilla == "Inicio")
        {
            cin.get();
            (*j)->vuelta++;
            if ((*j)->vuelta > *vueltaJuego)
            {
                *vueltaJuego = *vueltaJuego + 1;
            }
        }
        z++;
    }
    (*j)->ubicacion->Jugadores->J4 = true;
}

void juego(jugador **listaPlayer, Casilla **mapa, bool &PartidaActiva, string TAB)
{
    int moneda;
    int cas;
    int des;
    int preg;
    int prob;
    jugador *aux = *listaPlayer;
    bool catastrofeActivo = false;
    int vueltaJuego = 1;
    int dado;
    cin.get();

    while (vueltaJuego < 4)
    {
        aux = *listaPlayer;
        int i = 1;
        while ( vueltaJuego < 4 && i <= contadorjg(*listaPlayer))
        {
            system("cls");
            imprimirTabla(*mapa, catastrofeActivo);
            cout << TAB << " TURNO JUGADOR " << i << endl;

            MostrarEstadisticas(aux, TAB);

            cout << TAB << "Pulse una tecla para lanzar el dado \n";
            cin.get();
            dado = Dado();
            cout << TAB << "Te ha salido un: " << dado;
            cin.get();
            if (i == 1)
            {

                moverplayer1(aux, dado, &vueltaJuego);
            }
            if (i == 2)
            {
                moverplayer2(&aux, dado, &vueltaJuego);
            }
            if (i == 3)
            {
                moverplayer3(&aux, dado, &vueltaJuego);
            }
            if (i == 4)
            {
                moverplayer4(&aux, dado, &vueltaJuego);
            }
            cin.get();
            if (aux->ubicacion->TipoCasilla == "dinero")
            {
                prob = carta();
                if (prob == 1)
                {
                    moneda = 1;
                    aux->dinero = aux->dinero + moneda;
                }
                if (prob == 2)
                {
                    moneda = 5;
                    aux->dinero = aux->dinero + moneda;
                }
                if (prob == 1)
                {
                    moneda = 10;
                    aux->dinero = aux->dinero + moneda;
                }
                cout << TAB << "| HAS OBTENIDO " << moneda << " MONEDAS | \n";
            }
            if (aux->ubicacion->TipoCasilla == "vacio")
            {
                cout << TAB << "| HAS CAIDO EN UNA CASILLA DE DESCANSO | \n";
            }
            // if (aux->ubicacion->TipoCasilla == "estudio")
            // {
            //     preg = desafio(); // reutilizo desafio porque su parametro seria el mismo de estudio (1,10)
            //     // buscar nodo
            //     //  pregunta
            //     // respuesaA
            //     // respuestaB
            //     //  cin>>respuesta
            //     switch (respuesta)
            //     {
            //     case /* constant-expression */:
            //         aux->inteligencia = aux->inteligencia + 1;
            //         cout << TAB << "| RESPUESTA CORRECTA, TU INTELIGENCIA A AUMENTADO A " << aux->inteligencia << " | \n";
            //         break;
            //     case:
            //         cout << TAB << "| RESPUESTA INCORRECTA NO AUMENTASTE TU INTELIGENCIA | \n";
            //     default:
            //         break;
            //     }
            // }
            if (aux->ubicacion->TipoCasilla == "desafio")
            {
                des = desafio();
                // buscar nodo
                cout << TAB << "| DESAFIO DE NIVEL " << des << " |\n";
            }
            // if (aux->ubicacion->TipoCasilla == "catastrofe")
            // {
            //     cout << TAB << "|!!!!! ALERTA HA INICIADO UNA CATASTROFE !!!!!|\n";
            //     cas = catastrofe();
            //     // busca nodo
            //     // condiciones
            //     if (vencido)
            //     {
            //         aux->estrellas = aux->estrellas + 1;
            //         aux->ubicacion->TipoCasilla = "vacio";
            //     }
            //     else
            //     {
            //         cout << TAB << "| HAS FALLADO EN SOBREVIVIR A LA CATASTROFE |\n";
            //         cout << TAB << "| HAS MUERTO EN ACCION, HAS SIDO ELIMINADO DE LA PARTIDA |\n";
            //         aux->vida = 0
            //     }
            // }

            if (vueltaJuego > 1 && !catastrofeActivo){
                catastrofeActivo = true;
            }
            cin.get();

            i++;
            aux = aux->proxjg;
        }
        aux = *listaPlayer;
    }
}

void PuntajeFinal(jugador *lista)
{

    int a = 0, b = 0, c = 0, d = 0;

    jugador *aux = lista;

    a = aux->estrellas * 1000;
    a = (aux->inteligencia * 100) + a;
    a = aux->dinero + a;
    aux = aux->proxjg;
    b = aux->estrellas * 1000;
    b = (aux->inteligencia * 100) + b;
    b = aux->dinero + b;
    if (contadorjg(lista) > 2)
    {
        aux = aux->proxjg;
        c = aux->estrellas * 1000;
        c = (aux->inteligencia * 100) + c;
        c = aux->dinero + c;
    }
    if (contadorjg(lista) == 4)
        aux = aux->proxjg;
    d = aux->estrellas * 1000;
    d = (aux->inteligencia * 100) + d;
    d = aux->dinero + d;
    //
    if ((a > b) && (a > c) && (a > d))
    {
        cout << "JUGADOR 1 GANADOR\n";
        // AgregarTop(a);
    }
    if ((b > a) && (b > c) && (b > d))
    {
        cout << "JUGADOR 2 GANADOR\n";
        // AgregarTop(b);
    }
    if ((c > b) && (c > a) && (c > d))
    {
        cout << "Jugador 2 GANADOR\n";
        // AgregarTop(c);
    }
    if ((d > b) && (d > c) && (a < d))
    {
        cout << "Jugador 4 GANADOR\n";
        // AgregarTop(d);
    }
}
int main()
{
    string TAB = "\t\t\t\t\t\t\t\t\t\t";
    bool PartidaActiva = true;
    jugador *ListaJG = NULL;
    Desafio *desafio = NULL;
    Catastrofe *catastrofes = NULL;
    Inteligencia *inteligencia = NULL;
    Casilla *mapa = NULL;
    for (int z = 0; z < 200; z++)
    {
        distDado(rd);
        distCarta(rd);
        distCatastrofe(rd);
        distDesafio(rd);
    }

    cargarDatos(&desafio, &catastrofes, &inteligencia, &mapa);

    // int i = 0;
    // string numerocasilla;
    // string tipo, auxiliarstr;
    // ifstream archivo("mapa.txt");
    // while (i != 36)
    // {
    //     getline(archivo, auxiliarstr);
    //     numerocasilla = auxiliarstr;
    //     // cout << numerocasilla << endl;
    //     getline(archivo, auxiliarstr);
    //     tipo = auxiliarstr;
    //     // cout << tipo << endl;
    //     insertarUltimoMapa(&mapa, numerocasilla, tipo);
    //     i++;
    //     //  cout << i << endl;
    // }
    // archivo.close();

    Casilla *aux = mapa;
    while (aux->proxCasilla != NULL)
    {
        cout << aux->TipoCasilla << "->";
        aux = aux->proxCasilla;
    }
    aux->proxCasilla = mapa;
    cin.get();

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
                        insertarUltimoJG(&ListaJG, a, mapa);
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
    cin.get();
    return 0;
}