#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.05
#define PI 3.1415926535897

/* promenljive za skretanje */
const static float tr_x_delta = 0.05;
static float tr_x;

static void on_keyboard(unsigned char key, int x, int y);
static void on_display(void);
static void on_reshape(int width, int height);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("kolca");
        
    
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    
    tr_x = 0;
    
    glClearColor(0.7, 0.7, 0.99, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    glutMainLoop();
    
    return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
        /* skrecemo desno */
        case 'd':
        case 'D':
            tr_x += tr_x_delta;
            if (tr_x > 1.25) {
                tr_x = 1.25;
            }
            glutPostRedisplay();
            break;
        /* skrecemo levo */
        case 'a':
        case 'A':
            tr_x -= tr_x_delta;
            if (tr_x < -1.25) {
                tr_x = -1.25;
            }
            glutPostRedisplay();
            break;
    }
}

static void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width/height, 1, 300);
}

void set_normal_and_vertex_tire(float u, float v, float r)
{
    glNormal3f(0, r*cos(v), r*sin(v));
    glVertex3f(u, r*cos(v), r*sin(v));
}
 /* crtanje kruga */
void draw_circle(float r)
{
    float v;
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.1, 0.1, 0.1);
    glVertex3f(0, 0, 0);
    for (v = 0; v <= 2*PI+EPSILON; v += PI/20) {
        glNormal3f(1, 0, 0);
        glVertex3f(0, r*cos(v), r*sin(v));
    }
    glEnd();
}
    
/* crtanje tocka */
void draw_tire(float r, float h)
{
    float u, v;
    
    for (u = -h/2; u < h/2; u += 0.01) {
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.1, 0.1, 0.1);
        for (v = 0; v <= 2*PI+EPSILON; v += PI/20) {
            set_normal_and_vertex_tire(u, v, r);
            set_normal_and_vertex_tire(u + 0.01, v, r);
        }
        glEnd();
    }
    
    glPushMatrix();
        glTranslatef(h/2, 0, 0);
        draw_circle(r);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-h/2, 0, 0);
        draw_circle(r);
    glPopMatrix();
}

/* crtanje kolca */
void draw_car(void)
{
    /*hauba*/
    glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslatef(0, -0.125, -0.6);
        glScalef(0.75, 0.25, 0.4);
        glutSolidCube(1);
    glPopMatrix();
    
    /*kabina*/
    double clip_plane0[] = {0, -0.75, -1, 1/(2*sqrt(2))+0.05};
    double clip_plane1[] = {0, -1, 1, 1/(2*sqrt(2))+0.05};
    glClipPlane(GL_CLIP_PLANE0, clip_plane0);
    glClipPlane(GL_CLIP_PLANE1, clip_plane1);
    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);
    glPushMatrix();
        glColor3f(0, 1, 0);
        glScalef(0.75, 0.5, 0.8);
        glutSolidCube(1);
    glPopMatrix();
    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_CLIP_PLANE1);
    
    /*gepek*/
    glPushMatrix();
        glColor3f(0, 0, 1);
        glTranslatef(0, -0.125, 0.55);
        glScalef(0.75, 0.25, 0.3);
        glutSolidCube(1);
    glPopMatrix();
    
    /*tockovi*/
    glPushMatrix();
        glTranslatef(0.351, -0.25, -0.6);
        draw_tire(0.1, 0.05);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-0.351, -0.25, -0.6);
        draw_tire(0.1, 0.05);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.351, -0.25, 0.5);
        draw_tire(0.1, 0.05);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-0.351, -0.25, 0.5);
        draw_tire(0.1, 0.05);
    glPopMatrix();
}

/* generisanje mape */
void mapa(void)
{
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_POLYGON);
        glVertex3f(-2, 0, 5);
        glVertex3f(2, 0, 5);
        glVertex3f(2, 0, -350);
        glVertex3f(-2, 0, -350);
    glEnd();
}

static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 3, 7, 0, 0, 0, 0, 1, 0);
    
    /*
    glBegin(GL_POLYGON);
        glColor3f(0.5, 0.5, 0.5);
        glVertex3f(2.5, -0.5, 7.5);
        glVertex3f(-2.5, -0.5, 7.5);
        glVertex3f(-2.5, -0.5, -250);
        glVertex3f(2.5, -0.5, -250);
    glEnd();
    */
    
    mapa();
    
    /* iscrtavamo kolca */
    glPushMatrix();
        glTranslatef(tr_x, 0.375, 2);
        draw_car();
    glPopMatrix();
    
    glutSwapBuffers();
}