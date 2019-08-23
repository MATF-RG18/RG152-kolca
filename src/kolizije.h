#ifndef _KOLIZIJE_H_
#define _KOLIZIJE_H_

#include <math.h>
#include "prepreke.h"
#include "model_autica.h"

extern Prepreka prepreke[MAX_PREPREKA];
extern float tr_x;
extern int helti;

int sudar_u_toku;

void provera_sudara();

#endif