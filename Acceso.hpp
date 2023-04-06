/*
Author: Jose Angel Garcia Gomez
Date: 11/2021
Description: Program that defines the class Acceso
*/

#include "ListaSimple.hpp"
#include "Ip.hpp"

class Acceso{
    int num_Accesos;
    ListaSimple<string> * listaIps;
    public:
        Acceso(int num_Accesos){
            this -> num_Accesos = num_Accesos;
            this -> listaIps = new ListaSimple<string>();
        }

        void setNumAccesos(int num_Accesos){this->num_Accesos = num_Accesos;}
        void setListaIps(ListaSimple<string> * listaIps){this -> listaIps = listaIps;}

        int getNumAccesos(){return this->num_Accesos;}
        ListaSimple<string> * getListaIps(){return this->listaIps;}

        void AgregarIp(string DireccionIp){
            this->listaIps->agregarFin(DireccionIp);
        }
};

