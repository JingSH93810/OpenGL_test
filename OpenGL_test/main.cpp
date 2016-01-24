#include <string.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "ProfileList.h"

using namespace std;

#define PI 3.1415926535898
#define R 2 
#define drawOneLine(x1,y1,x2,y2)  glBegin(GL_LINES);  \
   glVertex2f ((x1),(y1)); glVertex2f ((x2),(y2)); glEnd();
static double year = 0, day = 0;
static ProfileList profileList;
static GLdouble translateY = 0;
static int profileNumber = 0;

GLdouble* createNewProfile(GLdouble translateY);

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

void generateSurface(GLdouble* circle1, GLdouble* circle2) {

	glColor3f(1.0, 0.0, 0.0);
	for (int k = 0; k < 150; k += 3)
	{
		glVertex3d(circle1[k], circle1[k + 1], circle1[k + 2]);
		glVertex3d(circle2[k], circle2[k + 1], circle2[k + 2]);
	}
	glVertex3d(circle1[0], circle1[1], circle1[2]);
	glVertex3d(circle2[0], circle2[1], circle2[2]);

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);


	glRotated(day, 1.0, 0.0, 0.0);
	glRotated(year, 0.0, 1.0, 0.0);

	glPushMatrix();
	
	glBegin(GL_TRIANGLE_STRIP);
	Node* p = profileList.GetHead();
	while (p != NULL && p->next != NULL)
	{
		GLdouble* circle1 = p->vertexArray;
		GLdouble* circle2 = p->next->vertexArray;
		generateSurface(circle1, circle2);
		p = p->next;
	}
	glEnd();

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
	case 'q': 
	{
		translateY = translateY + 0.5;
		GLdouble* newProfile = createNewProfile(translateY);
		if (profileList.GetHead() == NULL)
		{
			cout << "no head , create one " << endl;
			Node* p = new Node(newProfile);
			profileList.SetHead(p);
		}
		else
		{
			profileList.Insert(newProfile, profileList.GetNodeNumber() - 1);
		}
		cout << translateY << endl;
		cout << profileList.GetNodeNumber() << endl;
		glutPostRedisplay();
		break;
	}
		
	case 27:
		exit(0);
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

GLdouble* createNewProfile(GLdouble translateY) {
	GLdouble* profile = new GLdouble[150];
	GLint circle_points = 50, i = 0;
	for (int i = 0, k = 0; i < circle_points && k < 150; i++, k += 3)
	{
		double angle = 2 * PI*i / circle_points;
		profile[k] = 2 * cos(angle);
		profile[k + 1] = translateY;
		profile[k + 2] = 2 * sin(angle);;
	}
	return profile;
}