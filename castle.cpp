// gcc castle.cpp -lglut -lGL -lGLU -o  castle && ./castle

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

int rotX = 0;
int rotY = 0;
int list;
GLUquadricObj *pObj;
float angle = 0.0;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    GLUquadricObj *pObj;
    pObj = gluNewQuadric();

    gluLookAt(0.0, 5.0, 2.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0);


    // TORRE CENTRAL
        // BASE
    glPushMatrix();
        glTranslatef(1.0, 0.0, 0.0);    
        gluCylinder(pObj,0.4f,0.4f,1.5f,32,32);
    glPopMatrix();
        // TELHADO 
    glPushMatrix();
        glTranslatef(1.0, 0.0, 1.5);
        glutSolidCone(0.4, 1.0, 20, 16);
    glPopMatrix();


    // TORRE PORTÃO
        // BASE
    glPushMatrix();
        glRotatef(30.0f, 0.0f, 0.0f, 1.2f);
        glTranslatef(-0.5, -0.1, 0.4);
     	glScalef(1.0f, 1.0f, 2.8f);
        glutSolidCube(0.5);
    glPopMatrix();
    glPopMatrix();
         // TELHADO
    glPushMatrix();
        glTranslatef(-0.4, -0.3, 1.1);
        glutSolidCone (0.3, 0.5, 20, 16);
    glPopMatrix();

    // TORRE DIREITA
        // BASE
    glPushMatrix();
        glTranslatef(-2.0, 0.0, -0.2);    
        gluCylinder(pObj,0.4f,0.4f,1.5f,32,32);
    glPopMatrix();
        // TELHADO 
    glPushMatrix();
        glTranslatef(-2.0, 0.0, 1.3);
        glutSolidCone(0.4, 1.0, 20, 16);
    glPopMatrix();

    
    // TORRE FUNDO
        // BASE
    glPushMatrix();
        glTranslatef(0.5, -3.3, 0.0);    
        gluCylinder(pObj,0.5f,0.5f,1.8f,32,32);
    glPopMatrix();
        // TELHADO 
    glPushMatrix();
        glTranslatef(0.5, -3.3, 1.7);
        glutSolidCone(0.5, 1.0, 20, 16);
    glPopMatrix();

    // MURO CENTRAL - PORTÃO
    glPushMatrix();
        glTranslatef(0.5, -1.3, 0.0);
     	glScalef(2.5f, 1.0f, 2.5f);
        glutSolidCube(0.5);
    glPopMatrix();
    

    // MURO PORTÃO - DIREITA
    glPushMatrix();
        glTranslatef(-1.4, -1.3, 0.0);
     	glScalef(2.5f, 1.0f, 2.5f);
        glutSolidCube(0.5);
    glPopMatrix();
   
    glFlush();
    glutSwapBuffers();
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize(800,600);
    glutCreateWindow("Castelo");

    glutDisplayFunc(display);
    glutIdleFunc( display );

    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspect = (GLfloat) 800 / 600;
    gluPerspective(45, aspect, 2.0f, 15.0f);
    glMatrixMode(GL_MODELVIEW);
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    glClearColor(0.15, 0.15, 0.15, 1.0);

    GLfloat mat_shininess[] =  { 50.0 };
    GLfloat mat_specular[] =   { 0.75, 0.75, 0.75, 0.75 };

    GLfloat light_ambient[] =  {  0.5,  0.5,  0.5, 1.0 };
    GLfloat light_diffuse[] =  {  1.0,  1.0,  1.0, 1.0 };
    GLfloat light_specular[] = {  1.0,  1.0,  1.0, 1.0 };
    GLfloat light_position[] = {  10.0,  2.0,  10.0, 0.0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glutMainLoop();

    return 0;
}
