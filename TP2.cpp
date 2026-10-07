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
struct NodoComponente
{
    Componente info; //estructura del componente
    NodoComponente* sgte; //apuntador al siguiente NodoComponente
};

void insertarOrdenado(NodoComponente*& lista, Componente c){
    //crear el vector de direcciones
    NodoComponente* nuevo = new NodoComponente(); // creacion de un nuevo NodoComponente
    nuevo->info = c; //adquiere el valor del parametro en info
    nuevo->sgte = NULL; // pasa al siguiente NodoComponente que sera NULL
     NodoComponente* anterior = NULL; //declaro un NodoComponente NULL
     NodoComponente* aux = lista;
     while(aux!= NULL && aux ->info.id < c.id){
         anterior = aux;
         aux = aux -> sgte;
     }
     if(anterior== NULL){
         lista=nuevo;
     }else{
         anterior ->sgte = nuevo;
     }
     nuevo ->sgte = aux;
}
void mostrarLista(NodoComponente* lista){
    while (lista != NULL){
        std::cout << lista->info.id << " ";
        lista = lista->sgte;
    }
    std::cout << std::endl;
}

void liberarLista(NodoComponente*& lista){
    NodoComponente* aux;
    while(lista!=NULL){
        aux = lista;
        lista = lista -> sgte;
        delete aux;
    }
}

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
            //funcion de cargar/leer datos
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