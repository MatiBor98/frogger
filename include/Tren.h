#pragma once
#include "Object.h"
class Tren :
    public Object
{
public:
    Tren(vec3 origen, vec3 destino, double demora);
    void movimiento(double delta);  
    ~Tren() {};
private:
    vec3 origen, destino; // Indica de donde a donde va el auto
    double demora, tiempo; // Demora es lo que demora de ir de origen a destino y
                           // tiempo es en el tiempo que esta (Cuando tiempo == demora se borra el auto)

};