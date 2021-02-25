#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

struct carreta
{
    int id;
    carreta *siguiente;
};

struct cliente
{
    int id;
    carreta *carrito;
    cliente *siguiente;
    cliente *anterior;
};

struct caja
{
    int id;
    caja *anterior;
    caja *siguiente;
    cliente *client;
    int turnos;
};

struct ID
{
    int id;
    ID *siguinte;
};

//ACCIONES SOBRE CARRETAS
void agregarCarreta(carreta *&pila, int id);
void mostrarCarretas();
carreta *tomarCarreta();
void llenarPilasCarretas();
//ACCIONES SOBRE CLIENTES
//cola de espera
void agregarColaEspera(cliente *&agregar);
cliente *salirColaEspera();
void imprimirColaEspera();
//cola de cobro
void agregarColaCobro(cliente *&agregar);
cliente *salirColaCobro();
void imprimirColaCobro();
//lista de compras
void agregarCompras(cliente *nuevo);
cliente *salirDeCompras(int id);
void imprimirCompras();
//lista de cajas
void agregarCaja(int id);
void imprimirCajas();
void vaciarCajas();
void llenarCajas();
//ACCIONES CON IDS

void generarIds();
int tomarId();
void ingresarID(int _id);
void imprimirIds();

//obtener numero aleatorio
int getNumeroAleatorio(int inf, int sup);

void inicializarSimulacion();
void acciones();

//PARAMETROS PARA GRAPHVIZ
void ejecutarGraphviz();
void escribirDot(string code);

carreta *pilaCarreta1 = NULL, *pilaCarreta2 = NULL;
cliente *colaEspera = NULL, *colaEsperaFin = NULL, *colaCobro = NULL, *colaCobroFin = NULL, *compras = NULL;
caja *cajas = NULL;

ID *ids = NULL, *idsFin = NULL;

string reader = "";

int numeroCarretas = 0, numeroCajas = 0, ingreso = -1, pasos = 1;

///VARIABLES PARA GRAPHVIZ
//variables de lista de compras
string Nsc = "", NscR = "";
//variables de lista de cajas
string ParamCajas = "", ParamCajasR = "";
//variables cola cobros
string ParamColaCobro = "", ParamColaCobroR = "";
//variables cola espera entrada
string ParamColaEspera = "", ParamColaEsperaR = "";
//variables para pila de carreta
string ParamPila1 = "", ParamPila1R = "", ParamPila2 = "", ParamPila2R = "";

int main()
{
    //INICIALIZACION DE LOS NUMEROS ALEATORIOS
    srand(time(NULL));
    generarIds();

    inicializarSimulacion();

    string option;
    short int bandera = 1;
    short int bandera2 = 1;

    while (bandera == 1)
    {

        acciones();
        do
        {
            printf("Desea continuar la simulacion? y/n: ");
            try
            {
                cin >> reader;
                if (reader == "y")
                {
                    bandera2 = 0;
                }
                else if (reader == "Y")
                {

                    bandera2 = 0;
                }
                else if (reader == "n")
                {
                    bandera2 = 0;
                    bandera = 0;
                }
                else if (reader == "N")
                {
                    bandera2 = 0;
                    bandera = 0;
                }
                else
                {
                    bandera2 = 1;
                    printf("Error de opcion escriba la correcta\n");
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error de opcion escriba la correcta" << '\n';
            }

        } while (bandera2 == 1);
    }

    return 0;
}
void acciones()
{
    printf("\n********************* PASO NUMERO %d *********************\n", pasos);
    vaciarCajas();
    llenarCajas();

    int ale = getNumeroAleatorio(0, 100);
    printf("Numero aleatorio generado: %d\n", ale);
    if (compras != NULL)
    {
        cliente *tmp = salirDeCompras(ale);
        if (tmp != NULL)
        {
            agregarColaCobro(tmp);
        }
    }

    while (colaEspera != NULL && (pilaCarreta1 != NULL || pilaCarreta2 != NULL))
    {
        carreta *tmpCarreta = tomarCarreta();
        if (tmpCarreta != NULL)
        {
            cliente *tmpCliente = salirColaEspera();
            if (tmpCliente != NULL)
            {
                tmpCliente->carrito = tmpCarreta;
                agregarCompras(tmpCliente);
                printf("El cliente %d toma la carreta %d y realizara sus compras\n", tmpCliente->id, tmpCliente->carrito->id);
            }
        }
    }

    for (int i = 0; i < ingreso; i++)
    {
        int tmp = tomarId();
        if (tmp != -1)
        {
            cliente *tmpCliente = new cliente();
            tmpCliente->id = tmp;
            printf("Llega el cliente %d y se agrega a la cola de espera.\n", tmpCliente->id);
            agregarColaEspera(tmpCliente);
        }
    }

    ingreso = -1;
    while (ingreso < 0)
    {
        printf("Cuantas personas ingresaran en el turno: ");
        cin >> reader;
        try
        {
            ingreso = std::stoi(reader);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Cantidad de ingreso invalida!!" << '\n';
        }
    }

    //
    printf("-------------- MOVIMIENTO DE LOS DATOS ------------\n");
    printf("-- CAJAS --\n");
    imprimirCajas();
    printf("-- COBROS --\n");
    imprimirColaCobro();
    printf("-- ESPERA --\n");
    imprimirColaEspera();
    printf("-- COMPRAS --\n");
    imprimirCompras();
    printf("-- CARRETAS --\n");
    mostrarCarretas();
    printf("-------------- FIN MOVIMIENTO DE LOS DATOS ------------\n");
    //
    ejecutarGraphviz();
    pasos++;
}
void inicializarSimulacion()
{
    printf("Bienvenido a la simulacion de SuperMercado\n");
    //////////ASIGNACION DE DATOS DEL FUNCIONAMIENTO DEL PROGRAMA
    while (numeroCarretas == 0)
    {
        printf("Ingrese el numero de Carretas: ");
        cin >> reader;
        try
        {
            numeroCarretas = std::stoi(reader);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Cantidad de ingreso invalida!!" << '\n';
        }
    }

    while (numeroCajas == 0)
    {
        printf("Ingrese el numero de Cajas: ");
        cin >> reader;
        try
        {
            numeroCajas = std::stoi(reader);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Cantidad de ingreso invalida" << '\n';
        }
    }
    ingreso = -1;
    while (ingreso < 0)
    {
        printf("Cuantas personas ingresaran en el turno: ");
        cin >> reader;
        try
        {
            ingreso = std::stoi(reader);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Cantidad de ingreso invalida!!" << '\n';
        }
    }
    printf("EL SISTEMA DE INICIALIZO CON LOS SIGUINTES PARAMETROS\n");
    printf("Numero de carretas: %d\nNumero de cajas: %d\n\n", numeroCarretas, numeroCajas);
    llenarPilasCarretas();

    for (int i = 1; i <= numeroCajas; i++)
    {
        agregarCaja(i);
    }
}

void agregarCarreta(carreta *&pila, int id)
{
    carreta *nueva_carreta = new carreta();
    nueva_carreta->id = id;
    nueva_carreta->siguiente = pila;
    pila = nueva_carreta;
}
void mostrarCarretas()
{
    ParamPila1 = "";
    ParamPila1R = "";
    ParamPila2 = "";
    ParamPila2R = "";

    ParamPila1 = "TPIL [shape = ellipse,style=bold,color=red,label = \"PILA 1\\nCarretas\"];\n";
    carreta *aux = pilaCarreta1;
    if (aux != NULL)
    {
        reader = "";
        do
        {
            printf("Carreta id: %d en pila 1, Atras: %d\n", aux->id, (aux->siguiente == NULL) ? -1 : aux->siguiente->id);
            reader = reader + std::to_string(aux->id);
            if(aux->siguiente!=NULL){
                reader = reader + "|";
            }

            aux = aux->siguiente;
        } while (aux != NULL);

        ParamPila1R = "PILA1 [label=\"{" + reader + "}\"];\n";
    }
    else
    {
        ParamPila1 = "TPIL [shape = ellipse,style=bold,color=red,label = \"PILA 1\\nCarretas\"];\n";
        ParamPila1R = "PILA1 [label=\"{|||}\"];\n";
    }
    ParamPila2 = "TPIL2 [shape = ellipse,style=bold,color=red,label = \"PILA 2\\nCarretas\"];\n";
    carreta *aux2 = pilaCarreta2;
    if (aux2 != NULL)
    {
        reader="";
        do
        {
            printf("Carreta id: %d en pila 2, Atras: %d\n", aux2->id, (aux2->siguiente == NULL) ? -1 : aux2->siguiente->id);

            reader = reader + std::to_string(aux2->id);
            if(aux2->siguiente!=NULL){
                reader = reader + "|";
            }

            aux2 = aux2->siguiente;
        } while (aux2 != NULL);
        ParamPila2R = "PILA2 [label=\"{"+reader+"}\"];\n";
    }else{
        ParamPila2 = "TPIL2 [shape = ellipse,style=bold,color=red,label = \"PILA 2\\nCarretas\"];\n";
        ParamPila2R = "PILA2 [label=\"{||||}\"];\n";
    }
}
carreta *tomarCarreta()
{

    int opcion = getNumeroAleatorio(1, 2);
    carreta *aux;

    if (pilaCarreta1 != NULL)
    {
        aux = pilaCarreta1;
        pilaCarreta1 = aux->siguiente;

        return aux;
    }
    else if (pilaCarreta2 != NULL)
    {

        aux = pilaCarreta2;
        pilaCarreta2 = aux->siguiente;
        aux->siguiente = NULL;
        return aux;
    }
    else
    {
        return NULL;
    }
}
void llenarPilasCarretas()
{
    int tmp = numeroCarretas / 2;

    for (int i = 1; i <= tmp; i++)
    {
        agregarCarreta(pilaCarreta1, i);
    }
    for (int i = (tmp + 1); i <= numeroCarretas; i++)
    {
        agregarCarreta(pilaCarreta2, i);
    }
}

int getNumeroAleatorio(int inf, int sup)
{
    return (inf + rand() % (sup - inf));
}

void agregarColaEspera(cliente *&agregar)
{
    agregar->siguiente = NULL;
    if (colaEspera == NULL)
    {
        colaEspera = agregar;
    }
    else
    {
        colaEsperaFin->siguiente = agregar;
    }
    colaEsperaFin = agregar;
}
cliente *salirColaEspera()
{
    cliente *aux = colaEspera;
    if (colaEspera == colaEsperaFin)
    {
        colaEspera = NULL;
        colaEsperaFin = NULL;
    }
    else
    {
        colaEspera = colaEspera->siguiente;
    }
    if (aux != NULL)
    {
        aux->siguiente = NULL;
    }
    return aux;
}

void imprimirColaEspera()
{
    ParamColaEspera = "";
    ParamColaEsperaR = "";

    cliente *aux;
    aux = colaEspera;
    if (aux != NULL)
    {
        do
        {
            printf("Cliente id: %d, esperando en entrada, atras: %d\n", aux->id, (aux->siguiente == NULL) ? -1 : aux->siguiente->id);
            reader = "";
            reader = "COLE" + std::to_string(aux->id) + "[shape = box,label=\"Cliente " + std::to_string(aux->id) + "\"];" + "\n";
            ParamColaEspera = ParamColaEspera + reader;
            reader = "";
            if (aux->siguiente != NULL)
            {
                reader = "COLE" + std::to_string(aux->id) + " -> COLE" + std::to_string(aux->siguiente->id) + ";" + "\n";
            }
            ParamColaEsperaR = ParamColaEsperaR + reader;
            aux = aux->siguiente;
        } while (aux != NULL);
    }
    else
    {
        printf("Cola de espera vacia\n");
        ParamColaEspera = "TCE2 [shape = box,label = \"COLA DE ESPERA VACIA\"];\n";
    }
}

void agregarColaCobro(cliente *&agregar)
{
    agregar->siguiente = NULL;
    printf("El cliente id: %d, salio de las compras ahora esta en cola de cobros\n", agregar->id);
    if (colaCobro == NULL)
    {
        colaCobro = agregar;
    }
    else
    {
        colaCobroFin->siguiente = agregar;
    }
    colaCobroFin = agregar;
}
cliente *salirColaCobro()
{
    cliente *aux = colaCobro;
    if (colaCobro == colaCobroFin)
    {
        colaCobro = NULL;
        colaCobroFin = NULL;
    }
    else
    {
        colaCobro = colaCobro->siguiente;
    }
    if (aux != NULL)
    {
        aux->siguiente = NULL;
    }
    return aux;
}
void imprimirColaCobro()
{
    ParamColaCobro = "";
    ParamColaCobroR = "";
    cliente *aux;
    aux = colaCobro;
    if (aux != NULL)
    {
        do
        {
            printf("Cliente id: %d, con carreta: %d, esperando a ser atendido, atras: %d\n", aux->id, aux->carrito->id, (aux->siguiente == NULL) ? -1 : aux->siguiente->id);
            reader = "";
            reader = "COLC" + std::to_string(aux->id) + "[shape = box,label=\"Cliente " + std::to_string(aux->id) + "\"];" + "\n";
            ParamColaCobro = ParamColaCobro + reader;
            reader = "";
            if (aux->siguiente != NULL)
            {
                reader = "COLC" + std::to_string(aux->id) + " -> COLC" + std::to_string(aux->siguiente->id) + ";" + "\n";
            }
            ParamColaCobroR = ParamColaCobroR + reader;
            aux = aux->siguiente;
        } while (aux != NULL);
    }
    else
    {
        printf("Cola de cobro vacia\n");
        ParamColaCobro = "TC2 [shape = box,label = \"COLA PARA PAGAR VACIA\"];\n";
    }
}

void agregarCompras(cliente *nuevo)
{

    if (compras == NULL)
    {
        compras = nuevo;
        nuevo->siguiente = compras;
    }
    else
    {
        cliente *antCompras = compras;
        while (antCompras->siguiente != compras)
        {
            antCompras = antCompras->siguiente;
        }
        nuevo->siguiente = compras;
        antCompras->siguiente = nuevo;
    }
}
cliente *salirDeCompras(int id)
{
    cliente *anteriorSalir;
    bool encontrado = false;
    if (compras == NULL)
    {
        printf("Lista de compras vacia\n");
        return NULL;
    }
    else
    {
        anteriorSalir = compras;
        do
        {
            if (anteriorSalir->siguiente->id == id)
            {
                encontrado = true;
                break;
            }
            else
            {
                anteriorSalir = anteriorSalir->siguiente;
            }

        } while (anteriorSalir != compras);
        if (encontrado)
        {
            cliente *postSalir = anteriorSalir->siguiente->siguiente;
            cliente *salida = anteriorSalir->siguiente;

            anteriorSalir->siguiente = postSalir;
            compras = postSalir;

            salida->siguiente = NULL;
            salida->anterior = NULL;

            return salida;
        }
        else
        {
            printf("No existe un elemento con el id ingresado\n");
            return NULL;
        }
    }
}
void imprimirCompras()
{
    Nsc = "";
    NscR = "";
    cliente *tmp = compras;

    if (tmp == NULL)
    {
        printf("Lista de compras vacia\n");
        Nsc = "COMT2 [shape = box,label = \"LISTA DE COMPRAS VACIA\"];\n";
    }
    else
    {
        do
        {
            printf("Cliente id: %d, con carreta id: %d,en compras, siguinte: %d\n", tmp->id, tmp->carrito->id, tmp->siguiente->id);
            reader = "";
            reader = "COM" + std::to_string(tmp->id) + " [shape = box,label = \"Cliente " + std::to_string(tmp->id) + "\\nCarreta " + std::to_string(tmp->carrito->id) + "\"];" + "\n";
            Nsc = Nsc + reader;
            reader = "";
            reader = "COM" + std::to_string(tmp->id) + " -> COM" + std::to_string(tmp->siguiente->id) + ";" + "\n";
            NscR = NscR + reader;
            tmp = tmp->siguiente;
        } while (tmp != compras);
    }
}

void agregarCaja(int id)
{
    caja *nuevo = new caja();
    nuevo->id = id;
    nuevo->turnos = 0;

    if (cajas == NULL)
    {
        cajas = nuevo;
        nuevo->siguiente = NULL;
        nuevo->anterior = NULL;
    }
    else
    {
        caja *ultimaCaja = cajas;
        while (ultimaCaja->siguiente != NULL)
        {
            ultimaCaja = ultimaCaja->siguiente;
        }
        ultimaCaja->siguiente = nuevo;
        nuevo->anterior = ultimaCaja;
        nuevo->siguiente = NULL;
    }
}
void imprimirCajas()
{
    ParamCajas = "";
    ParamCajasR = "";
    caja *tmp = cajas;
    if (tmp != NULL)
    {
        while (tmp != NULL)
        {
            printf("Caja id: %d, turnos: %d, Estado: %s, Anterior: %d, Siguinte %d\n", tmp->id, tmp->turnos, (tmp->client == NULL) ? "Libre" : "Ocupado", (tmp->anterior == NULL) ? -1 : tmp->anterior->id, (tmp->siguiente == NULL) ? -1 : tmp->siguiente->id);

            reader = "";
            reader = "CAJA" + std::to_string(tmp->id) + " [shape = box,label = \"Caja " + std::to_string(tmp->id) + "\\n" + std::to_string(tmp->turnos) + " Turnos\\n" + ((tmp->client == NULL) ? "Libre" : "Ocupado") + "\"];" + "\n";
            ParamCajas = ParamCajas + reader;
            reader = "";
            if (tmp->siguiente != NULL)
            {
                reader = "CAJA" + std::to_string(tmp->id) + " -> CAJA" + std::to_string(tmp->siguiente->id) + ";" + "\n";
            }
            ParamCajasR = ParamCajasR + reader;
            reader = "";
            if (tmp->anterior != NULL)
            {
                reader = "CAJA" + std::to_string(tmp->id) + " -> CAJA" + std::to_string(tmp->anterior->id) + ";" + "\n";
            }
            ParamCajasR = ParamCajasR + reader;
            tmp = tmp->siguiente;
        }
    }
    else
    {
        printf("Lista de Cajas vacia\n");
    }
}
void vaciarCajas()
{
    caja *tmp = cajas;
    if (tmp != NULL)
    {
        while (tmp != NULL)
        {
            if (tmp->client != NULL)
            {
                cliente *aux = tmp->client;
                tmp->client = NULL;
                //ultima linea agregada
                tmp->turnos = tmp->turnos + 1;

                printf("Sale el cliente %d y deja libre la carreta %d\n", aux->id, aux->carrito->id);

                ingresarID(aux->id);
                if (getNumeroAleatorio(1, 2) == 1)
                {
                    agregarCarreta(pilaCarreta1, aux->carrito->id);
                    printf("Carrito %d entra en la pila 1\n", aux->carrito->id);
                    delete aux->carrito;
                    delete aux;
                }
                else
                {
                    agregarCarreta(pilaCarreta2, aux->carrito->id);
                    printf("Carrito %d entra en la pila 1\n", aux->carrito->id);
                    delete aux->carrito;
                    delete aux;
                }
            }
            tmp = tmp->siguiente;
        }
    }
    else
    {
        printf("Lista de Cajas vacia\n");
    }
}
void llenarCajas()
{
    caja *tmp = cajas;
    if (tmp != NULL)
    {
        while (tmp != NULL)
        {
            if (tmp->client == NULL)
            {
                cliente *aux = salirColaCobro();
                if (aux != NULL)
                {
                    tmp->client = aux;
                    printf("El cliente: %d, esta siendo atendido en la caja: %d\n", aux->id, tmp->id);
                }
            }
            tmp = tmp->siguiente;
        }
    }
    else
    {
        printf("Lista de Cajas vacia\n");
    }
}
void generarIds()
{
    for (int i = 0; i <= 100; i++)
    {
        ingresarID(i);
    }
}
int tomarId()
{
    ID *aux = ids;
    int val = -1;
    if (ids == idsFin)
    {
        ids = NULL;
        idsFin = NULL;
    }
    else
    {
        ids = ids->siguinte;
    }
    if (aux != NULL)
    {
        aux->siguinte = NULL;
        val = aux->id;
        delete aux;
    }
    return val;
}
void ingresarID(int _id)
{
    ID *nuevo = new ID();
    nuevo->id = _id;
    nuevo->siguinte = NULL;

    if (ids == NULL)
    {
        ids = nuevo;
    }
    else
    {
        idsFin->siguinte = nuevo;
    }
    idsFin = nuevo;
}

void imprimirIds()
{
    ID *aux;
    aux = ids;
    if (aux != NULL)
    {
        do
        {
            printf("ID: %d, atras: %d\n", aux->id, (aux->siguinte == NULL) ? -1 : aux->siguinte->id);
            aux = aux->siguinte;
        } while (aux != NULL);
    }
    else
    {
        printf("Cola de cobro vacia\n");
    }
}

void ejecutarGraphviz()
{
    string codigo = "digraph estructuraDatos" + std::to_string(pasos) + " {\n" +
                    "PT [shape = box,style=bold,label = \"INDICADOR DE GRAFICA SEGUN PASOS:\\nPaso: " + std::to_string(pasos) + "\",color=red];" +
                    "subgraph compras {\n" +
                    "TCOM [shape = ellipse,style=bold,label = \"COMPRAS\",color=red];\n" +
                    Nsc +
                    NscR +
                    "}\n" +
                    "subgraph carretas{\n" +
                    "subgraph pilas{\n" +
                    "node [shape=record];\n" +
                    ParamPila1+
                    ParamPila1R+
                    ParamPila2+
                    ParamPila2R+
                    "}\n" +
                    "}\n" +
                    "subgraph colaEspera{\n" +
                    "TCE [shape = ellipse,style=bold,color=red,label = \"COLA DE ESPERA\"];\n" +
                    ParamColaEspera +
                    ParamColaEsperaR +
                    "}\n" +
                    "subgraph colaCobro{\n" +
                    "TC [shape = ellipse,style=bold,color=red,label = \"COLA PARA PAGAR\"];\n" +
                    ParamColaCobro +
                    ParamColaCobroR +
                    "}\n" +
                    "subgraph cajas{\n" +
                    "TCA [shape = ellipse,style=bold,color=red,label = \"CAJAS\"];\n" +
                    ParamCajas +
                    ParamCajasR +
                    "}\n" +
                    "}\n";

    escribirDot(codigo);
    //EJECUCION DE DOT EN LINUX
    int respuesta = system("dot -Tpng -O estructura.dot");
    if (respuesta == 0)
    {
        printf("EL diagrama se genero exitosamente\n");
    }
    else
    {
        printf("Error en generar diagrama, verifique las variables del sistema, el programa fue programado para LINUX\n");
    }
}
void escribirDot(string code)
{
    ofstream archivo;
    archivo.open("estructura.dot", ios::out);
    if (archivo.fail())
    {
        cout << "No se pudo abrir/crear el archivo" << endl;
    }
    else
    {
        archivo << code;
        archivo.close();
    }
}