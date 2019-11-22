#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include "Robot.h"
#include "Utils.h"
#include <iostream>

class GameFunctions : public Utils
{
private:
    Ponto centroidAtk;
    Ponto centroidDef;

public:
    Robot robos[NUM_ROBOS];
    GameFunctions();
    ~GameFunctions();
    void setCentroidAtk(Ponto c){ centroidAtk = c; };
    void setCentroidDef(Ponto c){ centroidDef = c; };
    Ponto getCentroidAtk(){ return centroidAtk; };
    Ponto getCentroidDef(){ return centroidDef; };
    bool metaGoleiro(int, Ponto);
    bool metaZagueiro(int, Ponto);
    int seguirAngulo(int);
    bool andarAteMeta(int);
    bool bolaNossa(Ponto); //verifica se ha algum robo do time com posse da bola
    bool dentroDimensoes(Ponto); //verifica se o robo esta dentro de campo
};

#endif // GAMEFUNCTIONS_H
