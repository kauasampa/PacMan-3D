#include "PACMAN.h"
#include "Mapa.h"
#include <stdio.h>
#include <GL/glut.h>
#include <Math.h>

//Lembrar que Mapa é x31 por y28
//Quanto menor o y, mais o personagem "Sobe"
//Quanto menor o x, mais o personagem vai p/ esquerda
PACMAN::~PACMAN(void) {}


PACMAN::PACMAN(double tx, double ty)//Criação do player
{
	vidas = 3;
	tx = x;
	ty = y;
	angulo = 90;
	velocidade = 0.1;
	animacao = false;
}


void
PACMAN::Reinit(void)//Resetar o PacMan(posição inicial do PACMAN)
{
	x = 13.5;//13.5
	y = 23;//23
	angulo = 90;// No momento, nao muda nada
	animacao = false;//Se ele é animado(movimentado) no Inicio
}


void
PACMAN::Move()//Como é feito o movimento do PacMan
{
	x +=  velocidade * cos(M_PI / 180 * angulo);
	//x é acrescido da velocidade multiplicada pela conversao de graus para rad
	y +=  velocidade * sin(M_PI / 180 * angulo);
}


void
PACMAN::Draw(void)//Desenho do personagem é feito aqui
{
 int k =(360 - angulo +90) % 360;//AJUSTA ANGULO DE ROTAÇÃO
    //Desenhar Corpo
	glColor3d(1, 1, 0);
	glPushMatrix();
	glTranslatef(x, -y, 0);
	glTranslatef(0.5, 0.6, 0);//0.5,0.6,0//Define posicao mesmo parado(x(maior,direita),y(maior,cima),z(maior,perto)
	glTranslatef((float)Mapa::BOARD_X / -2.0f, (float) Mapa::BOARD_Y / 2.0f, 0.5);//Movimento pelo Mapa
    glRotated(k,0,0,1);//ROTACAO DO PAC
	glutSolidSphere(0.5, 40, 40);//0.5/20/20
 
 	 	 glColor3d(0.0f, 0.0f, 0.0f);
   	    // Desenhar o olho esquerdo
 		glTranslatef(-0.2, -0.35, 0.3); // Posição do novo objeto relativa ao corpo
    	glutSolidSphere(0.1, 40, 40);

    	// Desenhar o olho direito
    	glTranslatef(0.4, 0, 0); // Posição relativa ao corpo
    	glutSolidSphere(0.1, 40, 40);			
		glPopMatrix();

	
	for (int i = 0; i < vidas - 1; i++)
	{
		    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    		const double a = t*90.0;
        glColor3d(1,1,0);
		glPushMatrix();
		glTranslatef((float)Mapa::BOARD_X / -2.0f + i * 2, (float) Mapa::BOARD_Y / 2.0f + 3, 1);
		glRotated(a,0,0,1);//ROTACAO DAS VIDAS
		glutSolidSphere(0.5, 20, 20);
        glColor3d(0.0f, 0.0f, 0.0f);
   	    // Desenhar o olho esquerdo
 		glTranslatef(-0.2, -0.35, 0.3); // Posição do novo objeto relativa ao corpo
    	glutSolidSphere(0.1, 40, 40);

    	// Desenhar o olho direito
    	glTranslatef(0.4, 0, 0); // Posição relativa ao corpo
    	glutSolidSphere(0.1, 40, 40);			
		glPopMatrix();
	}
	
	

}
