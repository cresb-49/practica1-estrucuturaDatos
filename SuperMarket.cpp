#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

//---------------------------------CLASE CARRETA-----------------------------------------------------
class carreta
{
private:
    int id;
    carreta *siguinte;

public:
    carreta(int);
    carreta();
    carreta *getSiguiente();
    void setCarreta(carreta *);
    int getId();
};

carreta::carreta(int _id)
{
    id = _id;
}
carreta::carreta()
{
}
carreta *carreta::getSiguiente()
{
    return siguinte;
}

void carreta::setCarreta(carreta *_siguinte)
{
    siguinte = _siguinte;
}

int carreta::getId()
{
    return id;
}

//----------------------------CLASE CLIENTE-------------------------------------------------------
class cliente
{
private:
    int id;
    carreta *carrito;
    cliente *anterior;
    cliente *siguiente;

public:
    cliente(int);
    cliente();
    int getId();
    void setId(int);
    carreta *getCarrito();
    void setCarrito(carreta *);
    cliente *getSiguiente();
    void setSiguinte(cliente *);
};

cliente::cliente(int _id)
{
    id = _id;
}
cliente::cliente()
{
}
void cliente::setId(int _id)
{
    id = _id;
}

int cliente::getId()
{
    return id;
}

void cliente::setCarrito(carreta *_carrito)
{
    carrito = _carrito;
}

carreta *cliente::getCarrito()
{
    return carrito;
}

cliente *cliente::getSiguiente()
{
    return siguiente;
}

void cliente::setSiguinte(cliente *_siguiente)
{
    siguiente = _siguiente;
}

//--------------- OBJETO CAJA -------------------------------
class caja
{
private:
    int id;
    cliente *client;
    caja *siguiente;
    caja *anterior;

public:
    caja();
    caja(int id);
    int getId();
    cliente *getCliente();
    void setCliente(cliente *);
    caja *getSiguiente();
    void setSiguinte(caja *);
    caja *getAnterior();
    void setAnterior(caja *);
};

caja::caja()
{
}
caja::caja(int _id)
{
    id = _id;
}
int caja::getId()
{
    return id;
}
cliente *caja::getCliente()
{
    return client;
}

void caja::setCliente(cliente *_client)
{
    client = _client;
}

caja *caja::getSiguiente()
{
    return siguiente;
}

void caja::setSiguinte(caja *_siguiente)
{
    siguiente = _siguiente;
}

caja *caja::getAnterior()
{
    return anterior;
}

void caja::setAnterior(caja *_anterior)
{
    anterior = _anterior;
}
///-------------------OBJETO ID
class ID
{
private:
    int id;
    ID *siguiente;

public:
    ID(int);
    ID();
    int getId();
    void setSiguiente(ID *);
    ID *getSiguiente();
};

ID::ID()
{
}
ID::ID(int _id)
{
    id = _id;
}

int ID::getId()
{
    return id;
}

void ID::setSiguiente(ID *_siguiente)
{
    siguiente = _siguiente;
}

ID *ID::getSiguiente()
{
    return siguiente;
}

////SECCION DEL CODIGO PRINCIPAL DEL CODIGO
int numCarretas = 0, numCajas = 0, pasos = 0;
string reader;

carreta *pilaCarreta1, *pilaCarreta2;
cliente *colaEntrada, *colaCobro, *compras;

caja *cajas;

ID *idClientes;

//////DEFINICION DE METODOS DEL PROGRAMA

void inicializarSimulacion();
void limpiar_pantalla();
void pausa();
void pausaDoble();
void accionesSistema();
//metodos de acciones con carretas
void llenarPilaCarretas();
void agregarCarreta(carreta *nuevaCarreta, int pila);
carreta *tomarCarreta(int pila);
void imprimirCarretas(int pila);
int contarCarretas(int pila);
//acciones de caja
void generarCajas();
void agregarCaja(caja *cajaNueva);
void imprimirCajas();
void cajaVacia();
void vaciarCajas();
void llenarCajas();
int contarCajas();
///acciones de colas de personas
void agregarColaEntrada(cliente *clien);
cliente *sacarColaEntrada();
void agregarColaCobro(cliente *clien);
cliente *sacarColaCobro();
void imprimirColaEntrada();
void imprimirColaCobro();
//obtener numero aleatorio
int getNumeroAleatorio(int inf, int sup);
//metodos para la obtencion de ids
void generarIds();
int tomarId();
void agregarId(int id);
void imprimirIds();
//acciones en lista de compras
void agregarCompras(cliente *clien);
cliente *sacarCompras(int id);
cliente *retornarAnteriorCompras(int id);
void imprimirCompras();
//accion de eliminar cliente del super
void eliminarCliente(cliente *client);

//////FIN DE DEFINICION DE METODOS DEL PROGRAMA

int main()
{
    //INICIALIZACION DE LOS NUMEROS ALEATORIOS
    srand(time(NULL));

    inicializarSimulacion();
    pausaDoble();

    string option;
    short int bandera = 1;
    short int bandera2 = 1;

    while (bandera == 1)
    {
        limpiar_pantalla();
        printf("----------------------PASO NUMERO %d--------------------\n", pasos);

        accionesSistema();

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
                    limpiar_pantalla();
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error de opcion escriba la correcta" << '\n';
            }

        } while (bandera2 == 1);
        pasos++;
    }
    return 0;
}

void inicializarSimulacion()
{
    printf("Bienvenido a la simulacion de SuperMercado\n");
    //////////ASIGNACION DE DATOS DEL FUNCIONAMIENTO DEL PROGRAMA
    while (numCarretas == 0)
    {
        printf("Ingrese el numero de Carretas: ");
        cin >> reader;
        try
        {
            numCarretas = std::stoi(reader);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Cantidad de ingreso invalida!!" << '\n';
        }
    }

    while (numCajas == 0)
    {
        printf("Ingrese el numero de Cajas: ");
        cin >> reader;
        try
        {
            numCajas = std::stoi(reader);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Cantidad de ingreso invalida" << '\n';
        }
    }

    llenarPilaCarretas();
    generarCajas();
    generarIds();

    printf("EL SISTEMA DE INICIALIZO CON LOS SIGUINTES PARAMETROS\n");
    printf("Numero de carretas: %d\nNumero de cajas: %d\n", contarCarretas(1) + contarCarretas(2), contarCajas());
}
void limpiar_pantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void pausa()
{
    do
    {
        cout << '\n'
             << "Precione Enter para continuar";
    } while (cin.get() != '\n');
}
void pausaDoble()
{
    do
    {
        cout << "";
    } while (cin.get() != '\n');
    do
    {
        cout << '\n'
             << "Precione Enter para continuar";
    } while (cin.get() != '\n');
}
void accionesSistema()
{
    int numAle;
    cliente *tmpCliente;

    //VACIAR CAJAS DEL SISTEMA
    vaciarCajas();
    //FIN VACIAR CAJAS DEL SISTEMA

    //LLENAR CAJAS CON CLIENTES
    llenarCajas();
    //FIN LENAR CAJAS CON CLIENTES

    //SALIDA DE COMPRAS E INGRESO A COLA DE COBROS
    numAle = getNumeroAleatorio(0, 100);
    if (compras != NULL)
    {
        tmpCliente = sacarCompras(numAle);
        if (tmpCliente != NULL)
        {
            agregarColaCobro(tmpCliente);
        }
    }
    //FIN SALIDA DE COMPRAR E INGRESO A COLA DE COBROS

    ///ACCION DE TOMA DE CARRETA Y ENTRADA A COMPRAS
    carreta *tmpCarreta;
    if (colaEntrada != NULL)
    {
        while ((pilaCarreta1 != NULL || pilaCarreta2 != NULL) && colaEntrada != NULL)
        {
            if (colaEntrada != NULL)
            {
                if (pilaCarreta1 != NULL)
                {
                    tmpCliente = sacarColaEntrada();
                    tmpCarreta = tomarCarreta(1);
                    tmpCliente->setCarrito(tmpCarreta);
                    printf("El cliente %d toma la carreta %d y realizara sus compras\n", tmpCliente->getId(), tmpCarreta->getId());
                    agregarCompras(tmpCliente);
                }
                else if (pilaCarreta2 != NULL)
                {
                    tmpCliente = sacarColaEntrada();
                    tmpCarreta = tomarCarreta(2);
                    tmpCliente->setCarrito(tmpCarreta);
                    printf("El cliente %d toma la carreta %d y realizara sus compras\n", tmpCliente->getId(), tmpCarreta->getId());
                    agregarCompras(tmpCliente);
                }
            }
        }
    }
    ///FIN ACCION DE TOMA DE CARRETA Y ENTRADA A COMPRAS

    //ENTRADA DE CLIENTE NUEVO AL SISTEMA Y COLA DE ENTRADA
    numAle = getNumeroAleatorio(0, 50) % 5;
    if (numAle == 0)
    {
        //printf("Generar nuevo cliente\n");
        int tmp = tomarId();
        if (tmp != -1)
        {
            printf("Llega el cliente %d y se agrega a la cola de espera.\n", tmp);
            agregarColaEntrada(new cliente(tmp));
            //imprimirColaEntrada();
        }
    }
    //ENTRADA DE CLIENTE NUEVO AL SISTEMA Y COLA DE ENTRADA
}

void llenarPilaCarretas()
{
    int mitad1 = 0, mitad2 = 0;

    mitad1 = numCarretas / 2;
    mitad2 = numCarretas - mitad1;

    for (int i = 1; i <= mitad1; i++)
    {
        agregarCarreta(new carreta(i), 1);
    }

    for (int i = (mitad1 + 1); i <= numCarretas; i++)
    {
        agregarCarreta(new carreta(i), 2);
    }
}

void agregarCarreta(carreta *nuevaCarreta, int pila)
{
    if (pila == 1)
    {
        if (pilaCarreta1 == NULL)
        {
            pilaCarreta1 = nuevaCarreta;
        }
        else
        {
            carreta *tmp;
            tmp = pilaCarreta1;
            nuevaCarreta->setCarreta(tmp);
            pilaCarreta1 = nuevaCarreta;
        }
    }
    else if (pila == 2)
    {
        if (pilaCarreta2 == NULL)
        {
            pilaCarreta2 = nuevaCarreta;
        }
        else
        {
            carreta *tmp;
            tmp = pilaCarreta2;
            nuevaCarreta->setCarreta(tmp);
            pilaCarreta2 = nuevaCarreta;
        }
    }
    else
    {
        printf("Error al agregar la carreta, ruta por defecto pila 1\n");
        agregarCarreta(nuevaCarreta, 1);
    }
}

carreta *tomarCarreta(int pila)
{

    if (pila == 1)
    {
        if (pilaCarreta1 == NULL)
        {
            printf("Error al tomar la carreta pila 1 vacia\n");
        }
        else
        {
            carreta *tmp;
            tmp = pilaCarreta1;
            pilaCarreta1 = tmp->getSiguiente();
            tmp->setCarreta(NULL);
            return tmp;
        }
    }
    else if (pila == 2)
    {
        if (pilaCarreta2 == NULL)
        {
            printf("Error al tomar la carreta pila 2 vacia\n");
        }
        else
        {
            carreta *tmp;
            tmp = pilaCarreta2;
            pilaCarreta2 = tmp->getSiguiente();
            tmp->setCarreta(NULL);
            return tmp;
        }
    }
    else
    {
        //printf("Error al tomar la carreta, ruta por defecto pila 1\n");
        //tomarCarreta(1);
    }
    return NULL;
}

void imprimirCarretas(int pila)
{
    if (pila == 1)
    {
        printf("IMPRECION DE PILA NUMERO 1\n");
        if (pilaCarreta1 == NULL)
        {
            printf("Pila numero 1 vacia\n");
        }
        else
        {
            carreta *tmp;
            tmp = pilaCarreta1;
            while (tmp != NULL)
            {
                printf("Carreta id: %d, pila ubicacion: 1\n", tmp->getId());
                tmp = tmp->getSiguiente();
            }
        }
    }
    else if (pila == 2)
    {
        printf("IMPRECION DE PILA NUMERO 2\n");
        if (pilaCarreta2 == NULL)
        {
            printf("Pila numero 2 vacia\n");
        }
        else
        {
            carreta *tmp;
            tmp = pilaCarreta2;
            while (tmp != NULL)
            {
                printf("Carreta id: %d, pila ubicacion: 2\n", tmp->getId());
                tmp = tmp->getSiguiente();
            }
        }
    }
    else
    {
        printf("Error de imprecion en pila de carretas\n");
        printf("Imprecion por defecto:\n");
    }
}

int contarCarretas(int pila)
{
    int cont = 0;

    if (pila == 1)
    {
        if (pilaCarreta1 == NULL)
        {
            return cont;
        }
        else
        {
            carreta *tmp;
            tmp = pilaCarreta1;
            while (tmp != NULL)
            {
                cont++;
                tmp = tmp->getSiguiente();
            }

            return cont;
        }
    }
    else if (pila == 2)
    {
        if (pilaCarreta2 == NULL)
        {
            return cont;
        }
        else
        {
            carreta *tmp;
            tmp = pilaCarreta2;
            while (tmp != NULL)
            {
                cont++;
                tmp = tmp->getSiguiente();
            }
            return cont;
        }
    }
    else
    {
        printf("Error de contar carretas\n");
        return 0;
    }
}

void generarCajas()
{
    for (int i = 1; i <= numCajas; i++)
    {
        agregarCaja(new caja(i));
    }
}

void agregarCaja(caja *cajaNueva)
{
    if (cajas == NULL)
    {
        cajas = cajaNueva;
        cajas->setSiguinte(cajas);
        cajas->setAnterior(cajas);
    }
    else
    {
        caja *tmp1;
        tmp1 = cajas->getAnterior();
        cajaNueva->setSiguinte(cajas);
        cajaNueva->setAnterior(tmp1);

        tmp1->setSiguinte(cajaNueva);
        cajas->setAnterior(cajaNueva);
    }
}

void imprimirCajas()
{
    printf("\nLista de Cajas\n");
    if (cajas == NULL)
    {
        printf("Lista de cajas vacia\n");
    }
    else
    {
        caja *tmp;
        tmp = cajas;
        while (tmp->getSiguiente() != cajas)
        {
            printf("Caja id: %d, Caja anterior id: %d, Caja Siguinte id: %d\n", tmp->getId(), tmp->getAnterior()->getId(), tmp->getSiguiente()->getId());
            tmp = tmp->getSiguiente();
        }
        printf("Caja id: %d, Caja anterior id: %d, Caja Siguinte id: %d\n", tmp->getId(), tmp->getAnterior()->getId(), tmp->getSiguiente()->getId());
    }
}

void cajaVacia()
{
    if (cajas == NULL)
    {
        printf("Lista de cajas vacia\n");
    }
    else
    {
        caja *tmp;
        tmp = cajas;
        do
        {
            if (tmp->getCliente() == NULL)
            {
                printf("Caja id: %d esta vacia\n", tmp->getId());
            }

            tmp = tmp->getSiguiente();
        } while (tmp != cajas);
    }
}

void vaciarCajas()
{
    if (cajas == NULL)
    {
        printf("Lista de cajas vacia\n");
    }
    else
    {
        caja *tmp;
        tmp = cajas;
        do
        {
            if (tmp->getCliente() != NULL)
            {
                printf("El cliente %d sale del sistema. Libera carreta %d y la caja %d\n", tmp->getCliente()->getId(), tmp->getCliente()->getCarrito()->getId(), tmp->getId());
                eliminarCliente(tmp->getCliente());
                tmp->setCliente(NULL);
            }

            tmp = tmp->getSiguiente();
        } while (tmp != cajas);
    }
}
void llenarCajas()
{
    if (cajas == NULL)
    {
        printf("Lista de cajas vacia\n");
    }
    else
    {
        caja *tmp;
        cliente *tmpCliente;
        tmp = cajas;
        do
        {
            if (tmp->getCliente() == NULL)
            {
                if (colaCobro != NULL)
                {
                    tmpCliente = sacarColaCobro();
                    printf("El cliente %d esta siendo atendido por la caja %d\n", tmpCliente->getId(), tmp->getId());
                    tmp->setCliente(tmpCliente);
                }
            }

            tmp = tmp->getSiguiente();
        } while (tmp != cajas);
    }
}

int contarCajas()
{
    if (cajas == NULL)
    {
        return 0;
    }
    else
    {
        caja *tmp;
        int cont = 0;
        tmp = cajas;
        do
        {
            cont++;
            tmp = tmp->getSiguiente();
        } while (tmp != cajas);
        return cont;
    }
}

void agregarColaEntrada(cliente *clien)
{
    if (colaEntrada == NULL)
    {
        colaEntrada = clien;
    }
    else
    {
        cliente *tmp;
        tmp = colaEntrada;
        while (tmp->getSiguiente() != NULL)
        {
            tmp = tmp->getSiguiente();
        }
        tmp->setSiguinte(clien);
    }
}

cliente *sacarColaEntrada()
{
    if (colaEntrada == NULL)
    {
        printf("Cola de entrada vacia, no se puede sacar\n");
        return NULL;
    }
    else
    {
        cliente *tmp;
        tmp = colaEntrada;
        colaEntrada = tmp->getSiguiente();
        tmp->setSiguinte(NULL);
        return tmp;
    }
}

void agregarColaCobro(cliente *clien)
{
    if (colaCobro == NULL)
    {
        colaCobro = clien;
    }
    else
    {
        cliente *tmp;
        tmp = colaCobro;
        while (tmp->getSiguiente() != NULL)
        {
            tmp = tmp->getSiguiente();
        }
        tmp->setSiguinte(clien);
    }
}

cliente *sacarColaCobro()
{
    if (colaCobro == NULL)
    {
        printf("Cola de cobro vacia, no se puede sacar\n");
        return NULL;
    }
    else
    {
        cliente *tmp;
        tmp = colaCobro;
        colaCobro = tmp->getSiguiente();
        tmp->setSiguinte(NULL);
        return tmp;
    }
}

void imprimirColaEntrada()
{
    if (colaEntrada == NULL)
    {
        printf("Cola de entrada vacia\n");
    }
    else
    {
        cliente *tmp;
        tmp = colaEntrada;
        while (tmp != NULL)
        {
            printf("Cliente id: %d esperando una carreta\n", tmp->getId());
            tmp = tmp->getSiguiente();
        }
    }
}

void imprimirColaCobro()
{
    if (colaCobro == NULL)
    {
        printf("Cola de cobro vacia\n");
    }
    else
    {
        cliente *tmp;
        tmp = colaCobro;
        while (tmp != NULL)
        {
            printf("Cliente id: %d esperando una caja\n", tmp->getId());
            tmp = tmp->getSiguiente();
        }
    }
}

int getNumeroAleatorio(int inf, int sup)
{
    return (inf + rand() % (sup - inf));
}

void generarIds()
{
    for (int i = 0; i <= 100; i++)
    {
        agregarId(i);
    }
}

int tomarId()
{
    if (idClientes == NULL)
    {
        printf("Error al tomar id para cliente\n");
        return -1;
    }
    else
    {
        ID *tmp;
        int val;

        tmp = idClientes;

        idClientes = tmp->getSiguiente();
        val = tmp->getId();

        free(tmp);
        return val;
    }
}

void agregarId(int id)
{
    if (idClientes == NULL)
    {
        idClientes = new ID(id);
    }
    else
    {
        ID *tmp, *tmp2;
        tmp2 = new ID(id);

        tmp = idClientes;

        while (tmp->getSiguiente() != NULL)
        {
            tmp = tmp->getSiguiente();
        }

        tmp->setSiguiente(tmp2);
    }
}
void imprimirIds()
{
    if (idClientes == NULL)
    {
        printf("Ids clientes vacia\n");
    }
    else
    {
        ID *tmp;
        tmp = idClientes;
        while (tmp != NULL)
        {
            printf("Id: %d\n", tmp->getId());
            tmp = tmp->getSiguiente();
        }
    }
}

void agregarCompras(cliente *clien)
{
    if (compras == NULL)
    {
        compras = clien;
        compras->setSiguinte(compras);
    }
    else
    {
        cliente *tmp;
        tmp = compras->getSiguiente();
        compras->setSiguinte(clien);
        clien->setSiguinte(tmp);
    }
}
cliente *sacarCompras(int id)
{
    if (compras == NULL)
    {
        printf("La lista de compras esta vacia\n");
        return NULL;
    }
    else
    {
        cliente *tmp, *tmp2, *tmp3;

        if (compras->getId() == id)
        {
            tmp = compras;
            while (tmp->getSiguiente() != compras)
            {
                tmp = tmp->getSiguiente();
            }
            tmp2 = tmp->getSiguiente()->getSiguiente();
            tmp3 = tmp->getSiguiente();
            tmp->setSiguinte(tmp2);

            if (tmp == tmp2 && tmp == tmp3)
            {
                compras = NULL;
            }
            else
            {
                compras = tmp2;
            }
            tmp3->setSiguinte(NULL);
            return tmp3;
        }
        else
        {
            tmp = retornarAnteriorCompras(id);
            if (tmp == NULL)
            {
                //printf("No existe un cliente con el id %d\n", id);
                return NULL;
            }
            else
            {
                tmp2 = tmp->getSiguiente()->getSiguiente();
                tmp3 = tmp->getSiguiente();
                tmp->setSiguinte(tmp2);
                tmp3->setSiguinte(NULL);
                return tmp3;
            }
        }
    }
}
cliente *retornarAnteriorCompras(int id)
{
    if (compras == NULL)
    {
        return NULL;
    }
    else
    {
        cliente *tmp;
        tmp = compras;
        do
        {
            if (tmp->getSiguiente()->getId() == id)
            {
                return tmp;
            }
            tmp = tmp->getSiguiente();
        } while (tmp != compras);
        return NULL;
    }
}

void imprimirCompras()
{
    cliente *tmp;
    tmp = compras;
    if (tmp == NULL)
    {
        printf("Lista de compras vacia\n");
    }
    else
    {
        do
        {
            printf("Cliente id: %d en compras\n", tmp->getId());
            tmp = tmp->getSiguiente();
        } while (tmp != compras);
    }
}

void eliminarCliente(cliente *client)
{
    int ale = getNumeroAleatorio(1, 2);
    agregarCarreta(client->getCarrito(), ale);
    client->setCarrito(NULL);
    agregarId(client->getId());
    free(client);
}