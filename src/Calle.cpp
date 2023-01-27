#include "Calle.h"

Calle::Calle(vec3 posicion) {
    objDir = "calle.obj";
    objTex = "calle.png";
    tamaño = vec3(0, 0, 0);
    meshId = 0;
    cargarObj();

    int random = rand();

    this->posicion = posicion;
    carSpeed = 8000 + random % 20000;
    spawnRate = 2000 + random % 10000;
    if (random % 2 == 0) {
        origen = posicion + vec3(12, 0, 0);
        destino = posicion - vec3(12, 0, 0);
    } else {
        origen = posicion - vec3(12, 0, 0);
        destino = posicion + vec3(12, 0, 0);
    }
    timer = 0;
};

void Calle::movimiento(double delta) {
    timer -= delta;
    if (timer < 0) {
        timer = spawnRate;
        Auto* car = new Auto(origen, destino, carSpeed); 
        GameObjects::getInstance()->addObject(car);
    } 
}

Calle::~Calle() {}