// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "textura.h"
#include "material.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
	friend class sauron;
   public:

   // dibuja el objeto en modo inmediato

	void cambiaEstado(){
		dibujar = !dibujar;
	}

	void cambiaColor(Tupla3f color);

   // dibuja el objeto en modo diferido (usando VBOs)

	void cambiaMaterial(Material material);
	void draw_ModoAjedrez_Inmediato();
	void draw_ModoAjedrez_Diferido();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(char modo, bool dibujar_Ajedrez) ;
	void calculaNormales();

	void calcularTextura();
	void asignarTextura(std::string tex){
		textura = new Textura(tex);
	}

	GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);



   protected:
	virtual void draw_ModoDiferido();
	virtual void draw_ModoInmediato();


   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
	std::vector<Tupla3f> c_inmediato; // completar: tabla de colores, tabla de normales de vértices
	std::vector<Tupla3f> c_diferido;
	//Iluminación.
	std::vector<Tupla3f> nv;
	//Textura
	std::vector<Tupla2f> ct;
	Textura *textura = nullptr;

	Material m;

	Tupla3f inmediato = {1,0,1};
	Tupla3f diferido = {0,0,0};

	GLuint id_vbo_v = 0;
	GLuint id_vbo_f = 0;
	GLuint id_vbo_f_p = 0;
	GLuint id_vbo_c = 0;
	GLuint id_vbo_ci = 0;
	GLuint id_vbo_nv = 0;

	bool dibujar = false;


} ;


#endif
