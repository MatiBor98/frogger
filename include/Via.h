#pragma once
#include "Object.h"
class Via :
    public Object
{
public:
    Via(vec3 posicion);
    ~Via() {};
    void movimiento(double delta);
private:
    vec3 origen, destino;
    double tiempoTren, timer;
};