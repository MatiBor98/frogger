#pragma once
#include "vec3d.h"
#include "Object.h"

enum camMode {
	ORTHO,
	PERSPECTIVE
};

class Camara {
public:

	/**
		Se crea una camara estatica y ortogonal por defecto
	*/
	Camara(vec3 pos, vec3 front, vec3 up, int w, int h);

	/**
		Se crea una camara que sigue al objeto y ortogonal
	*/
	Camara(Object* obj, vec3 up, int w, int h);

	/**
		Ejecuta las operaciones de setModo pero con el modo actual (es por la interface)
	*/
	void modoUpdate();

	/**
		Setea el modo de la camara
	*/
	void setModo(camMode modo);

	/**
		Setea width
	*/
	void setWidth(int w);

	/**
		Setea height
	*/
	void setHeight(int h);

	/**
		Hace que la camara siga al objeto (Depende del modo de la camara)
	*/
	void followObj(Object* obj); 

	/**
		Actualiza posicion de la camara (Ejecuta gluLookat) - Se usa en el loop principal
	*/
	void update();

private:
	/**
		Posicion, vector "up", y direccion a donde apunta la camara
	*/
	vec3 pos, front, up;

	/**
		Modo de camara (Ortogonal o perspectiva)
	*/
	camMode modo;

	/**
		Tamaño de pantalla
	*/
	int width, height;

	/**
		Objeto al que sigue (En este caso a la gallina) - No es obligatorio
	*/
	Object* follows;

};
