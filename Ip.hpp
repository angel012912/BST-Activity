/*
Author: Jose Angel Garcia Gomez
Date: 11/2021
Description: Program that defines the class Ip
*/

#include <iostream>
#include <string>

class Ip{
    string num_Ip;
    int num_accesos;
    public:
        Ip(string num_Ip){
            this->num_Ip = num_Ip;
            this->num_accesos = 1;
        }
        void setNum_Ip(string num_Ip){ this-> num_Ip = num_Ip;}
        void setNum_Accesos(int num_accesos){ this->num_accesos = num_accesos;}

        string getNum_Ip(){return this-> num_Ip;}
        int getNum_Accesos(){return this-> num_accesos;} 

        void agregarAcceso(){this->num_accesos++;}
};