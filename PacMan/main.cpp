#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include <stdio.h>
#include "Globais.h"
#include "Visao.h"
#include "Mapa.h"
#include "PACMAN.h"
#include "Ghost.h"



int start_timer;
void init(void);
int num_ghosts = 4;
float ratio;
int h,w;
Visao *camera;
int view;
int v_timer;
Mapa *board;
PACMAN *pacman;
Ghost *ghost[4];


bool gameover = false;	// variavel fim de jogo

void verificar(){
	if(pontos[0]==58){
		pontos[1]++;
		pontos[0]=48;
	}
	if(pontos[1]==58){
		pontos[2]++;
		pontos[1]=48;
	}
	if(pontos[2]==58){
		pontos[3]++;
		pontos[2]=48;
	}
	if(pontos[3]==58){
		pontos[3]=48;
	}
}


void placar(){
	verificar();
	//glColor3f(1, 1, 0);
	glRasterPos2f(-16,15.5);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pontos[3]);
	//glColor3f(1, 1, 0);
	glRasterPos2f(-15,15.5);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pontos[2]);
	//glColor3f(1, 1, 0);
	glRasterPos2f(-14,15.5);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pontos[1]);
	//glColor3f(1, 1, 0);
	glRasterPos2f(-13,15.5);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pontos[0]);
	
}

void RenderScene()
{
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa Buffer de Profundidade(NAO TRANSLUCIDEZ)
	//att camera
	camera->Set_position(pacman->x, pacman->y, pacman->angulo, view);
	placar();
	
	//trasporte
	if ((int)pacman->x == 27 && (int) pacman->y == 14 && pacman->angulo == 0)
	{
		pacman->x = 0;
		pacman->animacao = true;
	}else
	if ((int)(pacman->x + 0.9) == 0 && (int) pacman->y == 14 && pacman->angulo == 180)
	{
		pacman->x = 27;
		pacman->animacao = true;
	}


	//movimento pacman
	if (pacman->animacao)
		pacman->Move();	
	if(!(board->IsOpen((int)(pacman->x + cos(M_PI/180*pacman->angulo)),
			(int)(pacman->y + sin(M_PI/180*pacman->angulo)))) &&
			pacman->x - (int)pacman->x < 0.1 && pacman->y - (int)pacman->y < 0.1)
		pacman->animacao = false;


	//comer bolinhas
	if (board->tp_array[(int)(pacman->y+0.5)][(int)(pacman->x+0.5)]	== 1)
	{
		board->tp_array[(int)(pacman->y+0.5)][(int)(pacman->x+0.5)]	= 0;
		board->pebbles_left--;
		PlaySound("eat.wav", NULL, SND_ASYNC);///////////////////////////////////////
		pontos[0]++;
		cont_vida++;
	} else if(board->tp_array[(int)(pacman->y+0.5)][(int)(pacman->x+0.5)] == 3)
	{
		board->tp_array[(int)(pacman->y+0.5)][(int)(pacman->x+0.5)]	= 0;
		board->pebbles_left--;
		PlaySound("eat.wav", NULL, SND_ASYNC);
		pontos[0]++;////////////////////////////////////////////////////////////////
		cont_vida++;
        PlaySound("PowerSound.wav", NULL, SND_SYNC);
		for (int i = 0; i < 4; i++)//transformar fantasmas em comida :v
		{
			if (!ghost[i]->morto)
				ghost[i]->Vulnerable();
		}
	}
	
	//caso todas as bolinhas sejam comidas
	if (board->pebbles_left == 0)
	{
		init();//reiniciar o jogo
		board->tp_restore();
	}



	board->Draw();
	if (!gameover)//ONDE O PACMAN RECEBE VIDA A CADA 100PTS
		if(cont_vida==100){
		pacman->vidas++;
		cont_vida=0;
	}
		
		pacman->Draw();


	for (int a = 0; a < num_ghosts; a++)
	{

		//movimento fantasmas
		if (!gameover && start_timer == 0)
			ghost[a]->Update();

		if (!ghost[a]->no_respawn &&
			ghost[a]->x - (int)ghost[a]->x < 0.1 && ghost[a]->y - (int)ghost[a]->y < 0.1)
		{

			bool open_move[4];
			//descobrir movimentos possiveis
			for (int ang = 0; ang < 4; ang++)
			{
				open_move[ang] = board->IsOpen((int)(ghost[a]->x + cos(M_PI/180*ang*90)),
					(int)(ghost[a]->y + sin(M_PI/180*ang*90)));
			}

            //ir atras do pacman
			if (!ghost[a]->morto)
			{
				if(ghost[a]->x - (int)ghost[a]->x < 0.1 && ghost[a]->y - (int)ghost[a]->y < 0.1)
					ghost[a]->Chase(pacman->x, pacman->y, open_move);//perseguir pac man
			} else {
				if(ghost[a]->x - (int)ghost[a]->x < 0.1 && ghost[a]->y - (int)ghost[a]->y < 0.1)
					ghost[a]->Chase(13, 11, open_move);//movimento livre
			}
		}
		if (ghost[a]->no_respawn && !(board->IsOpen((int)(ghost[a]->x + cos(M_PI/180*ghost[a]->angulo)),
			(int)(ghost[a]->y + sin(M_PI/180*ghost[a]->angulo)))) && ghost[a]->tempo_respawn > 0 &&
			ghost[a]->x - (int)ghost[a]->x < 0.1 && ghost[a]->y - (int)ghost[a]->y < 0.1)
		{
			ghost[a]->angulo = (double)(((int)ghost[a]->angulo + 180)%360);
		}

		if (!gameover && start_timer == 0)
			ghost[a]->Move();

		ghost[a]->Draw();
		
		if(!(ghost[a]->morto))
		{
			bool collide = ghost[a]->Catch(pacman->x, pacman->y);//COLISAO DO PACMAN COM FANTASMA
			if (collide && !(ghost[a]->estado))  //pacman morrer
			{
				PlaySound("deathSound.wav",NULL,SND_SYNC);//BARULHO DE MORTE, JOGO SO CONTINUA APOS ELE ACABAR
				pacman->vidas--;
				if (pacman->vidas == 0)
					gameover = true;
				else
					init();
				a = 4;
			}else
			if (collide && ((ghost[a]->estado)))	//mandar pro respawn os inimigos
			{
				pontos[3]++;////////////Adiciono 1000 Pontos para cada fantasma comido(1 unidade milhar)
				//reset do inimigo
				ghost[a]->estado = false;
				ghost[a]->morto = true;
				ghost[a]->velocidade = 0.1;
			}
		}

	}
	glutSwapBuffers();
}


void TimerFunction(int value)
{
	//mudar a visao
	if(GetAsyncKeyState(0x56) && v_timer == 0) // tecla 'v'
	{
		view = (view+1)%2;
		v_timer = 10;
	}
	if (v_timer > 0)
		v_timer--;	

	//tempo de preparação do game
	if (start_timer > 0)
		start_timer--;

	if (!gameover && start_timer == 0)
	{
		// teclado
		//direita
		if(GetAsyncKeyState(VK_RIGHT)&& !GetAsyncKeyState(VK_LEFT)
			&& (int) pacman->y - pacman->y > -0.1 && pacman->angulo != 0)
		{
			if (board->IsOpen(pacman->x+1, pacman->y))
			{
				pacman->animacao = true;
				pacman->angulo = 0;
			} 
		}else
		//pra esquerda
		if(GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT) 
			&& (int) pacman->y - pacman->y > -0.1 && pacman->angulo != 180)
		{
			if (board->IsOpen(pacman->x-1, pacman->y))
			{
				pacman->animacao = true;
				pacman->angulo = 180;
			}	
		}
		//pra cima
		if(GetAsyncKeyState(VK_UP)&& !GetAsyncKeyState(VK_DOWN) 
			&& (int) pacman->x - pacman->x > -0.1 && pacman->angulo != 270)
		{
			if (board->IsOpen(pacman->x, pacman->y - 1))
			{
				pacman->animacao = true;
				pacman->angulo = 270;
			}
		}else
		//pra baixo
		if(GetAsyncKeyState(VK_DOWN)&& !GetAsyncKeyState(VK_UP)
			&& (int) pacman->x - pacman->x > -0.1 && pacman->angulo != 90)
		{
			if (board->IsOpen(pacman->x, pacman->y + 1))
			{
				pacman->animacao = true;
				pacman->angulo = 90;
			}
		}
	}

	//reset do game
	if (GetAsyncKeyState(VK_RETURN) && gameover)// pressionando enter reinicia o jogo caso nao se tenha mais vidas
	{
		//zera pontos
		int remove=0;

		while(remove<=3){
			pontos[remove]=48;
			remove++;
		}
		//zera vidas
		pacman->vidas = 3;
		//zera pontos de vida(ao chegar em 100, eles davam 1 vida)
		cont_vida=0;
		init();
		board->tp_restore();
		gameover = false;
	}
	//quit
	if(GetAsyncKeyState(VK_ESCAPE))
	{
		exit(0);
	}

	glutPostRedisplay();

	glutTimerFunc(15, TimerFunction, 1);
}


void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)
		h = 1;	

	ratio = 1.0f * w / (h);
	glViewport(0,0,w,h);
	camera = new Visao(ratio);

}



//inicio do game
void init(void)
{
	glEnable(GL_DEPTH_TEST);//TESTE DE PROFUNCIDADE(NAO TRANSLUCIDEZ)
	
	start_timer = 140;
	pacman->Reinit();
	PlaySound("music.wav", NULL, SND_ASYNC);
	//posição inicial dos inimigos na gaiola
	int start_x[4] = {11,12,15,16};
	float ghost_colors[4][3] = {{255,0,0},{120,240,120},{255,200,200},{255,125,0}};

	for (int i = 0; i < num_ghosts; i++)
	{
		ghost[i]->Reinit();
		ghost[i]->x = start_x[i];
		ghost[i]->y = 14;
		ghost[i]->morto = false;
		ghost[i]->no_respawn = i*33 + 66;
		ghost[i]->max_velocidade = 0.1 - 0.01*(float)i;
		ghost[i]->velocidade = ghost[i]->max_velocidade;
		//pintar os inimigos
		for (int j = 0; j < 3; j++)
			ghost[i]->cor[j] = ghost_colors[i][j]/255.0f;
	}
}



int main(int argc, char * argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );//LIMPA BUFFER DE PROFUNDIDADE ANTES DO DESENHO
	pontos[0] = 48;
	pontos[1] = 48;
	pontos[2] = 48;
	pontos[3] = 48;
	//fullscreen mode
	glutGameModeString( "800x600:16@60" );
	glutEnterGameMode();

	//remover o mouse
	glutSetCursor(GLUT_CURSOR_NONE);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(15, TimerFunction, 1);
	
	//desenhar a fase
	glClearColor(.3, .3, .3, 1.0f);
	board = new Mapa();
	int start_x[4] = {11,12,15,16};
	pacman = new PACMAN(13.5,23);

	//colocar fantasmas no inicio
	for (int i = 0; i < num_ghosts; i++)
	{
		ghost[i] = new Ghost(start_x[i],14);
	}
	
       
	init();
	view = 0;
	v_timer = 0;

	glutMainLoop();

	return 0;
}