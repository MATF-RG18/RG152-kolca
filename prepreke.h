#ifndef _PREPREKE_H_
#define _PREPREKE_H_

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "tekstura.h"

#define MAX_PREPREKA 15

typedef enum {RUPA, RAMPA} tipPrepreke;

typedef struct rupa {
    float x;
    float z;
} Rupa;

typedef struct rampa {
    float x;
    float z;
    float velicina;
} Rampa;

typedef struct prepreka {
    tipPrepreke tip;
    union {
        Rupa rupa;
        Rampa rampa;
    } info;
} Prepreka;

Prepreka prepreke[MAX_PREPREKA];

extern void draw_circle(float r);

void nacrtaj_krug(float r);

Rupa napravi_rupu();
void nacrtaj_rupu();

Rampa napravi_rampu();
void nacrtaj_rampu();

void inicijalizacija_prepreka();
void azuriraj_prepreke();
void nacrtaj_prepreke();

#endif