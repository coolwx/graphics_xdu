#include<GL/glut.h>
typedef struct {
	float x, y, z;
}Point;
Point ctrlpoints[4] = { {0.0,1.0,0.0},{3.0,0.0,0.0},{0.0,1.0,0.0},{-3.0,0.0,0.0} };
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
void DrawCurve(int n)
{
	Point p;
	double t, deltat, et0, et1, et2, et3;
	int i;
	deltat = 1.0 / (n - 1);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < 100; i++)
	{
		t = i * deltat;
		et3 = 2 * t * t * t - 3 * t * t + 1;
		et2 = -2 * t * t*t + 3 * t * t;
		et1 = t * t * t - 2 * t * t + 1;
		et0 = t * t * t - t * t;
		p.x = et3 * ctrlpoints[0].x +  et2 * ctrlpoints[1].x +   et1 * ctrlpoints[2].x + et0 * ctrlpoints[3].x;
		p.y = et3 * ctrlpoints[0].y +  et2 * ctrlpoints[1].y +   et1 * ctrlpoints[2].y + et0 * ctrlpoints[3].y;
		p.z = et3 * ctrlpoints[0].z +  et2 * ctrlpoints[1].z +   et1 * ctrlpoints[2].z + et0 * ctrlpoints[3].z;
		glVertex3f(p.x, p.y, p.z);
	}
	glEnd();

	glPointSize(5.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (i = 0; i < 2; i++)
		glVertex3f(ctrlpoints[i].x, ctrlpoints[i].y, ctrlpoints[i].z);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 2, 0);//画出向量1
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(3, 0, 0);
	glVertex3f(0, 0, 0);//画出向量2
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
		glOrtho(-5.0, 5.0, -5.0 / aspectRatio, 5.0 / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-5.0 * aspectRatio, 5.0 * aspectRatio, -5.0, 5.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("第三次实验第二次实验，hermite曲线");

	init();
	glutDisplayFunc(RenderScence);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();

	return 0;
}