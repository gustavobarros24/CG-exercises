#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

class Polar{
	public:
		float radius;
		float alpha;
		float beta;

		Polar(float radius, float alpha, float beta) : radius(radius), alpha(alpha), beta(beta){

		}

		float getX() const{
			return radius * cos(beta) * sin(alpha);
		}

		float getY() const{
			return radius * sin(beta);
		}

		float getZ() const{
			return radius * cos(beta) * cos(alpha);
		}

};

Polar camPos(sqrt(88), M_PI_4, M_PI_4);

void changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
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
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void drawCylinder(float radius, float height, int slices)
{
	double h = height/2;
	double sliceAngle = M_PI * 2 / slices;

	Polar base(h, 0 , -M_PI/2);
	Polar upperbase(h,0,M_PI/2);

	double hypotenuse = sqrt(h * h + radius * radius);
	double beta = asin(h / hypotenuse);

	double radiusC = sqrt(pow(h, 2) + pow(radius, 2));

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(base.getX(), base.getY(), base.getZ());


	for (int i = slices; i >= 0; i--) {
		Polar p(radiusC, sliceAngle * i, -beta);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(p.getX(), p.getY(), p.getZ());
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(upperbase.getX(), upperbase.getY(), upperbase.getZ());
	for (int i = 0; i <= slices; i++) {
		Polar p(radiusC, sliceAngle * i, beta);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(p.getX(), p.getY(), p.getZ());
	}
	glEnd();

	int flag = 0;
	
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= slices; i++) {
		Polar polarbottom(radiusC, sliceAngle * i, beta);
		Polar polartop(radiusC, sliceAngle * i, -beta);
		if(flag == 0){
			glColor3f(1.0f, 1.0f, 0.0f);
			flag = 1;
		}
		else{
			glColor3f(0.0f, 0.0f, 1.0f);
			flag = 0;
		}
		glVertex3f(polarbottom.getX(), polarbottom.getY(), polarbottom.getZ());
		glVertex3f(polartop.getX(), polartop.getY(), polartop.getZ());
	}
	glEnd();

}

void renderScene(void)
{

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camPos.getX(), camPos.getY(), camPos.getZ(),
			  0.0, 0.0, 0.0,
			  0.0f, 1.0f, 0.0f);

	drawCylinder(1, 2, 28);

	// End of frame
	glutSwapBuffers();
}

void processSpecialKeys(int key, int xx, int yy)
{

	//KEYS USED TO MOVE THE CAMERA POSITION

	int n = 32;
	switch (key) {
        case GLUT_KEY_RIGHT:
			camPos.alpha = camPos.alpha - M_PI / n;	//MOVE UP
			break;
        case GLUT_KEY_LEFT:
			camPos.alpha = camPos.alpha + M_PI / n;	//MOVE DOWN
			break;
        case GLUT_KEY_DOWN:
			camPos.beta = camPos.beta + M_PI / n;	//MOVE LEFT
			break;
        case GLUT_KEY_UP:
			camPos.beta = camPos.beta - M_PI / n;	//MOVE RIGHT
			break;
    }

	if (camPos.alpha < 0){
		camPos.alpha += M_PI * 2;
	} 
	else if (camPos.alpha > M_PI * 2){
		camPos.alpha -= M_PI * 2;
	}

	if (camPos.beta < -M_PI){
		camPos.beta += M_PI * 2;
	}
	else if (camPos.beta > M_PI){
		camPos.beta -= M_PI * 2;
	} 


	glutPostRedisplay();
}

int main(int argc, char **argv)
{

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");

	// Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// Callback registration for keyboard processing
	glutSpecialFunc(processSpecialKeys);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
