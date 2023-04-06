/*
Author: Jose Angel Garcia Gomez
Date: 11/2021
Description: Program that reads a text file with a web server access log and creates a text file
with the Ips that connected and the number of accesses they had.
*/

#include "Acceso.hpp"
#include "BST.hpp"
#include <fstream>

int main(){
    //Lectura de la bitacora 
    ifstream datos;
    datos.open("bitacoraCompleta.txt");
    string ip;
    string basura;
    ListaSimple<string> * ListaIp = new ListaSimple<string>(); 
    ListaSimple<Ip *> * ListaIpAccesos = new ListaSimple<Ip *>();
    while(datos.good()){
        getline(datos, basura, ' ');
        getline(datos, basura, ' ');
        getline(datos, basura, ' ');
        getline(datos, ip, ':');
        getline(datos, basura, ' ');
        getline(datos, basura);
        if(!ListaIp -> buscarNodo(ip)){
            ListaIp -> agregarFin(ip);
            ListaIpAccesos->agregarFin(new Ip(ip));
        }else{
            NodoT<Ip *> * nodo=ListaIpAccesos->getHead();
            while(nodo){
                //Busqueda del valor dentro de los nodos
                if(nodo->getDato()->getNum_Ip()==ip)
                    nodo->getDato()->agregarAcceso();
                nodo=nodo->getSiguiente();
            }
        }
    }
    datos.close();
    ofstream miArchivo("datosIp.txt");
    NodoT<Ip* > * act = ListaIpAccesos -> getHead();
    while(act){
        miArchivo << "Ip: " << act -> getDato() -> getNum_Ip() << ", #Accesos: "<< act -> getDato() -> getNum_Accesos() << endl;
        act = act -> getSiguiente();
    }
    miArchivo.close();
    
    ListaSimple<Acceso *> * NodosAcceso = new ListaSimple< Acceso *>();
    NodoT<Ip *> * nodoIp=ListaIpAccesos->getHead();
        while(nodoIp){
            int acceso = nodoIp -> getDato() ->getNum_Accesos();
            NodoT<Acceso *> * nodoAcceso = NodosAcceso -> getHead();
            NodoT<Acceso *> * agregar = nullptr; 
           if(!nodoAcceso ){
                    Acceso * acce = new Acceso(acceso);
                    acce->AgregarIp(nodoIp -> getDato()->getNum_Ip());
                    NodosAcceso->agregarFin(acce);
            }
            else{
                while(nodoAcceso){
                    if(nodoAcceso->getDato() -> getNumAccesos() == acceso)
                        agregar = nodoAcceso;
                    nodoAcceso = nodoAcceso->getSiguiente();
                }
                if(agregar)
                    agregar->getDato()->AgregarIp(nodoIp -> getDato()->getNum_Ip());
                else{
                    Acceso * acce = new Acceso(acceso);
                    acce->AgregarIp(nodoIp -> getDato()->getNum_Ip());
                    NodosAcceso->agregarFin(acce);
                }
            }    
            nodoIp=nodoIp->getSiguiente();
        }
    
    
    BST<int> * arbol = new BST<int>();
    NodoT<Acceso *> * actualAcceso = NodosAcceso -> getHead();
    while(actualAcceso){
        arbol -> agregarNodo(actualAcceso -> getDato() -> getNumAccesos());
        //cout<<"Se agregó: "<< actualAcceso -> getDato() -> getNumAccesos() << " al arbol"<<endl;
        actualAcceso = actualAcceso -> getSiguiente();
    }
    
    int usuario;
    cout <<"Ingrese el numero de recurrencias de una Ip: "<<endl;
    cin >> usuario;
    if(arbol->buscarNodo(usuario)){
        NodoT<Acceso *> * recorrido = NodosAcceso -> getHead();
        while(recorrido){
            if(recorrido->getDato()->getNumAccesos() == usuario)
                recorrido->getDato()->getListaIps()->imprimirLista();
            recorrido = recorrido -> getSiguiente();
        }
    }else
        cout<<"No hay Ips con ese numero de acceso."<<endl;



}
