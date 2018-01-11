#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

bool cam_rot = false;

static int w = 0, h = 0;

double rotate_own_x = 0;
double rotate_own_y = 0;   
double rotate_own_z = 0;

double rotate_camera_x = 0;
double rotate_camera_y = 0;  
double rotate_camera_z = 0;

double rotate_pedestal_x = 0;
double rotate_pedestal_y = 0;   
double rotate_pedestal_z = 0;

double cam_x = 0.0f;
double cam_y = 1.0f;
double cam_z = 10.0f;

double look_x = 0.0f;
double look_y = 0.0f;
double look_z = 0.0f;

double zoom = 1;

bool all_around_centre_ped = false;

bool change = true;

//void changeViewPort(int w, int h)
//{
//	glViewport(0, 0, w, h);
//}

void Init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
}


void Reshape(int width, int height) {
	w = width;
	h = height;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, w / h, 1.0, 20.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouseWheel(int wheel, int direction, int x, int y)
{
	(direction > 0) ? zoom += 0.1 : zoom -= 0.1;
	glutPostRedisplay();
}


void Enable_Light0(void) {
	glEnable(GL_LIGHT0);

	GLfloat ambientLight[] = { 0.3, 0.3, 0.2, 1.0 };
	GLfloat diffuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specularLight[] = { 1.0, 0.8, 0.8, 1.0 };
	GLfloat position[] = { -1.0, 1.0, 2.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	//glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 5);
}

void Enable_Light1(void) {
	glEnable(GL_LIGHT1);

	GLfloat ambientLight[] = { 1.0, 0.0, 0.2, 1.0 };
	GLfloat diffuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { 0.0, 0.0, 3.0, 1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION,5.2);
	
}

void Enable_Light2(void) {
	glEnable(GL_LIGHT2);

	GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };
	GLfloat ambientLight[] = { 0.5, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { 0.0, 0.0, 10.0, 1.0 };

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT2, GL_POSITION, position);

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 10);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.0);

}


void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	Init();

	gluLookAt(cam_x, cam_y, cam_z, look_x, look_y, look_z, 0, 1, 0);

	glRotatef(rotate_camera_x, 1.0, 0.0, 0.0); //¬—® ¬Œ –”√ ÷≈Õ“–¿ —÷≈Õ€
	glRotatef(rotate_camera_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_camera_z, 0.0, 0.0, 1.0);

	// light 0
	//Enable_Light0();

	// light 1
	Enable_Light1();

	// light 2
	//Enable_Light2();

	glScalef(zoom, zoom, zoom);

	glPushMatrix();

	glBegin(GL_LINES);
	for (int i = -15; i <= 15; i++) {
		glVertex3f(i, -0.5, -15);
		glVertex3f(i, -0.5, 15);

		glVertex3f(-15, -0.5, i);
		glVertex3f(15, -0.5, i);
	};
	glEnd();
	glPopMatrix();


	if (all_around_centre_ped)
	{
		glRotatef(rotate_pedestal_x, 1.0, 0.0, 0.0); 
		glRotatef(rotate_pedestal_y, 0.0, 1.0, 0.0);
		glRotatef(rotate_pedestal_z, 0.0, 0.0, 1.0);
	}

	glPushMatrix();
	// a d s
	//bronze	0.2125	0.1275	0.054	0.714	0.4284	0.18144	0.393548	0.271906	0.166721	0.2
	//	gold	0.24725	0.1995	0.0745	0.75164	0.60648	0.22648	0.628281	0.555802	0.366065	0.4
	//	silver	0.19225	0.19225	0.19225	0.50754	0.50754	0.50754	0.508273	0.508273	0.508273	0.4

	// bronze
	glPushMatrix();
	GLfloat ambient_bronze[] = { 0.2125,0.1275,0.054, 1.00 };
	GLfloat diffuse_bronze[] = { 0.714,0.4284,0.18144, 1.00 };
	GLfloat specular_bronze[] = { 0.393548, 0.271906,0.166721, 1.00 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_bronze);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_bronze);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_bronze);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.2 * 128);
	glScalef(1.0, 0.9, 1.0);
	glTranslatef(1.0, -0.05, 0.0);
	//if (!all_around_centre_ped)
	//{
		glRotatef(rotate_own_x, 1.0, 0.0, 0.0);
		glRotatef(rotate_own_y, 0.0, 1.0, 0.0);
		glRotatef(rotate_own_z, 0.0, 0.0, 1.0);
	//}
	glutSolidCube(1);
	glPopMatrix();

	//gold 
	glPushMatrix();
	GLfloat ambient_gold[] = { 0.24725, 0.1995, 0.0745, 1.00 };
	GLfloat diffuse_gold[] = { 0.75164, 0.60648, 0.22648, 1.00 };
	GLfloat specular_gold[] = { 0.628281, 0.555802, 0.366065, 1.00 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_gold);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_gold);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_gold);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.4 * 128);
	glScalef(1.0, 2, 1.0);
	glTranslatef(0.0, 0.25, 0.0);
	//if (!all_around_centre_ped)
	//{
		glRotatef(rotate_own_x, 1.0, 0.0, 0.0);
		glRotatef(rotate_own_y, 0.0, 1.0, 0.0);
		glRotatef(rotate_own_z, 0.0, 0.0, 1.0);
	//}
	glutSolidCube(1);
	glPopMatrix();

	// silver
	glPushMatrix();
	GLfloat ambient_silver[] = { 0.19225,0.19225,0.19225, 1.00 };
	GLfloat diffuse_silver[] = { 0.50754,0.50754,0.50754, 1.00 };
	GLfloat specular_silver[] = { 0.508273,0.508273,0.508273, 1.00 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_silver);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_silver);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.4 * 128);
	glScalef(1.0, 1.3, 1.0);
	glTranslatef(-1.0, 0.11, 0.0);
	//if (!all_around_centre_ped)
	//{
		glRotatef(rotate_own_x, 1.0, 0.0, 0.0);
		glRotatef(rotate_own_y, 0.0, 1.0, 0.0);
		glRotatef(rotate_own_z, 0.0, 0.0, 1.0);
	//}
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();

}


void Mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		//rotate_own_x = 0;
		//rotate_own_y = 0;
		//rotate_own_z = 0;
		//glColor3ub(rand() % 255, rand() % 255, rand() % 255);
		////i < 7 ? i++ : i = 0;
		//glutPostRedisplay();
	}
}

//void zero_angles() {
//	rotate_pedestal_z = 0; rotate_pedestal_y = 0; rotate_pedestal_x = 0;
//	rotate_own_x = 0; rotate_own_y = 0;  rotate_own_z = 0;
//	rotate_camera_x = 0; rotate_camera_y = 0; rotate_camera_z = 0;
//}

//pedestal
void rotate_each(int key, int x, int y) {
	if (!all_around_centre_ped)
	{
		switch (key) {
		case GLUT_KEY_UP: rotate_own_x -= 5; break;
		case GLUT_KEY_DOWN: rotate_own_x += 5; break;

		case GLUT_KEY_RIGHT: rotate_own_y += 5; break;
		case GLUT_KEY_LEFT: rotate_own_y -= 5; break;

		case GLUT_KEY_F1: rotate_own_z += 5; break;
		case GLUT_KEY_F2: rotate_own_z -= 5; break;

		case GLUT_KEY_CTRL_L: all_around_centre_ped = !all_around_centre_ped; break;
		}
	}
	else
	{
		switch (key) {
		case GLUT_KEY_UP: rotate_pedestal_x -= 5; break;
		case GLUT_KEY_DOWN:rotate_pedestal_x += 5; break;

		case GLUT_KEY_RIGHT: rotate_pedestal_y += 5; break;
		case GLUT_KEY_LEFT: rotate_pedestal_y -= 5; break;

		case GLUT_KEY_F1: rotate_pedestal_z += 5; break;
		case GLUT_KEY_F2: rotate_pedestal_z -= 5; break;

		case GLUT_KEY_CTRL_L: all_around_centre_ped = !all_around_centre_ped; break;
		}
	}
	glutPostRedisplay();
}


void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w': rotate_camera_x -= 5; break;
	case 's': rotate_camera_x += 5; break;
	case 'a': rotate_camera_y += 5; break;
	case 'd': rotate_camera_y -= 5; break;
	case 'q': rotate_camera_z += 5; break;
	case 'e': rotate_camera_z -= 5; break;
	}
	glutPostRedisplay();
}



void mouseMove(int x, int y) {

	//glutPostRedisplay();
}

void mouseButton(int button, int state, int x, int y) {

	//if (button == GLUT_LEFT_BUTTON) {

	//}
}


int main(int argc, char* argv[]) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(900, 700);

	Init();

	glutCreateWindow("Opengl2");

	glutDisplayFunc(render);

	glutMouseWheelFunc(mouseWheel);
	glutSpecialFunc(rotate_each);
	glutKeyboardFunc(Keyboard);
	//glutIdleFunc(render);
	glutReshapeFunc(Reshape);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}


	glutMainLoop();
	return 0;
}

