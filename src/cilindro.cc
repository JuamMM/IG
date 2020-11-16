#include "aux.h"
#include "malla.h"
#include "cilindro.h"

Cilindro::Cilindro(std::vector<Tupla3f> archivo, bool tapas, int num_instancias){

	perfil = archivo;
	v = perfil;
	polo_sur = {0,perfil[0](1),0};
	int tam = perfil.size()-1;
	polo_norte = {0,perfil[tam](1),0};
	this->num_instancias = num_instancias;

	this->tapas = tapas;

	crearMalla('y');

	c_inmediato.resize(v.size());
	c_diferido.resize(v.size());

	for(auto it = c_inmediato.begin(); it != c_inmediato.end(); it++){
		(*it) =inmediato;
	}
}
