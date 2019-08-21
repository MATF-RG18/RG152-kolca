#include "model_autica.h"
#include "svetlo.h"

extern float tr_x;

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
    glVertex3f(0, 0, 0);
    for (v = 0; v <= 2*PI+EPSILON; v += PI/1000) {
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
        glColor3f(0.1, 0.1, 0.1);
        draw_circle(r);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-h/2, 0, 0);
        glColor3f(0.1, 0.1, 0.1);
        draw_circle(r);
    glPopMatrix();
}

/* crtanje kolca */
void draw_car(void)
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 0.3, 0.3, 0.9, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.2, 0.2, 0.6, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 0.1, 0.1, 0.3, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 20;
    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    /*hauba*/
    glPushMatrix();
        glColor3f(0.1, 0.1, 0.3);
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
        glColor3f(0.1, 0.1, 0.3);
        glScalef(0.75, 0.5, 0.8);
        glutSolidCube(1);
    glPopMatrix();
    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_CLIP_PLANE1);
    
    /*gepek*/
    glPushMatrix();
        glColor3f(0.1, 0.1, 0.3);
        glTranslatef(0, -0.125, 0.55);
        glScalef(0.75, 0.25, 0.3);
        glutSolidCube(1);
    glPopMatrix();
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

    /* svetla */
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.2, 0.2);
        glVertex3f(-0.35, -0.05, 0.75);
        glVertex3f(-0.2, -0.05, 0.75);
        glVertex3f(-0.2, 0.0, 0.75);
        glVertex3f(-0.35, 0.0, 0.75);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.2, 0.2);
        glVertex3f(0.35, -0.05, 0.75);
        glVertex3f(0.2, -0.05, 0.75);
        glVertex3f(0.2, 0.0, 0.75);
        glVertex3f(0.35, 0.0, 0.75);
    glEnd();
    
    /* tablice */
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.8, 0.8);
        glVertex3f(-0.15, -0.1, 0.75);
        glVertex3f(0.15, -0.1, 0.75);
        glVertex3f(0.15, -0.05, 0.75);
        glVertex3f(-0.15, -0.05, 0.75);
    glEnd();

    /* prozori */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);

    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs2[] = { 0.7, 0.7, 0.9, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs2[] = { 0.5, 0.5, 0.6, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs2[] = { 0.2, 0.2, 0.3, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess2 = 20;

    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs2);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess2);

    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.8, 0.8);
        glVertex3f(-0.35, 0.05, 0.4);
        glVertex3f(0.35, 0.05, 0.4);
        glVertex3f(0.35, 0.25, 0.25);
        glVertex3f(-0.35, 0.25, 0.25);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.8, 0.8);
        glVertex3f(-0.376, 0.05, -0.2);
        glVertex3f(-0.376, 0.05, +0.35);
        glVertex3f(-0.376, 0.25, +0.2);
        glVertex3f(-0.376, 0.25, -0.1);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.8, 0.8);
        glVertex3f(0.376, 0.05, -0.2);
        glVertex3f(0.376, 0.05, +0.35);
        glVertex3f(0.376, 0.25, +0.2);
        glVertex3f(0.376, 0.25, -0.1);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.8, 0.8);
        glVertex3f(-0.35, 0.05, 0.4);
        glVertex3f(0.35, 0.05, 0.4);
        glVertex3f(0.35, 0.25, 0.25);
        glVertex3f(-0.35, 0.25, 0.25);
    glEnd();

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT1);

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

void nacrtaj_kolca(void) {
    glPushMatrix();
        glTranslatef(tr_x, 0.375, 4);
        draw_car();
    glPopMatrix();
}