#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class Cilindro: public ObjRevolucion{
	public:
		Cilindro(std::vector<Tupla3f>, bool tapa_inf, bool tapa_sup, int num_instancias);

};

#endif
