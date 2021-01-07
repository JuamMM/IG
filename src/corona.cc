#include "corona.h"

Corona::Corona(){
	ojo = new Esfera(40,10,true);
	cuernos = new ObjPLY("./plys/corona.ply");
	cornea = new Esfera(40,5,true);

	ojo->cambiaEstado();
	cornea->cambiaEstado();
	cuernos->cambiaEstado();
}

void Corona::draw(char modoDibujo, bool ajedrez){
	glPushMatrix();

		glPushMatrix();
			glTranslatef(0,20,0);
			ojo->draw(modoDibujo,ajedrez);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,20,0);
			glRotatef(-grados_ojo,1.0,0,0);
			glTranslatef(0,0,7);
			cornea->draw(modoDibujo,ajedrez);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,0,0);
			glRotatef(grados_cuerpo,0,1.0,0);
			glScalef(13,20,13);
			cuernos->draw(modoDibujo,ajedrez);
		glPopMatrix();

	glPopMatrix();

}

void Corona::movimientoCorona(){
	grados_cuerpo = (grados_cuerpo + 2) %360;

}

void Corona::movimientoOjo(){
	grados_ojo = (grados_ojo + 2) %360;
}
