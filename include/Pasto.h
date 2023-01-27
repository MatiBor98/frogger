#pragma once
#include "Object.h"
#include "Arbol.h"
class Pasto :
    public Object
{
public:
    Pasto(vec3 posicion);
    ~Pasto() {};
};