#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
	v.resize(8);
	f.resize(12);
	c_inmediato.resize(8);
	c_diferido.resize(8);


   // inicializar la tabla de caras o triángulos:
	v[0] = {0.0f,0.0f,0.0f};
	v[1] = {lado,0.0f,0.0f};
	v[2] = {lado,0.0f,lado};
	v[3] = {0.0f,0.0f,lado};

	v[4] = {0.0f,lado,0.0f};
	v[5] = {lado,lado,0.0f};
	v[6] = {lado,lado,lado};
	v[7] = {0.0f,lado,lado};

	f[0] = {3,0,2};
	f[1] = {2,0,1};

	f[2] = {7,3,2};
	f[3] = {2,6,7};

	f[4] = {6,2,1};
	f[5] = {1,5,6};

	f[6] = {0,4,5};
	f[7] = {0,5,1};

	f[8] = {4,0,3};
	f[9] = {3,7,4};

	f[10] = {4,6,5};
	f[11] = {4,7,6};

   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

	for(auto it = c_inmediato.begin(); it != c_inmediato.end(); it++){
		(*it) = inmediato;
	}

}
