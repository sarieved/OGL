#include <ctime>
#include <windows.h>
#include <gl\glew.h>
#include <gl\freeglut.h>

double rotate_x = 0;
double rotate_y = 0;
double rotate_z = 0;
int obj = 0;
float r = rand() % 255;
float g = rand() % 255;
float b = rand() % 255;

//√лобальные статические переменные хран€т текущий размер экрана
static int w = 0, h = 0, k = 12, k2 = 3;

//‘ункци€ вызываема€ перед вхождением в главный цикл
void Init()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

//‘ункци€ вызываема€ каждый кадр дл€ его отрисовки, вычислений и т.д.
void Update()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

//‘ункц€ вызываема€ при изменении размеров окна
void Reshape(int width, int height)
{
	w = width;   h = height;
}

void DrawRect(float x1, float y1, float x2, float y2, int FillFlag)
{
	glBegin(FillFlag ? GL_QUADS : GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(x1, y1);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(x2, y1);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(x2, y2);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(x1, y2);
	glEnd();
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);

	glColor3ub(r, g, b);

	switch (obj)
	{
	case 0:
		glutWireTeapot(0.5);
		break;
	case 1:
		glutSolidTeapot(0.5);
		break;
	case 2:
		glutWireSphere(0.5, 15, 15);
		break;
	case 3:
		glutSolidSphere(0.5, 15, 15);
		break;
	case 4:
		glutWireCube(0.5);
		break;
	case 5:
		glutSolidCube(0.5);
		break;
	case 6:
		glutWireIcosahedron();
		break;
	case 7:
		glutSolidIcosahedron();
		break;
	case 8:
		glutWireCone(0.5, 1, 10, 5);
		break;
	case 9:
		glutSolidCone(0.5, 1, 10, 5);
		break;
	case 10:
		glutWireTorus(0.2, 0.4, 16, 16);
		break;
	case 11:
		glutSolidTorus(0.2, 0.4, 16, 16);
		break;
	}
	glFlush();
	glutSwapBuffers();
}

void DisplayT2()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);

	switch (obj)
	{
	case 0:
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-0.73f, -0.73f, 0.0f);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.73f, -0.73f, 0.0f);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.73f, 0.73f, 0.0f);
		glEnd();
		break;

	case 1:
		glBegin(GL_TRIANGLES);
		glColor3f(0.4, 0.6, 1.0);
		glVertex3f(-0.73f, -0.73f, 0.0f);
		glVertex3f(0.73f, -0.73f, 0.0f);
		glVertex3f(0.73f, 0.73f, 0.0f);
		glColor3f(0.3, 0.9, 0.8);
		glVertex3f(-0.73f, -0.73f, 0.0f);
		glVertex3f(-0.73f, 0.73f, 0.0f);
		glVertex3f(0.73f, 0.73f, 0.0f);
		glEnd();
		break;

	case 2:
		DrawRect(-0.73f, -0.73f, 0.73f, 0.73f, 1);
		break;
	}
	glFlush();
	glutSwapBuffers();
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{

		switch (button)
		{
			case
				//GLUT_LEFT_BUTTON: obj = (obj + 1) % k;
				GLUT_LEFT_BUTTON: obj = (obj + 1) % k2;
				r = rand() % 255;
				g = rand() % 255;
				b = rand() % 255;
				break;

				case
					//GLUT_RIGHT_BUTTON: obj = (obj - 1) > 0 ? obj - 1 : (obj - 1 == 0 ? 0 : k - 1);
					GLUT_RIGHT_BUTTON : obj = (obj - 1) > 0 ? obj - 1 : (obj - 1 == 0 ? 0 : k2 - 1);
					r = rand() % 255;
					g = rand() % 255;
					b = rand() % 255;
					break;
		}
		glutPostRedisplay();
	}
}

void Keyboard(unsigned char key, int x, int y)
{
#define ESCAPE '\033'
	if (key == ESCAPE)
		exit(0);
}

void renderWireTeapot()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);
	glutWireTeapot(0.5);
	glFlush();
	glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
		case
			GLUT_KEY_UP: rotate_x += 5;
			break;

			case
				GLUT_KEY_DOWN: rotate_x -= 5;
				break;

				case
					GLUT_KEY_RIGHT: rotate_y += 5;
					break;

					case
						GLUT_KEY_LEFT: rotate_y -= 5;
						break;

						case
							GLUT_KEY_PAGE_UP: rotate_z += 5;
							break;

						case GLUT_KEY_PAGE_DOWN: rotate_z -= 5;
							break;
	}
	glutPostRedisplay();
}

int main(int argcp, char **argv)
{
	srand(time(NULL));
	glutInit(&argcp, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 800);
	glutCreateWindow("MyOpenGL");
	//glutDisplayFunc(Display);
	glutDisplayFunc(DisplayT2);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
}