#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cono.h"
#include "cilindro.h"
#include "esfera.h"
#include "luzposicional.h"
#include "luzdireccional.h"
#include "sauron.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO} menu;
class Escena
{

   private:



 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)

       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();

	void Colores(Tupla3f nuevo_color);
	void enciendeLuces();



   void clear_window();

   menu modoMenu=NADA;
   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
	ObjPLY * modelo = nullptr;
	ObjRevolucion * peon = nullptr;
	ObjRevolucion * peon2 = nullptr;
	Cono * cono = nullptr;
	Cilindro * cilindro = nullptr;
	Esfera * esfera = nullptr;
	LuzPosicional * luz0 = nullptr;
	LuzDireccional * luz1 = nullptr;

	Sauron * sauron = nullptr;

	char modoDibujo = 'I';
	bool comoPuntos = false;
	bool comoLineas = false;
	bool comoTriangulos = true;
	bool ajedrez = false;
	bool luces=false;

	bool alpha_pulsada = false;
	bool beta_pulsada = false;

   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;
	void dibujaObjetos();

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
