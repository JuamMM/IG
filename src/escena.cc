

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************
//
//



Material plastico_negro({ 0.02f, 0.02f, 0.02f, 1.0f },{ 0.01f, 0.01f, 0.01f, 1.0f},{0.4f, 0.4f, 0.4f, 1.0f }, 10.0f);
Material oro ({0.24725, 0.1995, 0.0745, 1}, {0.75164, 0.60648, 0.22648, 1}, {0.628281, 0.555802, 0.366065, 1}, 0.4*128.0f);
Material ruby ({ 0.1745f, 0.01175f, 0.01175f, 0.55f },{0.61424f, 0.04136f, 0.04136f, 0.55f },{0.727811f, 0.626959f, 0.626959f, 0.55f }, 76.8f);
Material perla({ 0.25f, 0.20725f, 0.20725f, 0.922f }, {1.0f, 0.829f, 0.829f, 0.922f }, {0.296648f, 0.296648f, 0.296648f, 0.922f }, 11.264f);
Material obsidiana({ 0.05375f, 0.05f, 0.06625f, 0.82f }, { 0.18275f, 0.17f, 0.22525f, 0.82f}, {0.332741f, 0.328634f, 0.346435f, 0.82f }, 38.4f);

Tupla3f amarillo({1,1,0});
Tupla3f rojo({1,0,0});
Tupla3f verde({0,1,0});
Tupla3f azul({0,0,1});
Tupla3f cian({0,1,1});

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

	Camara cam1({300,0,0},{0,0,0},{1,1,0}, ORTOGONAL, Front_plane, Back_plane);
	Camara cam2({400,0,0},{0,0,0},{1,1,0}, PERSPECTIVA, Front_plane, Back_plane);
	Camara cam3({300,0,100},{0,0,0},{1,0,0}, ORTOGONAL, Front_plane, Back_plane);
	Camara cam4({450,100,0},{0,0,0},{0,0,1}, PERSPECTIVA, Front_plane, Back_plane);
	Camara cam5({450,100,0},{0,0,0},{0,0,1}, ORTOGONAL, Front_plane, Back_plane);

	camara_activa = 0;

	camaras.push_back(cam1);
	camaras.push_back(cam2);
	camaras.push_back(cam3);
	camaras.push_back(cam4);
	camaras.push_back(cam5);

	for(int i=0;i< camaras.size();i++){
		camaras[i].setIzquierda(75);
		camaras[i].setDerecha(-75);
		camaras[i].setAbajo(-75);
		camaras[i].setTop(75);
	}
	esfera->ajustaCentro({40,0,-30});
	cubo->ajustaCentro({0,-50,0});
	peon2->ajustaCentro({30,0,0});
	tetraedro->ajustaCentro({20,30,0});

	peon2->cambiaColorInmediato(verde);
	tetraedro->cambiaColorInmediato(azul);
	esfera->cambiaColorInmediato(rojo);
	cilindro->cambiaColorInmediato(cian);

	peon2->tipo = PEON;
	//sauron->cambiaColorInmediato(morado);
	//
	objetos_dibujo.push_back(cubo);
	objetos_dibujo.push_back(tetraedro);
	objetos_dibujo.push_back(esfera);
	objetos_dibujo.push_back(cilindro);
	objetos_dibujo.push_back(peon2);
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

   change_projection( );
	glViewport( 0, 0, UI_window_width, UI_window_height );

	peon2->cambiaEstado();
	tetraedro->cambiaEstado();
	cilindro->cambiaEstado();
	esfera->cambiaEstado();
	tetraedro->cambiaMaterial(oro);
	peon2->cambiaMaterial(obsidiana);
	lata->cambiaMaterial(perla);

	sauron->cambia_M_Base(obsidiana);
	sauron->cambia_M_Cuerpo(obsidiana);
	sauron->cambia_M_Ojo(ruby);

	cubo->cambiaEstado();
	lata->cambiaEstado();


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
		//Colores({1,0,0});
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		dibujaObjetos();
	 }

	 if(comoLineas){
		//Colores({0,0,1});
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		dibujaObjetos();
	 }

	 if(comoTriangulos){
		//Colores({0,1,0});
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
	peon2->cambiaColor(nuevo_color);
	tetraedro->cambiaColor(nuevo_color);
	esfera->cambiaColor(nuevo_color);
	cilindro->cambiaColor(nuevo_color);
	sauron->cambiaColor(nuevo_color);

}

void Escena::dibujaObjetos(){

	glPushMatrix();
	glTranslatef(0,-50,0);
	objetos_dibujo[0]->draw(modoDibujo,ajedrez);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20,30,0);
	objetos_dibujo[1]->draw(modoDibujo,ajedrez);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30,0,0);
	glScalef(15,15,15);
	objetos_dibujo[4]->draw(modoDibujo,ajedrez);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,-30);
	objetos_dibujo[3]->draw(modoDibujo,ajedrez);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40,0,-30);
	objetos_dibujo[2]->draw(modoDibujo,ajedrez);
	glPopMatrix();

	sauron->draw(modoDibujo,ajedrez);

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
				change_projection();
				change_observer();
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
				change_projection();
				change_observer();
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
				change_projection();
				change_observer();
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
		case '3':
			if(modoMenu ==CAMARA){
				cout<<"cambiando a camara 3"<<endl;
				camara_activa =3;
				change_projection();
				change_observer();
			}
			break;
		case '4':
			if(modoMenu ==CAMARA){
				cout<<"cambiando a camara 4"<<endl;
				camara_activa =4;
				change_projection();
				change_observer();
			}
			break;
		case '5':
			if(modoMenu ==CAMARA){
				cout<<"cambiando a camara 5"<<endl;
				camara_activa =5;
				change_projection();
				change_observer();
			}
			break;
		case '+':
			if(modoMenu == CAMARA){
				cout<<"Aumentando zoom camara "<<camara_activa<<endl;
				camaras[camara_activa].zoom(1.5);
				change_projection();
				change_observer();
			}
			break;
		case '-':
			if(modoMenu == CAMARA){
				cout<<"Decrementando zoom camara "<<camara_activa<<endl;
				camaras[camara_activa].zoom(0.5);
				change_projection();
				change_observer();
			}
			break;

		 case 'H':
			cout<<"Pulsa la tecla V para activar/desactivar el modo visualización."<<endl;
			cout<<"\t La tecla P activa/desactica el modo puntos."<<endl;
			cout<<"\t La tecla S activa/desactiva el modo superficie."<<endl;
			cout<<"\t La tecla L activa/desactiva el modo lineas."<<endl;
			cout<<"\t La tecla A activa/desactiva el modo ajedrez."<<endl;
			cout<<"Pulsa la tecla I para activar/desactivar el modo iluminación."<<endl;
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
	change_projection();

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( /*const float ratio_xy*/ )
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
   change_projection( );
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
	if(boton == GLUT_RIGHT_BUTTON){
		if(estado == GLUT_DOWN){
			x_mov = x;
			y_mov = y;
			raton_pulsado = true;
		}
		else{
			raton_pulsado = false;
		}
	}
	if(boton == GLUT_LEFT_BUTTON){
		if(estado == GLUT_UP){
			Seleccion(x,y);
		}
	}
}

void Escena::Seleccion(int x, int y){

	glDisable(GL_DITHER);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	GLint viewport[4];
	GLfloat pixels[3];
	Tupla3f color;

	glGetIntegerv(GL_VIEWPORT,viewport);
	glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_FLOAT,pixels);

	color = {pixels[0], pixels[1], pixels[2]};


	if(cubo->colorObjeto() == color){
		camaras[camara_activa].asignaObjeto(CUBO);
	}
	else if(peon2->colorObjeto() == color){
		camaras[camara_activa].asignaObjeto(PEON);
	}
	else if(tetraedro->colorObjeto() == color){
		camaras[camara_activa].asignaObjeto(TETRAEDRO);
	}
	else if(esfera->colorObjeto() == color){
		camaras[camara_activa].asignaObjeto(ESFERA);
	}
	else if(cilindro->colorObjeto() == color){
		camaras[camara_activa].asignaObjeto(CILINDRO);
	}

	for(int i=0; i<objetos_dibujo.size(); i++){
		if(objetos_dibujo[i]->tipo == camaras[camara_activa].MirandoA()){
			objetos_dibujo[i]->cambiaColor(amarillo);

			camaras[camara_activa].setEn(objetos_dibujo[i]->devuelveCentro());
			change_projection();
			change_observer();
		}
		else{
			objetos_dibujo[i]->cambiaColor(objetos_dibujo[i]->colorObjeto());
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
