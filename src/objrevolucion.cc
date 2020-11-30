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

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapas) {
	ply::read_vertices(archivo, this->perfil);


	this->v = this->perfil;
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

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)


ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapas) {

	this->perfil = archivo;
	this->v = this->perfil;
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

	calculaNormales();
}

void ObjRevolucion::crearMalla(char sentido) {
	float x,z,y;
	Tupla3f nuevo_v;
	for(int i =0; i<num_instancias; i++){
		for(auto it = perfil.begin(); it != perfil.end(); it++){
			float angulo = (2*M_PI*i)/(num_instancias);

			switch(sentido){
				case 'x':
					x = (*it)(0);
					y = (*it)(1) * cos(angulo) - (*it)(2) * sin(angulo);
					z = (*it)(1) * sin(angulo) + (*it)(2) *  cos(angulo);
					break;
				case 'y':
					x = (*it)(0) * cos(angulo) + (*it)(2) * sin(angulo);
					y = (*it)(1);
					z = (*it)(0) * -sin(angulo) + (*it)(2) * cos(angulo);
					break;
				case 'z':
					x = (*it)(0) * cos(angulo) - (*it)(1) * sin(angulo);
					y = (*it)(0) * sin(angulo) + (*it)(1) * cos(angulo);
					z = (*it)(2);
					break;
			}

			nuevo_v = {x,y,z};
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
	if(tapas){
		v.push_back(polo_norte);
		v1 = v.size()-1;
		indice_sup = f.size();

		for(int i=0; i<num_instancias;i++){
			int y = perfil.size()*i + perfil.size()-1;
			int z = y +perfil.size();

			f.push_back({v1,y,z});
		}

		v2 = perfil.size()-1;
		v3 = (perfil.size()*(num_instancias+1))-1;
		f.push_back({v2,v1,v3});

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
	intervalo_tapa = f.size() - (indice_sup+1);

	calculaNormales();
}

void ObjRevolucion::ocultaTapas(){
	tapas = !tapas;

}

void ObjRevolucion::draw_ModoInmediato()
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  //
  glPointSize(10);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3,GL_FLOAT,0,v.data());
  glColorPointer(3,GL_FLOAT,0,c_inmediato.data());

  if(glIsEnabled(GL_LIGHTING)){
	  glEnableClientState(GL_NORMAL_ARRAY);
	  glNormalPointer(GL_FLOAT,0,nv.data());

	  m.aplicar();
  }

  if(tapas){
	glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT,f.data());
  }
  else{
	glDrawElements(GL_TRIANGLES,(f.size()*3)-(intervalo_tapa*3),GL_UNSIGNED_INT,f.data());
  }

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  if (glIsEnabled(GL_LIGHTING)){
		  glDisableClientState(GL_NORMAL_ARRAY);

	}


}
