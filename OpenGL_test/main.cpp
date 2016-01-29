#include <string.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "ProfileList.h"
#include "Profile.h"
#include "Draw.h"
using namespace std;


/* 窗口长宽的一半 */
int halfWidth, halfHeight;
/* 绘制多边形的起始标志，0是开始绘制，1是结束绘制，初始为-1 */
int drawStatus = -1;

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


ProfileList profileList;
GLdouble translateY = 0;
GLdouble offset = -20;
GLdouble geoCenter_X = 0;
GLdouble geoCenter_Y = 0;
GLdouble geoRotation = 0;
GLdouble profileRadius = 0;
GLdouble radius_X[2];
GLdouble radius_Y[2];
int clickCount = 0;
/*用户指定旋转角度*/
GLdouble angle = 0;
GLdouble normal[3] = {0.0, 0.0, 0.0};

double bottle[] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 0.85, 0.8, 0.75, 0.7, 0.65, 0.6, 0.61};
int m = 19;

GLdouble length = 0;


//函数用来画图
void display(void)
{
	//GL_COLOR_BUFFER_BIT表示清除颜色
	glClear(GL_COLOR_BUFFER_BIT);
	//设置画线颜色

	/* 绘制取色盘 */
	glColorCircle(-280, 280, 10, red);
	glColorCircle(-250, 280, 10, yellow);
	glColorCircle(-220, 280, 10, grey);
	glColorCircle(-180, 280, 10, nowColor);
	glColorCircle(250, 280, 10, startBtn);
	glColorCircle(280, 280, 10, endBtn);

	for (int i = 0; i < clickCount; i++)
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
		glTranslated(geoCenter_X, geoCenter_Y, 0.0);
		glRotated(geoRotation, 0, 0, 1);
		glRotated(angle, 1, 0, 0);
		glColor3d(1,0,0);
		Node* p = profileList.GetHead();
		if (p != NULL) p->profile->draw();
		while (p != NULL && p->next != NULL)
		{
			glColor3b(0, 0, 0);
			p->profile->triangularize(p->next->profile);
			p = p->next;
			glColor3d(1, 0, 0);
			p->profile->draw();
		}
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
	glMatrixMode(GL_MODELVIEW);

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
				printf("drawStatus:%d\n", drawStatus);
				/* 如果点击了结束绘制的按钮 */
			}
			else if (sameColor(color, endBtn)) {
				if (clickCount == 2) {
					drawStatus = 1;
					printf("drawStatus:%d\n", drawStatus);
					clickCount = 0;
					printf("x1:%d, y1:%d, x2:%d, y2:%d\n", radius_X[0], radius_Y[0], radius_X[1], radius_Y[1]);

					geoCenter_X = (radius_X[1] + radius_X[0]) / 2.0;
					printf("origin x:%f\n", geoCenter_X);
					geoCenter_Y = (radius_Y[1] + radius_Y[0]) / 2.0;
					printf("origin y:%f\n", geoCenter_Y);
					profileRadius = calculateRadius(radius_X[0], radius_Y[0], radius_X[1], radius_Y[1]);
					printf("radius:%f\n", profileRadius);
					geoRotation = calculateAngle(radius_X[0], radius_Y[0], radius_X[1], radius_Y[1]);
					printf("angle a:%f\n", geoRotation);

					Profile* newProfile = new Profile(translateY, profileRadius);
					translateY = translateY + offset;
					if (profileList.GetHead() == NULL)
					{
						cout << "no head , create one " << endl;
						Node* p = new Node(newProfile);
						profileList.SetHead(p);
					}


				}


			}
			/* 如果点击的是下方的绘图页面 */
		}
		else {
			/* 如果当前是正在取点状态 */
			if (drawStatus == 0)
			{
				translateY = 0;
				profileList.~ProfileList();
				if (clickCount == 2) {
					clickCount = 0;
				}
				if (clickCount < 2) {
					radius_X[clickCount] = x - halfWidth;
					radius_Y[clickCount] = halfHeight - y;
					glColorCircle(radius_X[clickCount], radius_Y[clickCount], 5, red);
					clickCount++;
				}


			}

			if (drawStatus == 1 && clickCount == 0) {
				cout << " !!!! " << endl;
				int click_X = x - halfWidth;
				int click_Y = halfHeight - y;
				length = calculateDistance(radius_X[0], radius_Y[0], radius_X[1], radius_Y[1], click_X, click_Y);
				cout << length << endl;
				double transCount = -length / offset;
				cout << transCount << endl;
				for (int i = 0; i < transCount; i++)
				{
					Profile* newProfile = new Profile(translateY, profileRadius);
					translateY = translateY + offset;
					profileList.Insert(newProfile, profileList.GetNodeNumber() - 1);
				}
			}
		}
	}
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && drawStatus == 1) {
		int click_X = x - halfWidth;
		int click_Y = halfHeight - y;
		double minorAxis = calculateDistance(radius_X[0], radius_Y[0], radius_X[1], radius_Y[1], click_X, click_Y);
		angle = acos(2 * minorAxis / (profileRadius * 2)) * 180 / PI;
		normal[1] = cos(angle);
		normal[2] = sin(angle);
		printf("minorDiameter: %f, angle: %f \n", minorAxis, angle);
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	{
		
		if (drawStatus == 1) {
			Profile* newProfile = new Profile(translateY, profileRadius);
			translateY = translateY + offset;
			profileList.Insert(newProfile, profileList.GetNodeNumber() - 1);
		}
		cout << translateY << endl;
		cout << profileList.GetNodeNumber() << endl;
		glutPostRedisplay();
		break;
		
		/*
		if (drawStatus == 1) {
			for (int i = 0; i < m; i++)
			{
				Profile* newProfile = new Profile(translateY, profileRadius*bottle[i]);
				translateY = translateY + offset;
				profileList.Insert(newProfile, profileList.GetNodeNumber() - 1);
			}
			
		}
		glutPostRedisplay();
		break;*/
	}

	case 27:
		exit(0);
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
	glutInitWindowPosition(500, 300);
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

