#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class Esfera: public ObjRevolucion{
	public:
		Esfera(int num_instancias, int radio, bool tapa_sup, bool tapa_inf);
		void crearPerfil(int radio);

};

#endif
