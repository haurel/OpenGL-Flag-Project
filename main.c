#include "GLOS.H"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#define POINTS 4
#define POINTS_2 3

void myinit(void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK desenareSteag();
void CALLBACK desenareBat();
void CALLBACK desenareScenaSteag();
void CALLBACK soare();
void CALLBACK deseneazaMunte(float a, float b);
void CALLBACK deseneazaScenaMunte(float a,float b, float c, float d, float e);
void CALLBACK deseneazaScenaMunti();


GLUquadricObj *obj;
static int x = 0, y = 0, camera = 0;
void CALLBACK MutaStanga(void)
{
	x = x - 4;
}

void CALLBACK MutaDreapta(void)
{
	x = x + 4;
}

void CALLBACK cameraa(void)
{
	camera = camera + 4;
}
/*
GLfloat ctrlpoints[4][4][3] = {
	{
		{ -2.0, -1.5, 0.0 },{ -1.0, -1.0, 0.0 },{ 0.5, -1.0, 0.0 },{1.5, -1.5, 0.0 }
	},
	{
		{ -2.0, -0.5, 0.0 },{ -1.0, 0.5, 0.0 },{ 0.5, 0.5, 0.0 },{ 1.5, -0.5, 0.0 }
	},
	{
		{ -2.0, 0.5, 0.0 },{ -1.0, 2.0, 0.0 },{ 0.5, 2.0, 0.0 },{ 1.5, 0.5, 0.0 }
	},
	{
		{ -2.0, 1.5, 0.0 },{ -1.0, 2.0, 0.0 },{ 0.5, 2.0, 0.0 },{ 1.5, 1.5, 0.0 }
	}
};*/

GLfloat ctrlpoints[4][4][3] = {
	{
		{ -1.5, -1, 0.0 },{ -0.5, -0.5, 0.0 },{ 0.5, -0.5, 0.0 },{ 1, -1, 0.0 }
	},
	{
		{ -1.5, -0.5, 0.0 },{ -0.5, 0.0, 0.0 },{ 0.5, 0.0, 0.0 },{ 1.0, -0.5, 0.0 }
	},
	{
		{ -1.5, 0.5, 0.0 },{ -0.5, 1.5, 0.0 },{ 0.5, 1.5, 0.0 },{ 1.0, 0.5, 0.0 }
	},
	{
		{ -1.5, 1, 0.0 },{ -0.5, 1.5, 0.0 },{ 0.5, 1.5, 0.0 },{ 1, 1, 0.0 }
	}
};


void myinit(void)
{
	glClearColor(0.392, 0.584, 0.929, 1.0);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);

	glFrontFace(GL_CW);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_COLOR_MATERIAL);
	
	glShadeModel(GL_FLAT);
}

void CALLBACK display(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glRotatef((GLfloat)camera, 1, 0, 0);

	desenareScenaSteag();
	soare();
	deseneazaScenaMunti();

	glFlush();
	auxSwapBuffers();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-16.0, 16.0, -16.0*(GLfloat)h / (GLfloat)w,
			16.0*(GLfloat)h / (GLfloat)w, -16.0, 16.0);
	else
		glOrtho(-16.0*(GLfloat)w / (GLfloat)h,
			16.0*(GLfloat)w / (GLfloat)h, -16.0, 16.0, -16.0, 16.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CALLBACK desenareSteag()
{
	int i, j;
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	for (j = 0; j <= 6; j++) {
		glBegin(GL_LINE_STRIP);
		for (i = 0; i <= 30; i++)
			glEvalCoord2f((GLfloat)i / 30.0, (GLfloat)j / 6.0);
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (i = 0; i <= 30; i++)
			glEvalCoord2f((GLfloat)j / 6.0, (GLfloat)i / 30.0);
		glEnd();
	}
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints[0][0][0]);

}

void CALLBACK desenareBat()
{
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(2, 1);
	glVertex2i(2, 6);
	glEnd();
}

void CALLBACK desenareScenaSteag()
{	
	GLfloat albastru[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat galben[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat rosu[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat maro[] = { 0.545, 0.271, 0.075 };

	GLfloat ambient[] = { 0.3, 0.1, 0.2, 1.0 };
	GLfloat diffuse[] = { 0.8, 0.6, 0.3, 1.0 };
	GLfloat shininess[] = { 128.0 };
	GLfloat mat_emission[] = { 0.2, 0.234, 0.2, 0.0 };

	//Bat
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, maro);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glColor3f(0.545, 0.271, 0.075);
	glTranslatef(3, -9.0, 3.0);
	desenareBat();
	glPopMatrix();
	glLineWidth(1); // reset line
	
	//Red
	glPushMatrix();
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, rosu);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(6.6, -4.0, 3.0);
	desenareSteag();
	glPopMatrix();


	//Yellow
	glPushMatrix();
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, galben);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(8.6, -4.0, 3.0);
	glScaled(-1, 1, 1);
	desenareSteag();
	glPopMatrix();

	//Blue
	glPushMatrix();
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, albastru);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, albastru);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(11.6, -4.0, 3.0);
	desenareSteag();
	glPopMatrix();

}

void CALLBACK soare()
{
	GLfloat position[] = { 0.0, 10, 10.0, 1.0 };
	GLfloat global_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

	glPushMatrix();
	glTranslatef(x, position[1], position[2]);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 0.0);
	auxSolidSphere(2.5);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void CALLBACK deseneazaMunte(float a, float b)
{
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);
	GLfloat munte[] = { 0.412, 0.412, 0.412, 1.0 };
	//GLfloat ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat no_mat[] = { 0.6, 0.0, 0.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.0, 0.1, 1.0 };
	GLfloat mat_specular[] = { 0.1, 0.1, 0.0, 0.0 };
	GLfloat mat_emission[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat shininess[] = { 128.0 };
	glColor3f(0.412, 0.412, 0.412);
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glRotatef(260, 1.0, 0.0, 0.0);
	//gluCylinder(obj, 10, 0.5, 9, 30, 10);
	gluCylinder(obj, a, b, 9, 30, 10);
	glPopMatrix();
}

void CALLBACK deseneazaScenaMunte(float a ,float b, float c, float d, float e)
{
	// a = dimensiune munte, b = dimensiune varf, c = x, d = y, e = z
	glPushMatrix();
	glRotatef(12, 1, 0, 0);
	glTranslatef(c, d, e);
	deseneazaMunte(a, b);
	glPopMatrix();
}

void CALLBACK deseneazaScenaMunti()
{
	deseneazaScenaMunte(10, 0, -20, -20, 0);
	deseneazaScenaMunte(10, 0, -10, -15, 10);
	deseneazaScenaMunte(10, 0, -25, -20, 4);
	deseneazaScenaMunte(10, 0.2, 5, -15, 6);
	deseneazaScenaMunte(20, 0, 15, -20, -5);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_DOUBLE | AUX_RGB);
	auxInitPosition(100, 100, 900, 500);
	auxInitWindow("haurel - Steag");
	myinit();
	auxKeyFunc(AUX_LEFT, MutaStanga);
	auxKeyFunc(AUX_RIGHT, MutaDreapta);
	auxKeyFunc(AUX_DOWN, cameraa);
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return(0);
}