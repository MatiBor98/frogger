#include "Camara.h"
#include <GL/glu.h>
#define PI 3.141592

Camara::Camara(vec3 pos, vec3 front, vec3 up, int w, int h) {
	this->pos = pos;
	this->front = front;
	this->up = up;
	this->width = w;
	this->height = h;

	modo = ORTHO; // Por defecto

	glMatrixMode(GL_PROJECTION);
	glOrtho(-width / 200, width / 200, -height / 200, height / 200, -0.1, 100);
	glMatrixMode(GL_MODELVIEW);

	follows = NULL; // Por defecto
}

Camara::Camara(Object* obj, vec3 up, int w, int h) {
	this->pos = vec3(20, 20, 20);
	this->up = up;
	this->width = w;
	this->height = h;

	modo = ORTHO;

	glMatrixMode(GL_PROJECTION);
	glOrtho(-width / 200, width / 200, -height / 200, height / 200, -0.1, 100);
	glMatrixMode(GL_MODELVIEW);

	follows = obj;
}

void Camara::modoUpdate() {
	setModo(modo);
}

void Camara::setModo(camMode modo) {
	this->modo = modo;
	glEnable(GL_DEPTH_TEST);
	if (modo == ORTHO) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-width / 200.0, width / 200.0, -height / 200.0, height / 200.0, -0.1, 100);
		glMatrixMode(GL_MODELVIEW);
		glDisable(GL_FOG);
		
	}
	else if (modo == PERSPECTIVE) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, float(width) / float(height), 0.1, 100);
		glMatrixMode(GL_MODELVIEW);

		// Niebla
		glEnable(GL_FOG);
		glFogf(GL_FOG_START, 4);
		glFogf(GL_FOG_END, 10); // Se ven 10 calles
		GLfloat fogColor[4] = {.7, .7, .7, 0};
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_MODE, GL_LINEAR);
	}
}

void Camara::setWidth(int w) {
	this->width = w;
}

void Camara::setHeight(int h) {
	this->height = h;
}

void Camara::followObj(Object* obj) {
	this->follows = obj;
}

void Camara::update() {
	vec3 objPos = follows->getPos();
	switch (modo) {
	case PERSPECTIVE: 
		if (follows != NULL) {
			vec3 objPos = follows->getPos();
			pos = objPos + vec3(sin(follows->rot*PI/180.f)*3, .7, cos(follows->rot*PI/180.f)*3);
			front = normalize(objPos - pos);
			
		}
		gluLookAt(
			pos.getX(), pos.getY(), pos.getZ(),
			objPos.getX(), objPos.getY(), objPos.getZ(),
			up.getX(), up.getY(), up.getZ()
		);
		break;
	case ORTHO:
		double posx = 0, posy = 0, posz = 0;
		if (follows != NULL) {
			vec3 objPos = follows->getPos();
			pos = objPos + vec3(20, 20, 20);
			posx = objPos.getX();
			posy = objPos.getY();
			posz = objPos.getZ();
		}
		gluLookAt(
			pos.getX(), pos.getY(), pos.getZ(),
			posx, posy, posz,
			up.getX(), up.getY(), up.getZ()
		);
		break;

	
	
	}
}