#include <iostream>
#include <cmath>
#include "Utils.h"
#include "Robot.h"

using namespace std;

Utils::Utils()
{
    cout << "Criando objeto Utils" << endl;
}

Utils::~Utils()
{
    cout << "Destruindo objeto Utils" << endl;
}

void Utils::imprimeLocomocao(velRoda vel)
{
    if(vel.esq > 0 && vel.dir > 0)
        cout << "Robo andando para frente" << endl;
    else if(vel.esq < 0 && vel.dir < 0)
        cout << "Robo andando para tras" << endl;
    if(vel.esq > vel.dir)
        cout << "Robo fazendo curva para direita" << endl;
    else if(vel.esq < vel.dir)
        cout << "Robo fazendo curva pra esquerda" << endl;
}

float Utils::distancia(Ponto p1, Ponto p2)
{
    return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
    // formula da distancia entre dois pontos
}

int Utils::getAngulo(Ponto p1, Ponto p2)
{
    int angulo = round((atan((p2.y - p1.y)/(p2.x - p1.x)))*180/3.14159);
    //arco tangente do coef angular (delta y/ delta x) da reta
    return (angulo >= 0 ? angulo : angulo + 180);
    //ajuste para o angulo nao ser negativo
}

int Utils::distanciaAngular(Estado e, int alfa, Ponto p)
{
    cout << "\tAlfa: " << alfa << endl;
    cout << "\tTheta: " << e.theta << endl;
    int angulo = alfa - e.theta; //distancia angular
    cout << "\tAngulo: " << angulo << endl;
    if(e.y > p.y)
        angulo += 180;
    else if(angulo < 0)
        angulo += 360;
    //ajustes para o angulo ser limitado
    cout << "\tAngulo corrigido: " << angulo << endl;
    return angulo;
}
