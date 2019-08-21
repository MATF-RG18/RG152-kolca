#include "svetlo.h"

/* inicijalizujemo sva svetla koja imamo */
void inicijalizacija_svetla(void) {
    /* svetlo za kolca */
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 30, 30, -100, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.4, 0.4, 0.4, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.8, 0.8, 0.8, 1 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* svetlo za prozore */
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position2[] = { 30, 30, -100, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient2[] = { 0.1, 0.1, 0.1, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse2[] = { 0.4, 0.4, 0.4, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular2[] = { 0.8, 0.8, 0.8, 1 };

    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular2);
}