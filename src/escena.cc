

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************
//

Material oro ({0.24725, 0.1995, 0.0745, 1}, {0.75164, 0.60648, 0.22648, 1}, {0.628281, 0.555802, 0.366065, 1}, 0.4*128.0f);
Material ruby ({ 0.1745f, 0.01175f, 0.01175f, 0.55f },{0.61424f, 0.04136f, 0.04136f, 0.55f },{0.727811f, 0.626959f, 0.626959f, 0.55f }, 76.8f);
Material perla({ 0.25f, 0.20725f, 0.20725f, 0.922f }, {1.0f, 0.829f, 0.829f, 0.922f }, {0.296648f, 0.296648f, 0.296648f, 0.922f }, 11.264f);
Material obsidiana({ 0.05375f, 0.05f, 0.06625f, 0.82f }, { 0.18275f, 0.17f, 0.22525f, 0.82f}, {0.332741f, 0.328634f, 0.346435f, 0.82f }, 38.4f
);

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
	 tetraedro = new Tetraedro(30);
	 cubo= new Cubo(30);
	 modelo = new ObjPLY("./plys/beethoven.ply");
	 peon = new ObjRevolucion("./plys/peon.ply",15,true);
	 peon2 = new ObjRevolucion("./plys/peon.ply",15,true);

	 std::vector<Tupla3f> puntos;
	 puntos.push_back({10,-10,0});
	 puntos.push_back({0,10,0});
	 cono = new Cono(puntos,true,10);

	 puntos.clear();

	 puntos.push_back({10,-20,0});
	 puntos.push_back({10,20,0});
	 cilindro = new Cilindro(puntos,true,10);


	 esfera = new Esfera(20,10,true);

	 Tupla3f pos_0 = {0,50,0};
	 Tupla3f pos_1 = {50,0,0};


	 luz0 = new LuzPosicional(pos_0,GL_LIGHT0,{0,0,0,1},{1,1,1,1},{1,1,1,1});
	 luz1 = new LuzDireccional(pos_1, GL_LIGHT1,{0,0,0,1},{1,1,1,1},{1,1,1,1});

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
	glEnable(GL_NORMALIZE);

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );

	peon->cambiaEstado();
	peon2->cambiaEstado();
	tetraedro->cambiaEstado();
	cono->cambiaEstado();
	cilindro->cambiaEstado();
	cubo->cambiaEstado();
	esfera->cambiaEstado();
	esfera->cambiaMaterial(ruby);
	peon2->cambiaMaterial(obsidiana);
	peon->cambiaMaterial(perla);

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
	 glDisable(GL_LIGHTING);
    ejes.draw();
    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer
	 if(comoPuntos){
		Colores({1,0,0});
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		dibujaObjetos();
	 }

	 if(comoLineas){
		Colores({0,0,1});
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		dibujaObjetos();
	 }

	 if(comoTriangulos){
		Colores({0,1,0});
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		dibujaObjetos();
	 }

	 if(luces){
		glEnable(GL_LIGHTING);
		enciendeLuces();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		dibujaObjetos();
	 }

}

void Escena::enciendeLuces(){
	luz0->activar();
	luz1->activar();
}

void Escena::Colores(Tupla3f nuevo_color){
	cubo->cambiaColor(nuevo_color);
	peon->cambiaColor(nuevo_color);
	tetraedro->cambiaColor(nuevo_color);
	esfera->cambiaColor(nuevo_color);
	cilindro->cambiaColor(nuevo_color);
	cono->cambiaColor(nuevo_color);

}

void Escena::dibujaObjetos(){

	glPushMatrix();
	glTranslatef(0,50,0);
	cubo->draw(modoDibujo,ajedrez);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20,30,0);
	tetraedro->draw(modoDibujo,ajedrez);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-30,0,0);
	glScalef(15,15,15);
	peon->draw(modoDibujo,ajedrez);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30,0,0);
	glScalef(15,15,15);
	peon2->draw(modoDibujo,ajedrez);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,30);
	cono->draw(modoDibujo,ajedrez);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,-30);
	cilindro->draw(modoDibujo,ajedrez);
	glPopMatrix();

	esfera->draw(modoDibujo,ajedrez);
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
        case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         break ;
/*       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         break ;
         // COMPLETAR con los diferentes opciones de teclado
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
			break ;*/
		case 'P' :
			if(modoMenu == SELVISUALIZACION){
				cout<<"Dibujando en modo puntos"<<endl;
				comoPuntos = true;
				luces = false;
			}
			else{
				cout<<"Tecla no válida"<<endl;
			}
			break;
		case 'L' :
			if(modoMenu == SELVISUALIZACION){
				cout<<"Dibujando en modo lineas"<<endl;
				comoLineas = true;
				luces = false;
			}
			else{
				cout<<"Tecla no válida"<<endl;
			}
			break;
		case 'S' :
			if(modoMenu == SELVISUALIZACION){
				cout<<"Dibujando en modo Caras"<<endl;
				comoTriangulos = true;
				luces = false;
			}
			else{
				cout<<"Tecla no válida"<<endl;
			}
			break;
		case 'I' :
			if(modoMenu == SELVISUALIZACION){
				cout<<"Dibujando en modo iluminacion suave"<<endl;
				comoTriangulos = false;
				comoLineas = false;
				comoPuntos = false;
				ajedrez = false;
				luces = true;
			}
			else{
				cout<<"Tecla no válida"<<endl;
			}
			break;
		case 'B':
			if(luces){
				cout<<"cambiando angulo beta"<<endl;
				beta_pulsada = true;
				alpha_pulsada = false;
			}
			break;
		case 'A' :
			if(modoMenu == SELVISUALIZACION && !luces){
				cout<<"Dibujando en modo Ajedrez"<<endl;
				ajedrez = !ajedrez;
			}
			else if (luces){
				cout<<"cambiando angulo alpha"<<endl;
				alpha_pulsada = true;
				beta_pulsada = false;
			}
			else{
				cout<<"Tecla no válida"<<endl;
			}
			break;
		case 'T' :
			cout<<"Cambiando tapas inferiores"<<endl;
			esfera->ocultaTapas();
			cono->ocultaTapas();
			peon->ocultaTapas();
			cilindro->ocultaTapas();
			break;
		case '0' :
			if(luces){
				cout<<"Encendiendo luz 0"<<endl;
				luz0->encenderLuz();
			}
			else{
				cout<<"La iluminacion no está activada"<<endl;
			}
			break;
		case '1' :
			if(luces){
				cout<<"Encendiendo luz 1"<<endl;
				luz1->encenderLuz();
			}
			else{
				cout<<"La iluminacion no está activada"<<endl;
			}
			break;
		case	'<':
			if(alpha_pulsada){
				luz1->variarAnguloAlpha(5.0f);
			}

			if(beta_pulsada){
				luz1->variarAnguloBeta(5.0f);
			}
			break;
		case	'>':
			if(alpha_pulsada){
				luz1->variarAnguloAlpha(-5.0f);
			}

			if(beta_pulsada){
				luz1->variarAnguloBeta(-5.0f);
			}
			break;
		 case 'H':
			cout<<"Usa la tecla O para pintar los objetos"<<endl;
			cout<<"Pulsa la tecla T para eliminar/pintar las capas"<<endl;
			cout<<"La tecla V se emplea para el modo seleccion de visualización, luego P para puntos, L para lineas, A para el modo ajedrez y S para dibujar las caras, I para encender las luces"<<endl;
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
	   case GLUT_KEY_F2:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_F3:
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
