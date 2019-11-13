#ifndef ROBOT_H
#define ROBOT_H

struct Estado
{
  float x,y;
  int theta;
};

struct velRoda
{
    float Esquerda, Direita;
};

class Robot
{
  private:
    int numeroMotores;
    int numeroSensores;
    float bateria;
  protected:
    Estado orientacao;
  public:
    Robot();
    ~Robot();
    int getNumeroMotores() { return numeroMotores; };
    int getNumeroSensores() { return numeroSensores; };
    int getNivelBateria() { return bateria; };
    Estado getOrientacao() { return orientacao; };
    void setOrientacao(Estado e) { orientacao=e; };
    void setNivelBateria(float b) { bateria=b; };
    void setNumeroMotores(int m) { numeroMotores=m; };
    void setNumeroSensores(int s) { numeroSensores=s; };
    void locomocao(velRoda);
};

#endif // ROBOT_H
