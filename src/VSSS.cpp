#include <iostream>
#include <math.h>
#include <string>
#include "VSSS.h"
#include "Robot.h"

using namespace std;

VSSS::VSSS()
{
    cout << "Criando objeto VSSS" << endl;
    posicaoDaBola.x=0;
    posicaoDaBola.y=0;
    posicaoDaBola.theta=0;
    comunicacao=0;
    funcao=0;
    v.Esquerda=0;
    v.Direita=0;
    alfa=0;
}

VSSS::~VSSS()
{
    cout << "Destruindo objeto VSSS" << endl;
}

void VSSS::getCominicacao()
{
    cout << "Comunicacao: ";
    if(comunicacao)
        cout << "conectada." << endl;
    else
        cout << "desconectada." << endl;
}
string VSSS::getFuncao()
{
    if(funcao == 'A')
        return "Atacante";
    else if(funcao == 'Z')
        return "Zagueiro";
    else if(funcao == 'G')
        return "Goleiro";
    else
        return "Invalida";
}

void VSSS::setPosicaoDaBola(Estado b)
{
    posicaoDaBola.x=b.x;
    posicaoDaBola.y=b.y;
}

void VSSS::setAlfa(Estado r, Estado b)//calcula o angulo entre o robo e a bola
{
    alfa = round((atan((b.y-r.y)/(b.x-r.x)))*180/3.14159);
}

void VSSS::girar(bool j)//j=true girar no sentido anti-horário ou j=false para girar no sentido horário
{
    velRoda g;
    if(j)
    {
        g.Direita=100;
        g.Esquerda=-100;
        setVelRoda(g);
        cout<<"Robo girando no sentido anti-horario."<<endl;
        cout<<"Velocidade roda esquerda :"<<getVelRoda().Esquerda<<"         Velocidade roda direita :"<<getVelRoda().Direita<<endl;
    }
    else
    {
        g.Direita=-100;
        g.Esquerda=100;
        setVelRoda(g);
        cout<<"Robo girando no sentido horario."<<endl;
        cout<<"Velocidade roda esquerda:"<<getVelRoda().Esquerda<<"         Velocidade roda direita:"<<getVelRoda().Direita<<endl;
    }
}

void VSSS::ajustarPosicao(Estado orientacao,Estado e)
{
    for(int i=0; orientacao.theta!=alfa; i++)
    {

        if(alfa>orientacao.theta)
        {
            girar(true); //sentido anti-horario
            orientacao.theta++;
        }
        else
        {
            girar(false); //sentido horario
            orientacao.theta--;
        }
        cout<<"Novo theta: "<<orientacao.theta<<endl;
    }
    e.theta=orientacao.theta;
    setOrientacao(e);//atualiza a orientacao depois do ajuste
    cout<<"Robo esta na direcao da bola."<<endl;
}

void VSSS::andarAteABola(Estado r,Estado b)
{
    float x=sqrt(((b.x-r.x)*(b.x-r.x))+((b.y-r.y)*(b.y-r.y)));
    int d=round(x);
    for(int i=0; d!=0; i++)
    {
        cout<<"O robo esta a "<<d<<" unidades da bola."<<endl;
        velRoda v;
        v.Direita=100;
        v.Esquerda=100;
        locomocao(v);
        d--;
    }
    Estado u;
    u.x=b.x;
    u.y=b.y;
    u.theta=r.theta;
    setOrientacao(u);//atualiza a posição depois de ter andado até a bola

    cout<<"O robo chegou a bola!"<<endl;
}

void VSSS::curvaAteABola(string sentido)
{
    double raio=(sqrt((pow((orientacao.x-posicaoDaBola.x),2)+pow((orientacao.y-posicaoDaBola.y),2)))/2);
    //formula da distancia entre dois pontos
    double d=2*raio; //distancia=diametro do circulo que o robo vai percorrer
    for(int i = 0; d != 0; i++)
    {
        if(sentido == "horario")
        {
            girar(false); //sentido horario
            orientacao.theta--;
        }
        else
        {
            /*
            girar(true); //sentido anti-horario
            orientacao.theta++;
            */
            cout << "Erro em void vsss::curvaAteABola(string sentido);" << endl;
            //loop infinito
        }
        cout << "Novo theta: " << orientacao.theta << endl;
        velRoda v;
        v.Direita=100;
        v.Esquerda=100;
        locomocao(v);
        d=sqrt(2*raio*raio*(1-cos(abs(orientacao.theta-alfa+90)*3.14159/180)));
        //lei dos cossenos, abs(orientacao.theta-alfa+90)*3.14159/180: angulo do robo em relacao ao circulo
        cout<<"O robo esta a "<<d<<" unidades da bola."<<endl;
    }
    cout<<"O robo chegou a bola!"<<endl;
    if(orientacao.theta < 0)
    {
        orientacao.theta+=360;
    }
}
