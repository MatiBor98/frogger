#pragma once
#include "Object.h"
class Pollo:
    public Object
{
public:
    Pollo() {
        objDir = "pollo.obj";
        objTex = "";
        meshId = 1;
        tama�o = vec3(0.16, 0.46, 0.23);
        cargarObj();
    };
    ~Pollo() {  };
};

