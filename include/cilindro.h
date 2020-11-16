#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class Cilindro: public ObjRevolucion{
	public:
		Cilindro(std::vector<Tupla3f>, bool tapas, int num_instancias);

};

#endif
