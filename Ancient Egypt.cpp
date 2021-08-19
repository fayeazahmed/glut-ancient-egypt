#include <iostream>
#include <GL/glut.h>
#include <random>

using namespace std;

GLfloat boatX = -0.72;
GLfloat tx = 0.01; // translateX for boats
GLfloat circleTx = -.0005;
GLfloat circleTy = -.0001;
bool isDay = true;
bool rising = false;
// Keeping colors in global variable to change them later
int boatR = 0; 
int skyR = 217, skyG = 215, skyB = 195;
int desertR = 235, desertG = 242, desertB = 157;
int pyramidLeftR = 251, pyramidLeftG = 199, pyramidLeftB = 124;
int pyramidRightR = 227, pyramidRightG = 141, pyramidRightB = 81;
int circleB = 80;
int riverG = 152, riverB = 201;
int ff = 1; // ff (fast forward)- value to be multiplied when 'f' is pressed to fast forward day-night cycle
// Sections dividing the landscape in parts
void sections()
{
	// Sky with some gradient
	glBegin(GL_QUADS);
	glColor3ub(85, 85, 85);
	glVertex2f(-1.0, 0.1);
	glVertex2f(1.0, .1);
	glColor3ub(skyR, skyG, skyB);
	glVertex2f(1, 1);
	glVertex2f(-1, 1);
	glEnd();
	glColor3ub(desertR, desertG, desertB);
	glRectf(1.0, 0.2, -1.0, 0.0);
	glColor3ub(48, riverG, riverB);
	glRectf(1.0, 0.1, -1.0, -0.8);
	glColor3ub(224, 193, 144);
	glRectf(1.0, -0.8, -1.0, -1.0);
}

void pyramid()
{
	// Right pyramid
	glBegin(GL_TRIANGLES);
	glColor3ub(pyramidRightR, pyramidRightG, pyramidRightB);
	glVertex2f(0.0, 0.2);
	glVertex2f(0.4, 0.6);
	glVertex2f(0.56, 0.2);
	glEnd();
	glColor3ub(199, 152, 98);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.4, 0.6);
	glVertex2f(0.56, 0.2);
	glVertex2f(0.8, 0.2);
	glEnd();

	// Left pyramid
	glBegin(GL_TRIANGLES);
	glColor3ub(pyramidLeftR, pyramidLeftG, pyramidLeftB);
	glVertex2f(-0.3, 0.2);
	glVertex2f(0.0, 0.56);
	glVertex2f(0.1, 0.3);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.3, 0.2);
	glVertex2f(0.0, 0.2);
	glVertex2f(0.1, 0.3);
	glEnd();
	glColor3ub(199, 152, 98);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0, 0.56);
	glVertex2f(0.1, 0.3);
	glVertex2f(0.16, 0.36);
	glEnd();
}

struct stars
{
	float x, y;
};
struct stars starArr[110]; // Store x, y values for stars
int startCount = 90;
/* Uniform random numbers in range generated from - https://stackoverflow.com/a/7560564/11105382 */
void initStars()
{ 
	random_device rd; // obtain a random number from hardware
	mt19937 gen(rd()); // seed the generator
	uniform_real_distribution<float> distrx(-1, 1); // define the range
	uniform_real_distribution<float> distry(0.4, 0.96); // define the range
	for (int i = 0; i < startCount; i++) // Create 100 random x, y coordinates
		starArr[i] = { distrx(gen), distry(gen) };
}

void drawStars()
{
	glPointSize(2);
	glColor3ub(255, 255, 255);
	for (int i = 0; i < startCount; i++) {
		glBegin(GL_POINTS);
		glVertex2f(starArr[i].x, starArr[i].y);
		glEnd();
	}
}

void houses()
{
	// Left
	glColor3ub(180, 180, 179);
	glRectf(-0.8, 0.1, -0.88, 0.22);
	glColor3ub(97, 61, 1);
	glRectf(-0.82, 0.11, -0.84, 0.20);
	glRectf(-0.85, 0.18, -0.87, 0.21);

	// Middle
	glColor3ub(180, 180, 179);
	glRectf(-0.50, 0.1, -0.70, 0.20);
	glColor3ub(97, 61, 1);
	glRectf(-0.53, 0.12, -0.57, 0.18);
	glRectf(-0.65, 0.12, -0.69, 0.18);

	// Right
	glColor3ub(180, 180, 179);
	glRectf(-0.16, 0.1, -0.42, 0.20);
	glColor3ub(97, 61, 1);
	glRectf(-0.18, 0.12, -0.30, 0.18);
	glRectf(-0.38, 0.12, -0.41, 0.18);
}

void trees()
{
	// Left
	glColor3ub(61, 48, 0);
	glRectf(-0.74, 0.1, -0.78, 0.26);
	glColor3ub(18, 161, 46);
	glBegin(GL_POLYGON);
	glVertex2f(-0.74, 0.26);
	glVertex2f(-0.66, 0.24);
	glVertex2f(-0.62, 0.30);
	glVertex2f(-0.66, 0.40);
	glVertex2f(-0.76, 0.42);
	glVertex2f(-0.90, 0.30);
	glVertex2f(-0.84, 0.24);
	glVertex2f(-0.74, 0.26);
	glEnd();

	// Right
	glColor3ub(61, 48, 0);
	glRectf(-0.48, 0.1, -0.50, 0.26);
	glColor3ub(18, 161, 46);
	glBegin(GL_POLYGON);
	glVertex2f(-0.48, 0.26);
	glVertex2f(-0.36, 0.26);
	glVertex2f(-0.44, 0.43);
	glVertex2f(-0.58, 0.40);
	glVertex2f(-0.62, 0.26);
	glVertex2f(-0.58, 0.22);
	glVertex2f(-0.48, 0.26);
	glEnd();
}

void boats()
{
	// Left
	glPushMatrix();
	glTranslatef(tx, 0, 0);
	glColor3ub(boatR, 108, 108);
	glBegin(GL_POLYGON);
	glVertex2f(boatX, -0.52);
	glVertex2f(boatX + 0.08, -0.6);
	glVertex2f(boatX + 0.4, -0.6);
	glVertex2f(boatX + 0.48, -0.52);
	glVertex2f(boatX, -0.52);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(boatX + 0.04, -0.56);
	glVertex2f(boatX  - 0.04, -0.48);
	glVertex2f(boatX + 0.08, -0.4);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(boatX + 0.44, -0.56);
	glVertex2f(boatX + .52, -0.48);
	glVertex2f(boatX + .4, -0.4);
	glEnd();
	glColor3ub(224, 193, 144);
	glRectf(boatX + 0.23, -0.52, boatX + 0.21, -0.43);

	// Right
	glColor3ub(boatR + 90, 108, 108);
	glBegin(GL_POLYGON);
	glVertex2f(-boatX, -0.52);
	glVertex2f(-(boatX + 0.08), -0.6);
	glVertex2f(-(boatX + 0.4), -0.6);
	glVertex2f(-(boatX + 0.48), -0.52);
	glVertex2f(-boatX, -0.52);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-(boatX + 0.04), -0.56);
	glVertex2f(-(boatX - 0.04), -0.48);
	glVertex2f(-(boatX + 0.08), -0.4);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-(boatX + 0.44), -0.56);
	glVertex2f(-(boatX + .52), -0.48);
	glVertex2f(-(boatX + .4), -0.4);
	glEnd();
	glColor3ub(224, 193, 144);
	glRectf(-(boatX + 0.23), -0.52, -(boatX + 0.21), -0.43);
	glPopMatrix();

	// Middle
	glPushMatrix();
	glTranslatef(-tx, 0, 0);
	glColor3ub(boatR + 180, 108, 108);
	glBegin(GL_POLYGON);
	glVertex2f(boatX + 1.08, -0.12);
	glVertex2f(boatX + 1.0, -0.2);
	glVertex2f(boatX + 0.68, -0.2);
	glVertex2f(boatX + 0.6, -0.12);
	glVertex2f(boatX + 1.08, -0.12);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(boatX + 1.04, -0.16);
	glVertex2f(boatX + 1.12, -0.08);
	glVertex2f(boatX + 1.0, 0.0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(boatX + 0.64, -0.16);
	glVertex2f(boatX + 0.56, -0.08);
	glVertex2f(boatX + 0.68, 0.0);
	glEnd();
	glColor3ub(224, 193, 144);
	glRectf(boatX + 0.82, -0.02, boatX + 0.84, -0.12);
	glPopMatrix();
}

void grass()
{
	GLfloat top = -0.84; // Track the top edge of each grass
	glColor3ub(55, 184, 128);
	glRectf(-1.0, -1.0, 1.0, -0.84);
	while (top < 1.0) {
		glBegin(GL_TRIANGLES);
		glVertex2f(top, -0.64);
		glVertex2f(top - 0.12, -0.88);
		glVertex2f(top - 0.04, -0.88);
		glEnd();
		top += 0.12;
	}
}

// Sun / Moon
void circles()
{
	int triangles = 20; //# of triangles used to draw circle
	GLfloat radius = 0.06f;
	GLfloat twicePi = 2.0f * 3.1416;
	glPushMatrix();
	glTranslatef(circleTx, circleTy, 0);
	glColor3ub(244, 225, circleB);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0, 0.9); // center of circle
	for (int i = 0; i <= triangles; i++) {
		glVertex2f(
			0.0 + (cos(i * twicePi / triangles) * radius),
			0.9 + (sin(i * twicePi / triangles) * radius)
		);
	}
	glEnd();
	glPopMatrix();
}

void display(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	sections();
	if(!isDay)
		drawStars();
	circles();
	pyramid();
	houses();
	trees();
	grass();
	boats();

	glutSwapBuffers();
}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0); //Add a timer
	tx += .005 * ff;
	if (tx > 1.75) {
		tx = -tx;
		boatR += 30;
		if (boatR > 255)
			boatR = 0;
	}
	// Translate sun/moon upwards or downwards based on rising state
	if (!rising) {
		circleTx -= .00005 * ff;
		circleTy -= .00025 * ff;
	}
	else {
		circleTx += .00005 * ff;
		circleTy += .00025 * ff;
	}
	// Cycle between day and night after sun/moon rises or sets
	if (circleTy < -0.6) {
		circleB = (isDay) ? 200 : 80;
		skyR = (isDay) ? 0 : 217;
		skyG = (isDay) ? 0 : 215;
		skyB = (isDay) ? 0 : 195;
		pyramidLeftR = (isDay) ? 171 : 251;
		pyramidLeftG = (isDay) ? 119 : 199;
		pyramidLeftB = (isDay) ? 75 : 124;
		desertR = (isDay) ? 191 : 235;
		desertG = (isDay) ? 196 : 242;
		desertB = (isDay) ? 128 : 157;
		riverG = (isDay) ? 113 : 152;
		riverB = (isDay) ? 140 : 201;
		pyramidRightR = (isDay) ? 232 : 227;
		pyramidRightG = (isDay) ? 168 : 141;
		pyramidRightB = (isDay) ? 123 : 81;
		isDay = !isDay;
		rising = true;
	}
	if (circleTy > 0) {
		rising = false;
		ff = 1;
	}
}

void kbcallback(unsigned char key, int x, int y)
{
	if (key == 'f') {
		ff = (ff == 1) ? 20 : 1; // Cycle between 1x and 20x speed
		glutPostRedisplay();
	}
}

void mousecallback(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		float xpos = ((float)x / (float)1000) * 2.0f - 1.0f;
		float ypos = -(((float)y / (float)1000) * 2.0f - 1.0f);
		if (ypos > 0.1) {
			starArr[startCount] = { xpos, ypos };
			startCount++;
			glutPostRedisplay();
		}	
	}
}

void init(void)
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ancient Egypt");
	glOrtho(-1.01, 1.01, -1.01, 1.01, -1.01, 1.01);
	glMatrixMode(GL_MODELVIEW);
	initStars();
}

int main()
{
	init();
	glutDisplayFunc(display);
	glutTimerFunc(25, timer, 0); //Add a timer
	glutKeyboardFunc(kbcallback);
	glutMouseFunc(mousecallback);
	glutMainLoop();
	return 0; 
}