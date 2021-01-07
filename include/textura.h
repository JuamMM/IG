#ifndef TEXTURA_H
#define TEXTURA_H

#include<vector>
#include<string>
#include<GLFW/glfw3.h>

class Textura{
	private:
		GLuint idTex = -1;
		std::vector<unsigned char> data;
		int anchura, altura;

	public:
		Textura(std::string archivo);
		void activar();

};

#endif
