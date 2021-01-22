#include<GL/glut.h>

#include<stdlib.h>

#include<stdio.h>

#include<string>

#include<iostream>

double z = 40;//球的z坐标

double speed = 0.05;//球移动速度

int depth = 1000;//投影视体的深度

int start = 40;

int enable = 1;//运动的使能信号

void myinit();

void Rendscene();

void Changesize(GLsizei w, GLsizei h);

void mykey(unsigned char key, int x, int y);

void specialkey(int key, int x, int y);

void displayc(double x, double y, double z, char str[]);



int main(int argc, char** argv)

{
    glutInit(&argc, argv);//初始化固定格式

    glutInitWindowPosition(300, 200);//初始化窗口位置

    glutInitWindowSize(300, 300);//初始化窗口宽度和高度

    glutCreateWindow("小球沿直线运动");

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//初始化显示模式：双缓存窗口、RGB色彩空间、深度缓存



    myinit();//自己定义的初始化函数，设置背景颜色



    glutDisplayFunc(Rendscene);//注册显示回调函数

    glutReshapeFunc(Changesize);//注册窗口重塑回调函数

    glutKeyboardFunc(mykey);//注册键盘回调函数

    glutSpecialFunc(specialkey);

    glutMainLoop();//进入事件处理循环



}

void myinit()

{
    glClearColor(1, 1, 1, 1);//RGBA形式最后一个为透明度，1表示窗体颜色不透明



}



void Changesize(GLsizei w, GLsizei h)

{
    float ratio;

    if (h == 0)

        h = 1;

    ratio = (float)w / (float)h;

    glViewport(0, 0, w, h);//定义视口

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();//定义矩阵模式为投影矩阵，并将矩阵堆栈单位化

    gluPerspective(60, ratio, start, depth);//透视矩阵压入堆栈，进行透视变换，四个参数依次为，眼睛睁开角度、宽高比、前透视面距离、后透视面距离（填正值，但其实该透视体处于z负轴）



    glEnable(GL_DEPTH_TEST);//开启更新深度缓冲区功能

    gluLookAt(0, 10, 40, 0, 0, 0, 0, 1, 0);//相机从（0,10,40）看向（0,0,0,），（0,1,0）为正方向





    glMatrixMode(GL_MODELVIEW);//投影变换完了进入绘图模式

    glLoadIdentity();



}



void Rendscene()

{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色缓存

    glColor3f(1, 0, 0);

    glMatrixMode(GL_MODELVIEW);//投影变换完了进入绘图模式

    glLoadIdentity();



    if (z > depth)

        z = 40;

    else

        z = z + speed;



    glTranslated(0.0, 0.0, -z);//把整个场景移到到视图中

    glutWireSphere(10, 180, 180);//画半径为10，经度渲染180条和纬度渲染180的球,由于是矩阵堆栈，所以是先移动后转

    char str[] = "caowangxin";

    displayc(-30, 12, -z, str);



    glLoadIdentity();



    //画两条平行线当做路

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

    glutSwapBuffers();//交换缓冲区保证有流畅动画

    glLoadIdentity();

    if (enable == 1)

        glutPostRedisplay();//回调生产动画

}

void mykey(unsigned char key, int x, int y) //响应ASCII对应键，鼠标的当前x和y位置也被返回。

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

void displayc(double x, double y, double z, char str[])//显示字符函数

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

