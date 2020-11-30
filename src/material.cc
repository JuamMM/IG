#include "material.h"

Material::Material(){
	ambiente ={ 0.0f,0.05f,0.0f,1.0f };
	difuso ={ 0.4f,0.5f,0.4f,1.0f};
	especular ={0.04f,0.7f,0.04f,1.0f };
	brillo =  10.0f;

}

Material::Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, const float mbrillo){
	ambiente = mambiente;
	especular = mespecular;
	difuso = mdifuso;
	brillo = mbrillo;
}

void Material::aplicar(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

	glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void Material::operator =(const Material & otro){
	difuso = otro.difuso;
	especular = otro.especular;
	ambiente = otro.ambiente;
	brillo = otro.brillo;
}
