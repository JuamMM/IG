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

void Sauron::draw(){
	base->draw('I',false);

	glPushMatrix();
	glTranslatef(0,50,0);
	cuerpo->draw('I',false);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,115,0);
	ojo->draw('I',false);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,95,0);
	glScalef(13,20,13);
	corona->draw('I',false);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30,80,30);
	glScalef(10,10,10);
	nubes->draw('I',false);
	glPopMatrix();
}
