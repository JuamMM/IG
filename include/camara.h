#ifndef CAMARA_H
#define CAMARA_H

#include "aux.h"

class Camara{
Tupla3f ojo;
Tupla3f at;
Tupla3f up;

int tipo;
float izquierda, derecha, cerca, lejos;

Camara();

void rotarXExaminar(float angulo);
void rotarYExaminar(float angulo);
void rotarZExaminar(float angulo);

void rotarXPrimeraPersona(float angulo);
void rotarYPrimeraPersona(float angulo);
void rotarZPrimeraPersona(float angulo);

void mover(float x, float y, float z);
void zoom(float factor);

void setObservadorr();
void setProteccion();
};

#endif
