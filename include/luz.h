#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz{
	public:
		Tupla4f posicion;
		GLenum id;
		Tupla4f color_amb;
		Tupla4f color_dif;
		Tupla4f color_esp;
		bool act;

		Luz(){
			act = false;
		}
		void activar();
		void encenderLuz();

} ;

#endif
