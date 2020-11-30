#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzPosicional : public Luz
{
	public:
		LuzPosicional(Tupla3f p, GLenum i, Tupla4f amb, Tupla4f diff, Tupla4f esp){
			posicion(0) = p(0);
			posicion(1) = p(1);
			posicion(2) = p(2);
			posicion(3) = 1;

			id = i;
			color_amb = amb;
			color_dif = diff;
			color_esp = esp;
		}

} ;

#endif
