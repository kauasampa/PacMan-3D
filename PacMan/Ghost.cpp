#include "Ghost.h"
#include "Mapa.h"
#include <stdio.h>
#include <GL/glut.h>
#include <Math.h>


// Destrutor
Ghost::~Ghost(void){}

//Construtor
Ghost::Ghost(double tx, double ty)
{
	tx = x;
	ty = y;
	angulo = 90;
	max_velocidade = velocidade = 0.1;
	cor[0] = 1;
	cor[1] = 0;
	cor[2] = 0;
	morto = false;
	max_temp_editavel = 400;
	estado = false;
	no_respawn = true;
	tempo_respawn = 66;
}


void
Ghost::Reinit(void)
{
	//reinicia o fantasma
	estado = false;
	no_respawn = true;
	angulo = 90;
}

//movimento do fantasma
void
Ghost::Move()
{
	x +=  velocidade*cos(M_PI/180*angulo);
	y +=  velocidade*sin(M_PI/180*angulo);
}


void
Ghost::Update(void)
{
	//retorna 
	if ((int)x == 0 && (int) y == 14 && (!(respawn)))
	{
		angulo=180;
	}
	if (x < 0.1 && (int) y == 14)
	{
		x = 26.9;
		respawn = true;
	}

	if ((int)x == 27 && (int) y == 14 && (!(respawn)))
	{
		angulo=0;
	}
	if (x > 26.9 && (int) y == 14)
	{
		x = 0.1;
		respawn = true;
	}
	if ((int)x == 2 || (int)x == 25)
		respawn = false;

	if (((int) x < 5 || (int) x > 21) && (int) y == 14 && !estado && !morto)
		velocidade = max_velocidade/2;
	else if (!estado && !morto)
		velocidade = max_velocidade;

	//pode ser morto
	if (temp_editavel == 0 && estado && !morto)
	{
		estado = false;
		velocidade = max_velocidade;
	}

	if (estado)
		temp_editavel--;

	//ja na jaula, ele volta a vida muahahahaha
	if (no_respawn && (int) (y+0.9) == 11)
	{
		no_respawn = false;
		angulo = 180;
	}

	if (no_respawn && ((int)x == 13 || (int)x == 14))
	{
		angulo = 270;
	}

	//depois do tempo de respawn chegar a zero, ele sai da jaula
	if (tempo_respawn == 0  && no_respawn)
	{
		//move pra saida
		if (x < 13)
			angulo = 0;
		if (x > 14)
			angulo = 180;
	}

	//diminui o contador de tempo na jaula
	if (tempo_respawn > 0)
		tempo_respawn--;

	//manda o fantasma devorado pra jaula
	if (morto && ((int) x == 13 || (int) (x+0.9) == 14) && ((int)y > 10 && (int) y < 15))
	{
		no_respawn = true;
		angulo = 90;
		if((int) y == 14)
		{
			morto = false;
			velocidade = max_velocidade;
			no_respawn = 66;
			x = 11;
		}
	}
}


bool
Ghost::Catch(double px, double py)
{
	//caso o fantasma toque o pacman
	if (px - x < 0.2 && px - x > -0.2 && py - y < 0.2 && py - y > -0.2)
	{
		return true;
	}
	return false;
}


//quando o pacman devora a bola grande e os fantasmas se tornam devoraveis
void
Ghost::Vulnerable(void)
{
	if (!(estado))//se estado de devoravel for falso
	{
		angulo = ((int)angulo + 180)%360;
		velocidade = max_velocidade/2;//velocidade cai pela metade
	}
	estado = true;//se torna comestivel
	temp_editavel = max_temp_editavel;//seta o tempo devoravel para o maximo possivel
}




//perseguir o pacman
void
Ghost::Chase(double px, double py, bool *open_move)
{
	
	//variavel c recebe um valor se ele pode ser devorado
	int c;
	if (estado)
		c = -1;
	else
		c = 1;

	//muda a direção caso possa ser devorado
	if ((int) angulo == 0 || (int) angulo == 180)
	{
		if ((int)c*py > (int)c*y && open_move[1])
			angulo = 90;

		else if ((int)c*py < (int)c*y && open_move[3])
			angulo = 270;
	} else if ((int) angulo == 90 || (int) angulo == 270)
	{
		if ((int)c*px > (int)c*x && open_move[0])
			angulo = 0;
		else if ((int)c*px < (int)c*x && open_move[2])
			angulo = 180;
	}

	//gera movimento randonico caso o movimento seja livre, ou seja, não eta perseguindo o pacman

	if ((int) angulo == 0 && !open_move[0])
		angulo = 90;
	if ((int) angulo == 90 && !open_move[1])
		angulo = 180;
	if ((int) angulo == 180 && !open_move[2])
		angulo = 270;
	if ((int) angulo == 270 && !open_move[3])
		angulo = 0;
	if ((int) angulo == 0 && !open_move[0])
		angulo = 90;

}

void
Ghost::Draw(void)//desenhar os fantasmas
{
	 int k =(360 - angulo +90) % 360;//AJUSTA ANGULO DE ROTAÇÃO
	 
	if (!estado)
		glColor3f(cor[0],cor[1],cor[2]);
	else
	{
		if (temp_editavel < 150)
			glColor3f((temp_editavel/10)%2,(temp_editavel/10)%2,1);
		if (temp_editavel >= 150)
			glColor3f(0,0,0.5);
	}
	if (morto)
		glColor3f(0,0,0);
			
	//ESFERA PRINCIPAL
	glPushMatrix();
    glTranslatef(x, -y, 0);
    glTranslatef(.5, 0.5, 0);
    glTranslatef((float)Mapa::BOARD_X / -2.0f, (float) Mapa::BOARD_Y / 2.0f, 0.5);
    glRotated(k,0,0,1);//ROTACAO DO PAC
    glutSolidSphere(.5, 5, 5);

    //CILINDRO(PESCOÇO)
    GLUquadric* quadric = gluNewQuadric();
    glTranslatef(0, 0,-0.5);  // Mova para cima em relação ao corpo
    gluCylinder(quadric, .5, .5, .7, 40, 40);

    //ESFERA SUPERIOR(CABEÇA)
    glTranslatef(0, 0, .7);  // Mova para cima em relação ao pescoço
    glutSolidSphere(.5, 40, 40);

    gluDeleteQuadric(quadric);
    
    //OLHOS:
    	glColor3d(0.0f, 0.0f, 0.0f);
   	    // Desenhar o olho esquerdo
 		glTranslatef(-0.2, -0.35, 0.3); // Posição do novo objeto relativa ao corpo
    	glutSolidSphere(0.1, 40, 40);

    	// Desenhar o olho direito
    	glTranslatef(0.4, 0, 0); // Posição relativa ao corpo
    	glutSolidSphere(0.1, 40, 40);			
		glPopMatrix();
    glPopMatrix();
/*   	    // Desenhar o olho esquerdo
 		glTranslatef(-0.2, -0.35, 0.3); // Posição do novo objeto relativa ao corpo
    	glutSolidSphere(0.1, 40, 40);

    	// Desenhar o olho direito
    	glTranslatef(0.4, 0, 0); // Posição relativa ao corpo
    	glutSolidSphere(0.1, 40, 40);			
		glPopMatrix();
*/

}