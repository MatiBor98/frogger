#pragma once
#include "Object.h"
#include "vec3d.h"



class Auto :
    public Object
{

public:
    Auto(vec3 origen, vec3 destino, double demora);

    Auto();

    ~Auto();

    void movimiento(double delta);


private:
    vec3 origen, destino; // Indica de donde a donde va el auto
    double demora, tiempo; // Demora es lo que demora de ir de origen a destino y
                           // tiempo es en el tiempo que esta (Cuando tiempo == demora se borra el auto)
};

