#pragma once
#include <vector>
#include <string>
#include "OBJ_Loader.hpp"
#include "vec3d.h"
#include <SDL_opengl.h>

class Object
{
public:
	Object() {};

	virtual ~Object() = 0;

	/**
		Función para dibujar objeto (tiene en cuenta la posicion)
	*/
	void draw(bool texture);

	/**
		Funcion para cambiar propiedades de objeto (se llama cada frame) 
		El paramentro delta son los milisegundos que pasaron desde el ultimo frame
		Sirve para calcular movimiento de objeto
	*/
	virtual void movimiento(double delta); 

	/**
		Funcion que carga el .obj, textura y materiales (La usa el constructor)
	*/
	void cargarObj();

	/**
		Funcion que mueve en x
	*/
	void movX(double x);

	/**
		Funcion que mueve en y
	*/
	void movY(double y);

	/**
		Funcion que mueve en z
	*/
	void movZ(double z);

	void setRot(double r);

	void setPos(vec3 pos);

	bool colition(Object* o);

	vec3 getPos();


	bool borrar;

	int meshId;
		
	std::vector<objl::Mesh>* meshes;

	/**
		Posicion de objeto en el plano
	*/
	vec3 posicion;

	/**
		Direccion a donde apunta la gallina
	*/
	vec3 direccion;

	vec3 tamaño;

	double rot;

	/**
		Nombre de .obj
	*/
	std::string objDir; 

	/**
		Nombre de textura
	*/
	std::string objTex;

	/**
		ID de textura (en OpenGl)
	*/
	GLuint idText;

	/**
		Display list id
	*/
	GLint displayListId;
};

