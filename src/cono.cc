#include "aux.h"
#include "malla.h"
#include "cono.h"

Cono::Cono(std::vector<Tupla3f> archivo, bool tapa_inf, int num_instancias){

	perfil = archivo;
	v = perfil;
	polo_sur = {0,perfil[0](1),0};
	int tam = perfil.size()-1;
	polo_norte = {0,perfil[tam](1),0};
	this->num_instancias = num_instancias;

	this->tapas = tapa_inf;
	crearMalla('y');

	c_inmediato.resize(v.size());
	c_diferido.resize(v.size());

	for(auto it = c_inmediato.begin(); it != c_inmediato.end(); it++){
		(*it) =inmediato;
	}

	for(auto it = c_diferido.begin(); it != c_diferido.end(); it++){
		(*it) =diferido;
	}
	calculaNormales();
}
