#include "aux.h"
#include "malla.h"
#include "esfera.h"

Esfera::Esfera(int num_instancias, int radio, bool tapa_sup, bool tapa_inf){

	crearPerfil(radio);
	v = perfil;
	polo_sur = {0,perfil[0](1),0};
	int tam = perfil.size()-1;
	polo_norte = {0,perfil[tam](1),0};

	this->tapa_inf = tapa_inf;
	this->tapa_sup = tapa_sup;

	crearMalla(num_instancias,'y');

	c_inmediato.resize(v.size());
	c_diferido.resize(v.size());

	for(auto it = c_inmediato.begin(); it != c_inmediato.end(); it++){
		(*it) =inmediato;
	}
}

void Esfera::crearPerfil(int radio){
	float x = 6, y = radio*-1 ,z = 0;
	float x_antigua, y_antigua;
	Tupla3f vertice;
	x_antigua = x;
	y_antigua = y;
	float angulo = 2.81/50;
	for(int i=0;i<50;i++){

		x = x_antigua * cos(angulo*i) - y_antigua * sin(angulo*i);
		y = x_antigua * sin(angulo*i) + y_antigua * cos(angulo*i);

		perfil.push_back({x,y,z});

	}

}
