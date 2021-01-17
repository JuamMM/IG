

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************
//

Material plastico_negro({ 0.02f, 0.02f, 0.02f, 1.0f },{ 0.01f, 0.01f, 0.01f, 1.0f},{0.4f, 0.4f, 0.4f, 1.0f }, 10.0f);
Material oro ({0.24725, 0.1995, 0.0745, 1}, {0.75164, 0.60648, 0.22648, 1}, {0.628281, 0.555802, 0.366065, 1}, 0.4*128.0f);
Material ruby ({ 0.1745f, 0.01175f, 0.01175f, 0.55f },{0.61424f, 0.04136f, 0.04136f, 0.55f },{0.727811f, 0.626959f, 0.626959f, 0.55f }, 76.8f);
Material perla({ 0.25f, 0.20725f, 0.20725f, 0.922f }, {1.0f, 0.829f, 0.829f, 0.922f }, {0.296648f, 0.296648f, 0.296648f, 0.922f }, 11.264f);
Material obsidiana({ 0.05375f, 0.05f, 0.06625f, 0.82f }, { 0.18275f, 0.17f, 0.22525f, 0.82f}, {0.332741f, 0.328634f, 0.346435f, 0.82f }, 38.4f);

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

	 lata = new ObjRevolucion("./plys/lata-pcue.ply",15,true,'C');
	 p_inf = new ObjRevolucion("./plys/lata-pinf.ply",15,true);
	 p_sup = new ObjRevolucion("./plys/lata-psup.ply",15,true);

	 std::vector<Tupla3f> puntos;
	 puntos.push_back({10,-10,0});
	 puntos.push_back({0,10,0});
	 cono = new Cono(puntos,true,10);

	 cilindro = new Cilindro(10,10,true,10);


	 esfera = new Esfera(20,10,true);

	 Tupla3f pos_0 = {0,200,0};
	 Tupla3f pos_1 = {50,0,0};


	 luz0 = new LuzPosicional(pos_0,GL_LIGHT0,{0,0,0,1},{1,1,1,1},{1,1,1,1});
	 luz1 = new LuzDireccional(pos_1, GL_LIGHT1,{0,0,0,1},{1,1,1,1},{1,1,1,1});

	 sauron = new Sauron();

	 sauron->cambia_M_Base(plastico_negro);
	 sauron->cambia_M_Cuerpo(plastico_negro);
	 sauron->cambia_M_Corona(plastico_negro);

	 lata->asignarTextura("./texturas/text-lata-1.jpg");
	 cubo->asignarTextura("./texturas/text-madera.jpg");

	 sauron->cambia_T_Cuerpo("./texturas/text-piedra.jpg");
	 sauron->cambia_T_Base("./texturas/text-piedra.jpg");
	 sauron->cambia_T_Corona("./texturas/text-piedra.jpg");
	 sauron->cambia_T_Ojo("./texturas/tex-fuego.jpg");
	 sauron->cambia_T_Corona("./texturas/text-piedra.jpg");

	Camara cam1({150,0,0},{0,0,0},{1,1,0}, ORTOGONAL, Front_plane, Back_plane);
	Camara cam2({100,0,0},{0,0,0},{1,1,0}, PERSPECTIVA, Front_plane, Back_plane);
	Camara cam3({200,0,100},{0,0,0},{1,0,0}, ORTOGONAL, Front_plane, Back_plane);
	Camara cam4({150,100,0},{0,0,0},{0,0,1}, PERSPECTIVA, Front_plane, Back_plane);
	Camara cam5({150,100,0},{0,0,0},{0,0,1}, ORTOGONAL, Front_plane, Back_plane);

	camara_activa = 0;

	camaras.push_back(cam1);
	camaras.push_back(cam2);
	camaras.push_back(cam3);
	camaras.push_back(cam4);
	camaras.push_back(cam5);

	for(int i=0;i< camaras.size();i++){
		camaras[i].setIzquierda(25);
		camaras[i].setDerecha(-25);
		camaras[i].setAbajo(-25);
		camaras[i].setTop(25);
	}
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
	esfera->cambiaEstado();
	esfera->cambiaMaterial(ruby);
	tetraedro->cambiaMaterial(oro);
	peon2->cambiaMaterial(obsidiana);
	peon->cambiaMaterial(perla);
	lata->cambiaMaterial(perla);

	sauron->cambia_M_Base(obsidiana);
	sauron->cambia_M_Cuerpo(obsidiana);
	sauron->cambia_M_Ojo(ruby);

	cubo->cambiaEstado();
	lata->cambiaEstado();
	p_inf->cambiaEstado();
	p_sup->cambiaEstado();
	lata->cambiaColor({1,1,1});
	p_inf->cambiaColor({1,1,1});
	p_sup->cambiaColor({1,1,1});
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
	 glDisable(GL_TEXTURE);
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
		glEnable(GL_TEXTURE);
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
	peon2->cambiaColor(nuevo_color);
	tetraedro->cambiaColor(nuevo_color);
	esfera->cambiaColor(nuevo_color);
	cilindro->cambiaColor(nuevo_color);
	cono->cambiaColor(nuevo_color);
	sauron->cambiaColor(nuevo_color);

}

void Escena::dibujaObjetos(){

	glPushMatrix();
	glTranslatef(0,-50,0);
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

	glPushMatrix();
	glTranslatef(40,0,-30);
	esfera->draw(modoDibujo,ajedrez);
	glPopMatrix();

	sauron->draw(modoDibujo,ajedrez);

	glPushMatrix();
	glTranslatef(40,10,-40);
	glScalef(100,100,100);
	p_inf->draw(modoDibujo,ajedrez);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40,11,-40);
	glScalef(100,100,100);
	p_sup->draw(modoDibujo,ajedrez);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40,10,-40);
	glScalef(100,100,100);
	lata->draw(modoDibujo,ajedrez);
	glPopMatrix();
}

void Escena::animarModeloJearquico(){
	sauron->animarModelo();

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
		case 'C':
			modoMenu = CAMARA;
			break;
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
       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         break ;
         // COMPLETAR con los diferentes opciones de teclado
		 case '2':
			if(modoMenu == SELDIBUJADO){
				cout<<"Dibujando en Diferido"<<endl;
				modoDibujo = 'D';
			}
			else if(modoMenu == SELANIMACION){
				cout<<"Actiando/Desactivando movimiento de la base"<<endl;
				sauron->AnimacionBase();
			}
			else if(modoMenu == CAMARA){
				cout<<"Cambiando a camara 2"<<endl;
				camara_activa = 2;
			}
			else {
				cout<<"Tecla no válida"<<endl;
			}
			break ;
		case 'P' :
			if(modoMenu == SELVISUALIZACION){
				cout<<"Dibujando en modo puntos"<<endl;
				comoPuntos = !comoPuntos;
				luces = false;
			}
			else{
				cout<<"Tecla no válida"<<endl;
			}
			break;
		case 'L' :
			if(modoMenu == SELVISUALIZACION){
				cout<<"Dibujando en modo lineas"<<endl;
				comoLineas = !comoLineas;
				luces = false;
			}
			else{
				cout<<"Tecla no válida"<<endl;
			}
			break;
		case 'S' :
			if(modoMenu == SELVISUALIZACION){
				cout<<"Dibujando en modo Caras"<<endl;
				if(ajedrez){
					ajedrez = false;
				}
				else{
					comoTriangulos = !comoTriangulos;
				}
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
				comoTriangulos = true;
				luces = false;
			}
			else if (luces && modoMenu != SELANIMACION){
				cout<<"cambiando angulo alpha"<<endl;
				alpha_pulsada = true;
				beta_pulsada = false;
			}
			else if(modoMenu == SELANIMACION){
				cout<<"Desactivando Animaciones"<<endl;
				sauron->AnimacionCorona();
				sauron->AnimacionOjo();
				sauron->AnimacionBase();
			}
			break;
		case 'M':
			cout<<"Cambiando a modoAnimacion"<<endl;
			modoMenu = SELANIMACION;
			break;
		case 'T' :
			cout<<"Cambiando tapas inferiores"<<endl;
			esfera->ocultaTapas();
			cono->ocultaTapas();
			peon->ocultaTapas();
			cilindro->ocultaTapas();
			break;

			if(luces && modoMenu != SELANIMACION){
				cout<<"Encendiendo luz 0"<<endl;
				luz0->encenderLuz();
			}
			else if(modoMenu == SELANIMACION){
				cout<<"Activando/Desactivando movimiento del ojo"<<endl;
				sauron->AnimacionOjo();
			}
			else{
				cout<<"La iluminacion no está activada"<<endl;
			}
			break;
		case '0':
			if(modoMenu == CAMARA){
				cout<<"Cambiando a Cámara 0"<<endl;
				camara_activa = 0;
			}
			break;
		case '1' :
			if(modoMenu == SELDIBUJADO){
				cout<<"Dibujando en Inmediato"<<endl;
				modoDibujo = 'I';
			}
			else if(luces && modoMenu != SELANIMACION){
				cout<<"Encendiendo luz 1"<<endl;
				luz1->encenderLuz();
			}
			else if(modoMenu == SELANIMACION){
				cout<<"Activando/Desactivando movimiento corona"<<endl;
				sauron->AnimacionCorona();
			}
			else if(modoMenu == CAMARA){
				cout<<"Cambiando a camara 1"<<endl;
				camara_activa = 1;
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
			cout<<"Pulsa la tecla V para activar/desactivar el modo visualización."<<endl;
			cout<<"\t La tecla P activa/desactica el modo puntos."<<endl;
			cout<<"\t La tecla S activa/desactiva el modo superficie."<<endl;
			cout<<"\t La tecla L activa/desactiva el modo lineas."<<endl;
			cout<<"\t La tecla A activa/desactiva el modo ajedrez."<<endl;
			cout<<"Pula la tecla I para activar/desactivar el modo iluminación."<<endl;
			cout<<"\t Las teclas 0 y 1 activan/desactivan las respectivas luces."<<endl;
			cout<<"\t La tecla A activa la variación del ángulo alfa y la B la del ángulo beta."<<endl;
			cout<<"\t Las teclas < y > incrementan y decrementan respectivamente el ánglo."<<endl;
			cout<<"La tecla M Permite activar y desactivar los diferentes grados de libertad del modelo."<<endl;
			cout<<"\t La tecla 0 activa desactiva el movimiento del ojo."<<endl;
			cout<<"\t La tecla 1 activa desactiva el movimiento de la corona."<<endl;
			cout<<"\t La tecla 2 activa desactiva el movimiento de la nube."<<endl;
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
   //const float wx = float(Height)*ratio_xy ;
   //glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
	camaras[camara_activa].setProyeccion();
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
/*   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );*/

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camaras[camara_activa].setObservador();

}

void Escena::clickRaton(int boton, int estado, int x, int y){
	if(boton = GLUT_RIGHT_BUTTON){
		if(estado == GLUT_DOWN){
			x_mov = x;
			y_mov = y;
			raton_pulsado = true;
		}
		else{
			raton_pulsado = false;
		}
	}
}

void Escena::ratonMovido(int x, int y){
	if( raton_pulsado ){
		camaras[camara_activa].girar(x-x_mov,y-y_mov);
		x_mov = x;
		y_mov = y;
	}
}
