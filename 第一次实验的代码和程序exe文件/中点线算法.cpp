#include <GL/glut.h>
#include <cstdlib>
#include <cmath>

void ChangeToStandard(GLint& x0, GLint& y0, GLint& x1, GLint y1)
{
	if (x1 < x0)
	{
		GLint tmpx = x1;
		GLint tmpy = y1;
		x1 = x0;
		x0 = tmpx;
		y1 = y0;
		y0 = tmpy;
	}
}
typedef struct {
	GLint x, y;
}Pixel;
void init()
{
	glClearColor(1, 1, 1, 1);
}
int Midpoint(GLint x0, GLint y0, GLint x1, GLint y1,Pixel points[])//可以画四种线段，也就是所有的情况都能画出来，斜率不论正负，不论大于一还是小于1
{
	ChangeToStandard(x0, y0, x1, y1);//保证x0<x1；
	GLint dx = x1 - x0;
	GLint dy = y1 - y0;
	GLint a = y0 - y1, b = x1 - x0, c = x1 * y0 - x0 * y1;
	int i = 0;
	points[i].x = x0;
	points[i].y = y0;
	
	if ((fabs(dx) > fabs(dy)) && dy > 0)
	{
		GLint d1 = 2 * a;
		GLint d2 = 2 * (a + b);
		GLint d = 2 * a + b;
		while (x0 < x1)//斜率0到1
		{
			i++;
			if (d < 0)
			{
				x0++;
				y0++;
				d += d2;
			}
			else
			{
				x0++;
				d += d1;
			}
			points[i].x = x0;
			points[i].y = y0;
		}
	}
	if ((fabs(dx) > fabs(dy)) && dy < 0)//斜率大于-1小于0
	{
		GLint d1 = 2 * a;
		GLint d2 = 2 * (a - b);
		GLint d = 2 * a - b;
		while (x0 < x1)
		{
			i++;
			if (d > 0)
			{
				x0++;
				y0--;
				d += d2;
			}
			else
			{
				x0++;
				d += d1;
			}
			points[i].x = x0;
			points[i].y = y0;
		}
	}
	if ((fabs(dx) <= fabs(dy)) && dy > 0)//斜率大于1
	{
		GLint d1 = 2*b;
		GLint d2 = 2*a+2*b;
		GLint d  =a +2*b;
		while (y0 < y1)
		{
			i++;
			if (d > 0)
			{
				x0++;
				y0++;
				d += d2;
			}
			else
			{
				y0++;
				d += d1;
			}
			points[i].x = x0;
			points[i].y = y0;
		}
	}
	if ((fabs(dx) <= fabs(dy)) && dy < 0)//斜率小于-1
	{
		GLint d1 = -2 * b;
		GLint d2 = 2 * a - 2 * b;
		GLint d = a - 2 * b;
		while (y0 > y1)
		{
			i++;
			if (d < 0)
			{
				x0++;
				y0--;
				d += d2;
			}
			else
			{
				y0--;
				d += d1;
			}
			points[i].x = x0;
			points[i].y = y0;
		}
	}
	return i;
}
void drawline(GLint x0, GLint y0, GLint x1, GLint y1)
{
	Pixel points[100];
	int num = Midpoint(x0, y0, x1, y1, points);
	glBegin(GL_POINTS);
	for (int i = 0; i <= num; i++)
	{
		glVertex2i(points[i].x, points[i].y);
	}
	glEnd();


}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.f);
	glPointSize(2);
	drawline(10, 80, 60, 10); // 在这里更改你的画线范围
	drawline(10, 10, 60, 80);
	drawline(10, 50, 40, 20);
	drawline(10, 20, 60, 30);
	glFlush();
}
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)
		glOrtho(-100.0, 100.0, -100.0 / aspectRatio, 100.0 / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc,char **argv)
{
	//在drawline之中可以更改画线段的范围；
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("中点线算法，在drawline里面改线段");

	init();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}

