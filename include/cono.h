#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class Cono: public ObjRevolucion{
	public:
		Cono(std::vector<Tupla3f>, bool tapa_inf, int num_instancias);

};

#endif
