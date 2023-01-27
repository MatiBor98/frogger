#include "Tren.h"

 Tren::Tren(vec3 origen, vec3 destino, double demora){
	objDir = "train.obj";
	objTex = "";
	meshId = 5;
	tamaño = vec3(3.55, 0.84, 0.3);
	cargarObj();
	borrar = false;
	this->posicion = origen;
	this->origen = origen;
	this->destino = destino;

	if (origen.getX() < destino.getX()) {
		rot = 180;
	}

	this->demora = demora;
	this->tiempo = 0;
}

void Tren::movimiento(double delta) {
	if (tiempo < demora && !borrar) {
		tiempo += delta;
		posicion = origen + (destino - origen) * (tiempo / demora);
	}
	else {
		borrar = true;
	}
 }