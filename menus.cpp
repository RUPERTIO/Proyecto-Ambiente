#include <iostream>
using namespace std;

int main()
{
    int opcion, opcion2, opcion3, numjg=0;
    while (opcion != 5)
    {
        cout << "MONOPOLY AMBIENTAL" << endl;
        cout << "1) Iniciar Partida" << endl;
        cout << "2)Como jugar" << endl;
        cout << "3) Top Jugadores" << endl;
        cout << "4)Creditos" << endl;
        cout << "5)Salir" << endl;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            while (opcion2 != 3)
            {
                cout << "MONOPOLY AMBIENTAL" << endl;
                cout << "1) Iniciar partida nueva" << endl;
                cout << "2) Cargar Partida" << endl;
                cout << "3) Regresar" << endl;
                cin >> opcion2;
                switch (opcion2)
                {
                case 1: 
                while (numjg<2 || numjg>4){
                    cout<<"Cuantos Jugadores van a jugar (2-4): ";
                    cin>>numjg;
                    if (numjg>4 || numjg<2){
                        cout<<"cantidad invalida de jugadores\n";
                    }

                    cout<<"Se han cargado los jugadores\n"
                }
                    break;
                
                default:
                    break;
                }
            }
            break;

        case 2:
            //ComoJugar();
            break;
        case 3:
            //TopJugadores();
            break;
        case 4:
            //creditos();
            break;
        case 5:
            break;
        default:
            break;
        }
    }
}

/*struct BaseDatos{
    string tipo;
    carta *proxcarta;
    desafio *proxdesafio;
    Catastrofe *proxcatastrofe;
    dinero *proxdinero;
    BaseDatos *proxDatos;
}*/