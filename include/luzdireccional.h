#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzDireccional : public Luz
{
	protected:
		float alpha;
		float beta;
		Tupla3f posicion_original;

	public:

		LuzDireccional(Tupla3f direccion, GLenum id, Tupla4f amb, Tupla4f diff, Tupla4f esp);

		void variarAnguloAlpha(float incremento);
		void variarAnguloBeta(float incremento);

} ;

#endif
