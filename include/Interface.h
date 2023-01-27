#pragma once

#include <vec3d.h>
#include <vector>
#include <stack>
#include <SDL.h>
#include <SDL_opengl.h>
#include <FreeImage.h>
#include <gl/glu.h>
#include <SDL_ttf.h>

enum Estado {
	PAUSA,
	CERRAR,
	AJUSTES,
	REANUDAR,
	SIN_ESTADO,
	WIREFRAME,
	TEXTURA,
	REGRESAR,
	INTERPOLADO_FACETEADO,
	CAMBIARLUZ,
	MASVELOCIDAD,
	MENOSVELOCIDAD,
};

/**
	Un boton es un frame, una ventana es un frame, un checkbox es un frame
	Todo lo que sea interfaz es un frame
*/
class Frame {
public:
	vec2 pos;
	double xSize, ySize;
	GLuint textId; // Id de textura
	vec2 uvs[4]; // Coordenadas uv de la textura

	bool visible;

	int screenW, screenH;

	/*
	 *   Dibuja la interfaz
	 */
	virtual void draw();

	/*
	 *   Se fija si el mouse lo clickeo, hace lo que tiene que hacer y retorna si fue clickeado
	 */
	virtual bool click(SDL_Event event) = 0;
};

class Button : public Frame {
public:
	Button(GLuint textId, vec2 pos, int screenW, int screenH, double sizeX, double sizeY);
	Button(GLuint textId, vec2 pos, int screenW, int screenH);
	bool click(SDL_Event event);
	void draw() override;
	void setColor(GLfloat color[3]);
	GLfloat color[3];
};

class Label : public Frame {
public:
	Label(std::string texto, vec2 pos, int screenW, int screenH);
	Label(std::string texto, vec2 pos, int screenW, int screenH, int size);
	Label(std::string texto, vec2 pos, int screenW, int screenH, int size, SDL_Color color);
private:
	std::string texto;
	bool click(SDL_Event event);
	void draw() override;
	SDL_Color color;
	int size;
};


class Window : public Frame {
public:
	/**
		Elementos internos de la ventana (Botones, checkboxes, etc)
	*/
	std::vector<Frame*> items;

	virtual void draw() override;
	virtual bool click(SDL_Event event) = 0;

	Estado estado;
	Estado getEstado();
};

/**
	Ventana de configuraciones
*/
class Config : public Window {
public:
	Config(GLuint textId, int screenW, int screenH);
	bool click(SDL_Event event);
	Button *reanudarB, *ajustesB, *salirB;
};

class Ajustes : public Window {
public:
	Ajustes(GLuint textId, int screenW, int screenH);
	bool click(SDL_Event event);
	Button *wireFrameB, *texturaB, *regresarB, *interpoladoB, *luzB, *masVelocidadB, *menosVelocidadB, *velocidadB;
};

class Inicio : public Window {
public:
	Inicio(GLuint textId, int screenW, int screenH);
	bool click(SDL_Event event) override;
	Button *inicioB, *salirB;
};


class Interfaz {
public:
	Interfaz(int screenW, int screenH);

	Estado run();

	void click(SDL_Event event);

	GLuint textId;

	int screenW, screenH;

	Window* activa, * pausa, * ajustes, * perder, *inicio;
};