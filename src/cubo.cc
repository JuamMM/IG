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
	v[0] = {-lado/2,-lado/2,-lado/2};
	v[1] = {lado/2,-lado/2,-lado/2};
	v[2] = {lado/2,-lado/2,lado/2};
	v[3] = {-lado/2,-lado/2,lado/2};

	v[4] = {-lado/2,lado/2,-lado/2};
	v[5] = {lado/2,lado/2,-lado/2};
	v[6] = {lado/2,lado/2,lado/2};
	v[7] = {-lado/2,lado/2,lado/2};

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
	calculaNormales();

}
