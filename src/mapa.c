#include "mapa.h"

/* fja crta mapu */
void nacrtaj_mapu(void) {

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

    /* nebo */
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
    
    glEnd();

    nacrtaj_prepreke();
}