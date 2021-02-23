#include <iostream>
#include <stdlib.h>

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
    public:
        cliente(int);
        cliente();
        int getId();
        void setId(int);
        carreta* getCarrito();
        void setCarrito(carreta*);
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

//--------------- OBJETO CAJA -------------------------------
class caja{
    private:
        int id;
        cliente *client;
        caja *siguiente;
    public:
        caja();
        caja(int id);
        cliente* getCliente();
        void setCliente(cliente*);
        caja* getSiguiente();
        void setSiguinte(caja*);
};

caja::caja(){

}
caja::caja(int _id){
    id=_id;
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

////SECCION DEL CODIGO PRINCIPAL DEL CODIGO 
int numCarretas=0,numCajas=0;
string reader;

carreta *pilaCarreta1,*pilaCarreta2;
cliente *colaEntrada,*colaCobro;

//////DEFINICION DE METODOS DEL PROGRAMA
void llenarPilaCarretas();
void agregarCarreta(carreta *nuevaCarreta,int pila);
carreta* tomarCarreta(int pila);
void imprimirCarretas(int pila);
//////FIN DE DEFINICION DE METODOS DEL PROGRAMA



int main(){

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
    ///////FIN DE PARAMETROS DE ASIGNACION
    printf("El numero de carretas son: %d, el numero de cajas son: %d \n",numCarretas,numCajas);
    llenarPilaCarretas();
    imprimirCarretas(1);
    imprimirCarretas(2);



    return 0;
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

    }else if(pila ==2){

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
                printf("Carreta id: %d, pila ubicacion: 1\n",tmp->getId());
                tmp = tmp->getSiguiente();
            }
            
        }
    }else{
        printf("Error de imprecion en pila de carretas\n");
        printf("Imprecion por defecto:\n");
    }
}

