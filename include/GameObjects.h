#pragma once
#include "Object.h"
#include "vec3d.h"
#include "Calle.h"
#include "Auto.h"
#include <vector>
#include "Pollo.h"
#include "SDL.h"
#include "Fantasma.h"



class GameObjects {

public:

    static GameObjects* getInstance();
    ~GameObjects();

    /**
        Carga las meshes de los objetos de todo el juego
    */
    void loadMeshes();
    void init(Pollo* pollo);


    void run(double delta, bool texture);

    void addObject(Object* object);

    std::vector<objl::Mesh> *getMeshes(int id);
    GLint GameObjects::getDisplayListId(int id);

    void reset();
    void pausa();
    void iniciarMusica();

    Pollo* pollo;
    Fantasma* fantasma;

    std::vector<Object*> objectsTerreno;
    std::vector<Object*> objectsElementos;
    float paredInvicible;
    int paredAdelante;
    int puntajeMaximo;

    bool murioPollo; 
    
    std::vector<std::vector<objl::Mesh>> meshes;
    std::vector<GLint> displayListIds;

    double tiempo, timerMusica;
    double minZ;
    SDL_AudioDeviceID deviceId;
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;
    SDL_AudioSpec wavSpecDeath;
    Uint32 wavLengthDeath;
    Uint8* wavBufferDeath;
    SDL_AudioDeviceID deviceIdDeath;
    SDL_AudioSpec wavSpecMenu;
    Uint32 wavLengthMenu;
    Uint8* wavBufferMenu;
    SDL_AudioDeviceID deviceIdMenu;

    bool pausaa;
    double velocidadJuego;
    GLuint textId;

private:
    GameObjects();
    static GameObjects* instance;

};
