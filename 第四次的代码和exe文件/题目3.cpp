#include <GL/glut.h>

GLsizei winwidth = 400, winheight = 300;
int mousecount = -1;//һ��ʼ��ʱ��û�е�
double xx[5];
double yy[5];
void init()
{
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 200, 0, 150);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);//���Ǻ�ɫ��
	glPointSize(10);
	if (mousecount != 4)//����������5��ʱ���Ҫ�������
	{
		glBegin(GL_POINTS);
		for (int i = 0; i <= mousecount; i++)
		{
			glVertex2i(xx[i], yy[i]);
		}
		glEnd();
	}
	else
	{
		glColor3f(0, 0, 1);//���������ɫ��
		glBegin(GL_POLYGON);
		for (int i = 0; i <= mousecount; i++)
		{
			glVertex2i(xx[i], yy[i]);
		}
		glEnd();
	}
	glFlush();
}

	void ChangeSize(GLsizei w, GLsizei h)
	{


		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();


		gluOrtho2D(0, w, 0, h);
		winwidth = w;
		winheight = h;
	}

void plotpoint(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void mouse(GLint button, GLint action, GLint x, GLint y)//���ص�
{
	

	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		glutPostRedisplay();
		mousecount++;
		xx[mousecount] = x;//��¼������x��y����
		yy[mousecount] = winheight - y;
	}
	if (mousecount == 5)
	{
		mousecount = 0;
	}
	glFlush();

}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winwidth, winheight);
	glutCreateWindow("������");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(mouse);
	glutMainLoop();
}