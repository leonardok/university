/* gl_snake.cpp
*  INF01047 - Fundamentos de Computacao Grafica
*  mar, 2014 by Leonardo Korndorfer
*
*  Renders a simple snake game
*/


/* include de definicoes das funcoes da glut 
   glut.h inclui gl.h, que contem os headers de funcoes da OpenGL propriamente dita
   glut.h inclui tambem definicoes necessarias para o uso de OpenGl nos diversos ambientes Windows
*/

#include <unistd.h>
#include <stdlib.h>
#include <queue>
#include <iostream>

#ifdef OSX
    #include <GLUT/glut.h>
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#elif defined LINUX
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>

#else
    #include <gl/glut.h>

#endif

#define glVertex1p(point) glVertex2f(point->x, point->y)

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600


enum directions_enum { UP, DOWN, LEFT, RIGHT };


/**
 * SnakeDots
 *
 * This class represent a dot in the snake body.
 * It only has a direction, as each dot goes somewhere.
 *
 */
class SnakeDot {
public:
	GLfloat x, y;
	GLint direction;

	SnakeDot(){}

	SnakeDot(float nX, float nY)
	{
		x = nX;
		y = nY;
		direction = UP;
	}
};

/**
 * This is our snake.  It is a simple collection of dots, formed by
 * SnakeDots, that has some other additional attributes.
 */
std::vector<SnakeDot*> snake; SnakeDot candy(0, 0);

/* last direction we hit on keyboard */
GLint   last_direction = UP;

/* startup refresh_rate. this is changed along the game */
GLfloat refresh_rate = 100000;


/**
 * eatcandy
 *
 * if we have hit a candy, the snake grows and the candy is removed.
 * Add a new dot in the end of the snake
 *
 */
void eatCandy()
{
	int idx = 0;
	SnakeDot *p;

	refresh_rate -= 5000;
	for(idx=0; idx < snake.size(); ++idx)
	{
		p = snake[idx];
	}

	SnakeDot *new_p = new SnakeDot(p->x, p->y);
	switch (p->direction)
	{
		case UP:    new_p->y -= 5; break;
		case DOWN:  new_p->y += 5; break;
		case LEFT:  new_p->x += 5; break;
		case RIGHT: new_p->x -= 5; break;
	}

	snake.push_back(new_p);
}

/**
 * hashitcandy
 *
 * This is the colision algorithm to check if the snake hits the candy.
 * It is very basic, but we dont need other.
 *
 */
void hasHitCandy(void)
{
	int idx = 0;

	for(idx=0; idx < snake.size(); ++idx)
	{
		if(snake[idx]->x == candy.x && snake[idx]->y == candy.y)
		{
			eatCandy();
			candy.x = 0;
			candy.y = 0;
		}
	}
}

/**
 * hasHitItself
 *
 * This is the colision algorithm to check if the snake hits the itself.
 *
 */
void hasHitItself(void)
{
	int inner_idx, idx;
	SnakeDot *p;

	for(idx=0; idx < snake.size(); ++idx)
	{
		p = snake[idx];
		for(inner_idx=idx + 1; inner_idx < snake.size(); ++inner_idx)
		{
			if(p->y == snake[inner_idx]->y && p->x == snake[inner_idx]->x)
			{
				std::cout << "Game over! You just ate yourself!\n";
				exit(0);
			}
		}
	}
}

/**
 * hasHitBorder
 *
 * This is the colision algorithm to check if the snake hits the game frontier.
 *
 */
void hasHitBorder(void)
{
	int inner_idx, idx;
	SnakeDot *p;

	for(idx=0; idx < snake.size(); ++idx)
	{
		p = snake[idx];
		if(p->x <= 0 || p->x >= SCREEN_WIDTH || p->y <= 0 || p->y >= SCREEN_HEIGHT)
		{
			std::cout << "Game over! You just crawshed a wall!\n";
			exit(0);
		}
	}
}


/**
 * drawSnake
 *
 * Put on the openGL pipeline the snake dots
 *
 */
void drawSnake(){
	int index;

	// Indica para a OpenGL que todas as primitivas que forem chamadas
	// deste ponto em diante devem ter a cor vermelha
	glColor3f(1.0f, 0.0f, 0.0f);

	glDisable(GL_POINT_SMOOTH);

	glPointSize(5.0f);

	std::cout << "Snake head at x: " << snake[0]->x << "; y: " << snake[0]->y << "\n";

	glBegin(GL_POINTS);
	for(index=0; index < snake.size(); ++index) { glVertex1p(snake[index]); }
	glEnd();

}

/**
 * drawCandy
 *
 * Put on the openGL pipeline the candy point
 *
 */
void drawCandy()
{
	glColor3f(0.0f, 0.0f, 1.0f);
	glPointSize(7.0f);

	glEnable(GL_POINT_SMOOTH);

	glBegin(GL_POINTS);
		glVertex2f(candy.x, candy.y);
	glEnd();
}

/**
 * renderScene
 *
 * Callback function to draw each time the canvas need to be redraw
 * It is linked in the main function in glutDisplayFunc(renderScene);
 *
 */
void renderScene(void)
{
	// Clean the window with specific background color
	glClear(GL_COLOR_BUFFER_BIT);

	// Call drawing functions
	drawSnake();
	drawCandy();

	// Flush gl commands on openGL pipeline.
	glFlush();
}

/**
 * setupRC
 *
 * Set up the canvas props and game initial data
 *
 */
void setupRC(void)
{
	std::cout << "Initializing...";

	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluOrtho2D(0.0, 600.0, 0.0, 600.0);

	SnakeDot *p1 = new SnakeDot(300.0f, 200.0f);
	SnakeDot *p2 = new SnakeDot(300.0f, 195.0f);
	SnakeDot *p3 = new SnakeDot(300.0f, 190.0f);

	std::cout << "p1 - x:" << p1->x << " y:" << p1->y << "\n";
	std::cout << "p2 - x:" << p2->x << " y:" << p2->y << "\n";
	std::cout << "p3 - x:" << p3->x << " y:" << p3->y << "\n";

	snake.push_back(p1);
	snake.push_back(p2);
	snake.push_back(p3);


	std::cout << "done! \n";
}

    
/**
 * specialKeys(int, int, int)
 *
 * This function handles the keyboard functions
 *
 * Arguments:
 *   key: the key pressed
 *   nX:
 *   nY:
 *
 * Return:
 *   nothing
 */
void specialKeys(int key, int nX, int nY)
{
	int x = 0, y = 0, index = 0;

	if(key == GLUT_KEY_UP    and last_direction != DOWN)  last_direction = UP;
	if(key == GLUT_KEY_DOWN  and last_direction != UP)    last_direction = DOWN;
	if(key == GLUT_KEY_LEFT  and last_direction != RIGHT) last_direction = LEFT;
	if(key == GLUT_KEY_RIGHT and last_direction != LEFT)  last_direction = RIGHT;

	for(index=0; index < snake.size(); ++index)
	{
		snake[index]->x += x;
		snake[index]->y += y;
	}

	// Refresh da imagem: comanda a execucao da renderScene
	glutPostRedisplay();
}
    

/**
 * iddleFunction
 *
 * The iddlefunction will be going on when threre is nothing else happning. The
 * game loop is here.
 *
 * What it does, in high level: 
 * - updates the snake position, changing the position of the body parts (dots)
 * - check for colision -- hasHitCandy
 * - check if need to redraw the candy
 *
 */
void iddleFunction(void) { usleep(refresh_rate); SnakeDot *p;

	int m_last_direction = last_direction;
	int idx, p_direction;

	for(idx=0; idx < snake.size(); ++idx)
	{
		p = snake[idx];
		p_direction = p->direction;

		switch (m_last_direction){
			case UP:    p->y += 5; break;
			case DOWN:  p->y -= 5; break;
			case LEFT:  p->x -= 5; break;
			case RIGHT: p->x += 5; break;
			default: std::cout << "Last direction unknown: " << m_last_direction << "\n";
		}

		p->direction = m_last_direction;
		m_last_direction = p_direction;
	}

	hasHitCandy();
	hasHitItself();
	hasHitBorder();

	// New candy needed
	if(candy.x == 0 and candy.y == 0)
	{
		candy.x = rand() % ((SCREEN_WIDTH - 20) / 5) * 5 + 5;
		candy.y = rand() % ((SCREEN_HEIGHT - 20) / 5) * 5 + 5;

		std::cout << "Wild candy appears! x: " << candy.x << "; y: " << candy.y << "\n";
	}

	glutPostRedisplay();
}


int main( int argc, char** argv)
{
	glutInit(&argc, argv);
	
	// Indica que deve ser usado um unico buffer para armazenamento da imagem e representacao de cores RGB
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(600,600);     // set window size
	glutInitWindowPosition(200, 150); // set window position on screen
    
	// Cria uma janela com o titulo especificado
	glutCreateWindow("Programa com uso de Teclado");

	// Especifica a funcao que vai tratar teclas especiais
 	glutSpecialFunc(specialKeys);
  
	// Especifica para a OpenGL que funcao deve ser chamada para geracao da imagem
	glutDisplayFunc(renderScene);

	// Executa a inicializacao de parametros de exibicao
	setupRC();

	std::cout << "Main Loop...\n";

	glutIdleFunc(iddleFunction);
 
	// Dispara a maquina de estados de OpenGL 
	glutMainLoop();
	
	return 0;
}
