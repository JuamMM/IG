#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"



// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
	ply::read_vertices(archivo, this->perfil);


	this->v = this->perfil;
	polo_sur = {0,perfil[0](1),0};
	int tam = perfil.size()-1;
	polo_norte = {0,perfil[tam](1),0};


	this->tapa_inf = tapa_inf;
	this->tapa_sup = tapa_sup;
	crearMalla(num_instancias);

	c_inmediato.resize(v.size());
	c_diferido.resize(v.size());

	for(auto it = c_inmediato.begin(); it != c_inmediato.end(); it++){
		(*it) =inmediato;
	}


}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)


ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {

	this->perfil = archivo;
	this->v = this->perfil;
	polo_sur = {0,perfil[0](1),0};
	int tam = perfil.size()-1;
	polo_norte = {0,perfil[tam](1),0};

	this->tapa_inf = tapa_inf;
	this->tapa_sup = tapa_sup;
	crearMalla(num_instancias);

	c_inmediato.resize(v.size());
	c_diferido.resize(v.size());

	for(auto it = c_inmediato.begin(); it != c_inmediato.end(); it++){
		(*it) =inmediato;
	}
}

void ObjRevolucion::crearMalla(int num_instancias) {
	float x,z;
	Tupla3f nuevo_v;
	for(int i =0; i<num_instancias; i++){
		for(auto it = perfil.begin(); it != perfil.end(); it++){
			float angulo = (2*M_PI*i)/(num_instancias);

			x = (*it)(0) * cos(angulo) + (*it)(2) * sin(angulo);
			z = (*it)(0) * -sin(angulo) + (*it)(2) * cos(angulo);

			nuevo_v = {x,(*it)(1),z};
			v.push_back(nuevo_v);
		}
	}



	for(int i=0; i<num_instancias+1; i++){
		for(int j = 0 ; j<perfil.size()-1; j++){
			int x = perfil.size()*i + j;
			int y = perfil.size()*((i+1)%(num_instancias+1)) + j;
			int z = y+1;

			f.push_back({x,y,z});

			y = y+1;
			z = x+1;

			f.push_back({x,y,z});
		}
	}

	int v1,v2,v3;
	if(tapa_sup){
		v.push_back(polo_norte);
		v1 = v.size()-1;

		for(int i=0; i<num_instancias;i++){
			int y = perfil.size()*i + perfil.size()-1;
			int z = y +perfil.size();

			f.push_back({v1,y,z});
		}

		v2 = perfil.size()-1;
		v3 = (perfil.size()*(num_instancias+1))-1;
		f.push_back({v2,v1,v3});
	}

	if(tapa_inf){
		v.push_back(polo_sur);
		v1 = v.size()-1;

		for(int i=0; i<num_instancias;i++){
			int y = perfil.size()*i;
			int z = perfil.size()*(i+1);

			f.push_back({y,v1,z});
		}

		v2 = perfil.size()*num_instancias;
		v3 = perfil.size();
		f.push_back({v2,v1,v3});

	}
}
