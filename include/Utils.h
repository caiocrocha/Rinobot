#ifndef UTILS_H
#define UTILS_H

#include "Robot.h"

#define COMPRIMENTO 150
#define LARGURA 130

class Utils
{
public:
    Utils();
    ~Utils();
    void imprimeLocomocao(velRoda);
    int getAngulo(Ponto, Ponto);
    float distancia(Ponto, Ponto);
    int distanciaAngular(Estado, int, Ponto);
    bool campoDefesa(Ponto p){ return p.x <= COMPRIMENTO/2; };
};

#endif // UTILS_H
