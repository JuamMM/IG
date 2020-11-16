// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
//
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
	protected:
	Tupla3f polo_norte, polo_sur;
	bool tapas;
	std::vector<Tupla3f> perfil;
	std::vector<Tupla3i> f_sup;
	std::vector<Tupla3i> f_inf;
	int intervalo_tapa, indice_sup, num_instancias;
   public:
       ObjRevolucion();
   ObjRevolucion(const std::string & archivo, int num_instancias, bool tapas) ;
   ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapas) ;
    void crearMalla(char sentido);
	 void ocultaTapas();
	 void draw_ModoInmediato();

} ;




#endif
