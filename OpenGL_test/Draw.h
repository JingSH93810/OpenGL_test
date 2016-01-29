#pragma once

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#define PI 3.1415926
/* ÿ��ͼ�����Ķ����� */
#define MAX_VERTEX 10
/* ����ͼ�����ĸ��� */
#define MAX_PLOY 10
double calculateRadius(int x1, int y1, int x2, int y2) {
	double radius = (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) / 2.0);
	return radius;
}

double calculateDistance(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double calculateDistance(int x1, int y1, int x2, int y2, int x0, int y0) {
	double A = y2 - y1;
	double B = x1 - x2;
	double C = x2*y1 - x1*y2;
	double numerator = abs((y2 - y1)*x0 + (x1 - x2)*y0 + C);
	double denominator = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	return numerator / denominator;
}

double calculateAngle(int x1, int y1, int x2, int y2) {
	double angle = atan2(y2 - y1, x2 - x1) * 180.0 / PI;
	return angle;
}

//�����ߣ����ƫ����XY����ʼ�Ļ��ȣ������Ļ��ȣ��뾶
void glArc(double x, double y, double start_angle, double end_angle, double radius)
{
	//��ʼ��������
	glBegin(GL_LINE_STRIP);
	//ÿ�λ����ӵĻ���
	double delta_angle = PI / 180;
	//��Բ��
	for (double i = start_angle; i <= end_angle; i += delta_angle)
	{
		//���Զ�λ�����Ǻ���ֵ
		double vx = x + radius * cos(i);
		double vy = y + radius*sin(i);
		glVertex2d(vx, vy);
	}
	//�����滭
	glEnd();
}


//��Բ
void glCircle(double x, double y, double radius)
{
	//��ȫԲ
	glArc(x, y, 0, 2 * PI, radius);
}

/* ��������Բ�� */
void glColorCircle(int x, int y, int R, GLubyte color[3])
{
	/* ��ʼ�������� */
	glBegin(GL_POLYGON);
	/* ������ɫ */
	glColor3ub(color[0], color[1], color[2]);
	/* ÿ�λ����ӵĻ��� */
	double delta_angle = PI / 180;
	/* ��Բ�� */
	for (double i = 0; i <= 2 * PI; i += delta_angle)
	{
		/* ���Զ�λ�����Ǻ���ֵ */
		double	vx = x + R * cos(i);
		double	vy = y + R*sin(i);
		glVertex2d(vx, vy);
	}
	/* �����滭 */
	glEnd();
	glFlush();
}

//���ߣ�������������
void glLine(int x1, int y1, int x2, int y2) {
	//�������
	glBegin(GL_LINE_STRIP);
	//һ��
	glVertex2d(x1, y1);
	//����
	glVertex2d(x2, y2);
	//��������
	glEnd();
}

/* ���� */
void glPoints(int x, int y) {
	glBegin(GL_POINTS);
	/* ��ֱ������Ϊ��ɫ */
	glColor3ub(0, 0, 0);
	glPointSize(100);
	glVertex2d(x, y);
	glEnd();
	glFlush();
}

/* �ж�������ɫ�Ƿ���� */
bool sameColor(GLubyte color1[3], GLubyte color2[3])
{
	if (color1[0] - color2[0] < 5 && color1[1] - color2[1] < 5 && color1[2] - color2[1] < 5)
	{
		return(true);
	}
	else {
		return(false);
	}
}
