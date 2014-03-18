//#include <windows.h>   // use as needed for your system
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <unistd.h>
#include <stdlib.h>
#include <queue>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>

#elif defined LINUX
#include <GL/glut.h>
#include <GL/gl.h>

#else
#include <gl/glut.h>
#endif



class GLintPoint {
    public:
        GLint x, y;
};

class VertexPoint {
    public:
        GLint x, y;
        GLint module;
    
        // This is the last used direction. To draw the next line, flip this variable.
        // Direction: 0 is horizontal
        //            1 is vertical
        GLint direction;
    
        // Direction: 0 p3 goes as a sum
        //            1 p3 minus
        GLint p3_direction;
};

float reduction_factor = 0.7;
int current_color = 0;

std::queue<VertexPoint *> vertex_queue;


void drawSegment(void)
{
	
    
    VertexPoint *p = vertex_queue.front();
    vertex_queue.pop();

    
    // std::cout << "drawSegment... x:" << p->x << " y:" << p->y;
    
    glBegin(GL_LINES);
    
    VertexPoint *p1 = new VertexPoint();
    VertexPoint *p2 = new VertexPoint();
    VertexPoint *p3 = new VertexPoint();
    
    p1->module = p2->module = p3->module = (p->module * reduction_factor);
    
    /* last one was horizontal, now we have to draw vertical */
    if (p->direction == 0) {
        
        p1->x = p->x;
        p1->y = p->y - (p1->module / 2);
        p1->direction = 1;
        
        p2->x = p->x;
        p2->y = p->y + (p1->module / 2);
        p2->direction = 1;
        
        p3->x = p->x + (p1->module / 2);
        p3->y = p->y;
        p3->direction = 1;
    }
    
    /* last one was vertical, now we have to draw horizontal */
    else {
        p1->y = p->y;
        p1->x = p->x - (p1->module / 2);
        p1->direction = 0;
        p1->p3_direction = 1;
        
        p2->y = p->y;
        p2->x = p->x + (p1->module / 2);
        p2->direction = 0;
        p1->p3_direction = 0;
        
        p3->y = p->y + (p1->module / 2);
        p3->x = p->x;
        p3->direction = 0;
        p1->p3_direction = 2;
    }
    
    switch (current_color) {
        case 0: glColor3f(1.0f, 0.0f, 0.0f); break;
        case 1: glColor3f(0.0f, 1.0f, 0.0f); break;
        case 2: glColor3f(0.0f, 0.0f, 1.0f); break;
	}
    current_color = (current_color + 1) % 3;
    
    glVertex2f(p1->x, p1->y);
    glVertex2f(p2->x, p2->y);
    
    vertex_queue.push(p1);
    vertex_queue.push(p2);
	
	glEnd();
    
    // Flush dos comandos de desenho que estejam no pipeline da OpenGL
    // para conclusao da geracao da imagem
    glFlush();
    
    // std::cout << " done!\n";
}



void drawImage(GLint loops)
{
    for (int i = 0; i < loops; i++) {
        drawSegment();
    }
}

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void SetupRC(void)
{
    std::cout << "Initializing...\n";
    
    glClearColor(1.0,1.0,1.0,0.0);       // set white background color
    glColor3f(0.0f, 0.0f, 1.0f);          // set the drawing color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 900.0, 0.0, 640.0);
    glMatrixMode(GL_MODELVIEW);
    
    VertexPoint *v = new VertexPoint();
    v->x = 450;
    v->y = 320;
    v->module = 600;
    v->direction = 1;
    
    vertex_queue.push(v);
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void RenderScene(void)
{
    std::cout << "Rendering Scene...\n";
    
	// Limpa a janela com a cor especificada como cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);
    
    drawImage(100000);
    
	// Flush dos comandos de desenho que estejam no pipeline da OpenGL
    // para conclusao da geracao da imagem
    glFlush();
    
    std::cout << "Rendering Scene... Done!\n";
    
    return;
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    std::cout << "Init main...\n";
    
    glutInit(&argc, argv);          // initialize the toolkit
    
	// Indica que deve ser usado um unico buffer para armazenamento da imagem e representacao de cores RGB
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowSize(640,640);     // set window size
    glutInitWindowPosition(200, 150); // set window position on screen

    // Cria uma janela com o titulo especificado
	glutCreateWindow("Programa lines");
    
    // Especifica para a OpenGL que funcao deve ser chamada para geracao da imagem
	glutDisplayFunc(RenderScene);
    
    SetupRC();
    
    std::cout << "Init infinite loop...\n";
    glutMainLoop();
    return 0;
}
