#ifndef CORONA_H_INCLUDED
#define CORONA_H_INCLUDED

#include "aux.h"
#include "objply.h"
#include "esfera.h"
#include "material.h"

class Corona{
	private:
		Esfera * cornea = nullptr;
		Esfera * ojo = nullptr;
		ObjPLY * cuernos = nullptr;

		bool corona_mueve = true, ojo_mueve = true;
		int grados_cuerpo = 0.0f, grados_ojo = 0.0f;

	public:
		Corona();

		void draw(char modoDibujo, bool ajedrez);

		void cambia_M_CoronaC(Material material){
			cuernos->cambiaMaterial(material);
		}

		void cambia_M_CoronaO(Material material){
			ojo->cambiaMaterial(material);
		}

		void cambia_M_CoronaCo(Material material){
			cornea->cambiaMaterial(material);
		}

		void cambiaColor(Tupla3f nuevo_color){
			ojo->cambiaColor(nuevo_color);
			cornea->cambiaColor(nuevo_color);
			cuernos->cambiaColor(nuevo_color);
		}

		void movimientoCorona();
		void movimientoOjo();

};

#endif
