#include <iostream>
#include <cstdio>
#include <cstring>

struct Componente
{
    int id;
    char tipo[50];
    int codigo;
    char modelo[50];
    char marca[50];
    int consumo;
};
struct Nodo
{
    Componente info; //estructura del componente
    Nodo* sgte; //apuntador al siguiente nodo
};



int main(){
    int opcion = 0;
    do {
        std::cout<<"1) Cargar y procesar datos de componentes"<<std::endl;
        std::cout<<"2) Mostrar resultados"<<std::endl;
        std::cout<<"3) Salir del programa"<<std::endl;
        std::cout<<"Ingrese una opcion: ";
        std::cin>>opcion;
        switch (opcion)
        {
            case 1:
            //funcion de cargar y procesar datos
            break;
            case 2:
            //funcion de mostrar resultados
            break;
            case 3:
            //funcion de salida
            break;
        };
    }
    while (opcion != 3);
    return 0;
}