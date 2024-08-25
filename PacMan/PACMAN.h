#define _PAC_H_

#include <gl/glut.h>

class PACMAN
{
private:
	double velocidade;

public:

	int vidas;//quantidade de vidas sobrando
	int angulo;//Angulo de rotação dele
	double x, y;//??
	bool animacao;//??
	PACMAN(double, double);//construtor(2xdouble serve para posição do player inicial)
	~PACMAN(void);//destrutor
	void Move(); //mover o pacman
	void Reinit();//resetar o pacman
	void Draw(void);//desenhar o pacman
	
	static const double posX,posY,posZ;

};

