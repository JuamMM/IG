#ifndef CAMARA_H
#define CAMARA_H

#include "aux.h"

typedef enum{ORTOGONAL, PERSPECTIVA} tipo_cam;
typedef enum{CUBO, CILINDRO, SAURON, PEON, TETRAEDRO, ESFERA, LATA, NINGUNO} objeto;

class Camara{
private:
Tupla3f ojo;
Tupla3f en;
Tupla3f arriba;

tipo_cam tipo;
float izquierda, derecha, cerca, lejos, abajo, top;

objeto mirar = NINGUNO;

public:
Camara(const Tupla3f eye,const Tupla3f at,const Tupla3f up, tipo_cam camara, const float near, const float far);

void rotarXExaminar(float angulo);
void rotarYExaminar(float angulo);
void rotarZExaminar(float angulo);

void rotarXPrimeraPersona(float angulo);
void rotarYPrimeraPersona(float angulo);
void rotarZPrimeraPersona(float angulo);

void mover(float x, float y, float z);
void zoom(float factor){
	izquierda = izquierda*factor;
	derecha = derecha*factor;
	cerca = cerca*factor;
	lejos = lejos*factor;
}

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

float getTop(){
	return top;
}

float getAbajo(){
	return abajo;
}

// Cambiamos la tupla at para que la cámara apunte a unas nuevas coordenadas
void setEn(const Tupla3f enfoque){
	en = enfoque;
}

//Asignamos a que objeto se encuentra mirando la cámara
void asignaObjeto(const objeto tipo){
	mirar = tipo;
}

void girar(float x, float y);
void girarObjeto(float x, float y);

void asignarObjeto(objeto asig);

objeto MirandoA(){
	return mirar;
}

};

#endif
