#pragma once
#include <string.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
using namespace std;
class Profile
{
public:
	Profile();
	Profile(GLdouble* x, GLdouble* y, GLdouble* z);
	Profile(double z_offset, double radius);
	~Profile();
	static const int MAX_VERTICES_NUM = 360;
	void setPosVal(GLdouble x, GLdouble y, GLdouble z, int vertices);
	void triangularize(Profile* p2);
	GLdouble* getPosVal(int vertices);
	void draw();


private:
	GLdouble* posX;
	GLdouble* posY;
	GLdouble* posZ;
};

