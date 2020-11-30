#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(const float lado)
{

   // inicializar la tabla de vértices
	v.resize(4);
	f.resize(4);
	c_inmediato.resize(4);
	c_diferido.resize(4);

	float mediana = sqrt( pow(lado,2) - pow(lado/2,2));
	float altura = sqrt( pow(lado,2) - pow(mediana/3,2));


   // inicializar la tabla de caras o triángulos:
	v[0] = {0.0f,0.0f,0.0f};
	v[1] = {lado,0.0f,0.0f};
	v[2] = {lado/2,0.0f,mediana};
	v[3] = {lado/2,altura,mediana/3};

	f[0] = {3,1,0};
	f[1] = {2,1,3};
	f[2] = {0,2,3};
	f[3] = {0,1,2};
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
	for(auto it = c_inmediato.begin(); it != c_inmediato.end(); it++){
		(*it) = inmediato;
	}


	calculaNormales();
}
