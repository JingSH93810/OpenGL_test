#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
struct Triangle
{
	GLdouble v1[3];
	GLdouble v2[3];
	GLdouble v3[3];

	Triangle() {
	}


	void setVertex(GLdouble* vertex1, GLdouble* vertex2, GLdouble* vertex3) {
		for (int i = 0; i < 3; i++)
		{

			v1[i] = vertex1[i];
			v2[i] = vertex2[i];
			v3[i] = vertex3[i];
		}
	}



	void draw() {
		glBegin(GL_LINE_LOOP);
		glVertex3dv(v1);
		glVertex3dv(v2);
		glVertex3dv(v3);
		glEnd();
	}
};