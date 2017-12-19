// gcc fireworks.c -lglut -lGL -lGLU -lm -o fireworks

#include <GL/glut.h>  // Header File For The GLUT Library 
#include <GL/gl.h>	  // Header File For The OpenGL32 Library
#include <GL/glu.h>	  // Header File For The GLu32 Library
#include <math.h>
#include <unistd.h>

#define ESCAPE 27
#define NUM_PARTICLES 3000
#define GRAVITY 0.0003

struct s_pf_center {
  float x_c, y_c, veloc_x_c, veloc_y_c;
  unsigned lifetime_c;
} particles_c[NUM_PARTICLES];

struct s_pf_right {
  float x_r, y_r, veloc_x_r, veloc_y_r;
  unsigned lifetime_r;
} particles_r[NUM_PARTICLES];

struct s_pf_left {
  float x_l, y_l, veloc_x_l, veloc_y_l;
  unsigned lifetime_l;
} particles_l[NUM_PARTICLES];

int window; 
int countKeys=0;
float position = 0.0;
float color1 = 1.0, color2 = 1.0, color3 = 1.0;
float color4 = 1.0, color5 = 1.0, color6 = 1.0;
float color7 = 1.0, color8 = 1.0, color9 = 1.0;
int left=0, right=0;
float posX1 = 0.0, posY1 = 0.0;
float posX2 = 0.0, posY2 = 0.0;
float posX3 = 0.0, posY3 = 0.0;

// Initialize the firework
void InitParticleCenter(int pause){
  int i;

 // if(pause) usleep(200000 + rand() % 2000000);

  for(i=0;i<NUM_PARTICLES;i++) {
    float velocity_c = (float)(rand() % 100)/5000.0;
    int angle = rand() % 360;
    particles_c[i].veloc_x_c = cos( (M_PI * angle/180.0) ) * velocity_c;
    particles_c[i].veloc_y_c = sin( (M_PI * angle/180.0) ) * velocity_c;
    particles_c[i].x_c = 0.0;
    particles_c[i].y_c = 0.0;
    particles_c[i].lifetime_c = rand() % 100;
  }
}

// Initialize the firework
void InitParticleRight(int pause){
  int i;

 // if(pause) usleep(200000 + rand() % 2000000);

  for(i=0;i<NUM_PARTICLES;i++) {
    float velocity_r = (float)(rand() % 100)/5000.0;
    int angle = rand() % 360;
    particles_r[i].veloc_x_r = cos( (M_PI * angle/180.0) ) * velocity_r;
    particles_r[i].veloc_y_r = sin( (M_PI * angle/180.0) ) * velocity_r;
    particles_r[i].x_r = 0.0;
    particles_r[i].y_r = 0.0;
    particles_r[i].lifetime_r = rand() % 100;
  }
}

void InitParticleLeft(int pause){
  int i;

 // if(pause) usleep(200000 + rand() % 2000000);

  for(i=0;i<NUM_PARTICLES;i++) {
    float velocity_l = (float)(rand() % 100)/5000.0;
    int angle = rand() % 360;
    particles_l[i].veloc_x_l = cos( (M_PI * angle/180.0) ) * velocity_l;
    particles_l[i].veloc_y_l = sin( (M_PI * angle/180.0) ) * velocity_l;
    particles_l[i].x_l = 0.0;
    particles_l[i].y_l = 0.0;
    particles_l[i].lifetime_l = rand() % 100;
  }
}



/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height){
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix


  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	


  glMatrixMode(GL_MODELVIEW);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}

/* The main drawing function. */
void DrawGLScene(){
  int i, ative_particles_r=0;
  int j, ative_particles_c=0;
  int k, ative_particles_l=0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
  glLoadIdentity();				// Reset The View

    if (right == 1){
  	glColor3f(color1+0.1, color2+0.1, color3+0.1);
  	glTranslatef(-2.0,-2.0f,-6.0f);		// Move particles 6.0 units into the screen
	  glBegin(GL_POINTS);
	  for(j=0;j<NUM_PARTICLES;j++) {
	    if(particles_c[j].lifetime_c) {
			  ative_particles_c++;
			  particles_c[j].veloc_y_c -= GRAVITY;
			  particles_c[j].x_c += particles_c[j].veloc_x_c;
			  particles_c[j].y_c += particles_c[j].veloc_y_c;
			  particles_c[j].lifetime_c--;
			  glVertex3f( particles_c[j].x_c + posX1, particles_c[j].y_c + posY1, 0.0f); // draw pixel
	    }

	  }
	  glEnd();
  }


  		// Reset The View
  

  if (left == 1){
  	glColor3f(color4+0.1, color5+0.1, color6+0.1);
  	glTranslatef(-2.0,-2.0f,-6.0f);		// Move particles 6.0 units into the screen
	  glBegin(GL_POINTS);
	  for(k=0;k<NUM_PARTICLES;k++) {
	    if(particles_l[k].lifetime_l) {
			  ative_particles_l++;
			  particles_l[k].veloc_y_l -= GRAVITY;
			  particles_l[k].x_l += particles_l[k].veloc_x_l;
			  particles_l[k].y_l += particles_l[k].veloc_y_l;
			  particles_l[k].lifetime_l--;
			  glVertex3f( particles_l[k].x_l + posX2, particles_l[k].y_l + posY2, 0.0f); // draw pixel
	    }

	  }
	  glEnd();
  }

  
  // swap buffers to display, since we're double buffered.
  glutSwapBuffers();

//  if(!ative_particles) InitParticle(1); // reset particles
}



/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y){
	usleep(100);
	countKeys++;

	if (key == ESCAPE){ 
		glutDestroyWindow(window); 
		exit(0);                   
	}else if(key == 's'){
	//	position = 0.0;
		color1 = (float)((rand() % 9)/10.0);
		color2 = (float)((rand() % 9)/10.0);
		color3 = (float)((rand() % 9)/10.0);

		posX1 = (float)((rand() % 5)/1.0);
		posY1 = (float)((rand() % 5)/1.0);

		right = 1;
		InitParticleCenter(1);
	}else if (key == 'a'){
	//	position = -2.0;
		color4 = (float)((rand() % 9)/10.0);
		color5 = (float)((rand() % 9)/10.0);
		color6 = (float)((rand() % 9)/10.0);

		posX2 = (float)((rand() % 5)/1.0);
		posY2 = (float)((rand() % 5)/1.0);

		left = 1;
		InitParticleLeft(1);
		//InitParticle(1);
	}
}

int main(int argc, char **argv) 
{  
	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
	glutInitWindowSize(640, 480);  
	glutInitWindowPosition(0, 0);  
	window = glutCreateWindow("Fogos de artificio");  

	glutDisplayFunc(&DrawGLScene); glutIdleFunc(&DrawGLScene);

	glutReshapeFunc(&ReSizeGLScene);
	glutKeyboardFunc(&keyPressed);
	//  glutFullScreen();
	InitGL(640, 480);
	glutMainLoop();  

  return 0;
}

