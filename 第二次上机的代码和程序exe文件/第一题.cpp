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

	glRotatef(45.0, 1.0, 1.0, 1.0);//绕着向量（1,1,1）所指定的轴旋转45°,为了观察方便
	
	glutWireCube(10.0);
	glLoadIdentity();//初始化矩阵状态

	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(10.0, 20.0, 10.0); //沿x平移10，y轴正方向移动20个单位，z轴10，最后的矩阵反而最先指定
	glScalef(2, 1, 0.5);
	glTranslatef(-10, -20,-10);
	glRotatef(45.0, 1.0, 1.0, 1.0);//绕着向量（1,1,1）所指定的轴旋转45°，为了观察方便
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