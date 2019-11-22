#ifndef ROBOT_H
#define ROBOT_H

#define NUM_ROBOS 3
#define VMAX 10 // cm/s
#define TEMPO 200.0 // ms

struct Ponto
{
    float x, y;
};

struct Estado
{
    float x, y;
    int theta;
};

struct velRoda
{
    float esq, dir;
};

class Robot
{
protected:
    int numId;
    Estado posicao;
    Ponto meta;
    int numMotores;
    int numSensores;
    float bateria;
    bool comunicacao;
    velRoda velocidade;
    int alfa; // angulo da reta que liga o robo a bola
    char funcao;

public:
    Robot();
    ~Robot();
    void setNumId(int id){ numId = id; };
    void setMeta(Ponto m){ meta = m; };
    void setPosicao(Estado e){ posicao = e; };
    void setNumMotores(int mo){ numMotores = mo; };
    void setNumSensores(int s){ numSensores = s; };
    void setNivelBateria(float b){ bateria = b; };
    void setCominicacao(bool c){  comunicacao = c; };
    void setVelRoda(velRoda v){ velocidade = v; };
    void setAlfa();
    void setFuncao(char f){ funcao = f; }; // "A" para atacante, "Z" para zagueiro e "G" para goleiro
    int getNumId(int id){ return numId; };
    Ponto getMeta(){ return meta; };
    Estado getPosicao(){ return posicao; };
    int getNumeroMotores(){ return numMotores; };
    int getNumeroSensores(){ return numSensores; };
    int getNivelBateria(){ return bateria; };
    bool getComunicacao(){ return comunicacao; };
    velRoda getVelRoda(){ return velocidade; };
    int getAlfa(){ return alfa; };
    char getFuncao(){ return funcao; };
    void girar(bool);
};

#endif // ROBOT_H
