#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>





float translateX = 0.0f;
float translateZ = 0.0f;
float translateY = 0.0f;
float rotateY = 0.0f;
float scaleHeight = 1.0f;


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

// put axis drawing in here
	glBegin(GL_LINES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(100.0f,0.0f,0.0f);
		glVertex3f(-100.0f,0.0f,0.0f);

		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,100.0f,0.0f);
		glVertex3f(0.0f,-100.0f,0.0f);

		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,100.0f);
		glVertex3f(0.0f,0.0f,-100.0f);
	glEnd();
// put the geometric transformations here
	glPushMatrix();
	glTranslatef(translateX, translateY, translateZ);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
    glScalef(1.0f, scaleHeight, 1.0f);

// put pyramid drawing instructions here
	glBegin(GL_TRIANGLES);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 2.0, 0.0);
		glVertex3f(-1.0, 0.0, 1.0);
		glVertex3f(1.0, 0.0, 1.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 2.0, 0.0);
		glVertex3f(1.0, 0.0, 1.0);
		glVertex3f(1.0, 0.0, -1.0);

		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 2.0, 0.0);
		glVertex3f(1.0, 0.0, -1.0);
		glVertex3f(-1.0, 0.0, -1.0);

		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(0.0, 2.0, 0.0);
		glVertex3f(-1.0, 0.0, -1.0);
		glVertex3f(-1.0, 0.0, 1.0);
	glEnd();

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events

void keyboardspecial(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_UP:
			translateZ -= 0.1f;
			break;
        case GLUT_KEY_DOWN:
			translateZ += 0.1f;
			break;
        case GLUT_KEY_LEFT:
			translateX -= 0.1f;
			break;
        case GLUT_KEY_RIGHT:
			translateX += 0.1f;
			break;
    }

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
	switch (key) {
		case 's':
			translateY -= 0.1f;
			break;
		case 'w':
			translateY += 0.1f;
			break;
        case 'q':
			rotateY -= 5.0f;
			break;
        case 'e':
			rotateY += 5.0f;
			break;
        case 'z':
			scaleHeight += 0.1f;
			break;
        case 'x':
			scaleHeight -= 0.1f;
			break;
    }
	
	glutPostRedisplay();
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
	glutSpecialFunc(keyboardspecial);
	glutKeyboardFunc(keyboard);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
