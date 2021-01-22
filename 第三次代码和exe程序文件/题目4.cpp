#include<GL/glut.h>

#include<stdlib.h>

#include<stdio.h>

#include<string>

#include<iostream>

double z = 40;//���z����

double speed = 0.05;//���ƶ��ٶ�

int depth = 1000;//ͶӰ��������

int start = 40;

int enable = 1;//�˶���ʹ���ź�

void myinit();

void Rendscene();

void Changesize(GLsizei w, GLsizei h);

void mykey(unsigned char key, int x, int y);

void specialkey(int key, int x, int y);

void displayc(double x, double y, double z, char str[]);



int main(int argc, char** argv)

{
    glutInit(&argc, argv);//��ʼ���̶���ʽ

    glutInitWindowPosition(300, 200);//��ʼ������λ��

    glutInitWindowSize(300, 300);//��ʼ�����ڿ�Ⱥ͸߶�

    glutCreateWindow("С����ֱ���˶�");

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//��ʼ����ʾģʽ��˫���洰�ڡ�RGBɫ�ʿռ䡢��Ȼ���



    myinit();//�Լ�����ĳ�ʼ�����������ñ�����ɫ



    glutDisplayFunc(Rendscene);//ע����ʾ�ص�����

    glutReshapeFunc(Changesize);//ע�ᴰ�����ܻص�����

    glutKeyboardFunc(mykey);//ע����̻ص�����

    glutSpecialFunc(specialkey);

    glutMainLoop();//�����¼�����ѭ��



}

void myinit()

{
    glClearColor(1, 1, 1, 1);//RGBA��ʽ���һ��Ϊ͸���ȣ�1��ʾ������ɫ��͸��



}



void Changesize(GLsizei w, GLsizei h)

{
    float ratio;

    if (h == 0)

        h = 1;

    ratio = (float)w / (float)h;

    glViewport(0, 0, w, h);//�����ӿ�

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();//�������ģʽΪͶӰ���󣬲��������ջ��λ��

    gluPerspective(60, ratio, start, depth);//͸�Ӿ���ѹ���ջ������͸�ӱ任���ĸ���������Ϊ���۾������Ƕȡ���߱ȡ�ǰ͸������롢��͸������루����ֵ������ʵ��͸���崦��z���ᣩ



    glEnable(GL_DEPTH_TEST);//����������Ȼ���������

    gluLookAt(0, 10, 40, 0, 0, 0, 0, 1, 0);//����ӣ�0,10,40������0,0,0,������0,1,0��Ϊ������





    glMatrixMode(GL_MODELVIEW);//ͶӰ�任���˽����ͼģʽ

    glLoadIdentity();



}



void Rendscene()

{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ����

    glColor3f(1, 0, 0);

    glMatrixMode(GL_MODELVIEW);//ͶӰ�任���˽����ͼģʽ

    glLoadIdentity();



    if (z > depth)

        z = 40;

    else

        z = z + speed;



    glTranslated(0.0, 0.0, -z);//�����������Ƶ�����ͼ��

    glutWireSphere(10, 180, 180);//���뾶Ϊ10��������Ⱦ180����γ����Ⱦ180����,�����Ǿ����ջ�����������ƶ���ת

    char str[] = "caowangxin";

    displayc(-30, 12, -z, str);



    glLoadIdentity();



    //������ƽ���ߵ���·

    glBegin(GL_LINES);

    glColor3f(0, 0, 0);

    glVertex3d(-10, -5, 30);

    glVertex3d(-15, -5, -depth);

    glEnd();

    glBegin(GL_LINES);

    glColor3f(0, 0, 0);

    glVertex3d(10, -5, 30);

    glVertex3d(15, -5, -depth);

    glEnd();



    glFlush();

    glutSwapBuffers();//������������֤����������

    glLoadIdentity();

    if (enable == 1)

        glutPostRedisplay();//�ص���������

}

void mykey(unsigned char key, int x, int y) //��ӦASCII��Ӧ�������ĵ�ǰx��yλ��Ҳ�����ء�

{
    switch (key)

    {


    case 'r':enable = 1;

        glutPostRedisplay();

        break;

    case 's':enable = 0;

        glutPostRedisplay();

        break;



    case 27:  exit(-1);

    }

}

void specialkey(int key, int x, int y)

{
    switch (key)

    {
    case GLUT_KEY_UP:

        speed += 1;

        break;

    case GLUT_KEY_DOWN:

        speed -= 1;

        break;



    }



}

void displayc(double x, double y, double z, char str[])//��ʾ�ַ�����

{
    glColor3f(0, 0, 0);

    //glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos3d(x, y, z);

    for (int i = 0; i < strlen(str); i++)

    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);

    }

    //glFlush();

}

