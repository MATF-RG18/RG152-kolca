#ifndef _TEKSTURA_H_
#define _TEKSTURA_H_

#include "image.h"
#include <GL/glut.h>

#define PUT_FILE "teksture/put.bmp"
#define RUPA_FILE "teksture/sahta.bmp"
#define RAMPA_FILE "teksture/rampa.bmp"
#define TRAVA_FILE "teksture/trava.bmp"
#define NEBO_FILE "teksture/nebo.bmp"

#define PUT_TEKSTURA 0
#define RUPA_TEKSTURA 1
#define RAMPA_TEKSTURA 2
#define TRAVA_TEKSTURA 3
#define NEBO_TEKSTURA 4

GLuint names[5];
void inicijalizacija_teksture(void);

#endif