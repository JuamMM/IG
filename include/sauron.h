#ifndef SAURON_H_INCLUDED
#define SAURON_H_INCLUDED

#include "aux.h"
#include "objply.h"
#include "cilindro.h"
#include "esfera.h"
#include "material.h"
#include "corona.h"

class Sauron{
	private:
		Esfera * cornea = nullptr;
		Esfera * ojo = nullptr;
		Cilindro * base = nullptr;
		Cilindro * cuerpo = nullptr;
		Corona * corona = nullptr;
		int grados_lib = 0;
		bool bajar=false;

		bool base_mueve = true, ojo_mueve = true, corona_mueve = true;

	public:
		Sauron();
		void draw(char modoDibujo, bool ajedrez);

		void cambia_M_Ojo(Material material){
			corona->cambia_M_CoronaO(material);
		}

		void cambia_M_Cornea(Material material){
			corona->cambia_M_CoronaCo(material);
		}

		void cambia_M_Corona(Material material){
			corona->cambia_M_CoronaC(material);
		}

		void cambia_M_Base(Material material){
			base->cambiaMaterial(material);
		}

		void cambia_M_Cuerpo(Material material){
			cuerpo->cambiaMaterial(material);
		}

		void cambiaColor(Tupla3f nuevo_color){
			corona->cambiaColor(nuevo_color);
			base->cambiaColor(nuevo_color);
			cuerpo->cambiaColor(nuevo_color);
		}


		void animarModelo();

		void movimientoBase();


		void AnimacionOjo(){
			ojo_mueve = !ojo_mueve;
		}

		void AnimacionBase(){
			base_mueve = !base_mueve;
		}

		void AnimacionCorona(){
			corona_mueve = !corona_mueve;
		}

};

#endif
