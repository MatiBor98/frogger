#include "Arbol.h"

Arbol::Arbol(vec3 posicion) {
    objDir = "tree_blocks.obj";
    objTex = "";
    meshId = 3;
    tama�o = vec3(0.07, 1.2, 0.07);
    cargarObj();
    this->posicion = posicion;
};
