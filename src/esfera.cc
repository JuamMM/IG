#include "aux.h"
#include "malla.h"
#include "esfera.h"

Esfera::Esfera(int num_instancias, int radio, bool tapas){

	crearPerfil(radio);
	v = perfil;
	polo_sur = {0,perfil[0](1),0};
	int tam = perfil.size()-1;
	polo_norte = {0,perfil[tam](1),0};

	this->tapas = tapas;
	this->num_instancias = num_instancias;

	crearMalla('y');

	c_inmediato.resize(v.size());
	c_diferido.resize(v.size());

	for(auto it = c_inmediato.begin(); it != c_inmediato.end(); it++){
		(*it) =inmediato;
	}
}

void Esfera::crearPerfil(int radio){
	float x_antigua, y_antigua;
	float angulo = M_PI/40;
	Tupla3f vertice;
	float x = radio*sin(0), y = -radio*cos(0) ,z = 0;
	x_antigua = x;
	y_antigua = y;
	for(int i=1;i<40;i++){

		x = x_antigua * cos(angulo*i) - y_antigua * sin(angulo*i);
		y = x_antigua * sin(angulo*i) + y_antigua * cos(angulo*i);

		perfil.push_back({x,y,z});

	}

}
