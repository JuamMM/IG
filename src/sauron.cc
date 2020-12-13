#include "sauron.h"


Sauron::Sauron(){
	base = new Cilindro(50,20,true,30);
	cuerpo = new Cilindro(45,15,true,30);
	ojo = new Esfera(40,10,true);
	corona = new ObjPLY("./plys/corona.ply");
	nubes = new ObjPLY("./plys/nubes.ply");

	base->cambiaEstado();
	cuerpo->cambiaEstado();
	ojo->cambiaEstado();
	corona->cambiaEstado();
	nubes->cambiaEstado();

}

void Sauron::draw(char modoDibujo,bool ajedrez){
	glPushMatrix();
		base->draw(modoDibujo,ajedrez);

		glPushMatrix();
		glTranslatef(0,50,0);
		cuerpo->draw(modoDibujo,ajedrez);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0,110+grados_lib,0);
		ojo->draw(modoDibujo,ajedrez);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0,95,0);
		glRotatef(grados_cuerpo,0,1.0,0);
		glScalef(13,20,13);
		corona->draw(modoDibujo,ajedrez);
		glPopMatrix();

		glPushMatrix();
		glRotatef(grados_nube,0,1.0,0);
		glTranslatef(50,80,50);
		glRotatef(-2.0*grados_nube,0,1.0,0);
		glScalef(10,10,10);
		nubes->draw(modoDibujo,ajedrez);
		glPopMatrix();

	glPopMatrix();

}

void Sauron::animarModelo(){
	if(ojo_mueve)
		movimientoOjo();

	if(corona_mueve)
		movimientoBase();

	if(nube_mueve)
		movimientoNube();
}

void Sauron::movimientoOjo(){

	if(grados_lib == 50){
		bajar = true;
	}

	if(grados_lib == 0){
		bajar = false;
	}

	if(bajar){
		grados_lib--;
	}
	else{
		grados_lib++;
	}
}


void Sauron::movimientoBase(){
	grados_cuerpo= (grados_cuerpo + 3)%360;

}

void Sauron::movimientoNube(){
	grados_nube = (grados_nube + 2) %360;

}
