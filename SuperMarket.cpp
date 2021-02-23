#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//---------------------------------CLASE CARRETA-----------------------------------------------------
class carreta{
    private:
        int id;
        carreta *siguinte;
    public:
        carreta(int);
        carreta();
        carreta* getSiguiente();
        void setCarreta(carreta*);
        int getId();
};

carreta::carreta(int _id){
    id=_id;
}
carreta::carreta(){

}
carreta* carreta::getSiguiente(){
    return siguinte;
}

void carreta::setCarreta(carreta* _siguinte){
    siguinte=_siguinte;
}

int carreta::getId(){
    return id;
}

//----------------------------CLASE CLIENTE-------------------------------------------------------
class cliente{
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
        carreta* getCarrito();
        void setCarrito(carreta*);
        cliente* getSiguiente();
        void setSiguinte(cliente*);
};

cliente::cliente(int _id){
    id=_id;
}
cliente::cliente(){

}
void cliente::setId(int _id){
    id=_id;
}

int cliente::getId(){
    return id;
}

void cliente::setCarrito(carreta *_carrito){
    carrito=_carrito;
}

carreta* cliente::getCarrito(){
    return carrito;
}

cliente* cliente::getSiguiente(){
    return siguiente;
}

void cliente::setSiguinte(cliente *_siguiente){
    siguiente = _siguiente;
}

//--------------- OBJETO CAJA -------------------------------
class caja{
    private:
        int id;
        cliente *client;
        caja *siguiente;
        caja *anterior;
    public:
        caja();
        caja(int id);
        int getId();
        cliente* getCliente();
        void setCliente(cliente*);
        caja* getSiguiente();
        void setSiguinte(caja*);
        caja* getAnterior();
        void setAnterior(caja*);
};

caja::caja(){

}
caja::caja(int _id){
    id=_id;
}
int caja::getId(){
    return id;
}
cliente* caja::getCliente(){
    return client;
}

void caja::setCliente(cliente *_client){
    client=_client;
}

caja* caja::getSiguiente(){
    return siguiente;
}

void caja::setSiguinte(caja *_siguiente){
    siguiente =_siguiente;
}

caja* caja::getAnterior(){
    return anterior;
}

void caja::setAnterior(caja *_anterior){
    anterior = _anterior;
}

////SECCION DEL CODIGO PRINCIPAL DEL CODIGO 
int numCarretas=0,numCajas=0;
string reader;

carreta *pilaCarreta1,*pilaCarreta2;
cliente *colaEntrada,*colaCobro,*compras;

caja *cajas;



//////DEFINICION DE METODOS DEL PROGRAMA

void inicializarSimulacion();

//metodos de acciones con carretas
void llenarPilaCarretas();
void agregarCarreta(carreta *nuevaCarreta,int pila);
carreta* tomarCarreta(int pila);
void imprimirCarretas(int pila);
int contarCarretas(int pila);
//acciones de caja
void generarCajas();
void agregarCaja(caja *cajaNueva);
void imprimirCajas();
void cajaVacia();
int contarCajas();
///acciones de colas de personas
void agregarColaEntrada(cliente *cliente);
cliente* sacarColaEntrada();
void agregarColaCobro(cliente *cliente);
cliente* sacarColaCobro();
void imprimirColaEntrada();
void imprimirColaCobro();
//obtener numero aleatorio
int getNumeroAleatorio(int inf,int sup);
//////FIN DE DEFINICION DE METODOS DEL PROGRAMA



int main(){
    //INICIALIZACION DE LOS NUMEROS ALEATORIOS
    srand(time(NULL));

    inicializarSimulacion();



    return 0;
}

void inicializarSimulacion(){
    printf("Bienvenido a la simulacion de SuperMercado\n");
    //////////ASIGNACION DE DATOS DEL FUNCIONAMIENTO DEL PROGRAMA
    while (numCarretas == 0)
    {
        printf("Ingrese el numero de Carretas: ");
        cin >> reader;
        try
        {
            numCarretas= std::stoi(reader);    
        }
        catch(const std::exception& e)
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
        catch(const std::exception& e)
        {
            std::cerr << "Cantidad de ingreso invalida" << '\n';
        }
        
    }

    llenarPilaCarretas();
    generarCajas();

    printf("EL SISTEMA DE INICIALIZO CON LOS SIGUINTES PARAMETROS\n");
    printf("Numero de carretas: %d\nNumero de cajas: %d\n",contarCarretas(1)+contarCarretas(2),contarCajas());

}

void llenarPilaCarretas(){
    int mitad1=0,mitad2=0;

    mitad1 = numCarretas/2;
    mitad2 = numCarretas-mitad1;

    for (int i = 1; i <= mitad1; i++)
    {
        agregarCarreta(new carreta(i),1);
    }

    for (int i = (mitad1+1); i <= numCarretas; i++)
    {
        agregarCarreta(new carreta(i),2);
    }
}

void agregarCarreta(carreta *nuevaCarreta,int pila){
    if(pila==1){
        if(pilaCarreta1==NULL){
            pilaCarreta1 = nuevaCarreta;
        }else{
            carreta *tmp;
            tmp = pilaCarreta1;
            nuevaCarreta->setCarreta(tmp);
            pilaCarreta1 = nuevaCarreta;
        }
    }else if(pila ==2){
        if(pilaCarreta2==NULL){
            pilaCarreta2 = nuevaCarreta;
        }else{
            carreta *tmp;
            tmp = pilaCarreta2;
            nuevaCarreta->setCarreta(tmp);
            pilaCarreta2 = nuevaCarreta;
        }
    }else{
        printf("Error al agregar la carreta, ruta por defecto pila 1\n");
        agregarCarreta(nuevaCarreta,1);
    }
}

carreta* tomarCarreta(int pila){

    if(pila==1){
        if(pilaCarreta1 == NULL){
            printf("Error al tomar la carreta pila 1 vacia\n");
        }else{
            carreta *tmp;
            tmp = pilaCarreta1;
            pilaCarreta1 = tmp->getSiguiente();
            tmp->setCarreta(NULL);
            return tmp;
        }
    }else if(pila ==2){
        if(pilaCarreta2 == NULL){
            printf("Error al tomar la carreta pila 2 vacia\n");
        }else{
            carreta *tmp;
            tmp = pilaCarreta2;
            pilaCarreta2 = tmp->getSiguiente();
            tmp->setCarreta(NULL);
            return tmp;
        }
    }else{
        printf("Error al tomar la carreta, ruta por defecto pila 1\n");
        tomarCarreta(1);
    }
    return NULL;
}

void imprimirCarretas(int pila){
    if(pila == 1){
        printf("IMPRECION DE PILA NUMERO 1\n");
        if(pilaCarreta1==NULL){
            printf("Pila numero 1 vacia\n");
        }else{
            carreta *tmp;
            tmp = pilaCarreta1;
            while (tmp != NULL)
            {
                printf("Carreta id: %d, pila ubicacion: 1\n",tmp->getId());
                tmp = tmp->getSiguiente();
            }
            
        }

    }else if(pila == 2){
        printf("IMPRECION DE PILA NUMERO 2\n");
        if(pilaCarreta2==NULL){
            printf("Pila numero 2 vacia\n");
        }else{
            carreta *tmp;
            tmp = pilaCarreta2;
            while (tmp != NULL)
            {
                printf("Carreta id: %d, pila ubicacion: 2\n",tmp->getId());
                tmp = tmp->getSiguiente();
            }
            
        }
    }else{
        printf("Error de imprecion en pila de carretas\n");
        printf("Imprecion por defecto:\n");
    }
}

int contarCarretas(int pila){
    int cont =0;

    if(pila==1){
        if(pilaCarreta1==NULL){
            return cont;
        }else{
            carreta *tmp;
            tmp = pilaCarreta1;
            while (tmp != NULL)
            {
                cont++;
                tmp = tmp->getSiguiente();
            }

            return cont;
        }
    }else if(pila==2){
        if(pilaCarreta2==NULL){
            return cont;
        }else{
            carreta *tmp;
            tmp = pilaCarreta2;
            while (tmp != NULL)
            {
                cont++;
                tmp = tmp->getSiguiente();
            }
            return cont;
        }
    }else{
        printf("Error de contar carretas\n");
        return 0;
    }
}

void generarCajas(){
    for (int i = 1; i <= numCajas; i++)
    {
        agregarCaja(new caja(i));
    }
}

void agregarCaja(caja *cajaNueva){
    if(cajas == NULL){
        cajas = cajaNueva;
        cajas->setSiguinte(cajas);
        cajas->setAnterior(cajas);
    }else{
        caja *tmp1;
        tmp1 = cajas->getAnterior();
        cajaNueva->setSiguinte(cajas);
        cajaNueva->setAnterior(tmp1);

        tmp1->setSiguinte(cajaNueva);
        cajas->setAnterior(cajaNueva);      
    }
}

void imprimirCajas(){
    printf("\nLista de Cajas\n");
    if(cajas==NULL){
        printf("Lista de cajas vacia\n");
    }
    else{
        caja *tmp;
        tmp = cajas;
        while (tmp->getSiguiente() != cajas)
        {
            printf("Caja id: %d, Caja anterior id: %d, Caja Siguinte id: %d\n",tmp->getId(),tmp->getAnterior()->getId(),tmp->getSiguiente()->getId());
            tmp = tmp->getSiguiente();
        }
        printf("Caja id: %d, Caja anterior id: %d, Caja Siguinte id: %d\n",tmp->getId(),tmp->getAnterior()->getId(),tmp->getSiguiente()->getId());
    }
}

void cajaVacia(){
    if(cajas==NULL){
        printf("Lista de cajas vacia\n");
    }
    else{
        caja *tmp;
        tmp = cajas;
        do
        {
            if(tmp->getCliente()==NULL){
                printf("Caja id: %d esta vacia\n",tmp->getId());
            }

            tmp = tmp->getSiguiente();
        } while (tmp != cajas);
        
    }
}
int contarCajas(){
    if(cajas==NULL){
        return 0;
    }
    else{
        caja *tmp;
        int cont=0;
        tmp = cajas;
        do
        {
            cont++;
            tmp = tmp->getSiguiente();
        } while (tmp != cajas);
        return cont;
    }
}

void agregarColaEntrada(cliente *clien){
    if(colaEntrada == NULL){
        colaEntrada = clien;
    }else{
        cliente *tmp;
        tmp = colaEntrada;
        while (tmp->getSiguiente()!= NULL)
        {
            tmp = tmp->getSiguiente();
        }
        tmp->setSiguinte(clien);
    }
}

cliente* sacarColaEntrada(){
    if(colaEntrada == NULL){
        printf("Cola de entrada vacia, no se puede sacar\n");
        return NULL;
    }else{
        cliente *tmp;
        tmp = colaEntrada;
        colaEntrada = tmp->getSiguiente();
        tmp->setSiguinte(NULL);
        return tmp;
    }
}

void agregarColaCobro(cliente *clien){
    if(colaCobro == NULL){
        colaCobro = clien;
    }else{
        cliente *tmp;
        tmp = colaCobro;
        while (tmp->getSiguiente()!= NULL)
        {
            tmp = tmp->getSiguiente();
        }
        tmp->setSiguinte(clien);
    }
}

cliente* sacarColaCobro(){
    if(colaCobro == NULL){
        printf("Cola de cobro vacia, no se puede sacar\n");
        return NULL;
    }else{
        cliente *tmp;
        tmp = colaCobro;
        colaCobro = tmp->getSiguiente();
        tmp->setSiguinte(NULL);
        return tmp;
    }
}

void imprimirColaEntrada(){
    if(colaEntrada==NULL){
        printf("Cola de entrada vacia\n");
    }else{
        cliente *tmp;
        tmp = colaEntrada;
        while (tmp != NULL)
        {
            printf("Cliente id: %d esperando una carreta\n",tmp->getId());
            tmp = tmp->getSiguiente();
        }
        
    }
}

void imprimirColaCobro(){
    if(colaCobro==NULL){
        printf("Cola de cobro vacia\n");
    }else{
        cliente *tmp;
        tmp = colaCobro;
        while (tmp != NULL)
        {
            printf("Cliente id: %d esperando una caja\n",tmp->getId());
            tmp = tmp->getSiguiente();
        }
        
    }
}

int getNumeroAleatorio(int inf,int sup){
    return (inf+rand()%(sup-inf));
}