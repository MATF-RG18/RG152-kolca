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
#include "svetlo.h"
#include "mapa.h"

#define TIMER_ID 1
#define TIMER_INTERVAL 10

/* promenljive za skretanje */
const float tr_x_delta = 0.075; /* konstanta za promenu x parametra kolca */
float tr_x; /* trenutna vrednost x parametra kolca */
int animation_ongoing; /* parametar aktivnosti igrice */

int window_width, window_height;

/* funkcije */
void on_keyboard(unsigned char key, int x, int y);
void on_display(void);
void on_reshape(int width, int height);
void on_timer(int value);

void inicijalizacije(void); /* inicijalizuje pocetne vrednosti igrice */

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
    inicijalizacija_svetla();
}

void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
        /* pokrecemo igricu */
        case 'g':
        case 'G':
            if (!animation_ongoing) {
                animation_ongoing = 1;
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
            }
            break;
        /* stopiramo igricu */
        case 's':
        case 'S':
            animation_ongoing = 0;
            break;
        /* skrecemo desno */
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
        /* restartujemo igricu */
        case 'r':
        case 'R':
            inicijalizacije();
            break;
    }
}

void on_timer(int value) {
    if (value != TIMER_ID)
        return;

    poeni += 0.015; /* povecavamo broj poena */
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

void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 3, 7, 0, 0, 0, 0, 1, 0);
    
    nacrtaj_mapu();

    ispis_helti();
    ispis_poeni();
    
    nacrtaj_kolca();

    glutSwapBuffers();
}