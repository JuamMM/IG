

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena....
    // .......completar: ...
    // .....
	 tetraedro = new Tetraedro(100);
	 cubo= new Cubo(50);

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
	glEnable(GL_CULL_FACE);

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );

	std::cout<<"Pulsa H para recibir a ayuda"<<std::endl;
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
    ejes.draw();
    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer
	 if(comoPuntos){
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		cubo->cambiaColor({1,0,0});
		cubo->draw(modoDibujo );
		tetraedro->draw(modoDibujo);
	 }

	 if(comoLineas){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		cubo->cambiaColor({0,1,0});
		cubo->draw(modoDibujo);
		tetraedro->draw(modoDibujo);
	 }

	 if(comoTriangulos){
		cubo->cambiaColor({0,0,1});
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		cubo->draw(modoDibujo);
		tetraedro->draw(modoDibujo);
	 }

}

void Escena::dibujaObjetos(){
	cubo->draw(modoDibujo);
	tetraedro->draw(modoDibujo);
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO;
         break ;
        case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         break ;
       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         break ;
         // COMPLETAR con los diferentes opciones de teclado
		 case 'C' :
			if(modoMenu == SELOBJETO){
				cubo->cambiaEstado();
				cout<<"Mostrando el cubo"<<endl;
			}
			else{
				cout<<"Tecla no válida"<<endl;
			}
			break ;
		 case 'T' :
			if(modoMenu == SELOBJETO){
				tetraedro->cambiaEstado();
				cout<<"Mostrando el tetraedro"<<endl;
			}
			else{
				cout<<"Tecla no válida"<<endl;
			}
			break ;
		 case '1' :
			if(modoMenu == SELDIBUJADO){
				cout<<"Dibujando en Inmediato"<<endl;
				modoDibujo = 'I';
			}
			else {
				cout<<"Tecla no válida"<<endl;
			}
			break ;
		 case '2':
			if(modoMenu == SELDIBUJADO){
				cout<<"Dibujando en Diferido"<<endl;
				modoDibujo = 'D';
			}
			else {
				cout<<"Tecla no válida"<<endl;
			}
			break ;
		case 'P' :
			if(modoMenu == SELVISUALIZACION){
				cout<<"Dibujando en modo puntos"<<endl;
				comoPuntos = !comoPuntos;
			}
			else{
				cout<<"Tecla no válida"<<endl;
			}
			break;
		case 'L' :
			if(modoMenu == SELVISUALIZACION){
				cout<<"Dibujando en modo lineas"<<endl;
				comoLineas = !comoLineas;
			}
			else{
				cout<<"Tecla no válida"<<endl;
			}
			break;
		case 'S' :
			if(modoMenu == SELVISUALIZACION){
				cout<<"Dibujando en modo Caras"<<endl;
				comoTriangulos = !comoTriangulos;
			}
			else{
				cout<<"Tecla no válida"<<endl;
			}
			break;
		case 'A' :
			if(modoMenu == SELVISUALIZACION){
				cout<<"Dibujando en modo Ajedrez"<<endl;
				modoDibujo = 'A';
				comoTriangulos = true;
			}
			else{
				cout<<"Tecla no válida"<<endl;
			}
			break;
		 case 'H':
			cout<<"Usa la tecla O para seleccionar el objeto luego (C)ubo y (T)etraedro para las dos figuras"<<endl;
			cout<<"La tecla V se emplea para el modo seleccion de visualización, luego P para puntos, L para lineas, A para el modo ajedrez y S para dibujar las caras"<<endl;
			cout<<"La tecla D para el dibujado 1 para modo inmediato y 2 para modo deferido"<<endl;
			break;


   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
