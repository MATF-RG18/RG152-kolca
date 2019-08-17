#include "prepreke.h"

const float korak_prepreke = 5;
const float brzina_prepreke = 0.05;
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
            prepreke[i].info.rupa.z = -korak_prepreke * i;
        } else {
            prepreke[i].tip = RAMPA;
            prepreke[i].info.rampa = napravi_rampu();
            prepreke[i].info.rampa.z = -korak_prepreke * i;
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
    glPushMatrix();
    glColor3f(0.6, 0.4, 0.1);
    glTranslatef(r.x, 0, r.z);
    glRotatef(90, 0, 0, 1);
    draw_circle(0.5);
    glPopMatrix();
}

void nacrtaj_rampu(Rampa r) {
    if (r.velicina == 0.5) {
        glPushMatrix();
        glColor3f(0.2, 0.2, 0.1);
        glTranslatef(r.x-0.25, 0.15, r.z);
        glScalef(1, 3, 0.5);
        glutSolidCube(0.1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.2, 0.2, 0.1);
        glTranslatef(r.x+0.25, 0.15, r.z);
        glScalef(1, 3, 0.5);
        glutSolidCube(0.1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.8, 0.2, 0.1);
        glTranslatef(r.x, 0.4, r.z);
        glScalef(10, 2, 0.75);
        glutSolidCube(0.1);
        glPopMatrix();
    } else {
        glPushMatrix();
        glColor3f(0.2, 0.2, 0.1);
        glTranslatef(r.x-0.5, 0.15, r.z);
        glScalef(2, 3, 0.5);
        glutSolidCube(0.1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.2, 0.2, 0.1);
        glTranslatef(r.x+0.5, 0.15, r.z);
        glScalef(2, 3, 0.5);
        glutSolidCube(0.1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.8, 0.2, 0.1);
        glTranslatef(r.x, 0.4, r.z);
        glScalef(20, 2, 0.75);
        glutSolidCube(0.1);
        glPopMatrix();
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