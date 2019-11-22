#include <iostream>
#include <cmath>
#include "Robot.h"
#include "Utils.h"

using namespace std;

Robot::Robot()
{
    cout << "Criando objeto Robot" << endl;
    numId = -1;
    posicao = {0, 0, 0};
    numMotores = 0;
    numSensores = 0;
    bateria = 0;
    comunicacao = false;
}

Robot::~Robot()
{
    cout << "Destruindo objeto Robot" << endl;
}

void Robot::setAlfa()
{
    alfa = round((atan((meta.y - posicao.y)/(meta.x - posicao.x)))*180/3.14159);
    //alfa (angulo da reta) eh o arco tangente do coef angular da reta
    if(alfa < 0)
        alfa += 180;
}

void Robot::girar(bool sentido)
{
    if(sentido)
    {
        velocidade.dir = 100;
        velocidade.esq = -100;
        cout << "\tRobo girando no sentido anti-horario" << endl;
    }
    else
    {
        velocidade.dir = -100;
        velocidade.esq = 100;
        cout << "\tRobo girando no sentido horario" << endl;
    }
}
