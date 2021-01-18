#include "camara.h"
#include <cmath>

Camara::Camara(const Tupla3f eye, const Tupla3f at, const Tupla3f up, tipo_cam camara, const float near, const float far){
	ojo = eye;
	en = at;
	arriba = up;

	tipo = camara;

	cerca = near;
	lejos = far;
}

void Camara::rotarXExaminar(float angulo){
	ojo = ojo-en;
	Tupla3f ojo_aux = ojo;

	ojo(1) = ojo_aux(1)*cos(angulo) + ojo_aux(2)*sin(angulo);
	ojo(2) = ojo_aux(1)*sin(angulo) + ojo_aux(2)*cos(angulo);

	ojo = ojo+en;

}

void Camara::rotarYExaminar(float angulo){
	ojo = ojo-en;
	Tupla3f ojo_aux = ojo;

	ojo(0) = ojo_aux(0)*cos(angulo) - ojo_aux(2)*sin(angulo);
	ojo(2) = ojo_aux(0)*-1*sin(angulo) + ojo_aux(2)*cos(angulo);

	ojo = ojo+en;

}

void Camara::rotarZExaminar(float angulo){
	ojo = ojo-en;
	Tupla3f ojo_aux = ojo;

	ojo(0) = ojo_aux(0)*cos(angulo) + ojo_aux(1)*sin(angulo);
	ojo(1) = ojo_aux(0)*sin(angulo) + ojo_aux(1)*cos(angulo);

	ojo = ojo+en;

}

void Camara::rotarXPrimeraPersona(float angulo){
	en = en-ojo;
	Tupla3f en_aux = en;

	en(1) = en_aux(1)*cos(angulo) - en(2)*sin(angulo);
	en(2) = en_aux(1)*sin(angulo) + en_aux(2)*cos(angulo);

	en = en+ojo;

}

void Camara::rotarYPrimeraPersona(float angulo){
	en = en-ojo;
	Tupla3f en_aux = en;

	en(0) = en_aux(0)*cos(angulo) - en(2)*sin(angulo);
	en(2) = en_aux(0)*-1*sin(angulo) + en_aux(2)*cos(angulo);

	en = en+ojo;

}

void Camara::rotarZPrimeraPersona(float angulo){
	en = en-ojo;
	Tupla3f en_aux = en;

	en(0) = en_aux(0)*cos(angulo) - en(1)*sin(angulo);
	en(1) = en_aux(0)*sin(angulo) + en(1)*cos(angulo);

	en = en+ojo;
}

/*Creación de la matriz de visualización de la cámara
 * empleando los vectores ojo, en y arriba
 */
void Camara::setObservador(){

	gluLookAt(
			ojo(0), ojo(1), ojo(2),
			en(0), en(1), en(2),
			arriba(0), arriba(1), arriba(2)
			);
}

/*	Método empleado para alterar la matriz de visualización de la cámara
 *	en función de los parámetros de la variable tipo.
 */
void Camara::setProyeccion(){
	if(tipo == PERSPECTIVA){
		glFrustum(izquierda, derecha,
				abajo, top,
				cerca, lejos);
	}
	else if(tipo == ORTOGONAL){
		glOrtho(izquierda, derecha,
				abajo, top,
				cerca, lejos);
	}
}

void Camara::girar(float x, float y){
	if(mirar == NINGUNO){
		rotarXPrimeraPersona(-y*0.25*M_PI/180.0);
		rotarYPrimeraPersona(-x*0.25*M_PI/180.0);
	}
	else{
		rotarXExaminar(-y*0.25*M_PI/180.0);
		rotarYExaminar(-x*0.25*M_PI/180.0);
	}


}

void Camara::girarObjeto(float x, float y){
	rotarXExaminar(-y*0.25*M_PI/180.0);
	rotarYExaminar(-x*0.25*M_PI/180.0);
}
