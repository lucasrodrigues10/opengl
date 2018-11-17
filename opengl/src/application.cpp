#include<stdio.h>
#include<GL/freeglut.h>
#include <string>

// Variáveis Globais
GLfloat x = 100, b = 0, y = 100, d = 0, e = 0;
GLfloat cor_paisagem_r = .18f;
GLfloat cor_paisagem_g = .26f;
GLfloat cor_paisagem_b = .53f;
GLfloat cor_paisagem_a = 1.f;

// Protótipos de função
void desenhar_chao();
void teclado(int tecla, int x, int y);
void update(int value);
void desenhar_aviao();
void iniciar_paisagem();
void printar_texto(const char *text, int tamanho, int pos_x, int pos_y);
void printar_instrucoes();

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800.0, 600.0);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("AVIAO");
	glutDisplayFunc(desenhar_aviao);
	iniciar_paisagem();
	glutTimerFunc(50, update, 0);
	glutMainLoop();
	return 0;
}

void update(int value)
{
	x += 2.0;	
	b -= 1.0;	
	//y += 2.0;	
	if (b <= -78.0)
		b = 0.0;
	glutPostRedisplay();
	// tempo de atualização
	glutTimerFunc(100, update, 0); 
}


void desenhar_aviao()
{
	// Corpo do Avião
	glClear(GL_COLOR_BUFFER_BIT);
	desenhar_chao();
	glPushMatrix();
	glTranslated(x, y, 0.0);
	glColor3f(.0, .0, .0); // preto
	glBegin(GL_POLYGON);
	glVertex2f(0.0, 30.0);
	glVertex2f(0.0, 55.0);
	glVertex2f(135.0, 55.0);
	glVertex2f(135.0, 30.0);
	glEnd();
	glPopMatrix();


	// 
	glPushMatrix();
	glTranslated(x, y, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(135.0, 55.0);
	glVertex2f(150.0, 50.0);
	glVertex2f(155.0, 45.0);
	glVertex2f(160.0, 40.0);
	glVertex2f(135.0, 40.0);
	glEnd();
	glPopMatrix();

	// Triangulo Frente - Cima
	glPushMatrix();
	glTranslated(x, y, 0.0);
	glColor3f(.732, .1297, 0.1383); // vermelho
	glBegin(GL_POLYGON);
	glVertex2f(135.0, 55.0);
	glVertex2f(150.0, 50.0);
	glVertex2f(155.0, 45.0);
	glVertex2f(160.0, 40.0);
	glVertex2f(135.0, 40.0);
	glEnd();
	glPopMatrix();

	// Triangulo Frente - Baixo
	glPushMatrix();
	glTranslated(x, y, 0.0);
	glColor3f(.0, .22, .557); //azul escuro
	glBegin(GL_POLYGON);
	glVertex2f(135.0, 40.0);
	glVertex2f(160.0, 40.0);
	glVertex2f(160.0, 37.0);
	glVertex2f(145.0, 30.0);
	glVertex2f(135.0, 30.0);
	glEnd();
	glPopMatrix();

	// Aba Traseira
	glPushMatrix();
	glTranslated(x, y, 0.0);
	glColor3f(.0, .22, .557); //azul escuro
	glBegin(GL_POLYGON);
	glVertex2f(0.0, 55.0);
	glVertex2f(0.0, 80.0);
	glVertex2f(10.0, 80.0);
	glVertex2f(40.0, 55.0);
	glEnd();
	glPopMatrix();

	// Asa Esquerda
	glPushMatrix();
	glTranslated(x, y, 0.0);
	glColor3f(.732, .1297, 0.1383); // vermelho
	glBegin(GL_POLYGON);
	glVertex2f(65.0, 55.0);
	glVertex2f(50.0, 70.0);
	glVertex2f(75.0, 70.0);
	glVertex2f(90.0, 55.0);
	glEnd();
	glPopMatrix();

	// Asa Direita
	glPushMatrix();
	glTranslated(x, y, 0.0);
	glColor3f(.732, .1297, 0.1383);
	glBegin(GL_POLYGON);
	glVertex2f(70.0, 40.0);
	glVertex2f(100.0, 40.0);
	glVertex2f(80.0, 15.0);
	glVertex2f(50.0, 15.0);
	glEnd();
	glPopMatrix();

	printar_instrucoes();

	if (x > 500.0)
	{
		x = 0.0;
		b = 0.0;
	}
	glFlush();
	glutSwapBuffers();

	
	// Habilitar as teclas
	glutSpecialFunc(teclado);

}

void printar_instrucoes() {
	std::string text;
	text = "SETA CIMA - SOBE";
	glColor3f(1.0, 1.0, 1.0);
	printar_texto(text.data(), text.size(), 20, 550);
	text = "SETA BAIXO - DESCE";
	glColor3f(1.0, 1.0, 1.0);
	printar_texto(text.data(), text.size(), 20, 500);
	text = "SETA DIREITA - AVANCA";
	glColor3f(1.0, 1.0, 1.0);
	printar_texto(text.data(), text.size(), 20, 450);
	text = "SETA ESQUERDA - RECUA";
	glColor3f(1.0, 1.0, 1.0);
	printar_texto(text.data(), text.size(), 20, 400);
	text = "F1 - NOITE";
	glColor3f(1.0, 1.0, 1.0);
	printar_texto(text.data(), text.size(), 20, 350);
	text = "F2 - DIA";
	glColor3f(1.0, 1.0, 1.0);
	printar_texto(text.data(), text.size(), 20, 300);
	text = "F8 - SAI";
	glColor3f(1.0, 1.0, 1.0);
	printar_texto(text.data(), text.size(), 20, 250);
}

void printar_texto(const char *text, int tamanho, int pos_x, int pos_y)
{
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(pos_x, pos_y);
	for (int i = 0; i < tamanho; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
};

void teclado(int tecla, int k, int z) {

	switch (tecla) {
	case GLUT_KEY_UP:
		y += 20;
		break;
	case GLUT_KEY_DOWN:
		y -= 20;
		break;
	case GLUT_KEY_LEFT:
		x -= 20;
		break;
	case GLUT_KEY_RIGHT:
		x += 20;
		
		break;
	case GLUT_KEY_F1:
		cor_paisagem_r = .06f;
		cor_paisagem_g = .07f;
		cor_paisagem_b = .12f;
		cor_paisagem_a = 1.f;
		iniciar_paisagem();
		break;
	case GLUT_KEY_F2:
		cor_paisagem_r = .18f;
		cor_paisagem_g = .26f;
		cor_paisagem_b = .53f;
		cor_paisagem_a = 1.f;
		iniciar_paisagem();
		break;
	case GLUT_KEY_F8:
		exit(0);
		break;
	}
	glutPostRedisplay();

}

void desenhar_chao()
{
	// Desenha a superficie
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 100.0);
	glVertex2f(500.0, 100.0);
	glVertex2f(500.0, 0.0);
	glEnd();
	glPopMatrix();

	// Desenha arvores
	glPushMatrix();
	glTranslated(b, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.0, 40.0);
	glVertex2f(8.0, 60.0);
	glVertex2f(58.0, 60.0);
	glVertex2f(50.0, 40.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(b, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(100.0, 40.0);
	glVertex2f(108.0, 60.0);
	glVertex2f(158.0, 60.0);
	glVertex2f(150.0, 40.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(b, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(200.0, 40.0);
	glVertex2f(208.0, 60.0);
	glVertex2f(258.0, 60.0);
	glVertex2f(250.0, 40.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(b, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(300.0, 40.0);
	glVertex2f(308.0, 60.0);
	glVertex2f(358.0, 60.0);
	glVertex2f(350.0, 40.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(b, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(400.0, 40.0);
	glVertex2f(408.0, 60.0);
	glVertex2f(458.0, 60.0);
	glVertex2f(450.0, 40.0);
	glEnd();
	glPopMatrix();
}


void iniciar_paisagem()
{
	glClearColor(cor_paisagem_r, cor_paisagem_g, cor_paisagem_b, cor_paisagem_a);
	glColor3f(.0, .0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}