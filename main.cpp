#include <iostream>
#include <windows.h>
#include <time.h>
#include "Robot.h"
#include "Utils.h"
#include "GameFunctions.h"

using namespace std;

int main()
{
    GameFunctions funcaoJogo;
    Ponto bola = {23, 55};
    Estado e1 = {48, 56, 36};
    Estado e2 = {19, 40, 108};
    Estado e3 = {6, 29, 222};
    funcaoJogo.robos[0].setPosicao(e1);
    funcaoJogo.robos[0].setMeta(bola);
    funcaoJogo.robos[0].setAlfa();
    funcaoJogo.robos[1].setPosicao(e2);
    funcaoJogo.robos[1].setMeta(bola);
    funcaoJogo.robos[1].setAlfa();
    funcaoJogo.robos[2].setPosicao(e3);
    funcaoJogo.robos[2].setMeta(funcaoJogo.getCentroidDef());
    funcaoJogo.robos[2].setAlfa();
    bool flag = true;
    while(flag)
    {   /*
        for(int i = 0; i < NUM_ROBOS; i++)
            if(robos[i].getComunicacao() == false)
                flag = false; */
        if(funcaoJogo.metaZagueiro(0, bola)||funcaoJogo.metaZagueiro(1, bola)||funcaoJogo.metaGoleiro(2, bola))
            break; // chegou a bola
        cout << "Bola (x, y): (" << bola.x << ", " << bola.y << ")\n\n";

        Sleep(TEMPO);
        // nanosleep(TEMPO*1000);
    }
    return 0;
}
