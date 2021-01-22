
#include <stdlib.h>  
#include <GL/glut.h>  
#include<iostream>
using namespace std;
GLfloat speed = 0.0;// 用于设置设置旋转速率
GLfloat rote = 0.0;//设置旋转角度
GLfloat anglex = 0.0;//X 轴旋转
GLfloat angley = 0.0;//Y 轴旋转
GLfloat anglez = 0.0;//Z 轴旋转
GLint WinW = 400;
GLint WinH = 400;
int Mode = 1;//设置模式
GLfloat remeberx;//当左键按下时记录鼠标坐标  
GLfloat remebery;//当右键按下时记录鼠标坐标
GLfloat no_mat[] = { 0.0,0.0,0.0,1.0 };
GLfloat mat_ambient[] = { 0.7,0.7,0.7,1.0 };
GLfloat mat_diffuse[] = { 0.1,0.5,0.8,1.0 };
GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
GLfloat no_shininess[] = { 0.0 };//没有高光
GLfloat low_shininess[] = { 5.0 };//中高光
GLfloat high_shininess[] = { 100.0 };//高高光
GLfloat blackColor[] = { 0.0,0.0,0.0,1.0 };//黑色
GLfloat light_position[] = { 1,1,1,0 };
GLfloat greyColor[] = { 0.5, 0.5, 0.5, 1.0 };//灰色

GLfloat whiteColor[] = { 1.0,1.0,1.0,1.0 };//白色
void init(void)
{

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, greyColor);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	//glClearColor(1.0, 1.0, 1.0, 0.0); //背景色  
    
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glColor3f(1.0, 0.0, 0.0); //画笔红色
	glLoadIdentity();  //加载单位矩阵  
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(rote, 0.0f, 1.0f, 0.0f);
	glRotatef(anglex, 1.0, 0.0, 0.0);
	glRotatef(angley, 0.0, 1.0, 0.0);
	glRotatef(anglez, 0.0, 0.0, 1.0);
	glEnable(GL_LIGHTING);
	switch (Mode)
	{
	case 1:
	case 2:
		glDisable(GL_LIGHTING);
		
		break;
	case 3://仅有环境光
		//glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, no_mat);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
		break;
	case 4://环境光和漫反射光
		//glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
		break;
	case 5://低高光
		//glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
		break;
	case 6:
		//glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
		break;
	}
	//glColor3f(0.0, 0.0, 0.2);
	if(Mode==1)
	glutWireTeapot(1);
	else
	{
		glutSolidTeapot(1);
	}
	rote += speed;
	glutSwapBuffers();
	glPopMatrix();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			speed = 0;
			rote = 0;
			remeberx = x;//当左键按下时记录鼠标坐标  
			remebery = y;
			cout << "left" << endl;
		}

	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			speed += 1.0f;
			cout << "right" << endl;
		}

	}

}
void motion(int x, int y)
{
	GLint deltax = remeberx - x;
	GLint deltay = remebery - y;
	anglex += 360 * (GLfloat)deltax / (GLfloat)WinW;//根据屏幕上鼠标滑动的距离来设置旋转的角度  
	angley += 360 * (GLfloat)deltay / (GLfloat)WinH;
	anglez += 360 * (GLfloat)deltay / (GLfloat)WinH;
	remeberx = x;//记录此时的鼠标坐标，更新鼠标坐标  
	remebery = y;
	glutPostRedisplay();
	glutPostRedisplay();
}
//键盘响应函数，用于显示模式的转换
void keyboardFunc(unsigned char key, int x, int y) {

	switch (key) {

	case '1':

	case '2':

	case '3':

	case '4':

	case '5':

	case '6':

		Mode = key - '0';
		break;

	case 'q':

		exit(0);


	}

	glutPostRedisplay();
	


}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("旋转的茶壶");
	init();
	glutKeyboardFunc(keyboardFunc);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}