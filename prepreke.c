#include "prepreke.h"

const float korak_prepreke = 5;
const float brzina_prepreke = 0.075;
Prepreka prepreke[MAX_PREPREKA];

Rupa napravi_rupu() {
    Rupa tmp_rupa;
    tmp_rupa.x = -1.0 + rand() / (float)RAND_MAX * 2.0;
    tmp_rupa.z = 5 - korak_prepreke * MAX_PREPREKA; 

    return tmp_rupa;
}

Rampa napravi_rampu() {
    Rampa tmp_rampa;
    if (rand() % 3) {
        tmp_rampa.velicina = 0.5;
        tmp_rampa.x = -1.25 + rand() / (float)RAND_MAX * 2.5;
    } else {
        tmp_rampa.velicina = 1.0;
        tmp_rampa.x = -1.0 + rand() / (float)RAND_MAX * 2.0;
    }
    tmp_rampa.z = 5 - korak_prepreke * MAX_PREPREKA;

    return tmp_rampa;
}

void inicijalizacija_prepreka() {
    int i;
    for(i = 0; i < MAX_PREPREKA; i++) {
        if (rand() % 3) {
            prepreke[i].tip = RUPA;
            prepreke[i].info.rupa = napravi_rupu();
            prepreke[i].info.rupa.z = -korak_prepreke * i - 10;
        } else {
            prepreke[i].tip = RAMPA;
            prepreke[i].info.rampa = napravi_rampu();
            prepreke[i].info.rampa.z = -korak_prepreke * i - 10;
        }
    }
}

void azuriraj_prepreke() {
    int i;
    for (i = 0; i < MAX_PREPREKA; i++) {
        if (prepreke[i].tip == RUPA) {
            if (prepreke[i].info.rupa.z > 5)
                prepreke[i].info.rupa = napravi_rupu();
            prepreke[i].info.rupa.z += brzina_prepreke;
        } else if (prepreke[i].tip == RAMPA) {
            if (prepreke[i].info.rampa.z > 5)
                prepreke[i].info.rampa = napravi_rampu();
            prepreke[i].info.rampa.z += brzina_prepreke;
        }
    }
}

void nacrtaj_rupu(Rupa r) {
    /*
    glPushMatrix();
    glColor3f(0.6, 0.4, 0.1);
    glTranslatef(r.x, 0, r.z);
    glRotatef(90, 0, 0, 1);
    draw_circle(0.5);
    glPopMatrix();
    */
    
    GLUquadricObj *quadric_object = gluNewQuadric();
    gluQuadricDrawStyle(quadric_object, GLU_FILL);
    gluQuadricTexture(quadric_object, GL_TRUE);

    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, names[RUPA_TEKSTURA]);

    glColor3f(0.6, 0.4, 0.1);
    glTranslatef(r.x, 0, r.z);
    glRotatef(90, 1, 0, 0);
    gluDisk(quadric_object, 0, 0.5, 25, 25);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

}

void nacrtaj_rampu(Rampa r) {
    if (r.velicina == 0.5) {
        glPushMatrix();
        glColor3f(0.1, 0.1, 0.1);
        glTranslatef(r.x-0.25, 0.15, r.z);
        glScalef(1, 3, 0.5);
        glutSolidCube(0.1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.1, 0.1, 0.1);
        glTranslatef(r.x+0.25, 0.15, r.z);
        glScalef(1, 3, 0.5);
        glutSolidCube(0.1);
        glPopMatrix();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, names[RAMPA_TEKSTURA]);
        glPushMatrix();
        glColor3f(0.5, 0.5, 0.1);
        glTranslatef(r.x, 0.4, r.z);
        glScalef(10, 2, 0.75);
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-0.05, -0.05, 0.05);
            glTexCoord2f(1, 0);
            glVertex3f(0.05, -0.05, 0.05);
            glTexCoord2f(1, 1);
            glVertex3f(0.05, 0.05, 0.05);
            glTexCoord2f(0, 1);
            glVertex3f(-0.05, 0.05, 0.05);
        glEnd();
        glutSolidCube(0.1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    } else {
        glPushMatrix();
        glColor3f(0.1, 0.1, 0.1);
        glTranslatef(r.x-0.5, 0.15, r.z);
        glScalef(2, 3, 0.5);
        glutSolidCube(0.1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.1, 0.1, 0.1);
        glTranslatef(r.x+0.5, 0.15, r.z);
        glScalef(2, 3, 0.5);
        glutSolidCube(0.1);
        glPopMatrix();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, names[RAMPA_TEKSTURA]);
        glPushMatrix();
        glColor3f(0.8, 0.2, 0.1);
        glTranslatef(r.x, 0.4, r.z);
        glScalef(20, 2, 0.75);
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-0.05, -0.05, 0.05);
            glTexCoord2f(1, 0);
            glVertex3f(0.05, -0.05, 0.05);
            glTexCoord2f(1, 1);
            glVertex3f(0.05, 0.05, 0.05);
            glTexCoord2f(0, 1);
            glVertex3f(-0.05, 0.05, 0.05);
        glEnd();
        glutSolidCube(0.1);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }
}

void nacrtaj_prepreke() {
    int i;
    for (i = 0; i < MAX_PREPREKA; i++) {
        if (prepreke[i].tip == RUPA) {
            nacrtaj_rupu(prepreke[i].info.rupa);
        } else if (prepreke[i].tip == RAMPA) {
            nacrtaj_rampu(prepreke[i].info.rampa);
        }
    }
}