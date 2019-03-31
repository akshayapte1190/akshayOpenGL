#include<GL/freeglut.h>


bool bIsFullScreen = false;
GLfloat anglePyramid = 0.0f, angleCube = 0.0f;

int main(int argc, char * argv[])
{
	//function declaration
	void initialize(void);
	void uninitialize(void);
	void reshape(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void update(void);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH |GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My First OpenGL Program - Akshay Apte");

	initialize();

	//callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);
	glutIdleFunc(update);
	glutMainLoop();

	return (0);


}


void initialize(void)
{
	//code
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void uninitialize(void)
{
	//code
}

void reshape(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0f, (GLfloat)width / (GLfloat)height, 0.5f, 100.0f);

}

void display(void)
{
	//code
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(-2.0f, 0.0f, -10.0f);
	glRotatef(anglePyramid, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);


	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);


	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();


	//Top
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(2.0f, 0.0f, -15.0f);

	glRotatef(angleCube, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glColor3f(1.0f,1.0f,0.5f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();

	//Bottom
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(2.0f, 0.0f, -15.0f);

	glRotatef(angleCube, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(1.0f,0.0f,0.6f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();


	//Front
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(2.0f, 0.0f, -15.0f);

	glRotatef(angleCube, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(1.0f,0.3f,1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();


	//Back
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(2.0f, 0.0f, -15.0f);

	glRotatef(angleCube, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(0.5f,1.0f,1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	//Right
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(2.0f, 0.0f, -15.0f);

	glRotatef(angleCube, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(1.0f,0.5f,1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	//Left
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(2.0f, 0.0f, -15.0f);

	glRotatef(angleCube, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(1.0f,1.0f,0.5f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	//code
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		break;
	case 'F':
	case 'f':
		if (bIsFullScreen == false)
		{
			glutFullScreen();
			bIsFullScreen = true;
		}
		else
		{
			glutLeaveFullScreen();
			bIsFullScreen = false;
		}
		break;

	}
}

void mouse(int button, int state, int x, int y)
{
	//code
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		glutLeaveMainLoop();
		break;
	}
}
void update(void)
{
	anglePyramid = anglePyramid + 0.1f;
	if (anglePyramid >= 360.0f)
		anglePyramid = 0.0f;


	angleCube = angleCube + 0.1f;
	if (angleCube >= 360.0f)
		angleCube = 0.0f;

	glutPostRedisplay();
}
