#pragma once

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#define PI 3.1415926
/* 每个图形最多的顶点数 */
#define MAX_VERTEX 10
/* 画的图形最多的个数 */
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

//画弧线，相对偏移量XY，开始的弧度，结束的弧度，半径
void glArc(double x, double y, double start_angle, double end_angle, double radius)
{
	//开始绘制曲线
	glBegin(GL_LINE_STRIP);
	//每次画增加的弧度
	double delta_angle = PI / 180;
	//画圆弧
	for (double i = start_angle; i <= end_angle; i += delta_angle)
	{
		//绝对定位加三角函数值
		double vx = x + radius * cos(i);
		double vy = y + radius*sin(i);
		glVertex2d(vx, vy);
	}
	//结束绘画
	glEnd();
}


//画圆
void glCircle(double x, double y, double radius)
{
	//画全圆
	glArc(x, y, 0, 2 * PI, radius);
}

/* 绘制填充的圆形 */
void glColorCircle(int x, int y, int R, GLubyte color[3])
{
	/* 开始绘制曲线 */
	glBegin(GL_POLYGON);
	/* 设置颜色 */
	glColor3ub(color[0], color[1], color[2]);
	/* 每次画增加的弧度 */
	double delta_angle = PI / 180;
	/* 画圆弧 */
	for (double i = 0; i <= 2 * PI; i += delta_angle)
	{
		/* 绝对定位加三角函数值 */
		double	vx = x + R * cos(i);
		double	vy = y + R*sin(i);
		glVertex2d(vx, vy);
	}
	/* 结束绘画 */
	glEnd();
	glFlush();
}

//画线，传入两点坐标
void glLine(int x1, int y1, int x2, int y2) {
	//画封闭线
	glBegin(GL_LINE_STRIP);
	//一点
	glVertex2d(x1, y1);
	//二点
	glVertex2d(x2, y2);
	//结束画线
	glEnd();
}

/* 画点 */
void glPoints(int x, int y) {
	glBegin(GL_POINTS);
	/* 点直接设置为黑色 */
	glColor3ub(0, 0, 0);
	glPointSize(100);
	glVertex2d(x, y);
	glEnd();
	glFlush();
}

/* 判断两个颜色是否相等 */
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

