#include "Profile.h"

Profile::Profile()
{
	this->posX = NULL;
	this->posY = NULL;
	this->posZ = NULL;
	this->triangles = NULL;
}

Profile::Profile(GLdouble * x, GLdouble * y, GLdouble * z)
{
	this->posX = x;
	this->posY = y;
	this->posZ = z;
	this->triangles = NULL;
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
	this->triangles = NULL;
}


Profile::~Profile()
{
	delete this->posX;
	delete this->posY;
	delete this->posZ;
	delete this->triangles;
}

void Profile::setPosVal(GLdouble x, GLdouble y, GLdouble z, int vertices)
{
	this->posX[vertices] = x;
	this->posY[vertices] = x;
	this->posZ[vertices] = x;
}

void Profile::triangularize(Profile* p2)
{
	this->triangles = new Triangle[2 * MAX_VERTICES_NUM];
	
	for (int i = 0, k = 0; i < MAX_VERTICES_NUM; i++, k += 2)
	{	
		if (i - 1 < 0) {
			this->triangles[k].setVertex(this->getPosVal(i), p2->getPosVal(i), p2->getPosVal(MAX_VERTICES_NUM - 1));
			this->triangles[k+1].setVertex(this->getPosVal(i), p2->getPosVal(i), this->getPosVal(i+1));
		}
		else if (i + 1 == MAX_VERTICES_NUM) {
			this->triangles[k].setVertex(this->getPosVal(i), p2->getPosVal(i), p2->getPosVal(i-1));
			this->triangles[k+1].setVertex(this->getPosVal(i), p2->getPosVal(i), this->getPosVal(0));
		}
		else
		{
			this->triangles[k].setVertex(this->getPosVal(i), p2->getPosVal(i), p2->getPosVal(i - 1));
			this->triangles[k+1].setVertex(this->getPosVal(i), p2->getPosVal(i), this->getPosVal(i + 1));
		}
		
	}

	for (int i = 0; i < MAX_VERTICES_NUM*2; i++)
	{
		this->triangles[i].draw();
	}

}

GLdouble* Profile::getPosVal(int vertices)
{
	GLdouble* val = new GLdouble[3]{ this->posX[vertices],this->posY[vertices],this->posZ[vertices] };
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
