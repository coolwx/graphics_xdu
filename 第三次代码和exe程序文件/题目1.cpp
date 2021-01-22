#include<GL/glut.h>
typedef struct {
	float x, y, z;
}Point;
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
void DrawCurve(int n)
{
	Point p,q;
	double t, deltat;
	int i;
	deltat = 1.0 / (n - 1);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < 100; i++)
	{
		t = i * deltat;
		p.x = t * t - 2 * t + 1;//��p��x����
		p.y = t * t * t - 2 * t * t + t;//��p��y����
	   p.z = 0;
		glVertex3f(p.x, p.y, p.z);
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < 100; i++)
	{
		t = i * deltat;
		q.x = t * t;//��q��x����
		q.y = t * t * t ;//��q��y����
		q.z = 0;
		glVertex3f(q.x, q.y, q.z);
	}
	glEnd();

	glPointSize(5.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 1, 0);
	glEnd();

}
void RenderScence()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	DrawCurve(100);

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
		glOrtho(-2.0, 2.0, -2.0 / aspectRatio, 2.0 / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-2.0 * aspectRatio, 2.0 * aspectRatio, -2.0, 2.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("�������ϻ���һ��ʵ��");

	init();
	glutDisplayFunc(RenderScence);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();

	return 0;
}