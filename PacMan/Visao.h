#define _Visao_H_

#include <gl/glut.h>

class Visao {
  private:
  public:
    Visao(float);
    ~Visao(void);

	void Set_position(float, float,double,int);//seta a posição da Visao
};

