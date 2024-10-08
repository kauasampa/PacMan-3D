#include "Mapa.h"
#include <stdio.h>
#include <GL/glut.h>

const int Mapa::BOARD_X = 31;
const int Mapa::BOARD_Y = 28;
//cenario classico pacman
int board_array[Mapa::BOARD_X][Mapa::BOARD_Y] = 
	   {{8,5,5,5,5,5,5,5,5,5,5,5,5,1,1,5,5,5,5,5,5,5,5,5,5,5,5,7},
		{6,0,0,0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0,0,0,0,0,6},		
		{6,0,8,1,1,7,0,8,1,1,1,7,0,2,4,0,8,1,1,1,7,0,8,1,1,7,0,6},		
		{6,0,2,11,11,4,0,2,11,11,11,4,0,2,4,0,2,11,11,11,4,0,2,11,11,4,0,6},		
		{6,0,9,3,3,10, 0,9,3,3,3,10,0,9,10,0,9,3,3,3,10,0,9,3,3,10,0,6},		
		{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},		
		{6,0,8,1,1,7,0,8,7,0,8,1,1,1,1,1,1,7,0,8,7,0,8,1,1,7,0,6},		
		{6,0,9,3,3,10,0,2,4,0,9,3,3,11,11,3,3,10,0,2,4,0,9,3,3,10,0,6},		
		{6,0,0,0,0,0,0,2,4,0,0,0,0,2,4,0,0,0,0,2,4,0,0,0,0,0,0,6},		
		{9,5,5,5,5,7,0,2,11,1,1,7,0,2,4,0,8,1,1,11,4,0,8,5,5,5,5,10},		
		{0,0,0,0,0,6,0,2,11,3,3,10,0,9,10,0,9,3,3,11,4,0,6,0,0,0,0,0},		
		{0,0,0,0,0,6,0,2,4,0,0,0,0,0,0,0,0,0,0,2,4,0,6,0,0,0,0,0},		
		{0,0,0,0,0,6,0,2,4,0,8,5,5,1,1,5,5,7,0,2,4,0,6,0,0,0,0,0},		
		{5,5,5,5,5,10,0,9,10,0,6,0,0,0,0,0,0,6,0,9,10,0,9,5,5,5,5,5},		
		{0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0},		
		{5,5,5,5,5,7,0,8,7,0,6,0,0,0,0,0,0,6,0,8,7,0,8,5,5,5,5,5},		
		{0,0,0,0,0,6,0,2,4,0,9,5,5,5,5,5,5,10,0,2,4,0,6,0,0,0,0,0},		
		{0,0,0,0,0,6,0,2,4,0,0,0,0,0,0,0,0,0,0,2,4,0,6,0,0,0,0,0},		
		{0,0,0,0,0,6,0,2,4,0,8,1,1,1,1,1,1,7,0,2,4,0,6,0,0,0,0,0},		
		{8,5,5,5,5,10,0,9,10,0,9,3,3,11,11,3,3,10,0,9,10,0,9,5,5,5,5,7},		
		{6,0,0,0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0,0,0,0,0,6},		
		{6,0,8,1,1,7,0,8,1,1,1,7,0,2,4,0,8,1,1,1,7,0,8,1,1,7,0,6},		
		{6,0,9,3,11,4,0,9,3,3,3,10,0,9,10,0,9,3,3,3,10,0,2,11,3,10,0,6},		
		{6,0,0,0,2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,6},		
		{2,1,7,0,2,4,0,8,7,0,8,1,1,1,1,1,1,7,0,8,7,0,2,4,0,8,1,4},		
		{2,3,10,0,9,10,0,2,4,0,9,3,3,11,11,3,3,10,0,2,4,0,9,10,0,9,3,4},		
		{6,0,0,0,0,0,0,2,4,0,0,0,0,2,4,0,0,0,0,2,4,0,0,0,0,0,0,6},		
		{6,0,8,1,1,1,1,11,11,1,1,7,0,2,4,0,8,1,1,11,11,1,1,1,1,7,0,6},		
		{6,0,9,3,3,3,3,3,3,3,3,10,0,9,10,0,9,3,3,3,3,3,3,3,3,10,0,6},		
		{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},		
		{9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,10}};


int pebble_array[Mapa::BOARD_X][Mapa::BOARD_Y] = 
	   {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
	{0,3,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,3,0},
	{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
	{0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
	{0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
	{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
	{0,3,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,3,0},
	{0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
	{0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
	{0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
	{0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
	{0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};





// Destrutor
Mapa::~Mapa(void){}

//Construtor
Mapa::Mapa(void)
{
	//restaurar cenario
	tp_restore();
	//cria as diferentes possiveis celulas
	create_list_lib();
}

//reseta o array de bolinhas
void Mapa::tp_restore(void)
{
	for (int i = 0; i < BOARD_X; i++)
	{
		for (int j = 0; j < BOARD_Y; j++)
		{
			tp_array[i][j] = pebble_array[i][j];
		}
	}
	pebbles_left = 244;//Quantidade de "graos comestiveis"
}


void Mapa::create_list_lib(void)
{
    list[1] = glGenLists(1);
    glNewList(list[1], GL_COMPILE);
	//muro norte
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 1.0f);
	glEnd();
	glEndList();

    list[2] = glGenLists(1);
    glNewList(list[2], GL_COMPILE);
	glBegin(GL_QUADS);
	//muro norte
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 1.0f);

	//muro sul
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glEndList();

    list[3] = glGenLists(1);
    glNewList(list[3], GL_COMPILE);
	glBegin(GL_QUADS);
	//muro norte
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 1.0f);

	//muro leste
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();
	glEndList();

    list[4] = glGenLists(1);
    glNewList(list[4], GL_COMPILE);
	glBegin(GL_QUADS);
	//muro superior
		glNormal3f(0.0f, 0.0f, 1.0f);
	    glVertex3f(1, 1, 1.0);
	    glVertex3f(0, 1, 1.0);
	    glVertex3f(0, 0, 1.0);
	    glVertex3f(1, 0, 1.0);
	glEnd();
	glEndList();
}


void
Mapa::Draw(void)
{
	glColor3f(0,0.7,0);//////////////////////////////////////////////////////////////////
	//divide a tela ao meio para evitar problemas de desenho
	for (int i = 0; i < BOARD_X; i++)
	{
		for (int j = 0; j < BOARD_Y/2; j++)
		{
			glColor3f(0,0.7,0);//////////////////////////////////////////////////////////Ate aqui, muda metade do mapa
			int call_this = 0;
			glPushMatrix();

			glTranslatef(-(float) BOARD_X / 2.0f,-(float) BOARD_Y / 2.0f, 0);
			glTranslatef(j, BOARD_Y - i,0);
			glPushMatrix();
			glTranslatef(0.5,0.5,0);
			switch (board_array[i][j])
			{
			case 4:
				glRotatef(90.0,0,0,1);
			case 3:
				glRotatef(90.0,0,0,1);
			case 2:
				glRotatef(90.0,0,0,1);
			case 1:
				call_this = 1;
				break;
			case 6:
				glRotatef(90.0,0,0,1);
			case 5:
				call_this = 2;
				break;
			case 10:
				glRotatef(90.0,0,0,1);
			case 9:
				glRotatef(90.0,0,0,1);
			case 8:
				glRotatef(90.0,0,0,1);
			case 7:
				call_this = 3;
				break;
			}
			glScalef(1,1,0.5);
			glTranslatef(-0.5,-0.5,0);
			glCallList(list[call_this]);
			glPopMatrix();
			//colocar o teto dos muros
			if (call_this != 0 || board_array[i][j] == 11)
			{
				glTranslatef(0,0,-0.5);
				glCallList(list[4]);
			}
			glPopMatrix();

			if (tp_array[i][j] > 0)

			{		
				glColor3f(1,1,1/(float)tp_array[i][j]);
				glPushMatrix();
				glTranslatef(-(float) BOARD_X / 2.0f,-(float) BOARD_Y / 2.0f, 0);
				glTranslatef(j, BOARD_Y - i,0);
				glTranslatef(0.5,0.5,0.5);
				glutSolidSphere(0.1f*((float)tp_array[i][j]),6,6);
				glPopMatrix();
			}
		}
	}

	for (int i = 0; i < BOARD_X; i++)
	{
		for (int j = BOARD_Y-1; j >= BOARD_Y/2; j--)
		{
	

			glColor3f(0,0.7,0);//////////////////////////////////////////////////Muda cor da segunda metade do mapa
			int call_this = 0;
			glPushMatrix();

			glTranslatef(-(float) BOARD_X / 2.0f,-(float) BOARD_Y / 2.0f, 0);
			glTranslatef(j, BOARD_Y - i,0);
			glPushMatrix();
			glTranslatef(0.5,0.5,0);
			switch (board_array[i][j])
			{
			case 4:
				glRotatef(90.0,0,0,1);
			case 3:
				glRotatef(90.0,0,0,1);
			case 2:
				glRotatef(90.0,0,0,1);
			case 1:
				call_this = 1;
				break;
			case 6:
				glRotatef(90.0,0,0,1);
			case 5:
				call_this = 2;
				break;
			case 10:
				glRotatef(90.0,0,0,1);
			case 9:
				glRotatef(90.0,0,0,1);
			case 8:
				glRotatef(90.0,0,0,1);
			case 7:
				call_this = 3;
				break;
			}
			glScalef(1,1,0.5);
			glTranslatef(-0.5,-0.5,0);
			glCallList(list[call_this]);
			glPopMatrix();
			//coloca o topo dos muros
			if (call_this != 0 || board_array[i][j] == 11)
			{
				glTranslatef(0,0,-0.5);
				glCallList(list[4]);
			}
			glPopMatrix();

			if (tp_array[i][j] > 0)

			{		
				glColor3f(1,1,1/(float)tp_array[i][j]);/////////////////////////Sombreado das Paredes
				glPushMatrix();
				glTranslatef(-(float) BOARD_X / 2.0f,-(float) BOARD_Y / 2.0f, 0);
				glTranslatef(j, BOARD_Y - i,0);
				glTranslatef(0.5,0.5,0.5);
				glutSolidSphere(0.1f*((float)tp_array[i][j]),6,6);
				glPopMatrix();
			}
		}
	}
}


bool
Mapa::IsOpen(int x, int y)  //verificar determinado local � um muro ou espa�o aberto
{
	if (board_array[y][x] > 0)
	{
		return false;
	}
	return true;
}
