#include <GL/freeglut.h>
#include <math.h> 
#include <stdio.h>
#include <iostream>
using namespace std;

#define PI 3.1415926
/* 每个图形最多的顶点数 */
#define MAX_VERTEX 10
/* 画的图形最多的个数 */
#define MAX_PLOY 10
/* 窗口长宽的一半 */
int halfWidth, halfHeight;
/* 绘制多边形的起始标志，0是开始绘制，1是结束绘制，初始为-1 */
int drawStatus = -1;
/* 多边形结构体 */
struct polygon {
	/* 顶点坐标 */
	int x[MAX_VERTEX];
	int y[MAX_VERTEX];
	/* 定义第几个顶点 */
	int verNum;
	GLubyte color[3];
};
int radius_X[2];
int radius_Y[2];
int circle_count = 0;
struct circle
{
	/*圆心坐标*/
	double x;
	double y;
	/*圆半径*/
	double radius;
	double angle;
	GLubyte color[3];
};
circle circle1;
/* 各种颜色 */
GLubyte border[3] = { 0, 0, 0 };
GLubyte grey[3] = { 195, 195, 195 };
GLubyte yellow[3] = { 255, 243, 0 };
GLubyte red[3] = { 237, 28, 36 };
GLubyte darkGrey[3] = { 126, 126, 126 };
GLubyte white[3] = { 255, 255, 255 };
GLubyte startBtn[3] = { 10, 10, 10 };
GLubyte endBtn[3] = { 20, 20, 20 };
/* 当前颜色 */
GLubyte nowColor[3] = { 0, 0, 0 };
/* 声明多边形数组 */
polygon polygons[MAX_PLOY];
/* 记录画了几个多边形 */
int con = 0;
int day = 0;

double calculateRadius(int x1, int y1, int x2, int y2) {
	double radius = (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) / 2.0);
	return radius;
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

/* 绘制多边形 */
void glPolygons()
{
	if (con >= 0) {
		for (int i = 0; i <= con; i++) {
			/* 取到这个多边形 */
			polygon poly = polygons[i];
			/* 画封闭线 */
			glBegin(GL_LINE_LOOP);
			int num = poly.verNum;
			printf("num:%d\n", num);
			for (int j = 0; j < num; j++)
			{
				glColor3ub(poly.color[0], poly.color[1], poly.color[2]);
				glVertex2d(poly.x[j] - halfWidth, halfHeight - poly.y[j]);
				printf("polyx:%d,polyy:%d", poly.x[j], poly.y[j]);
			}
			/* 结束画线 */
			glEnd();
			/* 刷新 */
			glFlush();
		}
	}
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

//函数用来画图
void display(void)
{
	//GL_COLOR_BUFFER_BIT表示清除颜色
	glClear(GL_COLOR_BUFFER_BIT);
	//设置画线颜色
	glColor3f(0.5, 0.5, 0.5);

	/* 绘制取色盘 */
	glColorCircle(-280, 280, 10, red);
	glColorCircle(-250, 280, 10, yellow);
	glColorCircle(-220, 280, 10, grey);
	glColorCircle(-180, 280, 10, nowColor);
	glColorCircle(250, 280, 10, startBtn);
	glColorCircle(280, 280, 10, endBtn);

	for (int i = 0; i < circle_count; i++)
	{
		glColorCircle(radius_X[i], radius_Y[i], 5, red);
	}
	//保证前面的OpenGL命令立即执行，而不是让它们在缓冲区中等待 
	/* 绘制多边形 */
	//if(drawStatus == 1) glPolygons();
	if (drawStatus == 1) {
		glPushMatrix();

		glColorCircle(radius_X[0], radius_Y[0], 5, red);
		glColorCircle(radius_X[1], radius_Y[1], 5, red);
		glLine(radius_X[0], radius_Y[0], radius_X[1], radius_Y[1]);
		glTranslated(circle1.x, circle1.y, 0.0);
		glRotated(circle1.angle, 0, 0, 1);
		glRotated(day, 1, 0, 0);
		glColor3b(0,0,0);
		glCircle(0, 0, circle1.radius);
		glPopMatrix();
	}
	glFlush();
}


//窗口大小变化时调用的函数
void ChangeSize(GLsizei w, GLsizei h)
{
	//避免高度为0
	if (h == 0) {
		h = 1;
	}
	//定义视口大小，宽高一致  
	glViewport(0, 0, w, h);
	int half = 300;
	/* 定义宽高的一半 */
	halfHeight = 300;
	halfWidth = 300;
	//重置坐标系统，使投影变换复位
	glMatrixMode(GL_PROJECTION);
	//将当前的用户坐标系的原点移到了屏幕中心
	glLoadIdentity();
	//定义正交视域体  
	if (w<h) {
		//如果高度大于宽度，则将高度视角扩大，图形显示居中
		glOrtho(-half, half, -half*h / w, half*h / w, -half, half);
	}
	else {
		//如果宽度大于高度，则将宽度视角扩大，图形显示居中
		glOrtho(-half*w / h, half*w / h, -half, half, -half, half);
	}

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



/*鼠标点击事件 */
void mouseClick(int btn, int state, int x, int y)
{
	/* 选项卡的分界范围 */
	int optionHeight = 40;
	int optionWidth = 250;
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		/* 如果在颜色选项卡中点击 */
		if (y < optionHeight && x < optionWidth)
		{
			glReadPixels(x, 2 * halfHeight - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &nowColor);
			printf("r:%d,g:%d,b:%d\n", nowColor[0], nowColor[1], nowColor[2]);
			/* 设置绘图颜色并显示当前取色板颜色 */
			glColorCircle(-180, 280, 10, nowColor);
			/* 如果点击的是右侧选项按钮 */
		}
		else if (y < optionHeight && x > optionWidth) {
			//取当前的点
			GLubyte color[3];
			glReadPixels(x, 2 * halfHeight - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &color);
			printf("r:%d,g:%d,b:%d\n", color[0], color[1], color[2]);
			/* 如果点击了开始绘制的按钮 */
			if (sameColor(color, startBtn)) {
				drawStatus = 0;
				/* 开始画一个图形，顶点个数置零 */
				polygons[con].verNum = 0;
				printf("drawStatus:%d\n", drawStatus);
				/* 如果点击了结束绘制的按钮 */
			}
			else if (sameColor(color, endBtn)) {
				if(circle_count == 2) drawStatus = 1;
				circle_count = 0;
				day = 0;
				printf("x1:%d, y1:%d, x2:%d, y2:%d\n", radius_X[0], radius_Y[0], radius_X[1], radius_Y[1]);

				circle1.x = (radius_X[1] + radius_X[0]) / 2.0;
				printf("origin x:%f\n", circle1.x);
				circle1.y = (radius_Y[1] + radius_Y[0]) / 2.0;
				printf("origin y:%f\n", circle1.y);
				circle1.radius = calculateRadius(radius_X[0], radius_Y[0], radius_X[1], radius_Y[1]);
				printf("radius:%f\n", circle1.radius);
				circle1.angle = calculateAngle(radius_X[0], radius_Y[0], radius_X[1], radius_Y[1]);
				printf("angle a:%f\n", circle1.angle);

				/* 画的图形个数加一 */
				con++;
				printf("drawStatus:%d\n", drawStatus);
			}
			/* 如果点击的是下方的绘图页面 */
		}
		else {
			/* 如果当前是正在取点状态 */
			if (drawStatus == 0)
			{
				if (circle_count == 2) {
					circle_count = 0;
				}
				if (circle_count < 2) {
					radius_X[circle_count] = x - halfWidth;
					radius_Y[circle_count] = halfHeight - y;
					glColorCircle(radius_X[circle_count], radius_Y[circle_count], 5, red);
					circle_count++;
				}


			}
		}
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'd':
		day = day + 1;
		cout << day << endl;
		glutPostRedisplay();
		break;
	}
}


//程序入口
int main(int argc, char *argv[]) {
	//对GLUT进行初始化，并处理所有的命令行参数
	glutInit(&argc, argv);
	//指定RGB颜色模式和单缓冲窗口
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//定义窗口的位置
	glutInitWindowPosition(100, 100);
	//定义窗口的大小
	glutInitWindowSize(600, 600);
	//创建窗口，同时为之命名
	glutCreateWindow("OpenGL");
	//设置窗口清除颜色为白色
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//参数为一个函数，绘图时这个函数就会被调用
	glutDisplayFunc(&display);
	//参数为一个函数，当窗口大小改变时会被调用
	glutReshapeFunc(ChangeSize);
	/*鼠标点击事件，鼠标点击或者松开时调用 */
	glutMouseFunc(mouseClick);
	glutKeyboardFunc(keyboard);
	//该函数让GLUT框架开始运行，所有设置的回调函数开始工作，直到用户终止程序为止
	glutMainLoop();
	//程序返回
	return 0;
}