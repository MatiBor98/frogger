#include "Auto.h"
#include "GameObjects.h"

Auto::Auto(vec3 origen, vec3 destino, double demora) {
    objDir = "sedan.obj";
    objTex = "";
    tamaño = vec3(.5, .5, 0.3);
    meshId = 2;
    cargarObj();
    this->posicion = origen;
    this->origen = origen;
    this->destino = destino;

    if (origen.getX() < destino.getX()) {
        rot = 180;
    }

    this->demora = demora;
    this->tiempo = 0;
    borrar = false;
}

void Auto::movimiento(double delta) {
    if (tiempo < demora && !borrar) {
        tiempo += delta;
        posicion = origen + (destino - origen) * (tiempo / demora);
    } else {
        borrar = true;
    }
}

Auto::~Auto() {
}