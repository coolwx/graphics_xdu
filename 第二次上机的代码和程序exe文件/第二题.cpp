#include <GL/glut.h>

void init()
{
	glClearColor(1, 1, 1, 1);
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
		glOrtho(-50.0, 50.0, -50.0 / aspectRatio, 50.0 / aspectRatio, -50.0, 50.0);
	else
		glOrtho(-50.0 * aspectRatio, 50.0 * aspectRatio, -50.0, 50.0, -50.0, 50.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);//先画对称轴
	glBegin(GL_LINES);
		glVertex3f(-5, 0, 0);
		glVertex3f(20, 25, 0);
		glEnd();
	glColor3f(1, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRecti(0, 0, 15, 5);//一开始的矩形
	glTranslatef(0,5,0);
	glRotatef(45,0,0,1);
	glScalef(1,-1,0);
	glRotatef(-45,0,0,1);
	glTranslatef(0,-5,0);
	glRecti(0, 0, 15, 5);//最后变换的矩形
	glFlush();
}
int main(int argc,char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Cube");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}