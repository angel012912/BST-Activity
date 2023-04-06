/*
Author: Jose Angel Garcia Gomez
Date: 11/2021
Description: Program that defines the class NodoBST that will be used in the BST class
*/

#include <iostream>
using namespace std;

template <typename T>
class NodoBST{
    T dato;
    NodoBST<T> * izq;
    NodoBST<T> * der;
    NodoBST<T> * padre;
    int nivel;

    public:
        //getters y setters
         T getDato(){return this->dato;}
        NodoBST<T> * getIzq(){return this->izq;}
        NodoBST<T> * getDer(){return this->der;}
        NodoBST<T> * getPadre(){return this->padre;}
        int getNivel(){return this->nivel;}
        //Métodos set
        void setDato(T dato){this->dato=dato;}
        void setIzq(NodoBST<T> * izq){this->izq=izq;}
        void setDer(NodoBST<T> * der){this->der=der;}
        void setPadre(NodoBST<T> * padre){this->padre=padre;}
        void setNivel(int nivel){this->nivel = nivel;}

        //Constructores
        NodoBST(NodoBST<T> * padre, T dato, int nivel){
            this->izq=nullptr;
            this->der=nullptr;
            this->padre=padre;
            this->dato=dato;
            this->nivel = nivel;
        }
        //Destructor (delete)
        ~NodoBST(){
            cout<<"Destruccion"<<endl;
        }
        //Metodos de clase (no se necesita crear un objeto para utilizarlo)
        static void recorridoInOrder(NodoBST<T> * actual){
            if(actual){
                recorridoInOrder(actual->getIzq());
                cout<<actual->getDato()<<" ";
                recorridoInOrder(actual->getDer());
            }
        }
        static void recorridoPreOrder(NodoBST<T> * actual){
            if(actual){
                cout<<actual->getDato()<<" ";
                recorridoPreOrder(actual->getIzq());
                recorridoPreOrder(actual->getDer());
            }
        }
        static void recorridoPostOrder(NodoBST<T> * actual){
            if(actual){
                recorridoPostOrder(actual->getDer());
                cout<<actual->getDato()<<" ";
                recorridoPostOrder(actual->getIzq());
            }
        }

        static NodoBST<T> * valorMenor(NodoBST<T> * actual){
            if(actual)
                while(actual->getIzq())
                    actual = actual->getIzq();
            return actual;
        }
        static NodoBST<T> * valorMayor(NodoBST<T> * actual){
            if(actual)
                while(actual->getDer())
                    actual = actual ->getDer();
            return actual;
        }
};