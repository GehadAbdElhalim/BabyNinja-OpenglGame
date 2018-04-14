#include "TextureBuilder.h"
#include "GLTexture.h"
//#include <GL/freeglut.h>
#include <glut.h>
#include <math.h>

int WIDTH = 1280;
int HEIGHT = 720;

GLuint tex;
char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 28;


//Game variables
bool Stop = false;
bool Scene1 = true;
bool Scene2 = false;
bool Scene3 = false;
bool SpawnRandomVariant = true;
int RandomVariant = 0;
bool SpawnVariant0 = false;
bool SpawnVariant1 = false;
bool SpawnVariant2 = false;
bool SpawnVariant3 = false;
bool SpawnMore = true;
int MagicGateCounter = 0;
bool SpawnMagicGate = false;
bool SpawnCollectible = false;
double CollectibleXMovement = 0;
double CurrrentZpositin = 0;
double GameDifficulty = 7;
bool FirstPerson = false;
bool cameraMode = false;

//ground  variables 
double ground_x, ground_y, ground_z = 0;
double ground_x2, ground_y2, ground_z2 = 0;
double speed_ground = .02;

// wall variables
GLTexture tex_wall_scene_1;
GLTexture tex_wall_scene_2;
GLTexture tex_wall_scene_3;
GLuint tex_Ob2;
GLuint tex_Ob1;
GLuint tex_Cloth;


//smoke screen variables
const int circle_size = 120;
double circle_x1[circle_size];
double circle_y1[circle_size];
double circle_z1[circle_size];
double circle_rad1[circle_size];
double circle_flag1[circle_size];

const int circle_size2 = 1000;
double circle_x2[circle_size2];
double circle_y2[circle_size2];
double circle_z2[circle_size2];
double circle_rad2[circle_size2];
double circle_flag2[circle_size2];

const int circle_size3 = 1000;
double circle_x3[circle_size3];
double circle_y3[circle_size3];
double circle_z3[circle_size3];
double circle_rad3[circle_size3];
double circle_flag3[circle_size3];

double smoke_y = 0;
double smoke_screen2_speed = 0;


//Spawn Power Up Variables
int PowerUpCounter = 0;
double PowerUpXtranslation = 0;
double PowerUpSpawnLocation = 0;
bool RandomizePowerUpLocation = false;
bool SpawnPowerUp = false;
int PowerUpPossibleSpawnLocations[] = { 0,-2,2 };

//Scence 1 variables
double Ob1XV0Movement = 0;
double Ob1XV1Movement = 0;
double Ob1XV2Movement = 0;
double Ob1XV3Movement = 0;

//Scence 2 variables
double Ob2XV0Movement = 0;
double Ob2XV1Movement = 0;
double Ob2XV2Movement = 0;
double Ob2XV3Movement = 0;

//Scence 3 variables
double Ob3XV0Movement = 0;
double Ob3XV1Movement = 0;
double Ob3XV2Movement = 0;
double Ob3XV3Movement = 0;

//Magic Gate Variables
double GateXMovement = 0;

//Running
bool Run = true;
bool RunIncreasing = true;
double legAngle = 0;

//jumping
bool Jump = false;
bool JumpRighthandIncreasing = true;
double JumpRighthand = 0;
bool JumpBodyIncreasing = true;
double JumpBody = 0;
bool JumpLegPause = false;

//sliding
bool Slide = false;
bool SlideBodyIncreasing = true;
bool SlideLegIncreasing = true;
bool SlideArmIncreasing = true;
double SlideBody = 0;
double SlideArm = 0;
double SlideLeg = 0;
bool SlideLegPause = false;
bool SlideArmPause = false;

//Death
bool Death = false;
int DeathStage = 1;
double DeathS1BodyRotation = 0;
double DeathS1ArmRotation = 0;
double DeathS1LegRotation = 0;
double DeathS2BodyTranslation = 0;
double DeathS2ArmRotation = 0;
double DeathS2LegRotation = 0;

//Player's power
GLfloat immune = 1;
double immuneDuration = 0;

//Player's Hitbox
double NinjaHitRadius = 0.5;

//Player's Movement
double PlayerXposition = 0;
double PlayerYposition = 1.05;
double PlayerZposition = 0;

//Obstacle 1 movement
bool Ob1Increasing = true;
double Ob1Movement = 0;
double Ob1Rotation = 0;

//Obstacle 2 movement
double Ob2Rotation = 0;

//Obstacle 3 movement
bool Ob3Increasing = true;
double Ob3Rotation = 0;

//Collectible movement
double Collectible = 0;

//Obstacle 1 hitbox
double Ob1HitboxRadius = 0.2;

//Obstacle 2 hitbox
double Ob2HitboxRadius = 0.5;

//Obstacle 3 hitbox
double Ob3HitboxRadius = 0.55;

//Collectible Hitbox
double CollectibleHitboxRadius = 0.3;
int CollectibleCounter = 0;

//Power up Hitbox
double PowerUpHitboxRadius = 0.3;

//Power up
bool PowerUpAlphaIncreasing = true;
GLfloat PowerUpAlpha = 1;
double PowerUpRotation = 0;

// light variable
GLfloat l4_r = 1;
GLfloat l4_g = 0;
GLfloat l4_b = 0;

GLfloat l1_r = 0.6f;

GLfloat l1_g = 0.6f;
GLfloat l1_b = 0.6f;

GLfloat l2_r = 1.0f;
GLfloat l2_g = 1.0f;
GLfloat l2_b = 1.0f;

GLfloat l3_r = 0.6f;
GLfloat l3_g = 0.6f;
GLfloat l3_b = 0.6f;

GLfloat l5_r = 0.5f;
GLfloat l5_g = 0.5f;
GLfloat l5_b = 0.5f;
/////////////////////////
// score 
unsigned int score = 0;
unsigned int scoreTimer = 0;
///////

void left_wall();
void move_ground();
void right_wall();
void circle(double x, double y, double z, double rand);
void smoke_screen1();
void init_smoke_screen1(double playerZ);
void smoke_screen2();
void init_smoke_screen2(double playerZ);
void smoke_screen3();
void init_smoke_screen3(double playerZ);
class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(7, 5, 0);
Vector At(0, 2, 0);
Vector Up(0, 1, 0);

int cameraZoom = 0;

// Textures
GLTexture tex_ground;

//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	/*InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);*/
}

//=======================================================================
// Render Ground Function
//=======================================================================
void RenderGround()
{

	// Disable lighting

	//glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[3]{ 1,1,1 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, new GLfloat[3]{ 1,1,1 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, new GLfloat[1]{ 100 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, new GLfloat[3]{ 0,0,0 });
	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture
	glPushMatrix();
	glTranslated(ground_x, ground_y, ground_z);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslated(ground_x - 40, ground_y, ground_z);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	// Enable lighting again for other entites coming throung the pipeline.

	// Disable lighting

	//glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing
	if (Scene1)
		glBindTexture(GL_TEXTURE_2D, tex_wall_scene_1.texture[0]);
	else if (Scene2)
		glBindTexture(GL_TEXTURE_2D, tex_wall_scene_2.texture[0]);
	else if (Scene3)
		glBindTexture(GL_TEXTURE_2D, tex_wall_scene_3.texture[0]);
	glPushMatrix();
	glTranslated(ground_x, ground_y + 5, ground_z);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(20, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(20, 20);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 20);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslated(ground_x - 40, ground_y + 5, ground_z);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(20, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(20, 20);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 20);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	// Enable lighting again for other entites coming throung the pipeline.
	//glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

void drawCircle(int x, int y, float r) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	GLUquadric *quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}

void drawNinja() {

	//Right leg animation
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, new GLfloat[3]{ .1f,.1f,.1f });
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, new GLfloat[1]{ 100 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, new GLfloat[3]{ 0,0,0 });

	glPushMatrix();
	if (Death) {
		glTranslated(0, -0.49, 0.11);
		glTranslated(DeathS2BodyTranslation*0.5, DeathS2BodyTranslation, 0);
		glRotated(DeathS2LegRotation, 0, 0, 1);
		glRotated(DeathS1LegRotation, 0, 0, 1);
		glTranslated(0, 0.49, -0.11);
	}
	if (Slide) {
		glTranslated(0, -0.49, 0.11);
		glRotated(20 + SlideLeg, 0, 0, 1);
		glTranslated(0, 0.49, -0.11);
	}
	if (Jump) {
		glTranslated(0, -0.49, 0.11);
		glRotated(20 + JumpRighthand, 0, 0, 1);
		glTranslated(0, 0.49, -0.11);
	}
	if (Run) {
		glTranslated(0, -0.49, 0.11);
		glRotated(70 - legAngle, 0, 0, 1);
		glTranslated(0, 0.49, -0.11);
	}
	//Right leg
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	//glColor4f(0, 0, 0, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0,0,0,immune });
	glTranslated(0, -0.49, 0.11);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj53;
	qobj53 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, tex_Cloth);
	gluQuadricTexture(qobj53, true);
	gluQuadricNormals(qobj53, GL_SMOOTH);
	gluQuadricDrawStyle(qobj53, GLU_FLAT);
	gluCylinder(qobj53, 0.09, 0.08, 0.5, 20, 20);
	gluDeleteQuadric(qobj53);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Right foot
	glPushMatrix();
	//glColor4f(0.99, 0.68, 0.375, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.99f, 0.68f, 0.375f, immune });
	glTranslated(0.04, -1, 0.11);
	glScaled(1.3, 0.6, 0.9);
	glutSolidSphere(0.09, 20, 20);
	glPopMatrix();
	glPopMatrix();


	//left leg Animation
	glPushMatrix();
	if (Death) {
		glTranslated(0, -0.49, 0.11);
		glTranslated(DeathS2BodyTranslation*0.5, DeathS2BodyTranslation, 0);
		glRotated(DeathS2LegRotation, 0, 0, 1);
		glRotated(DeathS1LegRotation, 0, 0, 1);
		glTranslated(0, 0.49, -0.11);
	}
	if (Slide) {
		glTranslated(0, -0.49, 0.11);
		glRotated(-20 - SlideLeg, 0, 0, 1);
		glTranslated(0, 0.49, -0.11);
	}
	if (Jump) {
		glTranslated(0, -0.49, -0.11);
		glRotated(-20 - JumpRighthand, 0, 0, 1);
		glTranslated(0, 0.49, 0.11);
	}
	if (Run) {
		glTranslated(0, -0.49, -0.11);
		glRotated(-70 + legAngle, 0, 0, 1);
		glTranslated(0, 0.49, 0.11);
	}
	//Left leg
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	//glColor4f(0, 0, 0, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0, 0, 0, immune });
	glTranslated(0, -0.49, -0.11);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj54;
	qobj54 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, tex_Cloth);
	gluQuadricTexture(qobj54, true);
	gluQuadricNormals(qobj54, GL_SMOOTH);
	gluQuadricDrawStyle(qobj54, GLU_FLAT);
	gluCylinder(qobj54, 0.09, 0.08, 0.5, 20, 20);
	gluDeleteQuadric(qobj54);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Left foot
	glPushMatrix();
	//glColor4f(0.99, 0.68, 0.375, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.99f, 0.68f, 0.375f, immune });
	glTranslated(0.04, -1, -0.11);
	glScaled(1.3, 0.6, 0.9);
	glutSolidSphere(0.09, 20, 20);
	glPopMatrix();
	glPopMatrix();

	//Body Animation
	glPushMatrix();
	if (Death) {
		glTranslated(0, -0.49, 0);
		glTranslated(DeathS2BodyTranslation*0.5, DeathS2BodyTranslation, 0);
		glRotated(-45 + DeathS1BodyRotation, 0, 0, 1);
		glTranslated(0, 0.49, 0);
	}
	if (Slide) {
		glTranslated(0, -0.49, 0);
		glRotated(-45 - SlideArm, 0, 0, 1);
		glTranslated(0, 0.49, 0);
	}
	if (Run || Jump) {
		glTranslated(0, -0.49, 0);
		glRotated(-45, 0, 0, 1);
		glTranslated(0, 0.49, 0);
	}
	//Lower body
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	//glColor4f(0, 0, 0, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0, 0, 0, immune });
	glTranslated(0, -0.49, 0);
	glScaled(1, 1, 2);
	GLUquadricObj * qobj91;
	qobj91 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, tex_Cloth);
	gluQuadricTexture(qobj91, true);
	gluQuadricNormals(qobj91, GL_SMOOTH);
	gluSphere(qobj91, 0.1, 20, 20);
	gluDeleteQuadric(qobj91);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Body
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	//glColor4f(0, 0, 0, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0, 0, 0, immune });
	glScaled(1, 0.5, 2);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj50;
	qobj50 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, tex_Cloth);
	gluQuadricTexture(qobj50, true);
	gluQuadricNormals(qobj50, GL_SMOOTH);
	gluQuadricDrawStyle(qobj50, GLU_FLAT);
	gluCylinder(qobj50, 0.1, 0.1, 1, 20, 20);
	gluDeleteQuadric(qobj50);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Belt
	glPushMatrix();
	//glColor4f(0.5, 0.5, 0.5, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.5f, 0.5f, 0.5f, immune });
	glTranslated(0, -0.38, 0);
	glScaled(1.05, 0.5, 2.05);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj56;
	qobj56 = gluNewQuadric();
	gluQuadricDrawStyle(qobj56, GLU_FLAT);
	gluCylinder(qobj56, 0.1, 0.1, 0.2, 20, 20);
	glPopMatrix();

	//Upper body
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	//glColor4f(0, 0, 0, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0, 0, 0, immune });
	glScaled(1, 1, 2);
	GLUquadricObj * qobj92;
	qobj92 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, tex_Cloth);
	gluQuadricTexture(qobj92, true);
	gluQuadricNormals(qobj92, GL_SMOOTH);
	gluSphere(qobj92, 0.1, 20, 20);
	gluDeleteQuadric(qobj92);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//Right Arm Animation
	glPushMatrix();
	glTranslated(0, 0, 0.17);
	if (Death) {
		glRotated(DeathS2ArmRotation, 0, 0, 1);
		glRotated(-50 + DeathS1ArmRotation, 0, 0, 1);
	}
	if (Slide) {
		glRotated(-50 + SlideArm, 0, 0, 1);
	}
	if (Run || Jump) {
		glRotated(-50, 0, 0, 1);
	}
	glRotated(-15, 1, 0, 0);
	glTranslated(0, 0, -0.17);
	//Right shoulder
	glPushMatrix();
	//glColor4f(0.99, 0.68, 0.375, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.99f, 0.68f, 0.375f, immune });
	glTranslated(0, 0, 0.17);
	glutSolidSphere(0.07, 20, 20);
	glPopMatrix();

	//Right arm
	glPushMatrix();
	//glColor4f(0.99, 0.68, 0.375, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.99f, 0.68f, 0.375f, immune });
	glTranslated(0, 0, 0.17);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj51;
	qobj51 = gluNewQuadric();
	gluQuadricDrawStyle(qobj51, GLU_FLAT);
	gluCylinder(qobj51, 0.07, 0.06, 0.5, 20, 20);
	glPopMatrix();

	//Right hand
	glPushMatrix();
	//glColor4f(0.99, 0.68, 0.375, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.99f, 0.68f, 0.375f, immune });
	glTranslated(0, -0.5, 0.17);
	glutSolidSphere(0.06, 20, 20);
	glPopMatrix();
	glPopMatrix();

	//Left Arm Animation
	glPushMatrix();
	glTranslated(0, 0, -0.17);
	if (Death) {
		glRotated(DeathS2ArmRotation, 0, 0, 1);
		glRotated(-50 + DeathS1ArmRotation, 0, 0, 1);
	}
	if (Slide) {
		glRotated(-50 + SlideArm, 0, 0, 1);
	}
	if (Run || Jump) {
		glRotated(-50, 0, 0, 1);
	}
	glRotated(15, 1, 0, 0);
	glTranslated(0, 0, 0.17);
	//Left shoulder
	glPushMatrix();
	//glColor4f(0.99, 0.68, 0.375, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.99f, 0.68f, 0.375f, immune });
	glTranslated(0, 0, -0.17);
	glutSolidSphere(0.07, 20, 20);
	glPopMatrix();

	//Left arm
	glPushMatrix();
	//glColor4f(0.99, 0.68, 0.375, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.99f, 0.68f, 0.375f, immune });
	glTranslated(0, 0, -0.17);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj52;
	qobj52 = gluNewQuadric();
	gluQuadricDrawStyle(qobj52, GLU_FLAT);
	gluCylinder(qobj52, 0.07, 0.06, 0.5, 20, 20);
	glPopMatrix();

	//Left hand
	glPushMatrix();
	//glColor4f(0.99, 0.68, 0.375, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.99f, 0.68f, 0.375f, immune });
	glTranslated(0, -0.5, -0.17);
	glutSolidSphere(0.06, 20, 20);
	glPopMatrix();
	glPopMatrix();


	//neck
	glPushMatrix();
	//glColor4f(0.99, 0.68, 0.375, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.99f, 0.68f, 0.375f, immune });
	glTranslated(0, 0.2, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj * qobj55;
	qobj55 = gluNewQuadric();
	gluQuadricDrawStyle(qobj55, GLU_FLAT);
	gluCylinder(qobj55, 0.07, 0.07, 0.1, 20, 20);
	glPopMatrix();

	//Head Animation
	glPushMatrix();
	if (Run || Jump || Slide) {
		glTranslated(0, 0.35, 0);
		glRotated(45, 0, 0, 1);
		glTranslated(0, -0.35, 0);
	}
	//Head
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	//glColor4f(0, 0, 0, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0, 0, 0, immune });
	glTranslated(0, 0.35, 0);
	GLUquadricObj * qobj93;
	qobj93 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, tex_Cloth);
	gluQuadricTexture(qobj93, true);
	gluQuadricNormals(qobj93, GL_SMOOTH);
	gluSphere(qobj93, 0.25, 20, 20);
	gluDeleteQuadric(qobj93);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//mask
	glPushMatrix();
	//glColor4f(1, 0, 0, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 0, 0, immune });
	glTranslated(0, 0.35, 0);
	glRotated(90, 1, 0, 0);
	glScaled(0.65, 0.65, 0.6);
	glutSolidTorus(0.2, 0.2, 20, 20);
	glPopMatrix();

	//Right eye
	glPushMatrix();
	//glColor4f(1, 1, 1, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 1, 1, immune });
	glTranslated(0.23, 0.35, 0.07);
	glScaled(0.5, 1, 1.5);
	glutSolidSphere(0.05, 20, 20);
	glPopMatrix();

	//Left eye
	glPushMatrix();
	//glColor4f(1, 1, 1, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 1, 1, immune });
	glTranslated(0.23, 0.35, -0.07);
	glScaled(0.5, 1, 1.5);
	glutSolidSphere(0.05, 20, 20);
	glPopMatrix();
	glPopMatrix();

	//sword
	glPushMatrix();
	glTranslated(0.4, 0, 0);
	glTranslated(-0.5, -0.2, 0);
	glRotated(35, 1, 0, 0);
	glScaled(1, 1.3, 1);
	glTranslated(0.5, 0.2, 0);
	//Top sword
	glPushMatrix();
	//glColor4f(0.61, 0.24, 0.02, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.61f, 0.24f, 0.02f, immune });
	glTranslated(-0.5, 0.1, 0);
	glScaled(0.3, 1, 0.3);
	glutSolidCube(0.1);
	glPopMatrix();

	//Handler
	glPushMatrix();
	//glColor4f(0.61, 0.24, 0.02, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.61f, 0.24f, 0.02f, immune });
	glTranslated(-0.5, 0.05, 0);
	glRotated(90, 1, 0, 0);
	glScaled(0.3, 2, 0.3);
	glutSolidCube(0.1);
	glPopMatrix();

	//Middle sword
	glPushMatrix();
	//glColor4f(0.7, 0.7, 0.7, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.7f, 0.7f, 0.7f, immune });
	glTranslated(-0.5, -0.2, 0);
	glScaled(0.3, 5, 1.3);
	glutSolidCube(0.1);
	glPopMatrix();

	//Bottom sword
	glPushMatrix();
	//glColor4f(0.7, 0.7, 0.7, immune);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.7f, 0.7f, 0.7f, immune });
	glTranslated(-0.5, -0.45, 0);
	glRotated(45, 1, 0, 0);
	glScaled(0.3, 1, 1);
	glutSolidCube(0.1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void drawObstacle1() {

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, new GLfloat[3]{ 1,1,1 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, new GLfloat[1]{ 100 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, new GLfloat[3]{ 0,0,0 });

	//cylinder
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.61f, 0.24f, 0.02f, 1 });
	GLUquadricObj * qobj60;
	qobj60 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, tex_Ob1);
	gluQuadricTexture(qobj60, true);
	gluQuadricNormals(qobj60, GL_SMOOTH);
	gluQuadricDrawStyle(qobj60, GLU_FLAT);
	gluCylinder(qobj60, Ob1HitboxRadius, Ob1HitboxRadius, 3, 20, 20);
	gluDeleteQuadric(qobj60);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//1st spikes
	glPushMatrix();
	glTranslated(0, 0.2, 0);
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.5f, 0.5f, 0.5f, 1 });
	glTranslated(0, 0, 0.2);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(0, 0, 0.4);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();*/

	glPushMatrix();
	glTranslated(0, 0, 0.6);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(0, 0, 0.8);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();*/

	glPushMatrix();
	glTranslated(0, 0, 1);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(0, 0, 1.2);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();*/

	glPushMatrix();
	glTranslated(0, 0, 1.4);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(0, 0, 1.6);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();*/

	glPushMatrix();
	glTranslated(0, 0, 1.8);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(0, 0, 2);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();*/

	glPushMatrix();
	glTranslated(0, 0, 2.2);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(0, 0, 2.4);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();*/

	glPushMatrix();
	glTranslated(0, 0, 2.6);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(0, 0, 2.8);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();*/
	glPopMatrix();

	//2nd spikes
	glPushMatrix();
	glTranslated(0, -0.2, 0);
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.5f, 0.5f, 0.5f, 1 });
	glTranslated(0, 0, 0.2);
	glRotated(90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(0, 0, 0.4);
	glRotated(90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();*/

	glPushMatrix();
	glTranslated(0, 0, 0.6);
	glRotated(90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(0, 0, 0.8);
	glRotated(90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();*/

	glPushMatrix();
	glTranslated(0, 0, 1);
	glRotated(90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(0, 0, 1.2);
	glRotated(90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();*/

	glPushMatrix();
	glTranslated(0, 0, 1.4);
	glRotated(90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(0, 0, 1.6);
	glRotated(90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();*/

	glPushMatrix();
	glTranslated(0, 0, 1.8);
	glRotated(90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(0, 0, 2);
	glRotated(90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();*/

	glPushMatrix();
	glTranslated(0, 0, 2.2);
	glRotated(90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(0, 0, 2.4);
	glRotated(90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();*/

	glPushMatrix();
	glTranslated(0, 0, 2.6);
	glRotated(90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(0, 0, 2.8);
	glRotated(90, 1, 0, 0);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();*/
	glPopMatrix();

	//hitbox
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 0, 0, 0 });
	drawCircle(0, 0, 0.05);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 0, 0, 0 });
	glTranslated(0, 0, 3);
	drawCircle(0, 0, 0.05);
	glPopMatrix();
}

void drawObstacle2() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.2f, 0.2f, 0.2f, 1 });
	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, tex_Ob2);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, Ob2HitboxRadius, 100, 100);
	gluDeleteQuadric(qobj);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawObstacle3() {

	glPushMatrix();
	glTranslated(0, 2.13 + 1.5, 0);
	glRotated(Ob3Rotation, 1, 0, 0);
	glTranslated(0, -2.13 - 1.5, 0);
	//wooden stick
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.61f, 0.24f, 0.02f, 1 });
	glTranslated(0, 0.63 + 1.5, 0);
	glScaled(0.1, 10, 0.25);
	glutSolidCube(0.5);
	glPopMatrix();

	// midlle metal
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.7f, 0.7f, 0.7f, 1 });
	glScaled(0.05, 0.5, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	//left metal
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.7f, 0.7f, 0.7f, 1 });
	glTranslated(0, 0, -0.3);
	glScaled(0.05, 2, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	//left edge
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.7f, 0.7f, 0.7f, 1 });
	glTranslated(0, 0, -0.5);
	glScaled(0.03, 1, 0.5);
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();

	//right metal
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.7f, 0.7f, 0.7f, 1 });
	glTranslated(0, 0, 0.3);
	glScaled(0.05, 2, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	//right edge
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.7f, 0.7f, 0.7f, 1 });
	glTranslated(0, 0, 0.5);
	glScaled(0.03, 1, 0.5);
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();

	//Hitbox
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 0, 0, 0 });
	glTranslated(0, 0.1, 0);
	glScaled(0.1, 1, 1);
	glutSolidSphere(Ob3HitboxRadius, 20, 20);
	glPopMatrix();
	glPopMatrix();
}

void drawCollectibles() {

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, new GLfloat[3]{ 1,1,1 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, new GLfloat[1]{ 100 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, new GLfloat[3]{ 0,0,0 });

	glPushMatrix();
	//glColor4f(1, 1, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 1, 0, 1 });
	glRotated(45, 1, 0, 0);
	glScaled(0.1, 1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 1, 0);

	glPushMatrix();
	//glColor4f(1, 1, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 1, 0, 1 });
	glRotated(45, 1, 0, 0);
	glScaled(0.1, 1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glRotated(45, 0, 1, 0);

	glPushMatrix();
	//glColor4f(1, 1, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 1, 0, 1 });
	glRotated(45, 1, 0, 0);
	glScaled(0.1, 1, 1);
	glutSolidCube(0.4);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glRotated(-45, 0, 1, 0);

	glPushMatrix();
	//glColor4f(1, 1, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 1, 0, 1 });
	glRotated(45, 1, 0, 0);
	glScaled(0.1, 1, 1);
	glutSolidCube(0.4);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 0, 1);

	glPushMatrix();
	//glColor4f(1, 1, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 1, 0, 1 });
	glRotated(45, 1, 0, 0);
	glScaled(0.1, 1, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPopMatrix();
}

void drawPowerUp() {

	//head
	glPushMatrix();
	glScaled(0.75, 0.75, 0.75);
	//Head
	glPushMatrix();
	//glColor4f(0, 0, 0, PowerUpAlpha);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0, 0, 0, PowerUpAlpha });
	glTranslated(0, 0, 0);
	glutSolidSphere(0.25, 20, 20);
	glPopMatrix();

	//mask
	glPushMatrix();
	//glColor4f(1, 0, 0, PowerUpAlpha);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0, 0, 0, PowerUpAlpha });
	glTranslated(0, 0, 0);
	glRotated(90, 1, 0, 0);
	glScaled(0.65, 0.65, 0.6);
	glutSolidTorus(0.2, 0.2, 20, 20);
	glPopMatrix();

	//Right eye
	glPushMatrix();
	//glColor4f(1, 1, 1, PowerUpAlpha);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 1, 1, PowerUpAlpha });
	glTranslated(0.23, 0, 0.07);
	glScaled(0.5, 1, 1.5);
	glutSolidSphere(0.05, 20, 20);
	glPopMatrix();

	//Left eye
	glPushMatrix();
	//glColor4f(1, 1, 1, PowerUpAlpha);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 1, 1, PowerUpAlpha });
	glTranslated(0.23, 0, -0.07);
	glScaled(0.5, 1, 1.5);
	glutSolidSphere(0.05, 20, 20);
	glPopMatrix();
	glPopMatrix();

	//little Ball
	glPushMatrix();
	//glColor4f(0.5, 0.5, 0.5, 0.5);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 0.5f, 0.5f, 0.5f, .5f });
	glutSolidSphere(PowerUpHitboxRadius, 50, 50);
	glPopMatrix();
}

void SpawnCollectibleHelper(double Zpositin, double displacement) {
	if (Zpositin == 0) {
		//Collectibles
		glPushMatrix();
		glTranslated(-23 + displacement, 0.3, 2);
		glRotated(Collectible, 0, 1, 0);
		glScaled(0.5, 0.5, 0.5);
		drawCollectibles();
		glPushMatrix();
		//glColor4f(1, 0, 0, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 0, 0, 0 });
		glutSolidSphere(CollectibleHitboxRadius, 20, 20);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-23 + displacement, 0.3, -2);
		glRotated(Collectible, 0, 1, 0);
		glScaled(0.5, 0.5, 0.5);
		drawCollectibles();
		glPushMatrix();
		//glColor4f(1, 0, 0, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 0, 0, 0 });
		glutSolidSphere(CollectibleHitboxRadius, 20, 20);
		glPopMatrix();
		glPopMatrix();
	}

	if (Zpositin == 2) {
		//Collectibles
		glPushMatrix();
		glTranslated(-23 + displacement, 0.3, 0);
		glRotated(Collectible, 0, 1, 0);
		glScaled(0.5, 0.5, 0.5);
		drawCollectibles();
		glPushMatrix();
		//glColor4f(1, 0, 0, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 0, 0, 0 });
		glutSolidSphere(CollectibleHitboxRadius, 20, 20);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-23 + displacement, 0.3, -2);
		glRotated(Collectible, 0, 1, 0);
		glScaled(0.5, 0.5, 0.5);
		drawCollectibles();
		glPushMatrix();
		//glColor4f(1, 0, 0, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 0, 0, 0 });
		glutSolidSphere(CollectibleHitboxRadius, 20, 20);
		glPopMatrix();
		glPopMatrix();
	}

	if (Zpositin == -2) {
		//Collectibles
		glPushMatrix();
		glTranslated(-23 + displacement, 0.3, 2);
		glRotated(Collectible, 0, 1, 0);
		glScaled(0.5, 0.5, 0.5);
		drawCollectibles();
		glPushMatrix();
		//glColor4f(1, 0, 0, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 0, 0, 0 });
		glutSolidSphere(CollectibleHitboxRadius, 20, 20);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-23 + displacement, 0.3, 0);
		glRotated(Collectible, 0, 1, 0);
		glScaled(0.5, 0.5, 0.5);
		drawCollectibles();
		glPushMatrix();
		//glColor4f(1, 0, 0, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 0, 0, 0 });
		glutSolidSphere(CollectibleHitboxRadius, 20, 20);
		glPopMatrix();
		glPopMatrix();
	}
}

bool hitOb1V0() {
	double currentPlayerXposition = PlayerXposition;
	double currentPlayerYposition = PlayerYposition + JumpBody + SlideBody;
	double currentPlayerZposition = PlayerZposition;

	double currentObjectXposition = -23 + Ob1XV0Movement;
	double currentObjectYposition = Ob1Movement;

	double distance = sqrt(pow(currentPlayerXposition - currentObjectXposition, 2) + pow(currentPlayerYposition - currentObjectYposition, 2));

	return (distance < Ob1HitboxRadius + NinjaHitRadius);
}

bool hitOb1V1() {
	double currentPlayerXposition = PlayerXposition;
	double currentPlayerYposition = PlayerYposition + JumpBody + SlideBody;
	double currentPlayerZposition = PlayerZposition;

	double currentObjectXposition = -23 + Ob1XV1Movement;
	double currentObjectZposition = -2;

	double distance = sqrt(pow(currentPlayerXposition - currentObjectXposition, 2) + pow(currentPlayerZposition - currentObjectZposition, 2));

	return (distance < Ob1HitboxRadius);
}

bool hitOb1V2() {
	double currentPlayerXposition = PlayerXposition;
	double currentPlayerYposition = PlayerYposition + JumpBody + SlideBody;
	double currentPlayerZposition = PlayerZposition;

	double currentObjectXposition = -23 + Ob1XV2Movement;
	double currentObjectZposition = 2;

	double distance = sqrt(pow(currentPlayerXposition - currentObjectXposition, 2) + pow(currentPlayerZposition - currentObjectZposition, 2));

	return (distance < Ob1HitboxRadius);
}

bool hitOb1V3() {
	double currentPlayerXposition = PlayerXposition;
	double currentPlayerYposition = PlayerYposition + JumpBody + SlideBody;
	double currentPlayerZposition = PlayerZposition;

	double currentObjectXposition = -23 + Ob1XV3Movement;
	double currentObjectZposition = 0;

	double distance = sqrt(pow(currentPlayerXposition - currentObjectXposition, 2) + pow(currentPlayerZposition - currentObjectZposition, 2));

	return (distance < Ob1HitboxRadius);
}

bool hitOb2V0() {
	double currentPlayerXposition = PlayerXposition;
	double currentPlayerYposition = PlayerYposition + JumpBody + SlideBody;
	double currentPlayerZposition = PlayerZposition;

	double currentObjectXposition = -25 + Ob2XV0Movement;
	double currentObjectYposition = 0.75;
	double currentObjectZposition = 0;

	double distance = sqrt(pow(currentPlayerXposition - currentObjectXposition, 2) + pow(currentPlayerZposition - currentObjectZposition, 2));

	return (distance < Ob2HitboxRadius + NinjaHitRadius);
}

bool hitOb2V1() {
	double currentPlayerXposition = PlayerXposition;
	double currentPlayerYposition = PlayerYposition + JumpBody + SlideBody;
	double currentPlayerZposition = PlayerZposition;

	double currentObjectXposition = -25 + Ob2XV1Movement;
	double currentObjectYposition = 0.75;
	double currentObjectZposition = -2;

	double distance = sqrt(pow(currentPlayerXposition - currentObjectXposition, 2) + pow(currentPlayerZposition - currentObjectZposition, 2));

	return (distance < Ob2HitboxRadius + NinjaHitRadius);
}

bool hitOb2V2() {
	double currentPlayerXposition = PlayerXposition;
	double currentPlayerYposition = PlayerYposition + JumpBody + SlideBody;
	double currentPlayerZposition = PlayerZposition;

	double currentObjectXposition = -25 + Ob2XV2Movement;
	double currentObjectYposition = 0.75;
	double currentObjectZposition = 2;

	double distance = sqrt(pow(currentPlayerXposition - currentObjectXposition, 2) + pow(currentPlayerZposition - currentObjectZposition, 2));

	return (distance < Ob2HitboxRadius + NinjaHitRadius);
}

bool hitOb2V3() {
	double currentPlayerXposition = PlayerXposition;
	double currentPlayerYposition = PlayerYposition + JumpBody + SlideBody;
	double currentPlayerZposition = PlayerZposition;

	double currentObjectXposition = -25 + Ob2XV3Movement;
	double currentObjectYposition = 0.75;
	double currentObjectZposition1 = 2;
	double currentObjectZposition2 = -2;

	double distance1 = sqrt(pow(currentPlayerXposition - currentObjectXposition, 2) + pow(currentPlayerZposition - currentObjectZposition1, 2));

	double distance2 = sqrt(pow(currentPlayerXposition - currentObjectXposition, 2) + pow(currentPlayerZposition - currentObjectZposition2, 2));

	return (distance1 < Ob2HitboxRadius + NinjaHitRadius) || (distance2 < Ob2HitboxRadius + NinjaHitRadius);
}

bool hitOb3V0() {
	double currentPlayerXposition = PlayerXposition + 0.15;
	double currentPlayerYposition = PlayerYposition + JumpBody + SlideBody - 0.3;
	double currentPlayerZposition = PlayerZposition;

	double currentObjectXposition = -0.1*sin(Ob3Rotation) + 3.63*sin(Ob3Rotation);
	double currentObjectYposition = 0.1*cos(Ob3Rotation) - 3.63*cos(Ob3Rotation) + 3.63 + 1;
	double currentObjectZposition = -2;

	double distance = sqrt(pow(currentPlayerYposition - currentObjectYposition, 2) + pow(currentPlayerXposition - currentObjectXposition, 2));

	if (currentPlayerZposition != 0 && Ob3XV0Movement > 22.2) {
		return (distance < (Ob3HitboxRadius + NinjaHitRadius));
	}
	else {
		return false;
	}
}

bool hitOb3V1() {
	double currentPlayerXposition = PlayerXposition + 0.15;
	double currentPlayerYposition = PlayerYposition + JumpBody + SlideBody - 0.3;
	double currentPlayerZposition = PlayerZposition;

	double currentObjectXposition = -0.1*sin(Ob3Rotation) + 3.63*sin(Ob3Rotation);
	double currentObjectYposition = 0.1*cos(Ob3Rotation) - 3.63*cos(Ob3Rotation) + 3.63 + 1;
	double currentObjectZposition = -2;

	double distance = sqrt(pow(currentPlayerYposition - currentObjectYposition, 2) + pow(currentPlayerXposition - currentObjectXposition, 2));

	if (currentPlayerZposition == -2 && Ob3XV1Movement > 23) {
		return (distance < Ob3HitboxRadius + NinjaHitRadius);
	}
	else {
		return false;
	}
}

bool hitOb3V2() {
	double currentPlayerXposition = PlayerXposition + 0.15;
	double currentPlayerYposition = PlayerYposition + JumpBody + SlideBody - 0.3;
	double currentPlayerZposition = PlayerZposition;

	double currentObjectXposition = -0.1*sin(Ob3Rotation) + 3.63*sin(Ob3Rotation);
	double currentObjectYposition = 0.1*cos(Ob3Rotation) - 3.63*cos(Ob3Rotation) + 3.63 + 1;
	double currentObjectZposition = 0;

	double distance = sqrt(pow(currentPlayerYposition - currentObjectYposition, 2) + pow(currentPlayerXposition - currentObjectXposition, 2));

	if (currentPlayerZposition == 2 && Ob3XV2Movement > 23) {
		return (distance < Ob3HitboxRadius);
	}
	else {
		return false;
	}
}

bool hitOb3V3() {
	double currentPlayerXposition = PlayerXposition + 0.15;
	double currentPlayerYposition = PlayerYposition + JumpBody + SlideBody - 0.3;
	double currentPlayerZposition = PlayerZposition;

	double currentObjectXposition = -0.1*sin(Ob3Rotation) + 3.63*sin(Ob3Rotation);
	double currentObjectYposition = 0.1*cos(Ob3Rotation) - 3.63*cos(Ob3Rotation) + 3.63 + 1;
	double currentObjectZposition = 2;

	double distance = sqrt(pow(currentPlayerYposition - currentObjectYposition, 2) + pow(currentPlayerXposition - currentObjectXposition, 2));

	if (currentPlayerZposition == 0 && Ob3XV3Movement > 23) {
		return (distance < Ob3HitboxRadius);
	}
	else {
		return false;
	}
}

bool hitPowerUp() {
	double currentPlayerXposition = PlayerXposition;
	double currentPlayerYposition = PlayerYposition + JumpBody + SlideBody;
	double currentPlayerZposition = PlayerZposition;

	double currentObjectXposition = -33.5 + PowerUpXtranslation;
	double currentObjectYposition = 0.5;
	double currentObjectZposition = PowerUpSpawnLocation;

	double distance = sqrt(pow(currentPlayerXposition - currentObjectXposition, 2) + pow(currentPlayerYposition - currentObjectYposition, 2) + pow(currentPlayerZposition - currentObjectZposition, 2));

	return (distance < PowerUpHitboxRadius + NinjaHitRadius);
}

void Timer(int value) {

	if (!Death) {
		scoreTimer += 1;
		if (scoreTimer >= 25) {
			score += 1;
			scoreTimer = 0;
		}
	}

	/////////////light animation
	//l4
	l4_r -= .0009f;
	l4_g += .0009f;
	l4_b += .00045f;
	if (l4_r < 0)
		l4_r = 1;
	if (l4_g > 1)
		l4_g = 0;
	if (l4_b > 1)
		l4_b = 0;

	//l1
	if (Death) {
		if (l1_r<1)
			l1_r += .001;
		if (l1_g>0)
			l1_g -= .001;
		if (l1_b>0)
			l1_b -= .001;

		//l2
		if (l2_r<1)
			l2_r += .001;
		if (l2_g>0)
			l2_g -= .001;
		if (l2_b>0)
			l2_b -= .001;

		//l3
		if (l3_r<1)
			l3_r += .001;
		if (l3_g>0)
			l3_g -= .001;
		if (l3_b>0)
			l3_b -= .001;

		//l5
		if (l5_r<1)
			l5_r += .001;
		if (l5_g>0)
			l5_g -= .001;
		if (l5_b>0)
			l5_b -= .001;
	}

	//Camera Type
	if (!FirstPerson) {
		Eye.x = 7;
		Eye.y = 5;
		Eye.z = 0;
		At.x = 0;
		At.y = 2;
		At.z = 0;
		glLoadIdentity();
		gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	}
	if (FirstPerson) {
		Eye.x = PlayerXposition - 0.755;
		Eye.y = PlayerYposition + 0.1 + Jump - Slide;
		Eye.z = PlayerZposition;
		At.x = PlayerXposition - 1.5;
		At.y = PlayerYposition + 0.1 + Jump - Slide;
		At.z = PlayerZposition;
		glLoadIdentity();
		gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	}

	move_ground();

	//Collectible
	if (SpawnCollectible) {
		Collectible += 0.5;
		CollectibleXMovement++;
		if (CollectibleXMovement >= 500) {
			CollectibleCounter++;
			CollectibleXMovement = 0;
		}
		//if(CollectibleXMovement >= 30)
	}

	//Player's Animations
	///////////////////////////////////////
	if (Run) {
		if (RunIncreasing) {
			legAngle += 5 * 0.5*GameDifficulty;
			if (legAngle >= 140) {
				RunIncreasing = false;
			}
		}
		if (!RunIncreasing) {
			legAngle -= 5 * 0.5*GameDifficulty;
			if (legAngle <= 0) {
				RunIncreasing = true;;
			}
		}
	}

	if (Jump) {
		Run = false;
		if (JumpBodyIncreasing) {
			JumpBody += 0.0112;
			if (JumpBody >= 1) {
				JumpBodyIncreasing = false;
				JumpLegPause = false;
			}
		}
		if (!JumpBodyIncreasing) {
			JumpBody -= 0.0112;
			if (JumpBody <= 0) {
				JumpBodyIncreasing = true;
				JumpLegPause = false;
				Jump = false;
				Run = true;
			}
		}
		if (JumpRighthandIncreasing && !JumpLegPause) {
			JumpRighthand += 1.98;
			if (JumpRighthand >= 70 && !JumpBodyIncreasing) {
				JumpRighthandIncreasing = false;
			}
			if (JumpRighthand >= 70 && JumpBodyIncreasing)
				JumpLegPause = true;
		}
		if (!JumpRighthandIncreasing && !JumpLegPause) {
			JumpRighthand -= 1.98;
			if (JumpRighthand <= 0 && !JumpBodyIncreasing)
				JumpLegPause = true;
			if (JumpRighthand <= 0 && JumpBodyIncreasing) {
				JumpRighthandIncreasing = true;
			}
		}
	}

	if (Slide) {
		Run = false;
		if (SlideBodyIncreasing) {
			SlideBody -= 0.0112;
			if (SlideBody <= -0.5) {
				SlideBodyIncreasing = false;
				SlideLegPause = false;
				SlideArmPause = false;
			}
		}
		if (!SlideBodyIncreasing) {
			SlideBody += 0.0112;
			if (SlideBody >= 0) {
				SlideBodyIncreasing = true;
				SlideLegPause = false;
				SlideArmPause = false;
				Slide = false;
				Run = true;
			}
		}
		if (SlideLegIncreasing && !SlideLegPause) {
			SlideLeg += 2;
			if (SlideLeg >= 70 && !SlideBodyIncreasing) {
				SlideLegIncreasing = false;
			}
			if (SlideLeg >= 70 && SlideBodyIncreasing)
				SlideLegPause = true;
		}
		if (!SlideLegIncreasing && !SlideLegPause) {
			SlideLeg -= 2;
			if (SlideLeg <= 0 && !SlideBodyIncreasing)
				SlideLegPause = true;
			if (SlideLeg <= 0 && SlideBodyIncreasing) {
				SlideLegIncreasing = true;
			}
		}
		if (SlideArmIncreasing && !SlideArmPause) {
			SlideArm += 2;
			if (SlideArm >= 20 && !SlideBodyIncreasing) {
				SlideArmIncreasing = false;
			}
			if (SlideArm >= 20 && SlideBodyIncreasing)
				SlideArmPause = true;
		}
		if (!SlideArmIncreasing && !SlideArmPause) {
			SlideArm -= 2;
			if (SlideArm <= 0 && !SlideBodyIncreasing)
				SlideArmPause = true;
			if (SlideArm <= 0 && SlideBodyIncreasing) {
				SlideArmIncreasing = true;
			}
		}
	}

	if (Death) {
		Run = false;
		Slide = false;
		Jump = false;
		if (DeathStage == 1) {
			if (DeathS1BodyRotation < 135) {
				DeathS1BodyRotation += 0.5;
				DeathS1LegRotation += 0.5;
				DeathS1ArmRotation += 0.5;
			}
			if (DeathS1BodyRotation >= 135) {
				DeathStage++;
			}
		}
		else if (DeathStage = 2) {
			if (DeathS2BodyTranslation > -0.5) {
				DeathS2BodyTranslation -= 0.005;
				DeathS2LegRotation -= 0.5;
				DeathS2ArmRotation -= 0.85;
			}
		}
	}
	//////////////////////////////////////////////

	if (Ob1Increasing) {
		Ob1Rotation += 1 * GameDifficulty;
		Ob1Movement += 0.01 *0.5*GameDifficulty;
		if (Ob1Movement >= 3)
			Ob1Increasing = false;
	}
	if (!Ob1Increasing) {
		Ob1Rotation += 1 * GameDifficulty;
		Ob1Movement -= 0.01*0.5*GameDifficulty;
		if (Ob1Movement <= 0)
			Ob1Increasing = true;
	}
	if (Ob3Increasing) {
		Ob3Rotation += 0.25*GameDifficulty;
		if (Ob3Rotation >= 45)
			Ob3Increasing = false;
	}
	if (!Ob3Increasing) {
		Ob3Rotation -= 0.25*GameDifficulty;
		if (Ob3Rotation <= -45)
			Ob3Increasing = true;
	}

	//PowerUp
	if (PowerUpAlphaIncreasing) {
		PowerUpAlpha -= 0.001;
		PowerUpRotation += 0.2;
		if (PowerUpAlpha <= 0.2)
			PowerUpAlphaIncreasing = false;
	}

	if (!PowerUpAlphaIncreasing) {
		PowerUpAlpha += 0.001;
		PowerUpRotation += 0.2;
		if (PowerUpAlpha >= 1)
			PowerUpAlphaIncreasing = true;
	}

	if (!Stop) {

		//Scene 1 Engine
		//////////////////////////////////////////////////
		if (Scene1 && SpawnVariant0) {
			Ob1XV0Movement += 0.02*GameDifficulty;
			if (hitOb1V0() && immune != 0.5) {
				Stop = true;
				Death = true;
				SpawnVariant0 = false;
			}
			if (Ob1XV0Movement >= 15 && SpawnMore) {
				SpawnRandomVariant = true;
				SpawnMore = false;
			}
			if (Ob1XV0Movement > 30) {
				SpawnVariant0 = false;
				Ob1XV0Movement = 0;
				SpawnMore = true;
				if (!SpawnPowerUp) {
					PowerUpCounter++;
				}
			}
		}
		if (Scene1 && SpawnVariant1) {
			Ob1XV1Movement += 0.02*GameDifficulty;
			if (hitOb1V1() && immune != 0.5) {
				Stop = true;
				Death = true;
				SpawnVariant1 = false;
			}
			if (Ob1XV1Movement >= 15 && SpawnMore) {
				SpawnRandomVariant = true;
				SpawnMore = false;
			}
			if (Ob1XV1Movement > 30) {
				SpawnVariant1 = false;
				Ob1XV1Movement = 0;
				SpawnMore = true;
				if (!SpawnPowerUp) {
					PowerUpCounter++;
				}
			}
		}
		if (Scene1 && SpawnVariant2) {
			Ob1XV2Movement += 0.02*GameDifficulty;
			if (hitOb1V2() && immune != 0.5) {
				Stop = true;
				Death = true;
				SpawnVariant2 = false;
			}
			if (Ob1XV2Movement >= 15 && SpawnMore) {
				SpawnRandomVariant = true;
				SpawnMore = false;
			}
			if (Ob1XV2Movement > 30) {
				SpawnVariant2 = false;
				Ob1XV2Movement = 0;
				SpawnMore = true;
				if (!SpawnPowerUp) {
					PowerUpCounter++;
				}
			}
		}
		if (Scene1 && SpawnVariant3) {
			Ob1XV3Movement += 0.02*GameDifficulty;
			if (hitOb1V3() && immune != 0.5) {
				Stop = true;
				Death = true;
				SpawnVariant3 = false;
			}
			if (Ob1XV3Movement >= 15 && SpawnMore) {
				SpawnRandomVariant = true;
				SpawnMore = false;
			}
			if (Ob1XV3Movement > 30) {
				SpawnVariant3 = false;
				Ob1XV3Movement = 0;
				SpawnMore = true;
				if (!SpawnPowerUp) {
					PowerUpCounter++;
				}
			}
		}
		/////////////////////////////////////////////

		//Scene 2 Engine
		//////////////////////////////////////////////////
		if (Scene2 && SpawnVariant0) {
			Ob2XV0Movement += 0.02*GameDifficulty;
			if (hitOb2V0() && immune != 0.5) {
				Stop = true;
				Death = true;
				SpawnVariant0 = false;
			}
			if (Ob2XV0Movement >= 15 && SpawnMore) {
				SpawnRandomVariant = true;
				SpawnMore = false;
			}
			if (Ob2XV0Movement > 30) {
				SpawnVariant0 = false;
				Ob2XV0Movement = 0;
				SpawnMore = true;
				if (!SpawnPowerUp) {
					PowerUpCounter++;
				}
			}
		}
		if (Scene2 && SpawnVariant1) {
			Ob2XV1Movement += 0.02*GameDifficulty;
			if (hitOb2V1() && immune != 0.5) {
				Stop = true;
				Death = true;
				SpawnVariant1 = false;
			}
			if (Ob2XV1Movement >= 15 && SpawnMore) {
				SpawnRandomVariant = true;
				SpawnMore = false;
			}
			if (Ob2XV1Movement > 30) {
				SpawnVariant1 = false;
				Ob2XV1Movement = 0;
				SpawnMore = true;
				if (!SpawnPowerUp) {
					PowerUpCounter++;
				}
			}
		}
		if (Scene2 && SpawnVariant2) {
			Ob2XV2Movement += 0.02*GameDifficulty;
			if (hitOb2V2() && immune != 0.5) {
				Stop = true;
				Death = true;
				SpawnVariant2 = false;
			}
			if (Ob2XV2Movement >= 15 && SpawnMore) {
				SpawnRandomVariant = true;
				SpawnMore = false;
			}
			if (Ob2XV2Movement > 30) {
				SpawnVariant2 = false;
				Ob2XV2Movement = 0;
				SpawnMore = true;
				if (!SpawnPowerUp) {
					PowerUpCounter++;
				}
			}
		}
		if (Scene2 && SpawnVariant3) {
			Ob2XV3Movement += 0.02*GameDifficulty;
			if (hitOb2V3() && immune != 0.5) {
				Stop = true;
				Death = true;
				SpawnVariant3 = false;
			}
			if (Ob2XV3Movement >= 15 && SpawnMore) {
				SpawnRandomVariant = true;
				SpawnMore = false;
			}
			if (Ob2XV3Movement > 30) {
				SpawnVariant3 = false;
				Ob2XV3Movement = 0;
				SpawnMore = true;
				if (!SpawnPowerUp) {
					PowerUpCounter++;
				}
			}
		}
		/////////////////////////////////////////////

		//Scene 3 Engine
		//////////////////////////////////////////////////
		if (Scene3 && SpawnVariant0) {
			Ob3XV0Movement += 0.02*GameDifficulty;
			if (hitOb3V0() && immune != 0.5) {
				Stop = true;
				Death = true;
				SpawnVariant0 = false;
			}
			if (Ob3XV0Movement >= 15 && SpawnMore) {
				SpawnRandomVariant = true;
				SpawnMore = false;
			}
			if (Ob3XV0Movement > 30) {
				SpawnVariant0 = false;
				Ob3XV0Movement = 0;
				SpawnMore = true;
				if (!SpawnPowerUp) {
					PowerUpCounter++;
				}
			}
		}
		if (Scene3 && SpawnVariant1) {
			Ob3XV1Movement += 0.02*GameDifficulty;
			if (hitOb3V1() && immune != 0.5) {
				Stop = true;
				Death = true;
				SpawnVariant1 = false;
			}
			if (Ob3XV1Movement >= 15 && SpawnMore) {
				SpawnRandomVariant = true;
				SpawnMore = false;
			}
			if (Ob3XV1Movement > 30) {
				SpawnVariant1 = false;
				Ob3XV1Movement = 0;
				SpawnMore = true;
				if (!SpawnPowerUp) {
					PowerUpCounter++;
				}
			}
		}
		if (Scene3 && SpawnVariant2) {
			Ob3XV2Movement += 0.02*GameDifficulty;
			if (hitOb3V2() && immune != 0.5) {
				Stop = true;
				Death = true;
				SpawnVariant2 = false;
			}
			if (Ob3XV2Movement >= 15 && SpawnMore) {
				SpawnRandomVariant = true;
				SpawnMore = false;
			}
			if (Ob3XV2Movement > 30) {
				SpawnVariant2 = false;
				Ob3XV2Movement = 0;
				SpawnMore = true;
				if (!SpawnPowerUp) {
					PowerUpCounter++;
				}
			}
		}
		if (Scene3 && SpawnVariant3) {
			Ob3XV3Movement += 0.02*GameDifficulty;
			if (hitOb3V3() && immune != 0.5) {
				Stop = true;
				Death = true;
				SpawnVariant3 = false;
			}
			if (Ob3XV3Movement >= 15 && SpawnMore) {
				SpawnRandomVariant = true;
				SpawnMore = false;
			}
			if (Ob3XV3Movement > 30) {
				SpawnVariant3 = false;
				Ob3XV3Movement = 0;
				SpawnMore = true;
				if (!SpawnPowerUp) {
					PowerUpCounter++;
				}
			}
		}
		/////////////////////////////////////////////

		//Magic Gate
		////////////////////////////////////////////
		if (SpawnMagicGate) {
			GateXMovement += 0.02*GameDifficulty;
			if (GateXMovement >= 29 && Scene1) {
				Scene1 = false;
				Scene2 = true;
				SpawnMagicGate = false;
				GateXMovement = 0;
				SpawnRandomVariant = true;
				init_smoke_screen2(0);
				smoke_screen2_speed = 0;
			}

			if (GateXMovement >= 29 && Scene2) {
				Scene2 = false;
				Scene3 = true;
				SpawnMagicGate = false;
				GateXMovement = 0;
				SpawnRandomVariant = true;
				init_smoke_screen2(0);
				smoke_screen2_speed = 0;
			}

			if (GateXMovement >= 29 && Scene3) {
				Scene3 = false;
				Scene1 = true;
				SpawnMagicGate = false;
				GateXMovement = 0;
				SpawnRandomVariant = true;
				init_smoke_screen2(0);
				smoke_screen2_speed = 0;
				GameDifficulty += 0.5;
			}
		}
		/////////////////////////////////////////////

		Ob2Rotation += 0.5;

		if (PowerUpCounter >= 15) {
			RandomizePowerUpLocation = true;
			PowerUpCounter = 0;
		}

		if (SpawnPowerUp) {
			PowerUpXtranslation += 0.02*GameDifficulty;
			if (hitPowerUp()) {
				//printf("hello");
				immune = 0.5;
				SpawnPowerUp = false;
				PowerUpXtranslation = 0;
				init_smoke_screen1(PlayerZposition);
			}
			if (PowerUpXtranslation >= 40) {
				SpawnPowerUp = false;
				PowerUpXtranslation = 0;
			}
		}

		if (immune == 0.5) {
			if (immuneDuration >= 1500) {
				immune = 1;
				immuneDuration = 0;
				init_smoke_screen1(PlayerZposition);
			}
			else
				immuneDuration++;
		}

	}

	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();

	// recall the Timer function after 1 millisecond 
	glutTimerFunc(1, Timer, 0);
}

void setupLight() {


	//directional for walls
	glLightfv(GL_LIGHT1, GL_DIFFUSE, new GLfloat[3]{ l1_r,l1_g,l1_b });
	glLightfv(GL_LIGHT1, GL_SPECULAR, new GLfloat[3]{ 1.0f,1.0f,1.0f });
	glLightfv(GL_LIGHT1, GL_POSITION, new GLfloat[4]{ 0,0,-1,0 });
	//glLightfv(GL_LIGHT1, GL_AMBIENT, new GLfloat[3]{ .1f,.1f,.1f });
	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90);
	//glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0);
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, new GLfloat[3]{ 0.0f,-1,0.0f });


	//spot for ninja
	glLightfv(GL_LIGHT2, GL_DIFFUSE, new GLfloat[3]{ l2_r,l2_g,l2_b });
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45);
	glLightfv(GL_LIGHT2, GL_SPECULAR, new GLfloat[3]{ 1.0f,1.0f,1.0f });
	glLightfv(GL_LIGHT2, GL_POSITION, new GLfloat[4]{ 0,4,0,1 });
	//glLightfv(GL_LIGHT2, GL_AMBIENT, new GLfloat[3]{ 1,1,1 });
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, new GLfloat[3]{ 0.0f,-1,0.0f });

	//directional for ground
	glLightfv(GL_LIGHT3, GL_DIFFUSE, new GLfloat[3]{ l3_r,l3_g,l3_b });
	glLightfv(GL_LIGHT3, GL_SPECULAR, new GLfloat[3]{ 1.0f,1.0f,1.0f });
	glLightfv(GL_LIGHT3, GL_POSITION, new GLfloat[4]{ 0,5,0,0 });

	//directional for obstacles
	glLightfv(GL_LIGHT5, GL_DIFFUSE, new GLfloat[3]{ l5_r,l5_g,l5_b });
	glLightfv(GL_LIGHT5, GL_SPECULAR, new GLfloat[3]{ 1.0f,1.0f,1.0f });
	glLightfv(GL_LIGHT5, GL_POSITION, new GLfloat[4]{ 1,0,0,0 });
	//glLightfv(GL_LIGHT5, GL_LINEAR_ATTENUATION, new GLfloat[1]{ 0.9f });


	// postitional
	glLightfv(GL_LIGHT4, GL_DIFFUSE, new GLfloat[3]{ l4_r,l4_g,l4_b });
	glLightfv(GL_LIGHT4, GL_SPECULAR, new GLfloat[3]{ 1.0f,1.0f,1.0f });
	glLightfv(GL_LIGHT4, GL_POSITION, new GLfloat[4]{ -17,5,0,1 });
	glLightfv(GL_LIGHT4, GL_CONSTANT_ATTENUATION, new GLfloat[1]{ 0.0 });
	glLightfv(GL_LIGHT4, GL_LINEAR_ATTENUATION, new GLfloat[1]{ 0.3f });
	glLightfv(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, new GLfloat[1]{ 0.0 });

}

//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, new GLfloat[3]{ 1,1,1 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, new GLfloat[1]{ 100 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, new GLfloat[3]{ 0,0,0 });
	setupLight();
	// Draw Ground
	RenderGround();

	// Draw Tree Model
	/*glPushMatrix();
	glTranslatef(10, 0, 0);
	glScalef(0.7, 0.7, 0.7);
	model_tree.Draw();
	glPopMatrix();*/

	// Draw house Model
	/*glPushMatrix();
	glRotatef(90.f, 1, 0, 0);
	model_house.Draw();
	glPopMatrix();*/


	//sky box
	glPushMatrix();

	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 100, 100, 100);
	gluDeleteQuadric(qobj);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	if (SpawnRandomVariant)
	{
		int oldRandomVariant = RandomVariant;
		RandomVariant = rand() % 4;

		while (RandomVariant == oldRandomVariant) // making sure it is a different variant
		{
			RandomVariant = rand() % 4;
		}
		MagicGateCounter++;
		SpawnRandomVariant = false;

		if (RandomVariant == 0 && MagicGateCounter >= 10) {
			SpawnVariant0 = false;
			MagicGateCounter = 0;
			SpawnMagicGate = true;
			init_smoke_screen2(0);
			smoke_screen2_speed = 0.02;
		}
		else if (RandomVariant == 0) {
			SpawnVariant0 = true;
			CurrrentZpositin = 0;
		}

		if (RandomVariant == 1 && MagicGateCounter >= 10) {
			SpawnVariant1 = false;
			MagicGateCounter = 0;
			SpawnMagicGate = true;
			init_smoke_screen2(0);
			smoke_screen2_speed = 0.02;
		}
		else if (RandomVariant == 1) {
			SpawnVariant1 = true;
			CurrrentZpositin = -2;
		}

		if (RandomVariant == 2 && MagicGateCounter >= 10) {
			SpawnVariant2 = false;
			MagicGateCounter = 0;
			SpawnMagicGate = true;
			init_smoke_screen2(0);
			smoke_screen2_speed = 0.02;
		}
		else if (RandomVariant == 2) {
			SpawnVariant2 = true;
			CurrrentZpositin = 2;
		}

		if (RandomVariant == 3 && MagicGateCounter >= 10) {
			SpawnVariant3 = false;
			MagicGateCounter = 0;
			SpawnMagicGate = true;
			init_smoke_screen2(0);
			smoke_screen2_speed = 0.02;
		}
		else if (RandomVariant == 3) {
			SpawnVariant3 = true;
			CurrrentZpositin = 0;
		}

	}

	if (RandomizePowerUpLocation) {
		int random = rand() % 3;
		PowerUpSpawnLocation = PowerUpPossibleSpawnLocations[random];
		SpawnPowerUp = true;
		RandomizePowerUpLocation = false;
	}

	//left Wall
	left_wall();

	//right Wall
	right_wall();

	smoke_screen1();
	smoke_screen2();
	smoke_screen3();

	if (Scene1 && SpawnVariant0) {
		//Obstacle1 Variant 0
		glPushMatrix();
		glTranslated(Ob1XV0Movement, 0, 0);
		glTranslated(-23, Ob1Movement, -3.8);
		glRotated(Ob1Rotation, 0, 0, 1);
		glScaled(1, 1, 2.5);
		drawObstacle1();
		glPopMatrix();
	}

	if (Scene1 && SpawnVariant1) {
		//Obstacle1 Variant 1
		glPushMatrix();
		glTranslated(-23 + Ob1XV1Movement, 0, -2);
		glRotated(Ob1Rotation, 0, 1, 0);
		glRotated(-90, 1, 0, 0);
		glScaled(1, 1, 2.5);
		drawObstacle1();
		glPopMatrix();
	}

	if (Scene1 && SpawnVariant2) {
		//Obstacle1 Variant 2
		glPushMatrix();
		glTranslated(-23 + Ob1XV2Movement, 0, 2);
		glRotated(Ob1Rotation, 0, 1, 0);
		glRotated(-90, 1, 0, 0);
		glScaled(1, 1, 2.5);
		drawObstacle1();
		glPopMatrix();
	}

	if (Scene1 && SpawnVariant3) {
		//Obstacle1 Variant 3
		glPushMatrix();
		glTranslated(-23 + Ob1XV3Movement, 0, 0);
		glRotated(Ob1Rotation, 0, 1, 0);
		glRotated(-90, 1, 0, 0);
		glScaled(1, 1, 2.5);
		drawObstacle1();
		glPopMatrix();
	}

	if (Scene2 && SpawnVariant0) {
		//Obstacle 2 variant 0
		glPushMatrix();
		glTranslated(-25 + Ob2XV0Movement, 0, 0);
		glTranslated(0, 0.75, 0);
		glRotated(-Ob2Rotation, 0, 0, 1);
		glScaled(2, 2, 2);
		drawObstacle2();
		glPopMatrix();
	}

	if (Scene2 && SpawnVariant1) {
		//Obstacle 2 variant 1
		glPushMatrix();
		glTranslated(-25 + Ob2XV1Movement, 0, 0);
		glTranslated(0, 0.75, -2);
		glRotated(-Ob2Rotation, 0, 0, 1);
		glScaled(2, 2, 2);
		drawObstacle2();
		glPopMatrix();
	}

	if (Scene2 && SpawnVariant2) {
		//Obstacle 2 variant 2
		glPushMatrix();
		glTranslated(-25 + Ob2XV2Movement, 0, 0);
		glTranslated(0, 0.75, 2);
		glRotated(-Ob2Rotation, 0, 0, 1);
		glScaled(2, 2, 2);
		drawObstacle2();
		glPopMatrix();
	}

	if (Scene2 && SpawnVariant3) {
		//Obstacle 2 variant 3
		glPushMatrix();
		glTranslated(-25 + Ob2XV3Movement, 0, 0);
		glTranslated(0, 0.75, -2);
		glRotated(-Ob2Rotation, 0, 0, 1);
		glScaled(2, 2, 2);
		drawObstacle2();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-25 + Ob2XV3Movement, 0, 0);
		glTranslated(0, 0.75, 2);
		glRotated(-Ob2Rotation, 0, 0, 1);
		glScaled(2, 2, 2);
		drawObstacle2();
		glPopMatrix();
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (Scene3 && SpawnVariant0) {
		//Obstacle 3 variant 0
		glPushMatrix();
		glTranslated(-25 + Ob3XV0Movement, 0, 0);
		glTranslated(0, 1, -2);
		glRotated(90, 0, 1, 0);
		drawObstacle3();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-25 + Ob3XV0Movement, 0, 0);
		glTranslated(0, 1, 2);
		glRotated(90, 0, 1, 0);
		drawObstacle3();
		glPopMatrix();
	}

	if (Scene3 && SpawnVariant1) {
		//Obstacle 3 variant 1
		glPushMatrix();
		glTranslated(-25 + Ob3XV1Movement, 0, 0);
		glTranslated(0, 1, -2);
		glRotated(90, 0, 1, 0);
		drawObstacle3();
		glPopMatrix();
	}

	if (Scene3 && SpawnVariant2) {
		//Obstacle 3 variant 2
		glPushMatrix();
		glTranslated(-25 + Ob3XV2Movement, 0, 0);
		glTranslated(0, 1, 2);
		glRotated(90, 0, 1, 0);
		drawObstacle3();
		glPopMatrix();
	}

	if (Scene3 && SpawnVariant3) {
		//Obstacle 3 variant 3
		glPushMatrix();
		glTranslated(-25 + Ob3XV3Movement, 0, 0);
		glTranslated(0, 1, 0);
		glRotated(90, 0, 1, 0);
		drawObstacle3();
		glPopMatrix();
	}

	//glEnable(GL_COLOR_MATERIAL);
	if (SpawnMagicGate) {
		//Magic Gate
		glPushMatrix();
		//glColor4f(1, 1, 0, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 1, 0, 0 });
		glTranslated(-25 + GateXMovement, 0, 0);
		glScaled(0.1, 50, 20);
		glutSolidCube(3);
		glPopMatrix();
	}

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (SpawnCollectible)
		for (int i = 0; i <= CollectibleCounter; i += 1) {
			SpawnCollectibleHelper(CurrrentZpositin, i);
		}

	//Power Up
	if (SpawnPowerUp) {
		glPushMatrix();
		glTranslated(-33.5 + PowerUpXtranslation, 0.5, PowerUpSpawnLocation);
		glRotated(PowerUpRotation, 0, 1, 0);
		drawPowerUp();
		glPopMatrix();
	}

	//Mini Ninja
	glPushMatrix();
	if (Slide) {
		glTranslated(0, SlideBody, 0);
	}
	if (Jump || Run) {
		glTranslated(0, JumpBody, 0);
	}
	glTranslated(PlayerXposition, PlayerYposition, PlayerZposition);
	glRotated(180, 0, 1, 0);
	drawNinja();
	glPushMatrix();
	//glColor4f(1, 0, 0, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[4]{ 1, 0, 0, 0 });
	glTranslated(0.15, -0.3, 0);
	glutSolidSphere(NinjaHitRadius, 50, 50);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_BLEND);

	//glPushMatrix();
	//glColor4f(1, 0, 0, 1);
	//glTranslated(PlayerXposition-0.5, PlayerYposition+0.1, PlayerZposition);
	//glutSolidSphere(0.1,20,20);
	//glPopMatrix();

	//Show score
	glPushMatrix();
	glColor3f(0, 0, 1);
	glDisable(GL_LIGHTING);
	//glRasterPos3d(3.85, 1.85, 3);
	if (!FirstPerson) {
		glRasterPos3f(1, 4.5, 0);
	}
	if (FirstPerson) {
		glRasterPos3f(PlayerXposition - 3, PlayerYposition + 0.8 + Jump - Slide, PlayerZposition);
	}
	char score_s[10];
	_itoa_s(score / 10, score_s, 10);
	for (int i = 0; i<10; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (INT32)score_s[i]);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	////////////////////////////////////

	glutSwapBuffers();
}

//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char button, int x, int y)
{
	switch (button)
	{
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 27:
		exit(0);
		break;
		//case 'p':
		//if (!Run && !Slide && !Death)
		//Run = true;
		//break;
	case 'j':
		if (!Jump && !Slide && !Death && !cameraMode)
			Jump = true;
		break;
	case 'c':
		if (!Slide && !Jump && !Death && !cameraMode)
			Slide = true;
		break;
		//case 'm':
		//if (!Death)
		//Death = true;
		//else
		//Death = false;
		//break;
	case 'a':
		if (PlayerZposition != 2 && !Death && !cameraMode) {
			init_smoke_screen1(PlayerZposition);
			PlayerZposition += 2;
		}
		if (cameraMode) {
			if (Eye.z <= 2.5)
				Eye.z += 0.1;
		}
		break;
	case 'd':
		if (PlayerZposition != -2 && !Death && !cameraMode) {
			init_smoke_screen1(PlayerZposition);
			PlayerZposition -= 2;
		}
		if (cameraMode) {
			if (Eye.z >= -2.5)
				Eye.z -= 0.1;
		}
		break;
	case '`':
		if (!cameraMode) {
			if (!FirstPerson)
				FirstPerson = true;
			else
				FirstPerson = false;
		}
	case 'p':
		if (!cameraMode)
			cameraMode = true;
		else
			cameraMode = false;
	default:
		break;
	}

	glutPostRedisplay();
}

//=======================================================================
// Motion Function
//=======================================================================
void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	init_smoke_screen2(0);
	init_smoke_screen3(0);
	// Loading texture files
	tex_ground.Load("Textures/brick_cartoon2.bmp");
	//loadBMP(&tex, "Textures/sky4-jpg.bmp", true);
	tex_wall_scene_1.Load("textures/ceiling_cartoon.bmp");
	tex_wall_scene_2.Load("textures/brick_cartoon1.bmp");
	tex_wall_scene_3.Load("textures/wood_cartoon1.bmp");
	loadBMP(&tex_Ob2, "textures/iron.bmp", true);
	loadBMP(&tex_Ob1, "textures/wood_cartoon4.bmp", true);
	loadBMP(&tex_Cloth, "textures/Cloth.bmp", true);
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);


	glutCreateWindow(title);

	glutFullScreen();

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(myKeyboard);

	glutMotionFunc(myMotion);

	glutMouseFunc(myMouse);

	glutReshapeFunc(myReshape);

	glutTimerFunc(0, Timer, 0);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_NORMALIZE);
	//glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}

void left_wall() {

	glPushMatrix();
	//glDisable(GL_LIGHTING);	// Disable lighting 

	//glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[3]{ 1,1,1 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, new GLfloat[3]{ 1,1,1 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, new GLfloat[1]{ 100 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, new GLfloat[3]{ 0,0,0 });

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	if (Scene1)
		glBindTexture(GL_TEXTURE_2D, tex_wall_scene_1.texture[0]);
	if (Scene2)
		glBindTexture(GL_TEXTURE_2D, tex_wall_scene_2.texture[0]);
	if (Scene3)
		glBindTexture(GL_TEXTURE_2D, tex_wall_scene_3.texture[0]);
	// Bind the ground texture
	glPushMatrix();
	glTranslated(ground_x, 0, 3);
	glRotated(-90, 1, 0, 0);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(20, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(20, 20);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 20);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslated(ground_x - 40, 0, 3);
	glRotated(-90, 1, 0, 0);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(20, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(20, 20);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 20);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	/*glPushMatrix();
	if (Scene1)
	glColor4f(1, 0, 0, 1);
	if (Scene2)
	glColor4f(0, 1, 0, 1);
	if (Scene3)
	glColor4f(0, 0, 1, 1);
	glTranslated(-2.5, 0, 3.52);
	glScaled(1000, 50, 1);
	glutSolidCube(0.2);
	glPopMatrix();*/
	glDisable(GL_TEXTURE_2D);

	//glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

}
void move_ground() {
	if (!Death) {
		ground_x += speed_ground*GameDifficulty;
		if (ground_x >= 40) {
			ground_x = 0;
		}
	}
}

void right_wall() {

	glPushMatrix();
	//glDisable(GL_LIGHTING);	// Disable lighting 

	//glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, new GLfloat[3]{ 1,1,1 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, new GLfloat[3]{ 1,1,1 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, new GLfloat[1]{ 100 });
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, new GLfloat[3]{ 0,0,0 });

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	if (Scene1)
		glBindTexture(GL_TEXTURE_2D, tex_wall_scene_1.texture[0]);
	if (Scene2)
		glBindTexture(GL_TEXTURE_2D, tex_wall_scene_2.texture[0]);
	if (Scene3)
		glBindTexture(GL_TEXTURE_2D, tex_wall_scene_3.texture[0]);
	// Bind the ground texture
	glPushMatrix();
	glTranslated(ground_x, 0, -3);
	glRotated(-90, 1, 0, 0);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(20, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(20, 20);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 20);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslated(ground_x - 40, 0, -3);
	glRotated(-90, 1, 0, 0);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(20, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(20, 20);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 20);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	//glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

}
void init_smoke_screen1(double playerZ) {
	for (int i = 0; i < circle_size; i++) {
		circle_x1[i] = rand() % 100 * .01;
		circle_y1[i] = rand() % 300 * .01;
		circle_z1[i] = rand() % 100 * .01 + playerZ;
		circle_rad1[i] = .01;
		circle_flag1[i] = 1;

	}

}
void smoke_screen1() {

	glPushMatrix();
	glTranslated(0, 0, -0.3);
	for (int i = 0; i < circle_size; i++) {
		circle_y1[i] += .005;
		circle_rad1[i] += .002;
		circle_x1[i] += .02;
		if (circle_y1[i] > 2.2) {
			circle_y1[i] = 0;
			circle_flag1[i] = 0;
		}
		if (circle_flag1[i])
			circle(circle_x1[i], circle_y1[i], circle_z1[i], circle_rad1[i]);
	}
	glPopMatrix();

}
void circle(double x, double y, double z, double rand) {
	glPushMatrix();
	glTranslated(x, y, z);
	glScaled(.1, 1, 1);
	glutSolidSphere(rand, 8, 8);
	glPopMatrix();
}
void init_smoke_screen2(double playerZ) {
	for (int i = 0; i < circle_size2; i++) {
		circle_x2[i] = rand() % 1000 * .01 - 30;
		circle_y2[i] = rand() % 500 * .01 - .02;
		circle_z2[i] = rand() % 600 * .01 - 3;
		circle_rad2[i] = .8;
		circle_flag2[i] = 1;

	}

}
void smoke_screen2() {

	glPushMatrix();
	glTranslated(0, 0, -0.3);
	for (int i = 0; i < circle_size2; i++) {
		circle_y2[i] += .005;
		circle_rad2[i] += .002;
		circle_x2[i] += smoke_screen2_speed*GameDifficulty;
		if (circle_y2[i] > 5) {
			circle_y2[i] = -0.2;
			circle_rad2[i] = .8;
		}
		if (circle_flag2[i])
			circle(circle_x2[i], circle_y2[i], circle_z2[i], circle_rad2[i]);
	}
	glPopMatrix();

}


void init_smoke_screen3(double playerZ) {
	for (int i = 0; i < circle_size3; i++) {
		circle_x3[i] = rand() % 1000 * .01 + 10;
		circle_y3[i] = rand() % 500 * .01 - .02;
		circle_z3[i] = rand() % 600 * .01 - 3;
		circle_rad3[i] = .8;
		circle_flag3[i] = 1;

	}

}
void smoke_screen3() {

	glPushMatrix();
	glTranslated(0, 0, -0.3);
	for (int i = 0; i < circle_size3; i++) {
		circle_y3[i] += .005;
		circle_rad3[i] += .002;
		if (circle_y3[i] > 5) {
			circle_y3[i] = -0.2;
			circle_rad3[i] = .8;
		}
		if (circle_flag3[i])
			circle(circle_x3[i], circle_y3[i], circle_z3[i], circle_rad3[i]);
	}
	glPopMatrix();

}