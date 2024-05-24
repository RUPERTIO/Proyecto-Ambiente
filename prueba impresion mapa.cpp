#include <iostream>
#include <string>

struct Nodo
{
    int valor;
    std::string nombre;
    std::string color;
    Nodo *siguiente;
};

Nodo *inicializarLista()
{
    Nodo *cabeza = new Nodo;
    cabeza->valor = 1;
    cabeza->nombre = "Nodo 1";
    cabeza->color = "\033[1;31m"; // Rojo
    Nodo *actual = cabeza;

    for (int i = 2; i <= 36; ++i)
    {
        Nodo *nuevoNodo = new Nodo;
        nuevoNodo->valor = i;
        nuevoNodo->nombre = "Nodo " + std::to_string(i);
        nuevoNodo->color = "\033[1;32m"; // Verde
        nuevoNodo->siguiente = nullptr;

        actual->siguiente = nuevoNodo;
        actual = nuevoNodo;
    }

    return cabeza;
}

void imprimirTablero(Nodo *cabeza)
{
    Nodo *actual = cabeza;
    Nodo *temp = nullptr;
    int contador = 0;

    // Imprimir la primera fila
    for (int j = 0; j < 10; ++j)
    {
        std::cout << "| " << actual->nombre << " | ";
        actual = actual->siguiente;
    }
    std::cout << std::endl;

    // Imprimir las filas intermedias
    for (int i = 1; i < 9; ++i)
    {
        temp = actual;
        for (int j = 0; j < 8; ++j)
        {
            temp = temp->siguiente;
        }
        std::cout << "| " << temp->nombre << " | ";
        for (int j = 0; j < 8; ++j)
        {
            std::cout << "|   | ";
        }
        std::cout << "| " << actual->nombre << " | " << std::endl;
        actual = actual->siguiente;
    }

    // Imprimir la última fila
    for (int j = 0; j < 10; ++j)
    {
        std::cout << "| " << actual->nombre << " | ";
        actual = actual->siguiente;
    }
    std::cout << std::endl;
}

int main()
{
    Nodo *cabeza = inicializarLista();

    imprimirTablero(cabeza);

    return 0;
}
