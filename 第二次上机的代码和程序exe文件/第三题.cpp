#include"windows.h" 
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
int currentMode = 0;
const int ModeNums = 6;
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
float rotheta = 0;
void rotatehex(void)
{
	rotheta += 3;
	if (rotheta > 360)
		rotheta -= 360;
	glutPostRedisplay();
 }
void myKey(unsigned char key, int x, int y) //��ӦASCII��Ӧ�������ĵ�ǰx��yλ��Ҳ�����ء�
{
	switch (key)
	{
	case ' ': currentMode = (currentMode + 1) % ModeNums;
		if (currentMode == 4)
			glutIdleFunc(rotatehex);
		else if (currentMode == 5)
			glutIdleFunc(NULL);
		else
		glutPostRedisplay(); //����GLUTˢ�µ�ǰ���� 
		break;
	case 27:  exit(-1);
	}
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	switch (currentMode)
	{
	case 0: glPointSize(5);
		glBegin(GL_POINTS);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(3.0, 3.0);
		glVertex2f(8.0, 3.0);
		glVertex2f(5.0, 8.0);
		glEnd();
		break;
	case 1: glBegin(GL_LINE_STRIP);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(3.0, 3.0);
		glVertex2f(8.0, 3.0);
		glVertex2f(5.0, 8.0);
		glEnd();
		break;
	case 2: glBegin(GL_LINE_LOOP);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(3.0, 3.0);
		glVertex2f(8.0, 3.0);
		glVertex2f(5.0, 8.0);
		glEnd();
		break;
	case 3: glBegin(GL_TRIANGLES);
		glColor3f(1.0, 1.0, 0.0);
		glVertex2f(3.0, 3.0);
		glVertex2f(8.0, 3.0);
		glVertex2f(5.0, 8.0);
		glEnd();
		break;
	case 4:
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(16 / 3, 14 / 3, 0);
		glRotatef(rotheta, 0, 0, 1);
		glTranslatef(-16 / 3, -14 / 3, 0);
		glBegin(GL_TRIANGLES);
		glColor3f(0, 1, 1);
		glVertex2f(3.0, 3.0);
		glVertex2f(8.0, 3.0);
		glVertex2f(5.0, 8.0);
		glEnd();
	case 5:
		glBegin(GL_TRIANGLES);
		glColor3f(0, 1, 1);
		glVertex2f(3.0, 3.0);
		glVertex2f(8.0, 3.0);
		glVertex2f(5.0, 8.0);
		glEnd();
	}
	glutSwapBuffers();
	glFlush();
}
void ChangeSize(GLsizei w, GLsizei h)
{
	float ratio;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ratio = (float)w / (float)h;
	if (w <= h)
		gluOrtho2D(0.0, 10.0, 0.0 / ratio, 10.0 / ratio);
	else
		gluOrtho2D(0.0 * ratio, 10.0 * ratio, 0.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc,char **argv)

{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(360, 360);
	glutCreateWindow("KeyboardFunc");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(myKey);  //Ϊ��ǰ�������ü��̻ص�������

	printf("Press space to continue,press escape to exit!\n");
	glutMainLoop();
	return 0;
}