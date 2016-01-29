#pragma once
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Triangle.h"



class Profile
{
public:
	Profile();
	Profile(GLdouble* x, GLdouble* y, GLdouble* z);
	Profile(double z_offset, double radius);
	~Profile();
	static const int MAX_VERTICES_NUM = 50;
	void setPosVal(GLdouble x, GLdouble y, GLdouble z, int vertices);
	void triangularize(Profile* p2);
	GLdouble* getPosVal(int vertices);
	void draw();


private:
	GLdouble* posX;
	GLdouble* posY;
	GLdouble* posZ;
	Triangle* triangles;
};

