#ifndef SAURON_H_INCLUDED
#define SAURON_H_INCLUDED

#include "aux.h"
#include "objply.h"
#include "cilindro.h"
#include "esfera.h"
#include "material.h"

class Sauron{
	private:
		Esfera * ojo = nullptr;
		Cilindro * base = nullptr;
		Cilindro * cuerpo = nullptr;
		ObjPLY * nubes = nullptr;
		ObjPLY * corona = nullptr;
		int grados_lib = 0, grados_cuerpo=0, grados_nube = 1;
		float nube_x = 50, nube_z = 50, rot_nube = 0;
		bool bajar=false;
	public:
		Sauron();
		void draw(char modoDibujo, bool ajedrez);
		void cambia_M_Base(Material material){
			base->cambiaMaterial(material);
		}
		void cambia_M_Cuerpo(Material material){
			cuerpo->cambiaMaterial(material);
		}
		void cambia_M_Corona(Material material){
			corona->cambiaMaterial(material);
		}
		void cambia_M_Ojo(Material material){
			ojo->cambiaMaterial(material);
		}
		void cambia_M_Nube(Material material){
			nubes->cambiaMaterial(material);
		}

		void cambiaColor(Tupla3f nuevo_color){
			ojo->cambiaColor(nuevo_color);
			nubes->cambiaColor(nuevo_color);
			corona->cambiaColor(nuevo_color);
			base->cambiaColor(nuevo_color);
			cuerpo->cambiaColor(nuevo_color);
		}


		void animarModelo();

		void movimientoOjo();

		void movimientoBase();

		void movimientoNube();

};

#endif
