#include "Via.h"
#include "GameObjects.h"
#include "Tren.h"

Via::Via(vec3 posicion) {
    objDir = "via.obj";
    objTex = "";
    meshId = 4;
    tama�o = vec3(0, 0, 0);
    this->posicion = posicion;
    cargarObj();
    origen = posicion + vec3(12 + 3, 0, 0); // El +3 es por el tama�o del tren
    destino = posicion - vec3(12 + 3, 0, 0);
    tiempoTren = 2000 + 8000 + rand() % 20000; // El tren demora 500 en recorrer via + 4s minimo de espera
    timer = 0;
}

void Via::movimiento(double delta) {
    timer -= delta;
    if (timer < 0) {
        timer = tiempoTren;
        Tren* tren = new Tren(origen, destino, 2000);
        GameObjects::getInstance()->addObject(tren);
    }
}