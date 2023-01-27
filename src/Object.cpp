#include "Object.h"
#include "../include/OBJ_Loader.hpp"
#include <SDL_opengl.h>
#include "GameObjects.h"
#define PI 3.141592

Object::~Object() {}

void Object::cargarObj() {
	GameObjects* gameObjects = GameObjects::getInstance();
	meshes = gameObjects->getMeshes(meshId);
	displayListId = gameObjects->getDisplayListId(meshId);

	// Cargado de textura (si tiene)
	if (objTex != "") {
		idText = gameObjects->textId;
	}	
}

void Object::draw(bool texture) { // Faltaría agregar algo relacionado a la rotación

	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, posicion.z); // Mueve plano para dibujar
	glRotatef(rot, 0, 1, 0);	
	

	if (objTex != "" && !texture) { // Si hay textura cargada (Se podría agregar booleano)
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, idText);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	else {
		glDisable(GL_TEXTURE_2D);
	}

	glCallList(displayListId);
	
	glPopMatrix();
	if (objTex != "")
		glDisable(GL_TEXTURE_2D);
}

void Object::movimiento(double delta) {
	// La funcion se sobrecarga en la clase que herede a Object
}

void Object::movX(double x) {
	posicion.x += x;
}

void Object::movY(double y) {
	posicion.y += y;
}

void Object::movZ(double z) {
	posicion.z += z;
}

void Object::setRot(double r) {
	this->rot = r;
}

void Object::setPos(vec3 pos) {
	this->posicion = pos;
}

bool Object::colition(Object* o) {
	vec3 dis = o->posicion - this->posicion;

	bool colisionX = false;
	bool colisionY = false;
	bool colisionZ = false;

	if (abs(dis.x) <= this->tamaño.x + o->tamaño.x) {
		colisionX = true;
	}
	if (abs(dis.y) <= this->tamaño.y + o->tamaño.y) {
		colisionY = true;
	}
	if (abs(dis.z) <= this->tamaño.z + o->tamaño.z) {
		colisionZ = true;
	}

	return (colisionX && colisionY && colisionZ);
}

vec3 Object::getPos() {
	return posicion;
}