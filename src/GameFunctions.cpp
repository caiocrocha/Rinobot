#include <iostream>
#include <cmath>
#include <cstdlib>
#include "GameFunctions.h"
#include "Robot.h"

using namespace std;

GameFunctions::GameFunctions()
{
    cout << "Criando objeto GameFunctions" << endl;
    centroidAtk = {160, 65};
    centroidDef = {10, 65};
}

GameFunctions::~GameFunctions()
{
    cout << "Destruindo objeto GameFunctions" << endl;
}

bool GameFunctions::dentroDimensoes(Ponto p)
{
    return (p.x >= 0 && p.x <= COMPRIMENTO && p.y >= 0 && p.y <= LARGURA);
}

int GameFunctions::seguirAngulo(int i)
{
    robos[i].setAlfa(); // atualiza a inclinacao da reta
    Estado e = robos[i].getPosicao();
    int angulo = distanciaAngular(e, robos[i].getAlfa(), robos[i].getMeta());
    if(angulo > 180 && angulo < 355) // terceiro e quarto quadrantes
    {
        robos[i].girar(true); // sentido anti-horario
        angulo--;
        e.theta--;
        cout << "\tNovo angulo: " << angulo << endl;
    }
    else if(angulo <= 180 && angulo > 5) // primeiro e segundo quadrantes
    {
        robos[i].girar(false); // sentido horario
        angulo++;
        e.theta++;
        cout << "\tNovo angulo: " << angulo << endl;
    }
    else
    {
        cout << "\tO robo esta na direcao da bola" << endl;
        cout << "\tAngulo: " << angulo << endl;
    }
    if(e.theta >= 360)
        e.theta = 0;
    else if(e.theta < 0)
        e.theta += 360;
    // condicoes acima limitam o angulo entre 0 e 360 graus
    robos[i].setPosicao(e);
    cout << "\tNovo theta: " << robos[i].getPosicao().theta << endl;
    // atualiza o estado do robo
    return angulo;
}

bool GameFunctions::andarAteMeta(int i)
{
    Ponto coord_robo = {robos[i].getPosicao().x, robos[i].getPosicao().y};
    float dist = distancia(coord_robo, robos[i].getMeta()); // distancia entre o robo e a meta
    cout << "Posicao do robo " << i << " (x, y, theta): (" << robos[i].getPosicao().x << ", "
         << robos[i].getPosicao().y << ", " << robos[i].getPosicao().theta << ")" << endl;
    cout << "\tDistancia da meta (cm): " << dist << endl;
    if(dist < 2.5)
    {
        cout << "\tO robo <<" << i << ">> chegou a meta" << endl;
        return true; // robo esta dentro do alcance para chutar
    }
    else
    {
        int angulo = seguirAngulo(i);
        if(angulo > 90 && angulo < 270) // segundo e terceiro quadrantes
        {
            velRoda v = {-100, -100};
            robos[i].setVelRoda(v);
            cout << "\tRobo andando para tras" << endl;
        }
        else // primeiro e quarto quadrantes
        {
            velRoda v = {100, 100};
            robos[i].setVelRoda(v);
            cout << "\tRobo andando para frente" << endl;
        }
        float delta_s = (robos[i].getVelRoda().dir/100)*VMAX*TEMPO/1000;
        // delta s (em cm) eh igual a velocidade (em porcentagem passa para cm/s) x tempo (em ms passa para segundos)
        Estado e = robos[i].getPosicao();
        Ponto p = robos[i].getMeta();
        if(e.x < p.x && e.y < p.y) // primeiro quadrante do circulo trigonometrico: sen e cos positivos
        {
            e.x += abs(delta_s*cos(angulo*3.14159/180));
            e.y += abs(delta_s*sin(angulo*3.14159/180));
            // como avancou no eixo x e no eixo y, acumula o delta x e o delta y
        }
        else if(e.x > p.x && e.y > p.y) // segundo quadrante do circulo trigonometrico: sen positivo e cos negativo
        {
            e.x += -abs(delta_s*cos(angulo*3.14159/180));
            e.y += -abs(delta_s*sin(angulo*3.14159/180));
            // como regrediu no eixo x e no eixo y, subtrai o delta x e o delta y
        }
        else if(e.x < p.x && e.y > p.y) //terceiro quadrante do circulo trigonometrico: sen e cos negativos
        {
            e.x += abs(delta_s*cos(angulo*3.14159/180));
            e.y += -abs(delta_s*sin(angulo*3.14159/180));
            // como regrediu no eixo y, subtrai o delta y
        }
        else // quarto quadrante do circulo trigonometrico: sen negativo e cos positivo
        {
            e.x += -abs(delta_s*cos(angulo*3.14159/180));
            // como regrediu no eixo x, subtrai o delta x
            e.y += abs(delta_s*sin(angulo*3.14159/180));
        }
        robos[i].setPosicao(e); // atualiza a posicao do robo
    }
    return false; // ainda nao chegou a bola
}

bool GameFunctions::metaZagueiro(int i, Ponto bola)
{
    Ponto p = {robos[i].getPosicao().x, robos[i].getPosicao().y};
    cout << "Robo " << i << ": zagueiro" << endl;
    if(dentroDimensoes(p)) // se o robo estiver dentro de campo
    {
        bool nossa = andarAteMeta(i);
        bool defesa = campoDefesa(bola);
        if(defesa && nossa)
        {
            cout << "Meta: centroidDef"<< endl;
            robos[i].setMeta(centroidDef);
            cout << "\n\t\tBOLA NOSSA\n\n";
        }
        else if(defesa && !nossa)
        {
            cout << "Meta: bola" << endl;
            robos[i].setMeta(bola);
            cout << "\n\t\tBOLA DELES\n\n";
        }
        else
        {
            cout << "Meta: meio de campo" << endl;
            Ponto m = {COMPRIMENTO/2, LARGURA/2};
            robos[i].setMeta(m);
            cout << "\n\t\tBOLA NO ATAQUE\n\n";
        }
        return nossa;
    }
    else
    {
        cout << "Robo fora de campo" << endl;
        exit(1);
    }
}

bool GameFunctions::metaGoleiro(int i, Ponto bola)
{
    Ponto p = {robos[i].getPosicao().x, robos[i].getPosicao().y};
    cout << "Robo " << i << ": goleiro" << endl;
    if(dentroDimensoes(p)) // se o robo estiver dentro de campo
    {
        if(bola.x <= 10 && (bola.y >= 50 || bola.y <= 80))
        {
            cout << "Meta: bloquear a bola" << endl;
            robos[i].setMeta(bola);
        }
        else
        {
            cout << "Meta: guardar o gol" << endl;
            Ponto m = {2.5, 2.5};
            robos[i].setMeta(m);
        }
        return andarAteMeta(i);
    }
    else
    {
        cout << "Robo fora de campo" << endl;
        exit(2);
    }
}

bool GameFunctions::bolaNossa(Ponto bola)
{
    bool retorno = false;
    for(int i = 0; i < NUM_ROBOS; i++)
    {
        Ponto p = {robos[i].getPosicao().x, robos[i].getPosicao().y};
        if(distancia(p, bola) < 2.5)
            retorno = true;
    }
    return retorno;
}
