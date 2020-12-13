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

  if(glIsEnabled(GL_LIGHTING)){
	  glEnableClientState(GL_NORMAL_ARRAY);
	  glNormalPointer(GL_FLOAT,0,nv.data());

	  m.aplicar();
  }

  glColorPointer(3,GL_FLOAT,0,c_inmediato.data());

  glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT,f.data());

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  if (glIsEnabled(GL_LIGHTING)){
		  glDisableClientState(GL_NORMAL_ARRAY);

	}

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

	if(id_vbo_nv == 0){
		id_vbo_nv = CrearVBO(GL_ARRAY_BUFFER,nv.size()*3*sizeof(float),nv.data());
	}

	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER,id_vbo_v);
	glVertexPointer(3,GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,0);

  if(glIsEnabled(GL_LIGHTING)){
	  glEnableClientState(GL_NORMAL_ARRAY);
	  glBindBuffer(GL_ARRAY_BUFFER,id_vbo_nv);
	  glNormalPointer(GL_FLOAT, 0, 0);
	  glBindBuffer(GL_ARRAY_BUFFER, 0);

	  m.aplicar();
  }

	glBindBuffer(GL_ARRAY_BUFFER,id_vbo_c);
	glColorPointer(3,GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbo_f);

	glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDisableClientState(GL_VERTEX_ARRAY);

  if (glIsEnabled(GL_LIGHTING)){
		  glDisableClientState(GL_NORMAL_ARRAY);
	}

}

void Malla3D::draw_ModoAjedrez_Inmediato(){
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

void Malla3D::draw_ModoAjedrez_Diferido()
{
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

	if(id_vbo_v == 0){
		id_vbo_v = CrearVBO(GL_ARRAY_BUFFER,v.size()*3*sizeof(float),v.data());
	}

	if(id_vbo_f == 0){
		id_vbo_f = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,f_impar.size()*3*sizeof(int), f_impar.data());
	}

	if(id_vbo_f_p == 0){
		id_vbo_f_p = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,f_par.size()*3*sizeof(int), f_par.data());
	}

	if(id_vbo_c == 0){
		id_vbo_c = CrearVBO(GL_ARRAY_BUFFER,c_diferido.size()*3*sizeof(float),c_diferido.data());
	}

	if(id_vbo_ci == 0){
		id_vbo_ci = CrearVBO(GL_ARRAY_BUFFER,c_inmediato.size()*3*sizeof(float),c_inmediato.data());
	}

	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER,id_vbo_v);
	glVertexPointer(3,GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	glBindBuffer(GL_ARRAY_BUFFER,id_vbo_c);
	glColorPointer(3,GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbo_f_p);

	glDrawElements(GL_TRIANGLES,f_par.size()*3,GL_UNSIGNED_INT,0);

	glBindBuffer(GL_ARRAY_BUFFER,id_vbo_ci);
	glColorPointer(3,GL_FLOAT,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbo_f);

	glDrawElements(GL_TRIANGLES,f_impar.size()*3,GL_UNSIGNED_INT,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glDisableClientState(GL_VERTEX_ARRAY);


}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(char modo, bool dibujar_Ajedrez)
{
	glShadeModel(GL_SMOOTH);
   // completar .....(práctica 1)
	if(dibujar && dibujar_Ajedrez){
		if(modo == 'I'){
			draw_ModoAjedrez_Inmediato();
		}
		else{
			draw_ModoAjedrez_Diferido();
		}
	}
	else if(dibujar && modo == 'D'){
		draw_ModoDiferido();
	}
	else if(dibujar && modo == 'I'){
		draw_ModoInmediato();
	}


}

void Malla3D::cambiaColor(Tupla3f color){
	for(auto it = c_inmediato.begin(); it != c_inmediato.end(); it++){
		(*it) = color;
	}
}

void Malla3D::calculaNormales(){
	Tupla3f normal, m;

	nv.resize(v.size());

	for(int i=0; i< nv.size(); i++){
		nv[i] = {0,0,0};
	}

	for(auto it = f.begin(); it != f.end();++it){

		Tupla3f a = v[(*it)(1)]-v[(*it)(0)];
		Tupla3f b = v[(*it)(2)]-v[(*it)(0)];

		m = a.cross(b);

		if(m.lengthSq() !=0){
		normal = m;

		nv[(*it)(0)] = nv[(*it)(0)] + normal;
		nv[(*it)(1)] = nv[(*it)(1)] + normal;
		nv[(*it)(2)] = nv[(*it)(2)] + normal;
		}

	}

	for(int i=0; i<nv.size(); i++){
		if(nv[i].lengthSq() != 0){
			nv[i] = nv[i].normalized();
		}
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

void Malla3D::cambiaMaterial(Material material){
	m = material;
}
