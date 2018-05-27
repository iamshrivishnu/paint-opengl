#define _USE_MATH_DEFINES
#include<math.h>
#include<string.h>
#include<windows.h>
#include<GLUT/glut.h>

int xmax = 1366, ymax = 768;
int brushsize = 3;
int presentcolor = 0;
int shape = 0;
int screen;
int xscroll = 0;

bool mousedown = false;
bool done = false;
bool issolid;

GLfloat brush_color_array[][4][3] = { { { 1.0,0.0,0.0 },{ 0.0,0.0,1.0 },{ 0.0,1.0,0.0 },{ 1.0,0.0,1.0 } },
{ { 1.0,1.0,0.0 },{ 0.0,1.0,1.0 },{ 1.0,1.0,1.0 },{ 0.35,0.35,0.30 } } };
GLfloat xo = 0.0;
GLfloat yo = 0.0;
GLfloat xl = 0.0;
GLfloat yl = 0.0;

void keyboardfunction(unsigned char key, int mousex, int mousey);
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0, xmax, 0, ymax);
	glMatrixMode(GL_PROJECTION);
	glColor3f(0.0,0.0,0.0);
	glFlush();
}

void writestring(void *font, const char *string, int x, int y)
{
	glRasterPos2f(x, y);
	for (int i = 0; i < strlen(string); i++)
		glutBitmapCharacter(font, string[i]);
}


void defaultset() {
	glColor3f(0.50, 0.50, 0.50);
	glRectf(0.0, 0.0, xmax, 0.25 * ymax);
	int  row = 4, column = 2;
	float xf = (0.20 * xmax) / column;
	float yf = (0.20 * ymax) / row;
	for (int i = 0; i < column; i++) {
		for (int j = 0; j < row; j++) {
			glColor3fv(brush_color_array[i][j]);
			glRectf(((i + 1) * xf), ((j + 1) * yf), ((i + 1) * xf) + (xf * 0.5), ((j + 1) * yf) + (yf * 0.5));
			glColor3f(0.0, 0.0, 0.0);
			glLineWidth(2.0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(((i + 1) * xf), ((j + 1) * yf));
			glVertex2f(((i + 1) * xf), ((j + 1) * yf) + (yf * 0.5));
			glVertex2f(((i + 1) * xf) + (xf * 0.5), ((j + 1) * yf) + (yf * 0.5));
			glVertex2f(((i + 1) * xf) + (xf * 0.5), ((j + 1) * yf));
			glEnd();
			if ((i * 4) + j == presentcolor) {
				glColor3f(0.05, 0.50, 0.05);
				glLineWidth(2.0);
				glBegin(GL_LINE_LOOP);
				glVertex2f(((i + 1) * xf) - 5, ((j + 1) * yf) - 5);
				glVertex2f(((i + 1) * xf) - 5, ((j + 1) * yf) + (yf * 0.5) + 5);
				glVertex2f(((i + 1) * xf) + (xf * 0.5) + 5, ((j + 1) * yf) + (yf * 0.5) + 5);
				glVertex2f(((i + 1) * xf) + (xf * 0.5) + 5, ((j + 1) * yf) - 5);
				glEnd();
			}
		}
	}

	//Point
	if (shape == 0)
		glColor3f(0.0, 1.0, 1.0);
	else
		glColor3f(1.0, 1.0, 0.0);
	glRectf(0.35 * xmax, 0.15 * ymax, 0.45 * xmax, 0.2 * ymax);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.35 * xmax, 0.15 * ymax);
	glVertex2f(0.35 * xmax, 0.20 * ymax);
	glVertex2f(0.45 * xmax, 0.20 * ymax);
	glVertex2f(0.45 * xmax, 0.15 * ymax);
	glEnd();
	writestring(GLUT_BITMAP_TIMES_ROMAN_24, "POINT", 0.37 * xmax, 0.165 * ymax);

	//Line
	if (shape == 1)
		glColor3f(0.0, 1.0, 1.0);
	else
		glColor3f(1.0, 1.0, 0.0);
	glRectf(0.35 * xmax, 0.05 * ymax, 0.45 * xmax, 0.1 * ymax);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.35 * xmax, 0.05 * ymax);
	glVertex2f(0.35 * xmax, 0.10 * ymax);
	glVertex2f(0.45 * xmax, 0.10 * ymax);
	glVertex2f(0.45 * xmax, 0.05 * ymax);
	glEnd();
	writestring(GLUT_BITMAP_TIMES_ROMAN_24, "LINE", 0.37 * xmax, 0.065 * ymax);

	//Circle
	if (shape == 2)
		glColor3f(0.0, 1.0, 1.0);
	else
		glColor3f(1.0, 1.0, 0.0);
	glRectf(0.55 * xmax, 0.05 * ymax, 0.65 * xmax, 0.1 * ymax);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.55 * xmax, 0.05 * ymax);
	glVertex2f(0.55 * xmax, 0.1 * ymax);
	glVertex2f(0.65 * xmax, 0.1 * ymax);
	glVertex2f(0.65 * xmax, 0.05 * ymax);
	glEnd();
	writestring(GLUT_BITMAP_TIMES_ROMAN_24, "CIRCLE", 0.57 * xmax, 0.065 * ymax);

	//Box
	if (shape == 3)
		glColor3f(0.0, 1.0, 1.0);
	else
		glColor3f(1.0, 1.0, 0.0);
	glRectf(0.55 * xmax, 0.15 * ymax, 0.65 * xmax, 0.2 * ymax);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.55 * xmax, 0.15 * ymax);
	glVertex2f(0.55 * xmax, 0.20 * ymax);
	glVertex2f(0.65 * xmax, 0.20 * ymax);
	glVertex2f(0.65 * xmax, 0.15 * ymax);
	glEnd();
	writestring(GLUT_BITMAP_TIMES_ROMAN_24, "BOX", 0.57 * xmax, 0.165 * ymax);

	//Eraser
	if (shape == 4)
		glColor3f(0.0, 1.0, 1.0);
	else
		glColor3f(1.0, 1.0, 0.0);
	glRectf(0.75 * xmax, 0.05 * ymax, 0.85 * xmax, 0.1 * ymax);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.75 * xmax, 0.05 * ymax);
	glVertex2f(0.75 * xmax, 0.10 * ymax);
	glVertex2f(0.85 * xmax, 0.10 * ymax);
	glVertex2f(0.85 * xmax, 0.05 * ymax);
	glEnd();
	writestring(GLUT_BITMAP_TIMES_ROMAN_24, "ERASER", 0.770 * xmax, 0.065 * ymax);

	//Triangle
	if (shape == 5)
		glColor3f(0.0, 1.0, 1.0);
	else
		glColor3f(1.0, 1.0, 0.0);
	glRectf(0.75 * xmax, 0.15 * ymax, 0.85 * xmax, 0.2 * ymax);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.75 * xmax, 0.15 * ymax);
	glVertex2f(0.75 * xmax, 0.20 * ymax);
	glVertex2f(0.85 * xmax, 0.20 * ymax);
	glVertex2f(0.85 * xmax, 0.15 * ymax);
	glEnd();
	writestring(GLUT_BITMAP_TIMES_ROMAN_24, "TRIANGLE", 0.755 * xmax, 0.165 * ymax);

	//Is Solid
	glColor3f(1.0, 1.0, 0.0);
	glRectf(0.90 * xmax, 0.16 * ymax, 0.92 * xmax, 0.19 * ymax);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.90 * xmax, 0.16 * ymax);
	glVertex2f(0.90 * xmax, 0.19 * ymax);
	glVertex2f(0.92 * xmax, 0.19 * ymax);
	glVertex2f(0.92 * xmax, 0.16 * ymax);
	glEnd();
	if (issolid) {
		glLineWidth(2.25);
		glBegin(GL_POLYGON);
		glVertex2f(0.9025 * xmax, 0.165 * ymax);
		glVertex2f(0.9025 * xmax, 0.185 * ymax);
		glVertex2f(0.9175 * xmax, 0.185 * ymax);
		glVertex2f(0.9175 * xmax, 0.165 * ymax);
		glEnd();
	}
	glColor3f(1.0, 1.0, 0.0);
	writestring(GLUT_BITMAP_TIMES_ROMAN_24, "SOLID", 0.925 * xmax, 0.165 * ymax);
}

void drawcircle(int x, int y) {
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		glVertex2f(x + (brushsize*cosf(i * M_PI / 180.0)), y + (brushsize*sinf(i * M_PI / 180.0)));
	}
	glEnd();
}
void motionfunction(int mousex, int mousey)
{
	if (shape == 0) {
		int i = presentcolor / 4;
		int j = presentcolor % 4;
		glColor3fv(brush_color_array[i][j]);
		GLint x = mousex;
		GLint y = ymax - mousey;
		if (y > (0.25 * ymax) + brushsize) {
			drawcircle(x, y);
		}
		glFlush();
	}
	else if (shape == 4) {
		glColor3f(0.0, 0.0, 0.0);
		GLint x = mousex;
		GLint y = ymax - mousey;
		if (y > (0.25 * ymax) + brushsize) {
			drawcircle(x, y);
		}
		glFlush();
	}
}

void mousefunction(int button, int state, int x, int y) {
	int  row = 4, column = 2;
	float xf = (0.20 * xmax) / column;
	float yf = (0.20 * ymax) / row;
	for (int i = 0; i < column; i++) {
		for (int j = 0; j < row; j++) {
			if (x >((i + 1) * xf) && (ymax - y) >((j + 1) * yf) && x < ((i + 1) * xf) + (xf * 0.5) && (ymax - y) < ((j + 1) * yf) + (yf * 0.5)) {
				presentcolor = (i * 4) + j;
			}
		}
	}
	if (x > (0.35 * xmax) && (ymax - y) >(0.05 * ymax) && x < (0.45 * xmax) && (ymax - y) < (0.1 * ymax))
		shape = 1;//Line
	else if (x > (0.35 * xmax) && (ymax - y) >(0.15 * ymax) && x < (0.45 * xmax) && (ymax - y) < (0.2 * ymax))
		shape = 0;
	else if (x > (0.55 * xmax) && (ymax - y) >(0.05 * ymax) && x < (0.65 * xmax) && (ymax - y) < (0.1 * ymax))
		shape = 2;//Circle
	else if (x > (0.55 * xmax) && (ymax - y) >(0.15 * ymax) && x < (0.65 * xmax) && (ymax - y) < (0.2 * ymax))
		shape = 3;//Box
	else if (x > (0.75 * xmax) && (ymax - y) >(0.05 * ymax) && x < (0.85 * xmax) && (ymax - y) < (0.1 * ymax))
		shape = 4;//Eraser
	else if (x > (0.75 * xmax) && (ymax - y) >(0.15 * ymax) && x < (0.85 * xmax) && (ymax - y) < (0.2 * ymax))
		shape = 5;//Triangle
	else if (x > (0.90 * xmax) && (ymax - y) >(0.16 * ymax) && x < (0.92 * xmax) && (ymax - y) < (0.19 * ymax) && state == GLUT_DOWN)
		issolid = !issolid;//Change solid state
	if ((ymax - y) > (0.25 * ymax) + brushsize) {
		if (state == GLUT_DOWN && !mousedown) {
			mousedown = true;
			xo = x;
			yo = (ymax - y);
		}
		else if (state == GLUT_UP && !done && mousedown) {
			done = true;
			xl = x;
			yl = (ymax - y);
		}
	}
	glutPostRedisplay();
}

void display(void) {
	if (mousedown == true && done == true) {
		if (shape == 1) {//Line
			int i = presentcolor / 4;
			int j = presentcolor % 4;
			glColor3fv(brush_color_array[i][j]);
			glBegin(GL_LINES);
			glVertex2f(xo, yo);
			glVertex2f(xl, yl);
			glEnd();
		}
		else if (shape == 2) {//Circle
			int i = presentcolor / 4;
			int j = presentcolor % 4;
			glColor3fv(brush_color_array[i][j]);
			float r = sqrtf(pow(xl - xo, 2) + pow(yl - yo, 2));
			if (issolid)
				glBegin(GL_POLYGON);
			else
				glBegin(GL_LINE_LOOP);
			for (float i = 0.0; i < (2 * M_PI); i = i + 0.01) {
				glVertex2f(xo + (r * cosf(i)), yo + (r * sinf(i)));
			}
			glEnd();
		}
		else if (shape == 3) {//Box
			int i = presentcolor / 4;
			int j = presentcolor % 4;
			glColor3fv(brush_color_array[i][j]);
			if (issolid)
				glBegin(GL_POLYGON);
			else
				glBegin(GL_LINE_LOOP);
			glVertex2f(xo, yo);
			glVertex2f(xo, yl);
			glVertex2f(xl, yl);
			glVertex2f(xl, yo);
			glEnd();
		}
		else if (shape == 5) {//Triangle
			int i = presentcolor / 4;
			int j = presentcolor % 4;
			glColor3fv(brush_color_array[i][j]);
			if (issolid)
				glBegin(GL_POLYGON);
			else
				glBegin(GL_LINE_LOOP);
			glVertex2f(xo, yo);
			glVertex2f(xl + ((xo - xl) / 2), yl);
			glVertex2f(xl, yo);
			glEnd();
		}
		mousedown = false;
		done = false;
	}
	defaultset();
	glFlush();
}

void startscreen()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.749, 1.0);
	glVertex2f(-xmax, ymax);
	glColor3f(0.90, 0.049, 1.0);
	glVertex2f(-xmax, 0);
	glColor3f(0.780, 0.082, 0.522);
	glVertex2f(-xmax, -ymax);
	glColor3f(0.10, 0.545, 0.950);
	glVertex2f(-xmax / 2, -ymax / 2);
	glColor3f(0.10, 0.045, 0.050);
	glVertex2f(xmax, -ymax);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(xmax, -ymax/2);
	glColor3f(0.780, 0.082, 0.22);
	glVertex2f(xmax, ymax);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	writestring(GLUT_BITMAP_TIMES_ROMAN_24, "PINTAR", 0.45 * xmax, 0.80 * ymax);
	glPopMatrix();
	glColor3f(1.0,0.0,0.0);
	if ((xscroll / 50) % 4 == 0)
		writestring(GLUT_BITMAP_TIMES_ROMAN_24, "Loading", 0.75 * xmax, 0.05 * ymax);
	else if ((xscroll / 50) % 4 == 1)
		writestring(GLUT_BITMAP_TIMES_ROMAN_24, "Loading .", 0.75 * xmax, 0.05 * ymax);
	else if ((xscroll / 50) % 4 == 2)
		writestring(GLUT_BITMAP_TIMES_ROMAN_24, "Loading . .", 0.75 * xmax, 0.05 * ymax);
	else if((xscroll / 50) % 4 == 3)
		writestring(GLUT_BITMAP_TIMES_ROMAN_24, "Loading . . .", 0.75 * xmax, 0.05 * ymax);
	glRectf(0.0, 0.11 * ymax,xscroll,0.1 * ymax);
	glutPostRedisplay();
	xscroll++;
	glFlush();
	Sleep(5);
	if (xscroll > xmax) {
		glutDestroyWindow(screen);
		screen = glutCreateWindow("Paint");
		glutSetWindow(screen);
		glutFullScreen();
		myInit();
		glutDisplayFunc(display);
		glutKeyboardFunc(keyboardfunction);
		glutMouseFunc(mousefunction);
		glutMotionFunc(motionfunction);
		glutMainLoop();
	}
}

void keyboardfunction(unsigned char key, int mousex, int mousey) {
	switch (key) {
	case '+':brushsize++;
		break;
	case '-':if (brushsize > 1.0)
		brushsize--;
		break;
	case 'c':
	case 'C':
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		glutPostRedisplay();
		break;
	case 'q':
	case 'Q':glutDestroyWindow(screen);
		     exit(0);
	default:break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(xmax, ymax);
	glutInitWindowPosition(0, 0);
	screen = glutCreateWindow("PAINT TOOL");
	glutFullScreen();
	myInit();
	glutDisplayFunc(startscreen);
	glutKeyboardFunc(keyboardfunction);
	glutMainLoop();
}