#include <string.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

using namespace std;

#define PI 3.1415926535898
#define R 2 
#define drawOneLine(x1,y1,x2,y2)  glBegin(GL_LINES);  \
   glVertex2f ((x1),(y1)); glVertex2f ((x2),(y2)); glEnd();
static double year = 0, day = 0;


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void drawCircle() {
	GLint circle_points = 100, i = 0;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < circle_points; i++)
	{
		double angle = 2 * PI*i / circle_points;
		glVertex3d(2*cos(angle), 2*sin(angle), 0);
	}
	glEnd();
}

void display_Circle(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	drawCircle();
	glPushMatrix();
	glRotatef(day, 1, 0, 0);
	drawCircle();
	glPopMatrix();
	glutSwapBuffers();
}

void display_square(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	glPushMatrix();

	glRotated(day, 1.0, 0.0, 0.0);
	glRotated(year, 0.0, 1.0, 0.0);

	GLdouble v1[3] = { 1.0, 2.0, 0.0 };
	GLdouble v2[3] = { 0.0, 2.0, -1.0 };
	GLdouble v3[3] = { -1.0, 2.0, 0.0 };
	GLdouble v4[3] = { 0.0, 2.0, 1.0 };
	glBegin(GL_LINE_LOOP);
		glVertex3dv(v1);
		glVertex3dv(v2);
		glVertex3dv(v3);
		glVertex3dv(v4);
	glEnd();

	GLdouble v5[3] = { 1.0, -2.0, 0.0 };
	GLdouble v6[3] = { 0.0, -2.0, -1.0 };
	GLdouble v7[3] = { -1.0, -2.0, 0.0 };
	GLdouble v8[3] = { 0.0, -2.0, 1.0 };


	glBegin(GL_LINE_LOOP);
		glVertex3dv(v5);
		glVertex3dv(v6);
		glVertex3dv(v7);
		glVertex3dv(v8);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
		glVertex3dv(v1);
		glVertex3dv(v5);
		glColor3f(0.0, 1.0, 1.0);
		glVertex3dv(v4);
		glColor3f(0.0, 1.0, 1.0);
		
		glVertex3dv(v8);

		glColor3f(1.0, 1.0, 0.0);
		glVertex3dv(v3);
		
		glColor3f(1.0, 0.0, 1.0);
		glVertex3dv(v7);
		glColor3f(0.5, 1.0, 1.0);
		glVertex3dv(v2);
		glColor3f(0.0, 0.0, 1.5);
		glVertex3dv(v6);
		glColor3f(0.0, 0.5, 1.5);
		glVertex3dv(v1);
		glColor3f(0.5, 0.5, 1.5);
		glVertex3dv(v5);
		
	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();

	glRotated(day, 1.0, 0.0, 0.0);
	glRotated(year, 0.0, 1.0, 0.0);

	GLdouble* circle1 = new GLdouble[150];
	GLdouble* circle2 = new GLdouble[150];

	GLint circle_points = 50, i = 0;
	for (int i = 0, k = 0; i < circle_points && k < 150; i++, k += 3)
	{
		double angle = 2 * PI*i / circle_points;
		circle1[k] = 2 * cos(angle);
		circle1[k + 1] = 2;
		circle1[k + 2] = 2 * sin(angle);;

		circle2[k] = 2 * cos(angle);
		circle2[k + 1] = -2;
		circle2[k + 2] = 2 * sin(angle);;
	}

	glBegin(GL_LINE_LOOP);
	for (int k = 0; k < 150; k += 3)
	{
		glVertex3d(circle1[k], circle1[k + 1], circle1[k + 2]);
	}
	glEnd();

	/*
	glBegin(GL_LINE_LOOP);
	for (int k = 0; k < 150; k += 3)
	{
		glVertex3d(circle2[k], circle2[k + 1], circle2[k + 2]);
	}
	glEnd();
	*/
	/*
	glBegin(GL_LINE_STRIP);
		glVertex3d(circle1[0], circle1[1], circle1[2]);
		glVertex3d(circle2[0], circle2[1], circle2[2]);
		glVertex3d(circle1[27], circle1[28], circle1[29]);
	glEnd();
	*/
	
	/*
	glBegin(GL_LINE_STRIP);
	for (int k = 0; k < 150; k+=3)
	{	
		glVertex3d(circle1[k], circle1[k + 1], circle1[k + 2]);
		glVertex3d(circle2[k], circle2[k + 1], circle2[k + 2]);
	}
	glVertex3d(circle1[0], circle1[1], circle1[2]);
	glVertex3d(circle2[0], circle2[1], circle2[2]);
	glEnd();
	*/

	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 4.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'd':
		day = day + 1;
		cout << day << endl;
		glutPostRedisplay();
		break;
	case 'f':
		day = day - 1;
		cout << day << endl;
		glutPostRedisplay();
		break;
	case 'c':
		year = year + 1;
		cout << year << endl;
		glutPostRedisplay();
		break;
	case 'v':
		year = year - 1;
		cout << year << endl;
		glutPostRedisplay();
		break;
	case 'r':
		year = 0;
		day = 0;
		cout << year << endl;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(300, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}