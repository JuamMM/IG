#ifndef SAURON_H_INCLUDED
#define SAURON_H_INCLUDED

#include "aux.h"
#include "objply.h"
#include "cilindro.h"
#include "esfera.h"

class Sauron{
	private:
		Esfera * ojo = nullptr;
		Cilindro * base = nullptr;
		Cilindro * cuerpo = nullptr;
		ObjPLY * nubes = nullptr;
		ObjPLY * corona = nullptr;
	public:
		Sauron();
		void draw();


};

#endif
