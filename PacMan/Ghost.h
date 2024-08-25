#define _GHOST_H_

#include <gl/glut.h>

class Ghost {
  private:

  public:
	
	bool estado;//se pode ser comido ou não
	int max_temp_editavel;//maximo de tempo que ele pode ser comido
	int temp_editavel;//tempo decorrido desde que ele se tornou comivel
	bool morto;//se esta morto ou não
	bool respawn;//manda o fantasma de volta pra jaula
    float cor[3];//vetor que contem as cores dos fantasmas
	double velocidade;//velocidadde do fantasma
	double max_velocidade;//velocidade maxima do fantasma(quando persegue o pac man)
	bool no_respawn;//caso ele esteja dentro da jaula
	int tempo_respawn;//tempo até ele sair da jaula
	int angulo;//angulo de movimento do fantasma
	double x, y;//posição do fantasma
    Ghost(double, double);//construtor do fantasma
    ~Ghost(void);//destrutor do fantasma
	void Move(); //movimento do fantasma
	void Update(void);//atualizar o estado do fantasma
	void Chase(double, double, bool*);//perseguir o pacman
	bool Catch(double, double);//detector de colisão
	void Reinit(void);//reiniciaar os fantasmas
	void Vulnerable(void);//quando o pacman come a fruta grande e os fantasmas podem ser mortos
	void Draw(void);//desenhar fantasmas

};
