#include <iostream>
#include <cstdio>
#include <cstring>

struct Componente
{
    int id;
    char tipo[51];
    int codigo;
    char modelo[51];
    char marca[51];
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


struct NodoMarca {
    char nombre[51];
    int cant;          
    NodoMarca* sgte;   
};

NodoMarca* buscarMarca(NodoMarca* lista, const char* nombre) {
    
    while (lista != NULL && strcmp(lista->nombre, nombre) != 0) {
        lista = lista->sgte;
    }
    return lista; 
}

void agregarMarca(NodoMarca*& lista, const char* nombre) {
    
    NodoMarca* nuevo = new NodoMarca();
    strcpy(nuevo->nombre, nombre); 
    nuevo->cant = 1;               
    nuevo->sgte = NULL;            

    if (lista == NULL) {
         
        lista = nuevo;
    } else {

        NodoMarca* aux = lista;
        while (aux->sgte != NULL) {
            aux = aux->sgte;
        }
        aux->sgte = nuevo;
    }
}

void liberarMarcas(NodoMarca*& lista) {
    while (lista != NULL) {
        NodoMarca* aux = lista;   
        lista = lista->sgte;      
        delete aux;               
    }
}

bool fabricanteMasFrecuente(NodoComponente* vectorCategorias[], char resultado[]) {
    NodoMarca* marcas = NULL; 

    
    for (int i = 0; i < 20; i++) {
        NodoComponente* p = vectorCategorias[i]; 
        while (p != NULL) {
            // ¿Ya anotamos esta marca?
            NodoMarca* m = buscarMarca(marcas, p->info.marca);
            if (m != NULL) {
                m->cant++;                              
            } else {
                agregarMarca(marcas, p->info.marca);    
            }
            p = p->sgte; 
        }
    }

    if (marcas == NULL) {
        return false;
    }

    NodoMarca* mejor = marcas;
    for (NodoMarca* q = marcas->sgte; q != NULL; q = q->sgte) {
        if (q->cant > mejor->cant) {
            mejor = q;
        }
    }
    strcpy(resultado, mejor->nombre); // devolvemos el nombre ganador

  
    liberarMarcas(marcas);
    return true;
}

bool promedioConsumoCategoria(NodoComponente* lista, double& promedio) {
    int suma = 0;
    int cantidad = 0;

    while (lista != NULL) {
        suma += lista->info.consumo;
        cantidad++;
        lista = lista->sgte;
    }

    if (cantidad == 0) {
        promedio = 0;
        return false;
    }

    promedio = (double)suma / cantidad;
    return true;
}

bool componenteMayorConsumo(NodoComponente* vectorCategorias[], Componente& resultado) {
    bool hayDatos = false;

    for (int i = 0; i < 20; i++) {
        NodoComponente* p = vectorCategorias[i];
        while (p != NULL) {
            if (!hayDatos || p->info.consumo > resultado.consumo) {
                resultado = p->info;
                hayDatos = true;
            }
            p = p->sgte;
        }
    }

    return hayDatos;
}

bool generarArchivo(const char* nombreArchivo) {
    const int cantidad = 7;

    Componente datos[cantidad] = {
        {30, "Procesador",     0, "CPU-A", "Intel",    65},
        {10, "Procesador",     0, "CPU-B", "AMD",      95},
        {20, "Procesador",     0, "CPU-C", "Intel",   125},
        {40, "Procesador",     0, "CPU-D", "AMD",      65},
        {60, "Placa de video", 1, "GPU-A", "NVIDIA",  200},
        {50, "Placa de video", 1, "GPU-B", "AMD",     200},
        {70, "Disco SSD",      2, "SSD-A", "Kingston", 5}
    };

    std::FILE* archivo = std::fopen(nombreArchivo, "wb");

    if (archivo == NULL) {
        std::cout << "No se pudo crear el archivo." << std::endl;
        return false;
    }

    bool escrituraCorrecta =
        std::fwrite(datos, sizeof(Componente), cantidad, archivo)
        == cantidad;

    int resultadoCierre = std::fclose(archivo);

    if (!escrituraCorrecta || resultadoCierre != 0) {
        std::cout << "No se pudo guardar el archivo." << std::endl;
        return false;
    }

    return true;
}

void liberarVector(NodoComponente* vectorCategorias[]) {
    for (int i = 0; i < 20; i++) {
        liberarLista(vectorCategorias[i]);
    }
}

bool cargarDatos(NodoComponente* vectorCategorias[],
                 const char* nombreArchivo) {
    std::FILE* archivo = std::fopen(nombreArchivo, "rb");

    if (archivo == NULL) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        return false;
    }

    // Borramos la carga anterior para evitar duplicados.
    liberarVector(vectorCategorias);

    Componente c;

    while (std::fread(&c, sizeof(Componente), 1, archivo) == 1) {
        if (c.codigo < 0 || c.codigo >= 20) {
            std::fclose(archivo);
            liberarVector(vectorCategorias);
            std::cout << "Codigo de categoria invalido." << std::endl;
            return false;
        }

        insertarOrdenado(vectorCategorias[c.codigo], c);
    }

    bool lecturaCorrecta = std::feof(archivo) != 0;
    int resultadoCierre = std::fclose(archivo);

    if (!lecturaCorrecta || resultadoCierre != 0) {
        liberarVector(vectorCategorias);
        std::cout << "No se pudo completar la carga." << std::endl;
        return false;
    }


    return true;
}

int main() {
    const int CANT_CATEGORIAS = 20;
    NodoComponente* vectorCategorias[CANT_CATEGORIAS];

    // Todas las listas comienzan vacias.
    for (int i = 0; i < CANT_CATEGORIAS; i++) {
        vectorCategorias[i] = NULL;
    }

    // Creamos el archivo con los datos de prueba.
    if (!generarArchivo("componentes.dat")) {
        return 1;
    }

    int opcion = 0;

    do {
        std::cout << "1) Cargar y procesar datos de componentes"
                  << std::endl;
        std::cout << "2) Mostrar resultados" << std::endl;
        std::cout << "3) Salir del programa" << std::endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                if (cargarDatos(vectorCategorias, "componentes.dat")) {
                    std::cout << "Datos cargados correctamente."
                              << std::endl;
                }
                break;

            case 2:
                // Aqui se conectara la funcion del integrante 3.
                break;

            case 3:
                liberarVector(vectorCategorias);
                break;
        }
    } while (opcion != 3);

    return 0;
}