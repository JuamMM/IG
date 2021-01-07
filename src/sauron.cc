#include "sauron.h"


Sauron::Sauron(){
	base = new Cilindro(70,20,true,30);
	cuerpo = new Cilindro(100,15,true,30);
	corona = new Corona();

	base->cambiaEstado();
	cuerpo->cambiaEstado();

}

void Sauron::draw(char modoDibujo,bool ajedrez){
	glPushMatrix();
		base->draw(modoDibujo,ajedrez);

		glPushMatrix();
			glTranslatef(0,grados_lib,0);
			cuerpo->draw(modoDibujo,ajedrez);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,100+grados_lib,0);
			corona->draw(modoDibujo,ajedrez);
		glPopMatrix();

	glPopMatrix();

}

void Sauron::animarModelo(){
	if(base_mueve)
		movimientoBase();

	if(corona_mueve)
		corona->movimientoCorona();

	if(ojo_mueve)
		corona->movimientoOjo();

}

void Sauron::movimientoBase(){

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
