#include "Pasto.h"
#include <GameObjects.h>
#include "Moneda.h"


Pasto::Pasto(vec3 posicion) {
    objDir = "grass.obj";
    objTex = "";
    meshId = 6;

    tamaño = vec3(0, 0, 0);

    this->posicion = posicion;
    cargarObj();
    if (posicion.getZ() < -1) {
        for (int x = -12; x < 13; x++) {
            if (rand() % 2 == 0) {
                Arbol* arbol = new Arbol(vec3(x, this->posicion.getY(), this->posicion.getZ()));
                GameObjects::getInstance()->addObject(arbol);

            }
            else if (rand() % 10 == 0 && abs(x) <= 4) {
                Moneda* moneda = new Moneda(vec3(x, this->posicion.getY(), this->posicion.getZ()));
                GameObjects::getInstance()->addObject(moneda);
            }
        }
    }


}

