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
int SuperMarket(){

    printf("Bienvenido a la simulacion de SuperMercado\n");

    printf("Ingrese el numero de Carretas: ");
    printf("Ingrese el numero de Cajas: ");
    return 0;
}