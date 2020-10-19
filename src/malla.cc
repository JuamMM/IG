#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  //
  glPointSize(10);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3,GL_FLOAT,0,v.data());
  glColorPointer(3,GL_FLOAT,0,c_inmediato.data());

  glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT,f.data());

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);


}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....
	if(id_vbo_v == 0){
		id_vbo_v = CrearVBO(GL_ARRAY_BUFFER,v.size()*3*sizeof(float),v.data());
	}

	if(id_vbo_f == 0){
		id_vbo_f = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,f.size()*3*sizeof(int), f.data());
	}

	if(id_vbo_c == 0){
		id_vbo_c = CrearVBO(GL_ARRAY_BUFFER,c_diferido.size()*3*sizeof(float),c_diferido.data());
	}

	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER,id_vbo_v);
	glVertexPointer(3,GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	glBindBuffer(GL_ARRAY_BUFFER,id_vbo_c);
	glColorPointer(3,GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbo_f);

	glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDisableClientState(GL_VERTEX_ARRAY);


}

void Malla3D::draw_ModoAjedrez(){
	std::vector<Tupla3i> f_par;
	std::vector<Tupla3i> f_impar;

	for(int i=0; i<f.size();i++){
		if(i%2 == 0){
			f_par.push_back(f[i]);
		}
		else{
			f_impar.push_back(f[i]);
		}
	}

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3,GL_FLOAT,0,v.data());

  glColorPointer(3,GL_FLOAT,0,c_inmediato.data());
  glDrawElements(GL_TRIANGLES,f_par.size()*3,GL_UNSIGNED_INT,f_par.data());

  glColorPointer(3,GL_FLOAT,0,c_diferido.data());
  glDrawElements(GL_TRIANGLES,f_impar.size()*3,GL_UNSIGNED_INT,f_impar.data());

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(char modo)
{
   // completar .....(práctica 1)
	if(dibujar && modo == 'D'){
		draw_ModoDiferido();
	}
	else if(dibujar && modo == 'I'){
		draw_ModoInmediato();
	}
	else if(dibujar && modo == 'A'){
		draw_ModoAjedrez();
	}


}

void Malla3D::cambiaColor(Tupla3f color){
	for(auto it = c_inmediato.begin(); it != c_inmediato.end(); it++){
		(*it) = color;
	}
}

GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram){
	GLuint id_vbo;
	glGenBuffers(1, & id_vbo);
	glBindBuffer(tipo_vbo, id_vbo);
	glBufferData(tipo_vbo,tamanio_bytes,puntero_ram, GL_STATIC_DRAW);
	glBindBuffer(tipo_vbo,0);
	return id_vbo;
}
