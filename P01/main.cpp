#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

static double oscillationFactor = 0.0;

void changeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	float ratio = w * 1.0f / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 5.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f, 0.0f);

	// Aumentando a amplitude e velocidade da oscilação
	glutWireTeapot(1.0 + 0.4 * sin(oscillationFactor));
	oscillationFactor = oscillationFactor + 0.04; // Maior velocidade

	glutSwapBuffers();
	glutPostRedisplay(); // Força a atualização contínua
}

void printInfo()
{
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@TP1");

	printInfo();

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutMainLoop();
	
	return 0;
}
