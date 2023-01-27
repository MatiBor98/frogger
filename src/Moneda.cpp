#include "Moneda.h"

Moneda::Moneda(vec3 posicion) {
    objDir = "moneda.obj";
    objTex = "";
    meshId = 7;
    tamaño = vec3(.15, 1 ,.15);
    cargarObj();
    this->posicion = posicion;
};

void Moneda::movimiento(double delta) {
    rot = fmod(rot + 0.36*delta, 360.0); // rotación moneda
}