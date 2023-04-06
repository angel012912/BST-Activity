/*
Author: Jose Angel Garcia Gomez
Date: 11/2021
Description: Program that defines the BST data structure as a Class
*/

#include "NodoBST.hpp"
#include "Fila.hpp"


template <typename T>
class BST{
    NodoBST<T> * raiz;
    int numNodos;
    public:
        //getters y setters
        NodoBST<T> * getRaiz(){return this->raiz;}
        void setRaiz(NodoBST<T> * raiz){this->raiz=raiz;}
        int getNumNodos(){return this->numNodos;}
        void setNumNodos(int numNodos){this->numNodos=numNodos;} 
        //constructor
        BST(){
            this->raiz=nullptr;
            this->numNodos=0;
        }
        ~BST(){

        }

        void agregarNodo(T dato){
            NodoBST<T> * actual= this->raiz;
            NodoBST<T> * padre;
            if(this->raiz){//Arbol no vacio
                if(this->buscarNodo(dato)) //Nodo encontrado
                    cout<<"Nodo existente"<<endl;                
                else{ //Nodo inexistente, 
                    //Encontrar al nodo padre
                    while(actual){
                        padre=actual;
                        //Relacion de orden de los nodos
                        if(dato<actual->getDato())
                            actual=actual->getIzq();
                        else
                            actual=actual->getDer();
                    }
                    //Colocar el nuevo nodo
                    padre->getDato()>dato?padre->setIzq(new NodoBST<T>(padre,dato, (padre->getNivel()+1))):padre->setDer(new NodoBST<T>(padre,dato,(padre->getNivel()+1)));
                    this->numNodos++;
                }
            }else{//Arbol vacio
                this->raiz = new NodoBST<T>(nullptr,dato, 0);
                this->numNodos++;
            }
            return; //opcional
        }
        NodoBST<T> * buscarNodo(T dato){
            //Primer paso crear el apuntador a nodo raiz
            NodoBST<T> * actual = this->raiz;
            while(actual){
                //Si el nodo actual es el valor que busco
                if(actual->getDato()==dato)
                    return actual;
                else//cond?opc_verdadera:opc_falsa
                    actual=actual->getDato()>dato?actual->getIzq():actual->getDer();
            }
            return nullptr; //return actual;
        }

        void imprimirPreOrder(){
            NodoBST<T>::recorridoPreOrder(this->raiz);
            cout<<endl;
        }

        void imprimirInOrder(){
            NodoBST<T>::recorridoInOrder(this->raiz);
            cout<<endl;
        }
        void imprimirPostOrder(){
            NodoBST<T>::recorridoPostOrder(this->raiz);
            cout<<endl;
        }

        void eliminarNodo(T dato){
            NodoBST<T> * eliminar = this->buscarNodo(dato);
            NodoBST<T> * padre = nullptr;
            if(eliminar){ //El nodo que se quiere eliminar si existe
                //Establezco el nodo padre
                padre=eliminar->getPadre();
                if(!eliminar->getIzq()&&!eliminar->getDer())//Caso 1 eliminar nodo hoja
                {
                    //Actualizar la referencia del padre
                    if(!padre) //this->numNodos==1 si es nodo raiz
                        this->raiz=nullptr;
                    else if(padre->getDato()>eliminar->getDato()) //Nodo hoja es hijo izq
                        padre->setIzq(nullptr);
                    else //Nodo hoja es hijo derecho
                        padre->setDer(nullptr);
                    delete eliminar;
                }
                //Caso nodo con un hijo
                else if(eliminar->getIzq()&&!eliminar->getDer())//Caso 2.1 eliminar un nodo con un hijo izq
                {
                    //Actualizar los apuntadores
                    if (!padre) //El nodo es raiz con hijo izquierdo
                        this->raiz = eliminar->getIzq(); 
                    else if(padre->getDato()>eliminar->getDato())//El nodo es el hijo izquierdo del padre   
                        padre->setIzq(eliminar->getIzq()); //izq izq
                    else
                        padre->setDer(eliminar->getIzq()); //der izq
                    eliminar->getIzq()->setPadre(padre);
                    delete eliminar;
                }
                else if(!eliminar->getIzq()&&eliminar->getDer()){//Caso 2.2 eliminar un nodo con un hijo der
                    //Actualizar los apuntadores
                    if (!padre) //Nodo raiz con hijo derecho
                        this->raiz = eliminar->getDer();
                    else if(padre->getDato()>eliminar->getDato())//El nodo es el hijo izquierdo del padre   
                        padre->setIzq(eliminar->getDer()); //izq der
                    else
                        padre->setDer(eliminar->getDer()); //der der
                    eliminar->getDer()->setPadre(padre);
                    delete eliminar;
                }//Caso 3 eliminar un nodo con dos hijos (sucesor: derecha-todo izq) 
                else{
                    NodoBST<T> * sucesor = NodoBST<T>::valorMenor(eliminar->getDer());
                    //NodoBST<T> * predesecor = NodoBST<T>::valorMayor(eliminar->getIzq());
                    eliminar->setDato(sucesor->getDato());
                    if(sucesor->getPadre()->getDato()>sucesor->getDato())//Sucesor es hijo izq
                        if(sucesor->getDer()){//El sucesor tiene un hijo derecho
                            sucesor->getPadre()->setIzq(sucesor->getDer());
                            sucesor->getDer()->setPadre(sucesor->getPadre());
                        }
                        else //El sucesor no tiene hijos
                            sucesor->getPadre()->setIzq(nullptr);
                    else //Sucesor es hijo der
                        if(sucesor->getDer()){//El sucesor tiene un hijo derecho
                            sucesor->getPadre()->setDer(sucesor->getDer());
                            sucesor->getDer()->setPadre(sucesor->getPadre());
                        }
                        else //El sucesor no tiene hijos
                            sucesor->getPadre()->setDer(nullptr);
                    delete sucesor;
                }
                this->numNodos--;
            }else
                cout<<"Valor inexistente"<<endl;
        }

        //Imprimir dependiendo de la entrada
        void visit(int op){ 
            //Se evalúa la opcion ingresada.
            if(op == 1){ //Si ingresa la opcion 1 llama a la funcion de clase "imprimirPreOrder".
                this->imprimirPreOrder();
            }
            else if(op == 2){ //Si ingresa la opcion 2 llama a la funcion de clase "imprimirPostOrder".
                this->imprimirPostOrder();
            }
            else if(op == 3){ //Si ingresa la opcion 3 llama a la funcion de clase "imprimirInOrder". 
                this->recorridoLevelByLevel();
            }
            else{ // Si no entra en ninguna condicion anterior entonces manda un mensaje de error. 
                cout<<"Opcion invalida"<<endl;
            }
        }

        //Regresar el antecesor de un valor dentro del arbol
        NodoBST<T> * antecesor(T dato){
            //Buscar el nodo en el arbol BST
            NodoBST<T> * nodoUsuario = this->buscarNodo(dato);
            //Evaluar si el nodo existe en el Arbol
            if(nodoUsuario){
                //Para obtener el antecesor del valor ingresado se hace uso de la funcion de instancia de NodoBST llamada "valorMenor()"
                NodoBST<T> * antecesor = NodoBST<T>::valorMayor(nodoUsuario->getIzq());
                //Regresar el nodo encontrado
                return antecesor;
            }else
                //Si no enuentra el valor dentro del arbol BST entonces regresa un apuntador nulo.
                return nullptr;
        }
        //Recorrido por nivel
        void recorridoLevelByLevel(){
            NodoBST<T> * actual = this-> raiz;
            if(actual){
                Fila<NodoBST<T> *> * fila = new Fila<NodoBST<T> *>();
                fila->push(actual);
                while(fila->front()){
                    NodoT<NodoBST<T> * > * impr = fila->pop();
                    cout<<impr->getDato()->getDato()<<" ";
                    if(impr->getDato()->getIzq())
                        fila->push(impr->getDato()->getIzq());
                    if(impr->getDato()->getDer())
                        fila->push(impr->getDato()->getDer());
                }
                cout<<endl;
            }else
                cout<<"El BST está vacío"<<endl;
        }
        int whatlevelamI(T dato){
            NodoBST<T> * busqueda = this->buscarNodo(dato);
            if(busqueda)
                return busqueda->getNivel();
            else
                return -1;
        }

        static int height(BST<T> * arbol){
            NodoBST<T> * actual = arbol->getRaiz();
            if(actual){
                Fila<NodoBST<T> *> * fila = new Fila<NodoBST<T> *>();
                fila->push(actual);
                int nivel;
                while(fila->front()){
                    NodoT<NodoBST<T> * > * impr = fila->pop();
                    nivel = impr->getDato()->getNivel();
                    if(impr->getDato()->getIzq())
                        fila->push(impr->getDato()->getIzq());
                    if(impr->getDato()->getDer())
                        fila->push(impr->getDato()->getDer());
                }
                return nivel;
            }else
                return -1;
        }
};