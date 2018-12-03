#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

const static float tr_x_delta = 0.1;
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
    
    glutMainLoop();
    
    return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
        case 'd':
            tr_x += tr_x_delta;
            if (tr_x > 2) {
                tr_x = 2;
            }
            glutPostRedisplay();
            break;
        case 'a':
            tr_x -= tr_x_delta;
            if (tr_x < -2) {
                tr_x = -2;
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

static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 3, 10.5, 0, 0, 0, 0, 1, 0);
    
    glBegin(GL_POLYGON);
        glColor3f(0.5, 0.5, 0.5);
        glVertex3f(2.5, -0.5, 7.5);
        glVertex3f(-2.5, -0.5, 7.5);
        glVertex3f(-2.5, -0.5, -300);
        glVertex3f(2.5, -0.5, -300);
    glEnd();
    glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslatef(tr_x, 0, 6);
        glScalef(1, 1, 2.5);
        glutSolidCube(0.8);
    glPopMatrix();
    glutSwapBuffers();
}