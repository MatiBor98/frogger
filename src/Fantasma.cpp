#include <Fantasma.h>

Fantasma::Fantasma() {
    objDir = "fantasma.obj";
    objTex = "";
    tama�o = vec3(0,0,0);
    meshId = 8;
    cargarObj();

    this->posicion = vec3(0,0, 5);
}

Fantasma::~Fantasma() {}