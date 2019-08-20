#include "helti.h"

void ispis_helti(void) {
    if (helti <= 0) {
        int i;
        const char poruka[] = "GAME OVER";
        glRasterPos3f(-1, 1, 1);
        int len = strlen(poruka);
        glColor3f(1, 1, 1);
        for (i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, poruka[i]);
        }
    
        animation_ongoing = 0;
    } else {
        int i;
        char poruka[15];
        glColor3f(0.1, 0.2, 0.1);
        sprintf(poruka, "health: %d", helti);
        glRasterPos3f(-3, 3.5, 1);
        int len = strlen(poruka);
        for (i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, poruka[i]);
        }
    }
}

void ispis_poeni(void) {
    if (helti > 0) {
        int i;
        char poruka[15];
        sprintf(poruka, "points: %d", (int)poeni);
        glRasterPos3f(-1.5, 3.5, 1);
        int len = strlen(poruka);
        glColor3f(0.1, 0.2, 0.1);
        for (i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, poruka[i]);
        }
    } else {
        int i;
        char poruka[15];
        glColor3f(0.1, 0.1, 0.1);
        sprintf(poruka, "POINTS: %d", (int)poeni);
        glRasterPos3f(-0.75, 0.5, 1);
        int len = strlen(poruka);
        for (i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, poruka[i]);
        }
    }
}