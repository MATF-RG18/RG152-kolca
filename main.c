#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "prepreke.h"
#include "model_autica.h"
#include "kolizije.h"
#include "helti.h"
#include "tekstura.h"
#include "image.h"

#define TIMER_ID 1
#define TIMER_INTERVAL 10

/* promenljive za skretanje */
const float tr_x_delta = 0.075;
float tr_x;
int animation_ongoing;

int window_width, window_height;

void on_keyboard(unsigned char key, int x, int y);
void on_display(void);
void on_reshape(int width, int height);
void on_timer(int value);

void mapa(void);
void inicijalizacije(void);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("kolca");
        
    inicijalizacije();
    
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor(0.7, 0.7, 0.99, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    glutMainLoop();
    
    return 0;
}

void inicijalizacije(void) {
    tr_x = 0;
    inicijalizacija_prepreka();
    srand(time(NULL));
    animation_ongoing = 0;
    helti = 100;
    sudar_u_toku = 0;
    inicijalizacija_teksture();
    poeni = 0;
}

void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
        /* skrecemo desno */
        case 'g':
        case 'G':
            if (!animation_ongoing) {
                animation_ongoing = 1;
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
            }
            break;
        case 's':
        case 'S':
            animation_ongoing = 0;
            break;
        case 'd':
        case 'D':
            tr_x += tr_x_delta;
            if (tr_x > 1.4)
                tr_x = 1.4;
            break;
        /* skrecemo levo */
        case 'a':
        case 'A':
            tr_x -= tr_x_delta;
            if (tr_x < -1.4)
                tr_x = -1.4;
            break;
    }
}

void on_timer(int value) {
    if (value != TIMER_ID)
        return;

    poeni += 0.015;
    provera_sudara();
    azuriraj_prepreke();
    glutPostRedisplay();

    if (animation_ongoing)
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
}


void on_reshape(int width, int height)
{
    window_width = width;
    window_height = height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width/height, 1, 300);
}

/* generisanje mape */
void mapa(void)
{
    /* put */
    /*glColor3f(0.25, 0.25, 0.25);*/
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, names[PUT_TEKSTURA]);
    glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 0);
        glVertex3f(-2, 0, 5);

        glTexCoord2f(1, 0);
        glVertex3f(2, 0, 5);

        glTexCoord2f(1, 1);
        glVertex3f(2, 0, -75);

        glTexCoord2f(0, 1);
        glVertex3f(-2, 0, -75);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    /* leva trava */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, names[TRAVA_TEKSTURA]);
    glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);

        glTexCoord2f(0, 0);
        glVertex3f(-100, 0, 5);

        glTexCoord2f(10, 0);
        glVertex3f(-2, 0, 5);

        glTexCoord2f(10, 10);
        glVertex3f(-2, 0, -75);

        glTexCoord2f(0, 10);
        glVertex3f(-100, 0, -75);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    /* desna trava */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, names[TRAVA_TEKSTURA]);
    glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);

        glTexCoord2f(0, 0);
        glVertex3f(2, 0, 5);

        glTexCoord2f(10, 0);
        glVertex3f(100, 0, 5);

        glTexCoord2f(10, 10);
        glVertex3f(100, 0, -75);

        glTexCoord2f(0, 10);
        glVertex3f(2, 0, -75);
    glEnd();    
    glDisable(GL_TEXTURE_2D);

    /* desna planina *//*
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, names[PLANINA_TEKSTURA]);
    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);
        glVertex3f(-10, 0, -75);
        glTexCoord2f(0, 20);
        glVertex3f(50, 0, -75);
        glTexCoord2f(20, 10);
        glVertex3f(20, 10, -75);
    glEnd();
    glDisable(GL_TEXTURE_2D);*/

    /* leva planina *//*
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, names[PLANINA_TEKSTURA]);
    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-50, 0, -75);
        glVertex3f(10, 0, -75);
        glVertex3f(-20, 10, -75);
    glEnd();
    glDisable(GL_TEXTURE_2D);
*/

    /* nebo *//*
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, names[PLANINA_TEKSTURA]);*/
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.6, 0.9);
        glTexCoord2f(0, 0);
        glVertex3f(-100, 0, -75);

        glTexCoord2f(6, 0);
        glVertex3f(100, 0, -75);
        
        glTexCoord2f(6, 6);
        glVertex3f(100, 100, -75);
        
        glTexCoord2f(0, 6);
        glVertex3f(-100, 100, -75);
       /* 
    glDisable(GL_TEXTURE_2D);*/
    glEnd();

    nacrtaj_prepreke();
}

void dnevno_svetlo() {
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 30, 30, -100, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.2, 0.2, 0.2, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1 };

    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 0.3, 0.3, 0.3, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.5, 0.5, 0.5, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 20;

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /*dnevno_svetlo();*/

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 3, 7, 0, 0, 0, 0, 1, 0);
    
    mapa();

    ispis_helti();
    ispis_poeni();
    
    /* iscrtavamo kolca */
    nacrtaj_kolca();

    glutSwapBuffers();
}