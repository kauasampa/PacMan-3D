#include "Visao.h"
#include "Mapa.h"
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>


// Destrutor
Visao::~Visao(void){}

//Construtor
Visao::Visao(float ratio)
{
	glEnable(GL_CULL_FACE);


    float   color[4], dir[4];

	// habilitar a luz(apenas uma)
	glEnable(GL_LIGHT0);//sombra
	glEnable(GL_LIGHTING);//luz

	// Habilitar cor com base na luz
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// para normalizar objetos
	glEnable(GL_NORMALIZE);//??

	// difusão de cor
	color[0] = 1.0f; color[1] = 1.0f; color[2] = 1.0f; color[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	color[0] = 0.0f; color[1] = 0.0f; color[2] = 0.0f; color[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_SPECULAR, color);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// star a pespectiva
	gluPerspective(60,ratio,0.005,100);//(abertura de visao,larguraDaJanela/Altura,distanciaMinimaDeVisualização,distanciaMaximaDeVisualização)

	// limpar tela
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    dir[0] = 0.0; dir[1] = 1.0; dir[2] = 1.0; dir[3] = 0.0;
    glLightfv(GL_LIGHT0, GL_POSITION, dir);
}
static float currentCenterX = 15; // Valor inicial, ajuste conforme necessário
static float currentCenterY = 14.5; // Valor inicial, ajuste conforme necessário
void
Visao::Set_position(float x_at, float y_at, double angle, int view)
{
    //limpar tela
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (view == 1)//mudar a visão da tela de primeira pessoa em 3d, para terceira pessoa em 2d
			gluLookAt(-1.5, 0, 40, -1.5, 0, 0, 0.0f,1.0f,0.0f);//{(x,y,z)=posição do olho da Visao.} + {(x,y,z)=Ponto que a Visao esta olhando na cena} + {(upX,upY,upZ)==NAO MEXER}
	else{
		x_at=x_at-15;
		y_at=y_at-14.5;
			
			float eyeX = x_at;
		    float eyeY = -y_at;
		    float eyeZ = 2; // Altura da câmera
	        // Valores alvo para centerX e centerY
			float targetCenterX = eyeX + cos(angle * M_PI / 180);
			float targetCenterY = eyeY - sin(angle * M_PI / 180);
			float centerZ = eyeZ - 0.3; // Mantém a câmera olhando horizontalmente
			
			// Ajuste o valor de t conforme necessário para controlar a rapidez da mudança
			float t =0.4; // Exemplo de valor, ajuste conforme necessário
			currentCenterX = currentCenterX + t * (targetCenterX - currentCenterX);
			currentCenterY = currentCenterY + t * (targetCenterY - currentCenterY);
			
			gluLookAt(eyeX, eyeY, eyeZ, currentCenterX, currentCenterY, centerZ, 0.0f, 0.0f, 1.0f);

	}

}
