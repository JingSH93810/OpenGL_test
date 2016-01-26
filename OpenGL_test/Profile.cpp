#include "Profile.h"



Profile::Profile()
{
	this->posX = NULL;
	this->posY = NULL;
	this->posZ = NULL;
}

Profile::Profile(GLdouble * x, GLdouble * y, GLdouble * z)
{
	this->posX = x;
	this->posY = y;
	this->posZ = z;
}

Profile::Profile(double z_offset, double radius)
{
	double PI = 3.1415926;
	GLdouble* x = new GLdouble[MAX_VERTICES_NUM];
	GLdouble* y = new GLdouble[MAX_VERTICES_NUM];
	GLdouble* z = new GLdouble[MAX_VERTICES_NUM];
	//画圆弧
	for (int i = 0; i < MAX_VERTICES_NUM; i++)
	{
		//每次画增加的弧度
		double delta_angle = 2 * PI * i / MAX_VERTICES_NUM;
		//绝对定位加三角函数值
		x[i] = radius * cos(delta_angle);
		y[i] = radius*sin(delta_angle);
		z[i] = z_offset;
	}
	
	this->posX = x;
	this->posY = y;
	this->posZ = z;
}


Profile::~Profile()
{
	delete this->posX;
	delete this->posY;
	delete this->posZ;
}

void Profile::setPosVal(GLdouble x, GLdouble y, GLdouble z, int vertices)
{
	this->posX[vertices] = x;
	this->posY[vertices] = x;
	this->posZ[vertices] = x;
}

void Profile::triangularize(Profile* p2)
{

	glBegin(GL_TRIANGLE_STRIP);
	for (int k = 0; k < 360; k++)
	{
		glVertex3dv(this->getPosVal(k));
		glVertex3dv(p2->getPosVal(k));
	}
	glVertex3dv(this->getPosVal(0));
	glVertex3dv(p2->getPosVal(0));
	glEnd();
}

GLdouble* Profile::getPosVal(int vertices)
{
	GLdouble val[3] = { this->posX[vertices],this->posY[vertices],this->posZ[vertices] };
	return val;
}


void Profile::draw()
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < MAX_VERTICES_NUM; i++)
	{
		glVertex3dv(getPosVal(i));
	}
	glEnd();
}
