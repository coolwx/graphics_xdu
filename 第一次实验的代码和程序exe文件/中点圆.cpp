#include <GL/glut.h>

class screenPt
{
private:
	GLint x, y;
public:
	screenPt()
	{
		x = y = 0;
	}
	void setCoords(GLint xCoordValue, GLint yCoordValue)
	{
		x = xCoordValue;
		y = yCoordValue;
	}
	GLint getx()
	{
		return x;
	}
	GLint gety()
	{
		return y;
	}
	void incrementx()
	{
		x++;
	}
	void decrementy()
	{
		y--;
	}
};
void setPixel(GLint xcoord, GLint yCoord)
{
	glBegin(GL_POINTS);
	glVertex2i(xcoord, yCoord);
	glEnd();
}
void circleMidpoint(GLint xc, GLint yc, GLint redius)
{
	screenPt circlept;
	GLint p = 1 - redius;
	circlept.setCoords(0, redius);
	void circleplotpoints(GLint, GLint, screenPt);
	circleplotpoints(xc,yc,circlept);
	while (circlept.getx() < circlept.gety())
	{
		circlept.incrementx();
		if (p < 0)
		{
			p +=1 + 2 * circlept.getx();

		}
		else
		{
			circlept.decrementy();
			p += 2 * (circlept.getx() - circlept.gety()) + 1;
		}
		circleplotpoints(xc, yc, circlept);
	}
}
void circleplotpoints(GLint xc,GLint yc,screenPt circlePt)
{
	setPixel(xc + circlePt.getx(), yc + circlePt.gety());
	setPixel(xc - circlePt.getx(), yc + circlePt.gety());
	setPixel(xc + circlePt.getx(), yc - circlePt.gety());
	setPixel(xc - circlePt.getx(), yc - circlePt.gety());
	setPixel(xc + circlePt.gety(), yc + circlePt.getx());
	setPixel(xc - circlePt.gety(), yc + circlePt.getx());
	setPixel(xc + circlePt.gety(), yc - circlePt.getx());
	setPixel(xc - circlePt.gety(), yc - circlePt.getx());


}

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
		glOrtho(-100.0, 100.0, -100.0 / aspectRatio, 100.0 / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void show()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f,1.0f);
	glPointSize(5);
	circleMidpoint(0, 0, 50);
	glFlush();
}
int main(int argc,char** argv)

{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("ÖÐµãÔ²Ëã·¨");

	init();

	glutDisplayFunc(show);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}

