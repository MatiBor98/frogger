#pragma once
#include "Object.h"
#include "vec3d.h"



class Moneda : public Object {

public:
    Moneda(vec3 posicion);
    ~Moneda() {};
    void movimiento(double delta);

};
