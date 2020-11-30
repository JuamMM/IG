#include "aux.h"
#include "luzdireccional.h"

LuzDireccional::LuzDireccional(Tupla3f direccion, GLenum i, Tupla4f amb, Tupla4f diff, Tupla4f esp){
	id = i;
	color_amb = amb;
	color_dif = diff;
	color_esp = esp;

	alpha = atan((sqrt(pow(direccion(0),2) + pow(direccion(1),2))) / direccion(2));
   beta = atan(direccion(1)/direccion(0));
   posicion = {direccion(0),direccion(1),direccion(2),0.0};
	posicion_original = posicion;

}

void LuzDireccional::variarAnguloAlpha(float incremento){
	alpha = fmod((alpha + incremento*M_PI/180.0),2*M_PI);
	if(alpha <0.0){
		alpha = 2*M_PI;
	}
	float x,y,z;

	x = sin(alpha)*cos(beta)*sqrt(posicion_original.lengthSq());
   y = sin(alpha)*sin(beta)*sqrt(posicion_original.lengthSq());
   z = cos(alpha)*sqrt(posicion_original.lengthSq());
   posicion = {x,y,z,0.0};

}

void LuzDireccional::variarAnguloBeta(float incremento){
	beta = beta + incremento*M_PI/180.0;
	if(beta > M_PI/2){
		alpha = -M_PI/2;
	}else if(beta < -M_PI/2){
		beta = M_PI/2;
	}
	float x,y,z;

	x = sin(alpha)*cos(beta)*sqrt(posicion_original.lengthSq());
   y = sin(alpha)*sin(beta)*sqrt(posicion_original.lengthSq());
   z = cos(alpha)*sqrt(posicion_original.lengthSq());
   posicion = {x,y,z,0.0};

}
