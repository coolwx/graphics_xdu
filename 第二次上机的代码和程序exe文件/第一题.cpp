#include <GL/glut.h>
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(45.0, 1.0, 1.0, 1.0);//����������1,1,1����ָ��������ת45��,Ϊ�˹۲췽��
	
	glutWireCube(10.0);
	glLoadIdentity();//��ʼ������״̬

	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(10.0, 20.0, 10.0); //��xƽ��10��y���������ƶ�20����λ��z��10�����ľ��󷴶�����ָ��
	glScalef(2, 1, 0.5);
	glTranslatef(-10, -20,-10);
	glRotatef(45.0, 1.0, 1.0, 1.0);//����������1,1,1����ָ��������ת45�㣬Ϊ�˹۲췽��
	glutWireCube(10.0);
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
		glOrtho(-50.0, 50.0, -50.0 / aspectRatio, 50.0 / aspectRatio, -50.0, 50.0);
	else
		glOrtho(-50.0 * aspectRatio, 50.0 * aspectRatio, -50.0, 50.0, -50.0, 50.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc,char **argv)
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