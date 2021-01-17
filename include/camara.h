#ifndef CAMARA_H
#define CAMARA_H

#include "aux.h"

typedef enum{ORTOGONAL, PERSPECTIVA} tipo_cam;

class Camara{
private:
Tupla3f ojo;
Tupla3f en;
Tupla3f arriba;

tipo_cam tipo;
float izquierda, derecha, cerca, lejos, abajo, top;

public:
Camara(const Tupla3f eye,const Tupla3f at,const Tupla3f up, tipo_cam camara, const float near, const float far);

void rotarXExaminar(float angulo);
void rotarYExaminar(float angulo);
void rotarZExaminar(float angulo);

void rotarXPrimeraPersona(float angulo);
void rotarYPrimeraPersona(float angulo);
void rotarZPrimeraPersona(float angulo);

void mover(float x, float y, float z);
void zoom(float factor);

void setObservador();
void setProyeccion();

void setTop(const float top){
	this->top = top;
}

void setAbajo(const float abajo){
	this->abajo = abajo;
}

void setIzquierda(const float izquierda){
	this->izquierda = izquierda;
}

void setDerecha(const float derecha){
	this->derecha = derecha;
}

void girar(float x, float y);
};

#endif
