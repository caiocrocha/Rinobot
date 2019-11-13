#include <iostream>
#include "Robot.h"

using namespace std;

Robot::Robot()
{
    cout << "Criando objeto Robot" << endl;
    numeroMotores=0;
    numeroSensores=0;
    bateria=0;
    orientacao.x=0;
    orientacao.y=0;
    orientacao.theta=0;
}

Robot::~Robot()
{
    cout << "Destruindo objeto Robot" << endl;
}

void Robot::locomocao(velRoda v)
{
    if((v.Esquerda>0)&&(v.Direita>0))
        cout << "Robo andando para frente." << endl;
    else if((v.Esquerda<0)&&(v.Direita<0))
        cout << "Robo andando para tras." << endl;
    if(v.Esquerda>v.Direita)
        cout << "Robo fazendo curva pra direita." << endl;
    else if(v.Esquerda<v.Direita)
        cout << "Robo fazendo curva pra esquerda." << endl;
}
