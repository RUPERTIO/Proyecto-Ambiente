#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct TOP
{
    string nombre;
    int puntuacion;
    TOP *proxtop;
};

void insertarNodoTOP(TOP **top, string nombre, int puntuacion)
{
    TOP *nuevo = new TOP;
    nuevo->nombre = nombre;
    nuevo->puntuacion = puntuacion;
    nuevo->proxtop = NULL;

    if (top == NULL || puntuacion > (*top)->puntuacion)
    {
        nuevo->proxtop = (*top);
        *top = nuevo;
    }
    else
    {
        TOP *aux = *top;
        while (aux->proxtop != NULL && aux->proxtop->puntuacion > puntuacion)
        {
            aux = aux->proxtop;
        }
        nuevo->proxtop = aux->proxtop;
        aux->proxtop = nuevo;
    }
}

void eliminarextratop(TOP **top)
{

    TOP *aux = *top;
    for (int i = 1; i < 10; ++i)
    {

        aux = aux->proxtop;
    }

    TOP *safado = aux->proxtop;
    aux->proxtop = safado->proxtop;
    delete safado;
}

void guardarListaEnArchivo(TOP *top)
{
    ofstream archivo("TOP.txt");
    if (archivo.is_open())
    {
        TOP *aux = top;
        while (aux != NULL)
        {
            archivo << aux->nombre << " " << aux->puntuacion << endl;
            aux = aux->proxtop;
        }
        archivo.close();
    }
    else
    {
        cout << "Error al abrir el archivo para escritura." << endl;
    }
}

void imprimirTOP(TOP *top)
{
    TOP *aux = top;
    while (aux != NULL)
    {
        cout << "Nombre: " << aux->nombre << ", Puntuación: " << aux->puntuacion << endl;
        aux = aux->proxtop;
    }
}
void LiberarMemoriaTOP(TOP **top)
{
    while (top != NULL)
    {
        TOP *temp = *top;
        (*top) = (*top)->proxtop;
        delete temp;
    }
}
void FuncionesTopjg(TOP **top, int puntacionJG)
{

    string nombre;
    cout << "| INGRESE UN APODO: ";
    cin >> nombre;
    insertarNodoTOP(top, nombre, puntacionJG);

    eliminarextratop(top);

    cout << endl
         << "| TU PUNTAJE A SIDO REGISTRADO |" << endl;

    guardarListaEnArchivo(*top);
}
int main()
{
    // COSAS QUE VAN EN EL MAIN
    TOP *top = NULL;
    ifstream archivo("TOP.txt");
    if (archivo.is_open())
    {
        string nombre;
        int puntuacion;
        for (int i = 0; i < 10; ++i)
        {
            archivo >> nombre >> puntuacion;
            insertarNodoTOP(&top, nombre, puntuacion);
        }
        archivo.close();
    }
    FuncionesTopjg(&top, 3000);
    eliminarextratop(&top);
    imprimirTOP(top);
    guardarListaEnArchivo(top);
    return 0;
}