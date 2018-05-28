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
void CALLBACK pamant(void);
void CALLBACK deseneazaMunte(float a, float b, float c);
void CALLBACK deseneazaScenaMunte(float a,float b, float c, float d, float e, float f);
void CALLBACK deseneazaScenaMunti();
void CALLBACK animatie_steag();
void calcCoeficinetiPlan(float P[3][3], float coef[4]);
void MatriceUmbra(GLfloat puncte[3][3], GLfloat pozSursa[4], GLfloat mat[4][4]);


GLUquadricObj *obj;
static int x = 0, y = 0, camera = 0, z = 0, umbra = 0;
//GLfloat position[] = { 0.0, 10, 10.0, 1.0 };
GLfloat position[] = { 80.0, 90, 100.0, 1.0 };
GLfloat position_umbra[] = { 80.0, 90, -100.0, 1.0 };
void CALLBACK MutaStanga(void)
{
	position[0] = position[0] - 4;
	position_umbra[0] = position_umbra[0] - 4;
}

void CALLBACK MutaDreapta(void)
{
	position[0] = position[0] + 4;
	position_umbra[0] = position_umbra[0] + 4;
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
/*
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
*/
GLfloat ctrlpoints[4][4][3] = {
	{
		{ -10.5, -10.0, 0.0 },{ -10.5, -5, 4.0 },{ 10.5, -5, 0.0 },{ 10, -10, 2.5 }
	},
	{
		{ -10.5, -10.5, 2.0 },{ -10.5, 10.0, 4.0 },{ 10.5, 10.0, 2.0 },{ 10.0, -10.5, 2.5 }
	},
	{
		{ -10.5, 10.5, 2.0 },{ -10.5, 15.0, 4.0 },{ 10.5, 15.0, 2.0 },{ 10.0, 10.5, 2.5 }
	},
	{
		{ -10.5, 10.0, 0.0 },{ -10.5, 15.0, 4.0 },{ 10.5, 15.0, 0.0 },{ 10, 10, 2.5 }
	}
};


void myinit(void)
{
	glClearColor(0.392, 0.584, 0.929, 1.0);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);

	GLfloat ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat mat_specular[] = { 0.3f, 0.1f, 0.4f, 1.0f };
	GLfloat mat_shininess[] = { 128.0f };
	GLfloat global_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	glEnable(GL_LIGHTING); // activare iluminare
	glEnable(GL_LIGHT0);	// activare sursa 0	
	glEnable(GL_NORMALIZE);
	//permite urmarirea culorilor
	glEnable(GL_COLOR_MATERIAL);
	//seteaza proprietatile de material pentru a urma glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// seteaza sursa

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	//  seteaza maerialul
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


	glFrontFace(GL_CW);
	glEnable(GL_AUTO_NORMAL);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glShadeModel(GL_FLAT);
}

void CALLBACK display(void)
{	
	GLfloat matUmbra[4][4];
	//oricare 3 puncte din plan in ssens trigonometric
	//GLfloat puncte[3][3] = { { 100.0f,-100.0f, 100.0f },{ 80.0f,-160.0f,600.0f },{ 200.0f,-100.0f,100.0f } };
	
	GLfloat puncte[3][3] = { { 100.0f,-100.0f, 160.0f },{ 80.0f,-160.0f,600.0f },{ 200.0f,-100.0f,160.0f } };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	MatriceUmbra(puncte, position_umbra, matUmbra);

	glLoadIdentity();

	glPushMatrix();
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		umbra = 0;
		glRotatef((GLfloat)camera, 1, 0, 0);
		desenareScenaSteag();
	glPopMatrix();


	//deseneaza umbra
	//mai intai se dezactiveaz iluminarea si se salveaza starea matricei de proiectie
	glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		glPushMatrix();
			//apoi se inmulteste matricea curenta cu matricea de umbrire
			glMultMatrixf((GLfloat*)matUmbra);
			//si cu cea de rotatie
			//se deseneaza masina umbra cu negru
			glRotatef((GLfloat)camera, 1, 0, 0);
			//glScaled(1, -1, 1);
			//glTranslatef(0, 13, 0);
			umbra = 1;
			//glScalef(1, 1, 1);
			//desenareScenaSteag();
			desenareScenaSteag();
		glPopMatrix();
		//se deseneaza soarele
		glPushMatrix();
			soare();
		glPopMatrix();

		//se deseneaza muntii
		glRotatef((GLfloat)camera, 1, 0, 0);
		deseneazaScenaMunti();
		pamant();
		
	glPopAttrib();

	glFlush();
	auxSwapBuffers();
}


void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*
	if (w <= h)
		glOrtho(-16.0, 16.0, -16.0*(GLfloat)h / (GLfloat)w,
			16.0*(GLfloat)h / (GLfloat)w, -16.0, 16.0);
	else
		glOrtho(-16.0*(GLfloat)w / (GLfloat)h,
			16.0*(GLfloat)w / (GLfloat)h, -16.0, 16.0, -16.0, 16.0);*/
	if (w <= h)
		glOrtho(-100.0, 100.0, -100.0*(GLfloat)h / (GLfloat)w,
			100.0*(GLfloat)h / (GLfloat)w, -100.0, 100.0);
	else
		glOrtho(-100.0*(GLfloat)w / (GLfloat)h,
			100.0*(GLfloat)w / (GLfloat)h, -100.0, 100.0, -100.0, 100.0);
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
		glVertex2i(2, 50);
	glEnd();
}

void CALLBACK desenareScenaSteag()
{	
	//Bat
	glPushMatrix();
		if(umbra == 0)glColor3f(0.545, 0.271, 0.075);
		else glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-23, -80.0, 1.0);
		desenareBat();
		glPopMatrix();
		glLineWidth(1); // reset line
	
	//Blue
	glPushMatrix();
		if(umbra == 0)glColor3f(0.0, 0.0, 1.0);
		else glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-10, -40.0, 3.0);
		desenareSteag();
		glPopMatrix();


	//Yellow
	glPushMatrix();
		if(umbra == 0) glColor3f(1.0, 1.0, 0.0);
		else glColor3f(0.0, 0.0, 0.0);
		glTranslatef(10, -40.0, 3.0);
		glScaled(-1, 1, 1);
		desenareSteag();
		glPopMatrix();

	//Red
	glPushMatrix();
		if(umbra == 0)glColor3f(1.0, 0.0, 0.0);
		else glColor3f(0.0, 0.0, 0.0);
		glTranslatef(31, -40.0, 3.0);
		desenareSteag();
	glPopMatrix();

}




void CALLBACK soare()
{
	glPushMatrix();
		glTranslatef(position[0], position[1], position[2]);
		glDisable(GL_LIGHTING);
		glColor3f(1.0, 1.0, 0.0);
		auxSolidSphere(2.5);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

void CALLBACK pamant(void)
{
	glColor3f(0.133, 0.545, 0.133);
	glTranslatef(0, -130, 0);
	glRotatef(120, 1, 0, 0);
	glBegin(GL_QUAD_STRIP);
	glVertex2f(-1200, -1200);
	glVertex3f(-1200, 2000, -1);

	glVertex2f(1200, -1200);
	glVertex3f(1200, 2000, -1);
	glEnd();
}

void CALLBACK deseneazaMunte(float a, float b, float c)
{
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);


	glColor3f(0.412, 0.412, 0.412);

	glPushMatrix();
		glRotatef(260, 1.0, 0.0, 0.0);
		//gluCylinder(obj, 10, 0.5, 9, 30, 10);
		gluCylinder(obj, a, b, c, 170,50);
	glPopMatrix();
}

void CALLBACK deseneazaScenaMunte(float a ,float b, float c, float d, float e, float f)
{
	// a = dimensiune munte, b = dimensiune varf, c = x, d = y, e = z
	glPushMatrix();
		glRotatef(12, 1, 0, 0);
		glTranslatef(d, e, f);
		deseneazaMunte(a, b, c);
	glPopMatrix();
}

void CALLBACK deseneazaScenaMunti()
{
	deseneazaScenaMunte(80, 0, 140, -120, -80, -5);
	deseneazaScenaMunte(50, 0, 40, -40, -85, -40);
	deseneazaScenaMunte(70, 0, 70, 25, -90, -65);
	deseneazaScenaMunte(90, 0, 100, 105, -90, -65);
}


void calcCoeficinetiPlan(float P[3][3], float coef[4])
{
	float v1[3], v2[3];
	float length;
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;
	//calculeaza doi vectori din 3 puncte
	v1[x] = P[0][x] - P[1][x];
	v1[y] = P[0][y] - P[1][y];
	v1[z] = P[0][z] - P[1][z];
	v2[x] = P[1][x] - P[2][x];
	v2[y] = P[1][y] - P[2][y];
	v2[z] = P[1][z] - P[2][z];
	// se calculeaza produsul vectorial al celor 2 vectori
	//care reprezinta un al treilea vector perpendicular pe plan
	//ale carui componente sunt chiar coeficientii A,B,C din ecuatiea planului

	coef[x] = v1[y] * v2[z] - v1[z] * v2[y];
	coef[y] = v1[z] * v2[x] - v1[x] * v2[z];
	coef[z] = v1[x] * v2[y] - v1[y] * v2[x];
	//normalizarea vectorului

	length = (float)sqrt((coef[x] * coef[x]) + (coef[y] * coef[y]) + (coef[z] * coef[z]));
	coef[x] /= length;
	coef[y] /= length;
	coef[z] /= length;
}

void MatriceUmbra(GLfloat puncte[3][3], GLfloat pozSursa[4], GLfloat mat[4][4])
{
	GLfloat coefPlan[4];
	GLfloat temp;
	//determina coeficientii planului
	calcCoeficinetiPlan(puncte, coefPlan);
	//determina si pe D
	coefPlan[3] = -((coefPlan[0] * puncte[2][0]) + (coefPlan[1] * puncte[2][1]) + (coefPlan[2] * puncte[2][2]));
	//temp=A*xL+B*yL+C*zL+D*w
	temp = coefPlan[0] * pozSursa[0] + coefPlan[1] * pozSursa[1] + coefPlan[2] * pozSursa[2] + coefPlan[3] * pozSursa[3];
	//prima coloana
	mat[0][0] = temp - pozSursa[0] * coefPlan[0];
	mat[1][0] = 0.0f - pozSursa[0] * coefPlan[1];
	mat[2][0] = 0.0f - pozSursa[0] * coefPlan[2];
	mat[3][0] = 0.0f - pozSursa[0] * coefPlan[3];
	//a doua coloana
	mat[0][1] = 0.0f - pozSursa[1] * coefPlan[0];
	mat[1][1] = temp - pozSursa[1] * coefPlan[1];
	mat[2][1] = 0.0f - pozSursa[1] * coefPlan[2];
	mat[3][1] = 0.0f - pozSursa[1] * coefPlan[3];
	//a treia coloana
	mat[0][2] = 0.0f - pozSursa[2] * coefPlan[0];
	mat[1][2] = 0.0f - pozSursa[2] * coefPlan[1];
	mat[2][2] = temp - pozSursa[2] * coefPlan[2];
	mat[3][2] = 0.0f - pozSursa[2] * coefPlan[3];
	//a patra coloana
	mat[0][3] = 0.0f - pozSursa[3] * coefPlan[0];
	mat[1][3] = 0.0f - pozSursa[3] * coefPlan[1];
	mat[2][3] = 0.0f - pozSursa[3] * coefPlan[2];
	mat[3][3] = temp - pozSursa[3] * coefPlan[3];

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
	//auxIdleFunc(animatie_steag);
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return(0);
}