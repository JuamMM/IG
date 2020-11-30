#include "aux.h"
#include "luz.h"

void Luz::activar(){
	if(act){
		glLightfv(id, GL_AMBIENT, color_amb);
		glLightfv(id, GL_DIFFUSE, color_dif);
		glLightfv(id, GL_SPECULAR, color_esp);
		glLightfv(id, GL_POSITION, posicion);
	}
}

void Luz::encenderLuz(){
	act = !act;
	if(act){
		glEnable(id);
	}
	else{
		glDisable(id);
	}
}
