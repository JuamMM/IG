#include "textura.h"
#include "iostream"
#include "jpg_imagen.hpp"


Textura::Textura(std::string archivo){
	jpg::Imagen * pimg = new jpg::Imagen(archivo);

	anchura = pimg->tamX();
	altura = pimg->tamY();
	unsigned char * pixel;

	for(int i=0; i<altura; i++){
		for(int j=0; j<anchura; j++){
			pixel = pimg->leerPixel(j,altura-i-1);

			data.push_back(*pixel);
			pixel++;

			data.push_back(*pixel);
			pixel++;

			data.push_back(*pixel);
		}
	}

}

void Textura::activar(){

	glEnable(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if(idTex == -1){
		glGenTextures(1, &idTex);

		glBindTexture(GL_TEXTURE_2D, idTex);
		glTexImage2D(GL_TEXTURE_2D,
				0,
				GL_RGB,
				anchura,
				altura,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data.data());
	}

	glBindTexture(GL_TEXTURE_2D, idTex);


}
