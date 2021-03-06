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
#include "camara.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,SELANIMACION, CAMARA} menu;
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
	void change_projection(/*const float ratio_xyi*/);
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
	ObjRevolucion * lata = nullptr;
	ObjRevolucion * p_inf = nullptr;
	ObjRevolucion * p_sup = nullptr;
	ObjRevolucion * peon = nullptr;
	ObjRevolucion * peon2 = nullptr;
	Cono * cono = nullptr;
	Cilindro * cilindro = nullptr;
	Esfera * esfera = nullptr;
	LuzPosicional * luz0 = nullptr;
	LuzDireccional * luz1 = nullptr;

	int camara_activa = 0;
	Sauron * sauron = nullptr;


	char modoDibujo = 'I';
	bool comoPuntos = false;
	bool comoLineas = false;
	bool comoTriangulos = true;
	bool ajedrez = false;
	bool luces=false;
	bool texturas=false;


	bool alpha_pulsada = false;
	bool beta_pulsada = false;

	std::vector<Camara> camaras;
	std::vector<Malla3D*> objetos_dibujo;

	bool raton_pulsado=false;
	int x_mov=0;
	int y_mov=0;

	void pintaSeleccion();

   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;
	void animarModeloJearquico();

	// Dibujar
	void dibujar() ;
	void dibujaObjetos();

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

	void clickRaton(int boton, int estado, int x, int y);
	void ratonMovido(int x, int y);

	void dibujaSeleccion();
	void Seleccion(int x, int y);

};
#endif
