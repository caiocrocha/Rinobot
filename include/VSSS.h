#ifndef VSSS_H
#define VSSS_H
#include "Robot.h"
#include <iostream>
#include <string>

class VSSS : public Robot
{
    private:
        Estado posicaoDaBola;
        bool comunicacao;
        char funcao;
        velRoda v;
        int alfa;//angulo da reta que liga o robo e a bola
    public:
        VSSS();
        ~VSSS();
        void setCominicacao(bool c) { comunicacao=c; }; //true para comunicacao conectada e false para comunicacao desconectada
        void setFuncao(char f) { funcao=f; }; //"A" para atacante, "Z" para zagueiro e "G" para goleiro
        void setVelRoda(velRoda vel) { v=vel; };
        void setAlfa(Estado,Estado);
        void getCominicacao();
        std::string getFuncao();
        velRoda getVelRoda() { return v; };
        void setPosicaoDaBola(Estado);
        Estado getPosicaoDaBola() { return posicaoDaBola; };
        int getAlfa() { return alfa; };
        void girar(bool);
        void ajustarPosicao(Estado,Estado);
        void andarAteABola(Estado,Estado);
        void curvaAteABola(std::string);
};

#endif // VSSS_H
