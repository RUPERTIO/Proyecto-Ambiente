#include <iostream>
#include <windows.h> 
#include <fstream>
#include <conio.h>
#include<cstdlib>
#include <stdio.h>
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

void gotoxy(int x, int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void determinarColor(string tipoCasilla, int i, int j){

  int tamX = 6, tamY = 3;

  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  if (tipoCasilla == "Inicio"){
    SetConsoleTextAttribute(hConsole, 136);
  } else if (tipoCasilla == "dinero"){
    SetConsoleTextAttribute(hConsole, 238);

  }else if (tipoCasilla == "estudio"){
    SetConsoleTextAttribute(hConsole, 187);

  }else if (tipoCasilla == "desafio"){
    SetConsoleTextAttribute(hConsole, 153);

  }else if (tipoCasilla == "carta"){
    SetConsoleTextAttribute(hConsole, 221);

  }else if (tipoCasilla == "catastrofe"){
    SetConsoleTextAttribute(hConsole, 204);
  }else if (tipoCasilla == "vacio"){
    SetConsoleTextAttribute(hConsole, 255);
  }

  int m = j, n = i;

  while (m < j+tamY){
    while(n < i+tamX){
      gotoxy(n, m);
      cout << " ";
      n++;
    }
    n = i;
    m++;
  }

}

void imprimirTabla(Casilla *mapa){
  int valor = 36;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


  float posiciones = valor / 4;
  int i = 1, j = 1;
  gotoxy(i*6, j*3);
  determinarColor(mapa->TipoCasilla,i*6, j*3);
  // cout << " ";

  while (i<=posiciones){
    i++;
    gotoxy(i*3, j*2);
    mapa = mapa->proxCasilla;
    determinarColor(mapa->TipoCasilla,i*6, j*3);
    // cout << " ";
  }
  
  while (j<=posiciones){
    j++;
    gotoxy(i*3, j*2);
    mapa = mapa->proxCasilla;
    determinarColor(mapa->TipoCasilla,i*6, j*3);
    // cout << " ";
  }

  while (i>1){
    i--;
    gotoxy(i*3, j*2);
    mapa = mapa->proxCasilla;
    determinarColor(mapa->TipoCasilla,i*6, j*3);
    // cout << " ";
  }

  while (j>2){
    j--;
    gotoxy(i*3, j*2);
    mapa = mapa->proxCasilla;
    determinarColor(mapa->TipoCasilla,i*6, j*3);
    // cout << " ";
  }
  SetConsoleTextAttribute(hConsole, 7);
}

main(){
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
    cin.get();
    imprimirTabla(mapa);
    cin.get();
}