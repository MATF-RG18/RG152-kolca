#include "prepreke.h"

const float korak_prepreke = 5; /* razmak izmedju prepreka */
float brzina_prepreke = 0.075; /* brzina kretanja prepreka */
Prepreka prepreke[MAX_PREPREKA]; /* niz prepreka */

/* fja pravi rupu i inicijalizuje pocetne vrednosti */
Rupa napravi_rupu() {
    Rupa tmp_rupa;
    tmp_rupa.x = -1.0 + rand() / (float)RAND_MAX * 2.0;
    tmp_rupa.z = 5 - korak_prepreke * MAX_PREPREKA; 
    tmp_rupa.u = 0;

    return tmp_rupa;
}

/* pravi rampu i inicijalizuje pocetne vrednosti */
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
    tmp_rampa.udarena = 0;
    tmp_rampa.y = 0;

    return tmp_rampa;
}

/* inicijalizuje niz prepreka */
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

/* proverava da li je udareno u rupu i ako jeste smanjuje brzinu prepreke */
void udarena_rupa(void) {
    int i;
    for (i = 0; i < MAX_PREPREKA; i++) {
        if (prepreke[i].tip == RUPA) {
            if (prepreke[i].info.rupa.u) {
                brzina_prepreke = 0.055;
                return;
            }
            brzina_prepreke = 0.075;
        }
    }
}

/* azurira kretanje prepreka*/
void azuriraj_prepreke() {
    udarena_rupa();
    int i;
    for (i = 0; i < MAX_PREPREKA; i++) {
        if (prepreke[i].tip == RUPA) {
            if (prepreke[i].info.rupa.z > 5)
                prepreke[i].info.rupa = napravi_rupu();
            prepreke[i].info.rupa.z += brzina_prepreke;
        } else if (prepreke[i].tip == RAMPA) {
            if (prepreke[i].info.rampa.z > 5)
                prepreke[i].info.rampa = napravi_rampu();
            else if (prepreke[i].info.rampa.udarena) {
                if (prepreke[i].info.rampa.x <= 0) {
                    prepreke[i].info.rampa.x -= 0.05;
                } else {
                    prepreke[i].info.rampa.x += 0.05;
                }
                prepreke[i].info.rampa.y += 0.1;
            }
            prepreke[i].info.rampa.z += brzina_prepreke;
        }
    }
}

/* fja crta rupu */
void nacrtaj_rupu(Rupa r) {    
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

/* fja crta rampu */
void nacrtaj_rampu(Rampa r) {
    if (r.udarena) {
        nacrtaj_udarenu_rampu(r);
        return;
    }
    if (r.velicina == 0.5) { /* crtanje manje rampe */
        glPushMatrix();
        glColor3f(0.1, 0.1, 0.1);
        glTranslatef(r.x-0.25, r.y + 0.15, r.z);
        glScalef(1, 3, 0.5);
        glutSolidCube(0.1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.1, 0.1, 0.1);
        glTranslatef(r.x+0.25, r.y + 0.15, r.z);
        glScalef(1, 3, 0.5);
        glutSolidCube(0.1);
        glPopMatrix();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, names[RAMPA_TEKSTURA]);
        glPushMatrix();
        glColor3f(0.5, 0.5, 0.1);
        glTranslatef(r.x, r.y + 0.4, r.z);
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
    } else { /* crtanje vece rampe */
        glPushMatrix();
        glColor3f(0.1, 0.1, 0.1);
        glTranslatef(r.x-0.5, r.y + 0.15, r.z);
        glScalef(2, 3, 0.5);
        glutSolidCube(0.1);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.1, 0.1, 0.1);
        glTranslatef(r.x+0.5, r.y + 0.15, r.z);
        glScalef(2, 3, 0.5);
        glutSolidCube(0.1);
        glPopMatrix();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, names[RAMPA_TEKSTURA]);
        glPushMatrix();
        glColor3f(0.8, 0.2, 0.1);
        glTranslatef(r.x, r.y + 0.4, r.z);
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

/* fja crta rampu kada je udareno u nju, rotira i translira udarenu rampu */
void nacrtaj_udarenu_rampu(Rampa r) {
    glPushMatrix();
    if (r.x <= 0)
        glRotatef(r.y*10, 0, 0, 1);    
    else
        glRotatef(-r.y*10, 0, 0, 1);
    glTranslatef(0, r.y, 0);
    r.udarena = 0;
    nacrtaj_rampu(r);
    r.udarena = 1;
    glPopMatrix();
}

/* fja iscrtava sve prepreke */
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