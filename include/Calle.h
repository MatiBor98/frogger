#pragma once
#include "Object.h"
#include "Auto.h"
#include "GameObjects.h"

class Calle :
    public Object
{
public:
    Calle(vec3 posicion);
    void movimiento(double delta);
    ~Calle();

private:
    vec3 origen, destino;
    double spawnRate, timer, carSpeed;
};
