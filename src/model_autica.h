#ifndef _MODEL_AUTICA_H_
#define _MODEL_AUTICA_H_

#include <GL/glut.h>
#include <math.h>

#define EPSILON 0.05
#define PI 3.1415926535897

void draw_circle(float r);
void set_normal_and_vertex_tire(float u, float v, float r);
void draw_tire(float r, float h);
void draw_car(void);
void nacrtaj_kolca(void);

#endif