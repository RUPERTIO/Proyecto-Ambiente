#include <iostream>
#include <random>
using namespace std;
random_device rd;
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
