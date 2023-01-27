#include "GameObjects.h"
#include "../include/OBJ_Loader.hpp" // Para el loadMeshes
#include "Via.h"
#include "Pasto.h"

#include "FreeImage.h"

GameObjects* GameObjects::instance = NULL;

GameObjects* GameObjects::getInstance() {
    if (instance == NULL)
        instance = new GameObjects();
    return instance;
}

GameObjects::GameObjects() {};

GLint genDisplayList(std::vector<objl::Mesh> meshes, double alpha) {

    GLuint listId = glGenLists(1);
    glNewList(listId, GL_COMPILE);

    for (int cantM = 0; cantM < meshes.size(); cantM += 1) { // Itera por cada Mesh
        GLfloat ambientColor[] = { meshes.at(cantM).MeshMaterial.Ka.X, meshes.at(cantM).MeshMaterial.Ka.Y, meshes.at(cantM).MeshMaterial.Ka.Z, alpha };
        GLfloat difusseColor[] = { meshes.at(cantM).MeshMaterial.Kd.X, meshes.at(cantM).MeshMaterial.Kd.Y, meshes.at(cantM).MeshMaterial.Kd.Z, alpha };
        GLfloat specularColor[] = { meshes.at(cantM).MeshMaterial.Ks.X,  meshes.at(cantM).MeshMaterial.Ks.Y, meshes.at(cantM).MeshMaterial.Ks.Z, alpha };
        glMaterialfv(GL_FRONT, GL_DIFFUSE, difusseColor);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

        glBegin(GL_TRIANGLES); // Comienza dibujado de triangulos de la mesh
        for (unsigned int v = 0; v < meshes.at(cantM).Vertices.size(); v += 3) { // Itera por cada 3 vertices
            glTexCoord2f(meshes.at(cantM).Vertices[v].TextureCoordinate.X, meshes.at(cantM).Vertices[v].TextureCoordinate.Y);
            glNormal3f(meshes.at(cantM).Vertices[v].Normal.X, meshes.at(cantM).Vertices[v].Normal.Y, meshes.at(cantM).Vertices[v].Normal.Z);
            glVertex3f(meshes.at(cantM).Vertices[v].Position.X, meshes.at(cantM).Vertices[v].Position.Y, meshes.at(cantM).Vertices[v].Position.Z);

            glTexCoord2f(meshes.at(cantM).Vertices[v + 1].TextureCoordinate.X, meshes.at(cantM).Vertices[v + 1].TextureCoordinate.Y);
            glNormal3f(meshes.at(cantM).Vertices[v + 1].Normal.X, meshes.at(cantM).Vertices[v + 1].Normal.Y, meshes.at(cantM).Vertices[v + 1].Normal.Z);
            glVertex3f(meshes.at(cantM).Vertices[v + 1].Position.X, meshes.at(cantM).Vertices[v + 1].Position.Y, meshes.at(cantM).Vertices[v + 1].Position.Z);

            glTexCoord2f(meshes.at(cantM).Vertices[v + 2].TextureCoordinate.X, meshes.at(cantM).Vertices[v + 2].TextureCoordinate.Y);
            glNormal3f(meshes.at(cantM).Vertices[v + 2].Normal.X, meshes.at(cantM).Vertices[v + 2].Normal.Y, meshes.at(cantM).Vertices[v + 2].Normal.Z);
            glVertex3f(meshes.at(cantM).Vertices[v + 2].Position.X, meshes.at(cantM).Vertices[v + 2].Position.Y, meshes.at(cantM).Vertices[v + 2].Position.Z);

        }
        glEnd();
    }
    glEndList();

    return listId;
}

void GameObjects::loadMeshes() {
    objl::Loader loader;

    // Carga mesh de calle (pos 0)
    loader.LoadFile("../objetos/calle.obj");
    meshes.push_back(loader.LoadedMeshes);
    displayListIds.push_back(genDisplayList(loader.LoadedMeshes,1));

    std::string dir = "../objetos/calle.png";
    //CARGAR IMAGEN
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(dir.c_str());
    FIBITMAP* bitmap = FreeImage_Load(fif, dir.c_str());
    bitmap = FreeImage_ConvertTo24Bits(bitmap);
    int w = FreeImage_GetWidth(bitmap);
    int h = FreeImage_GetHeight(bitmap);
    void* datos = FreeImage_GetBits(bitmap);
    //FIN CARGAR IMAGEN
    GLuint idText;
    glGenTextures(1, &textId);
    glBindTexture(GL_TEXTURE_2D, textId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, datos);


    // Carga mesh de pollo (pos 1)
    loader.LoadFile("../objetos/pollo.obj");
	meshes.push_back(loader.LoadedMeshes);
    displayListIds.push_back(genDisplayList(loader.LoadedMeshes,1));
    // Carga mesh de auto (pos 2)
	loader.LoadFile("../objetos/sedan.obj");
	meshes.push_back(loader.LoadedMeshes);
    displayListIds.push_back(genDisplayList(loader.LoadedMeshes,1));
    // Carga mesh de arbol (pos 3)
    loader.LoadFile("../objetos/tree_blocks.obj");
    meshes.push_back(loader.LoadedMeshes);
    displayListIds.push_back(genDisplayList(loader.LoadedMeshes,1));
    // Carga mesh de via (pos 4)
    loader.LoadFile("../objetos/via.obj");
    meshes.push_back(loader.LoadedMeshes);
    displayListIds.push_back(genDisplayList(loader.LoadedMeshes,1));
    // Carga mesh de tren (pos 5)
    loader.LoadFile("../objetos/train.obj");
    meshes.push_back(loader.LoadedMeshes);
    displayListIds.push_back(genDisplayList(loader.LoadedMeshes,1));
    // Carga mesh de pasto (pos 6)
    loader.LoadFile("../objetos/grass.obj");
    meshes.push_back(loader.LoadedMeshes);
    displayListIds.push_back(genDisplayList(loader.LoadedMeshes,1));
    // Carga mesh de moneda (pos 7)
    loader.LoadFile("../objetos/moneda.obj");
    meshes.push_back(loader.LoadedMeshes);
    displayListIds.push_back(genDisplayList(loader.LoadedMeshes,1));
    // Carga mesh de moneda (pos 8)
    loader.LoadFile("../objetos/fantasma.obj");
    meshes.push_back(loader.LoadedMeshes);
    displayListIds.push_back(genDisplayList(loader.LoadedMeshes, .5));
}


void GameObjects::init(Pollo* pollo) {
    tiempo = 0;
    timerMusica = 0;
    this->pollo = pollo;
    this->fantasma = new Fantasma();
    for (int z = -1; z < 10; z++) {
        Pasto* pasto = new Pasto(vec3(0, 0, z));
        objectsTerreno.push_back(pasto);
    }

    for (int z = -20; z < -1; z++) {
        int random = rand();
        if (random % 2 == 0 || random % 3 == 0) {
            Calle* calle = new Calle(vec3(0, 0, z));
            objectsTerreno.push_back(calle);
        }
        else if (random % 5 == 0) {
            Via* via = new Via(vec3(0, 0, z));
            objectsTerreno.push_back(via);
        }
        else {
            Pasto* pasto = new Pasto(vec3(0, 0, z));
            objectsTerreno.push_back(pasto);
        }
    }
    this->paredInvicible = pollo->posicion.getZ() + 4;
    this->paredAdelante = -21;
    this->puntajeMaximo = 0;
    this->minZ = 0;
    murioPollo = false;
    this->pausaa = false;
}



std::vector<objl::Mesh> *GameObjects::getMeshes(int id) {
    return &meshes.at(id);
}

GLint GameObjects::getDisplayListId(int id) {
    return displayListIds.at(id);
}

void GameObjects::addObject(Object* obj) {
    objectsElementos.push_back(obj);
}

void GameObjects::iniciarMusica() {
    timerMusica = 0;
    SDL_Init(SDL_INIT_AUDIO);
    if (SDL_LoadWAV("../sound/mixkit-game-level-music-689.wav", &wavSpec, &wavBuffer, &wavLength) == NULL) {
        std::cout << "No se pudo cargar archivo de sonido\n";
    }
    deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    SDL_ClearQueuedAudio(deviceId);
    int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 1);

    if (SDL_LoadWAV("../sound/menu1.wav", &wavSpecMenu, &wavBufferMenu, &wavLengthMenu) == NULL) {
        std::cout << "No se pudo cargar archivo de sonido\n";
    }
    deviceIdMenu = SDL_OpenAudioDevice(NULL, 0, &wavSpecMenu, NULL, 0);
    SDL_ClearQueuedAudio(deviceIdMenu);
    success = SDL_QueueAudio(deviceIdMenu, wavBufferMenu, wavLengthMenu);
    SDL_PauseAudioDevice(deviceIdMenu, 1);

    if (SDL_LoadWAV("../sound/hurt1.wav", &wavSpecDeath, &wavBufferDeath, &wavLengthDeath) == NULL) {
        std::cout << "No se pudo cargar archivo de sonido\n";
    }
    deviceIdDeath = SDL_OpenAudioDevice(NULL, 0, &wavSpecDeath, NULL, 0);
    SDL_ClearQueuedAudio(deviceIdDeath);
    success = SDL_QueueAudio(deviceIdDeath, wavBufferDeath, wavLengthDeath);
    SDL_PauseAudioDevice(deviceIdDeath, 1);
}


void GameObjects::run(double delta, bool texture) {
    
    tiempo += delta/velocidadJuego;
    timerMusica += delta/velocidadJuego;
    if (timerMusica > 30000){
        SDL_ClearQueuedAudio(deviceId);
        SDL_QueueAudio(deviceId, wavBuffer, wavLength);
        SDL_PauseAudioDevice(deviceId, 0);
        timerMusica = 0;
    }
    puntajeMaximo -= -floor(minZ);
    minZ = minZ > pollo->getPos().getZ() ? pollo->getPos().getZ() : minZ;
    puntajeMaximo += -floor(minZ);

    // Recorrer terrenos
    auto it1 = objectsTerreno.begin();
    while (it1 != objectsTerreno.end()) {
        if ((*it1)->getPos().getZ() < paredInvicible + 10) {
            (*it1)->movimiento(delta);
            (*it1)->draw(texture);
            ++it1;
        }
        else {
            Object *aux = (*it1); //habria que usar dynamic o static cast capaz
            it1 = objectsTerreno.erase(it1);
            delete aux;      //falta hacer un delete correcto 
        }

    }

    auto it = objectsElementos.begin();

    while ( it != objectsElementos.end()) {
        if ((*it)->getPos().getZ() < paredInvicible + 10) {

            if ((*it)->borrar == false) {
                (*it)->movimiento(delta);
                if (pollo->colition((*it)) && (*it)->meshId != 3 && (*it)->meshId != 7)
                    murioPollo = true;
                if (pollo->colition((*it)) && (*it)->meshId == 7) {
                    this->puntajeMaximo = puntajeMaximo + 5;
                    Object* aux = (*it);
                    it = objectsElementos.erase(it);
                    delete aux;
                }
                (*it)->draw(texture);
                ++it;
            }
            else {
                Object *aux = (*it); //habria que usar dynamic o static cast capaz
                it = objectsElementos.erase(it);
                delete aux;      //falta hacer un delete correcto 
            }
        } else {
            Object *aux = (*it);
            it = objectsElementos.erase(it);
            delete aux;    

        }

    }

    // Muerte gallina
    float distancia = paredInvicible - this->pollo->getPos().getZ();
    if (distancia > 5) {
        this->paredInvicible = pollo->posicion.getZ() + 5;
        //std::cout << "Sigue al pollo " << distancia << "\n";
    } else if (distancia < 0) {
        murioPollo = true;
    } else {
        this->paredInvicible -= 0.0005*delta;
        //std::cout << "Se mueve lento " << distancia << "\n";
    }

    fantasma->posicion = vec3(pollo->getPos().getX(), 0, paredInvicible);
    /*
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_FRONT);*/
    fantasma->draw(texture);
    /* glCullFace(GL_FRONT_AND_BACK);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE); */

    float distAdelante= this->pollo->getPos().getZ() - paredAdelante;

    if (distAdelante<=20.f){
        int random = rand();
        if (random % 2 == 0 || random % 3 == 0) {
            Calle* calle = new Calle(vec3(0, 0, paredAdelante));
            objectsTerreno.push_back(calle);
        }
        else if (random % 5 == 0) {
            Via* via = new Via(vec3(0, 0, paredAdelante));
            objectsTerreno.push_back(via);
        }
        else {
            Pasto* pasto = new Pasto(vec3(0, 0, paredAdelante));
            objectsTerreno.push_back(pasto);
        }
        this->paredAdelante -= 1;
    }

    if (murioPollo) {

        reset();
    }
}

void GameObjects::reset() {
    auto itE = objectsElementos.begin();
    auto itT = objectsTerreno.begin();
    while (itE != objectsElementos.end()) {
        Object *aux = (*itE);
        itE = objectsElementos.erase(itE);
        delete aux;   
    }
    while (itT != objectsTerreno.end()) {
        Object *aux = (*itT);
        itT = objectsTerreno.erase(itT);
        delete aux;   
    }
    pollo->posicion = vec3(0, 0, 0);
    pollo->rot = 0;
    init(this->pollo);
       
    SDL_ClearQueuedAudio(deviceIdDeath);
    SDL_QueueAudio(deviceIdDeath, wavBufferDeath, wavLengthDeath);
    SDL_PauseAudioDevice(deviceIdDeath, 0);

    SDL_ClearQueuedAudio(deviceId);
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
    
}

void GameObjects::pausa() {
    //SDL_PauseAudioDevice(deviceId, 1);
    //SDL_CloseAudioDevice(deviceId);
    //SDL_FreeWAV(wavBuffer);
    pausaa = !pausaa;
    if (pausaa) {
        SDL_PauseAudioDevice(deviceId, 1);
        SDL_ClearQueuedAudio(deviceIdMenu);
        SDL_QueueAudio(deviceIdMenu, wavBufferMenu, wavLengthMenu);
        SDL_PauseAudioDevice(deviceIdMenu, 0);
    }
    else {
        SDL_PauseAudioDevice(deviceId, 0);
        SDL_PauseAudioDevice(deviceIdMenu, 1);
    }


}

