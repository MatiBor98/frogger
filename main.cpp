#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include "include/OBJ_Loader.hpp"
#include "Pollo.h"
#include "vec3d.h"
#include "GameObjects.h"
#include "Camara.h"
#include "Object.h"
#include "audio.h"
#include "Interface.h"
#define PI 3.141592


#include <SDL_ttf.h>

using namespace std;
using namespace objl;

SDL_Rect RenderText(TTF_Font* font, std::string message, SDL_Color color, int x, int y, int size, int screenw, int screenh) {
	//ENABLE2D
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0, screenw, screenh, 0, 1, -1); //left,right,bottom,top

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	const char* final = message.c_str();
	font = TTF_OpenFont("../fuentes/Kenney Blocks.ttf", size);

	SDL_Surface* sFont = TTF_RenderText_Blended(font, final, color);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0); glVertex2f(x, y);
		glTexCoord2f(1, 0); glVertex2f(x + sFont->w, y);
		glTexCoord2f(1, 1); glVertex2f(x + sFont->w, y + sFont->h);
		glTexCoord2f(0, 1); glVertex2f(x, y + sFont->h);
	}
	glEnd();
	SDL_Rect pos;
	pos.w = sFont->clip_rect.w;
	pos.h = sFont->clip_rect.h;
	pos.x = sFont->clip_rect.w / 2;
	pos.y = sFont->clip_rect.h;

	//DISABLE 2D
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDeleteTextures(1, &texture);

	SDL_FreeSurface(sFont);
	TTF_CloseFont(font);

	return pos;

}


void setLuz(int tipo) {
	switch (tipo) {
	case 0: {
		GLfloat light0pos0[4] = { 5 , 5, -5, 0 };
		GLfloat light0col0[4] = { 1, 1, 1, 1 };
		GLfloat light0amb0[4] = { 0, 0, 0, 1 };
		GLfloat light0spe0[4] = { 0.5, 0.5, 0.5, 1 };
		glLightfv(GL_LIGHT0, GL_POSITION, light0pos0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0col0);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0spe0);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0amb0);
		glClearColor(.5, .8, .9, 1);
		break;
	}
	case 1: {
		GLfloat light0pos1[4] = { 1 , 1,  1, 0 };
		GLfloat light0col1[4] = { 1, 1, .7, 1 };
		GLfloat light0amb1[4] = { 0, 0, 0, 1 };
		GLfloat light0spe1[4] = { 1, 1, 1, 1 };
		glLightfv(GL_LIGHT0, GL_POSITION, light0pos1);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0col1);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0spe1);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0amb1);
	}
	case 2: {
		GLfloat light0pos2[4] = { 0 , 1, 1, 0 };
		GLfloat light0col2[4] = { .9, .9, 1, 1 };
		GLfloat light0amb2[4] = { 0, .3, 0, 1 };
		GLfloat light0spe2[4] = { 0, 0, 0, 1 };
		glLightfv(GL_LIGHT0, GL_POSITION, light0pos2);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0col2);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0spe2);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0amb2);
		break;
	}
	case 3: {
		GLfloat light0pos3[4] = { 0 , 1, 0, 0 };
		GLfloat light0col3[4] = { 1, 0, 1, 1 };
		GLfloat light0amb3[4] = { 0, 0, .3, 1 };
		GLfloat light0spe3[4] = { 0.5, 0.5, 0.5, 1 };
		glLightfv(GL_LIGHT0, GL_POSITION, light0pos3);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0col3);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0spe3);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0amb3);
		break;
	}
	case 4: {
		GLfloat light0pos4[4] = { -1 , 1, 1, 0 };
		GLfloat light0col4[4] = { 1, .8, .8, 1 };
		GLfloat light0amb4[4] = { 0, .2, .2, 1 };
		GLfloat light0spe4[4] = { 0.5, 0.5, 0.5, 1 };
		glLightfv(GL_LIGHT0, GL_POSITION, light0pos4);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0col4);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0spe4);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0amb4);
		break;
	}
	case 5: {
		GLfloat light0pos5[4] = { 1 , 1, 0, 0 };
		GLfloat light0col5[4] = { 1, 1, .9, 1 };
		GLfloat light0amb5[4] = { 0, 0, 0, 1 };
		GLfloat light0spe5[4] = { 0.5, 0.5, 0.5, 1 };
		glLightfv(GL_LIGHT0, GL_POSITION, light0pos5);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0col5);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0spe5);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0amb5);
		break;
	}
	case 6: {
		GLfloat light0pos6[4] = { 5 , 5, -5, 0 };
		GLfloat light0col6[4] = { 1, 0, 1, 1 };
		GLfloat light0amb6[4] = { 0, 0, 0, 1 };
		GLfloat light0spe6[4] = { 0.5, 0.5, 0.5, 1 };
		glLightfv(GL_LIGHT0, GL_POSITION, light0pos6);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0col6);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0spe6);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0amb6);
		break;
	}
	case 7: {
		GLfloat light0pos7[4] = { -1, .1, 1, 0 };
		GLfloat light0col7[4] = { 1, 1, 1, 1 };
		GLfloat light0amb7[4] = { 0, 0, 0, 1 };
		GLfloat light0spe7[4] = { 0.5, 0.5, 0.5, 1 };
		glLightfv(GL_LIGHT0, GL_POSITION, light0pos7);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0col7);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0spe7);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0amb7);
		break;
	}
	case 8: {
		GLfloat light0pos8[4] = { 0 , -1, 0, 0 };
		GLfloat light0col8[4] = { 1, 1, 1, 1 };
		GLfloat light0amb8[4] = { .2, .2, .2, 1 };
		GLfloat light0spe8[4] = { 0.5, 0.5, 0.5, 1 };
		glLightfv(GL_LIGHT0, GL_POSITION, light0pos8);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0col8);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0spe8);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0amb8);
		break;
	}
	case 9: {
		GLfloat light0pos9[4] = { 0 , 1, 1, 0 };
		GLfloat light0col9[4] = { .5, 0, 1, 1 };
		GLfloat light0amb9[4] = { 0, 0, .3, 1 };
		GLfloat light0spe9[4] = { 0.5, 0.5, 0.5, 1 };
		glLightfv(GL_LIGHT0, GL_POSITION, light0pos9);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0col9);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0spe9);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0amb9);
		break;
	  }
	}
}

int main(int argc, char* argv[]) {
	int xMouse;
	int yMouse;
	bool texture = false;
	bool wireframe = false;
	bool interpolado = false;
	unsigned seed = time(0);
	srand(seed);
	//INICIALIZACION
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}

	SDL_Window* win = SDL_CreateWindow("ICG-UdelaR",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1200, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GLContext context = SDL_GL_CreateContext(win);

	TTF_Init();
	TTF_Font* font = TTF_OpenFont("../fuentes/Kenney Blocks.ttf", 25);
	SDL_Color color = { 255, 255, 255 };
	/*
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font,
		"Welcome to Gigi Labs", color);
	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);*/
	int w, h;
	SDL_GetWindowSize(win, &w, &h);

	glMatrixMode(GL_PROJECTION);


	glClearColor(.5, .8, .9, 1);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);

	bool fin = false;
	bool rotate = false;
	bool scale = false;

	int tipoLuz = 0;
	double incremento = 0;

	SDL_Event evento;
	GLuint i = 0;

	Interfaz* interfaz = new Interfaz(w, h);

	GameObjects* gameObjects = GameObjects::getInstance();
	gameObjects->loadMeshes();
	Pollo* pollo = new Pollo();

	gameObjects->init(pollo);



	Camara cam(pollo, vec3(0, 1, 0), 1200, 720);
	camMode modo = ORTHO;


	// Delta data
	double delta = 0;
	gameObjects->velocidadJuego = 1;
	Uint64 now = SDL_GetPerformanceCounter();
	Uint64 last;

	Estado estadoInterface = SIN_ESTADO;

	bool pausa = true;
	gameObjects->iniciarMusica();

	bool keyUpPressed = false, keyDownPressed = false, keyRightPressed = false, keyLeftPressed = false;

	double x = 0;
	gameObjects->pausa();
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		last = now;
		now = SDL_GetPerformanceCounter();

		delta = ((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());

		delta = delta* gameObjects->velocidadJuego;

		if (pausa) delta = 0;

		cam.update();

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		setLuz(tipoLuz);

		if (wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		if (interpolado) {
			glShadeModel(GL_SMOOTH);
		}
		else {
			glShadeModel(GL_FLAT);
		}
		
	

		GameObjects::getInstance()->run(delta, texture);
		/*
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		*/
	
		glDisable(GL_TEXTURE_2D);
		pollo->draw(texture);
		glEnable(GL_TEXTURE_2D);
		/*
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		*/


		
		glDisable(GL_LIGHTING);



		while (SDL_PollEvent(&evento)) {
			float angleChange;
			switch (evento.type) {
			case SDL_MOUSEMOTION:
				if (modo == PERSPECTIVE && !pausa) {
					angleChange = evento.motion.xrel;
					pollo->rot -= angleChange;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
				if (pausa)
					interfaz->click(evento);
				break;
			case SDL_QUIT:
				fin = true;
				break;
			case SDL_KEYDOWN:
				switch (evento.key.keysym.sym) {
				case SDLK_ESCAPE:
					fin = true;
					break;
				case SDLK_UP:
					keyUpPressed = true;
					break;
				case SDLK_DOWN:
					keyDownPressed = true;
					break;
				case SDLK_RIGHT:
					keyRightPressed = true;
					break;
				case SDLK_LEFT:
					keyLeftPressed = true;
					break;
				case SDLK_v:
					if (modo == ORTHO) {
						modo = PERSPECTIVE;
					}
					else {
						modo = ORTHO;
					}
					cam.setModo(modo);
					break;
				case SDLK_p:
					pausa = !pausa;
					SDL_ShowCursor(pausa);
					gameObjects->pausa();
					interfaz->activa = interfaz->pausa;
					break;
				case SDLK_q:
					fin = true;
					break;
				case SDLK_F11:
					Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
					bool IsFullscreen = SDL_GetWindowFlags(win) & FullscreenFlag;
					SDL_SetWindowFullscreen(win, IsFullscreen ? 0 : FullscreenFlag);
					SDL_ShowCursor(IsFullscreen);
					break;

				}
				break;
			case SDL_KEYUP:
				switch (evento.key.keysym.sym) {
				case SDLK_UP:
					keyUpPressed = false;
					break;
				case SDLK_DOWN:
					keyDownPressed = false;
					break;
				case SDLK_RIGHT:
					keyRightPressed = false;
					break;
				case SDLK_LEFT:
					keyLeftPressed = false;
					break;
				}
			}
		}

		if (keyUpPressed && !pausa) {
			if (modo == ORTHO) {
				pollo->setRot(0);
				pollo->movZ(-3 * delta / 1000);
				for (Object* obj : gameObjects->objectsElementos) {
					if (obj->meshId == 3 && pollo->colition(obj)) // Arbol
						pollo->movZ(3 * delta / 1000);
				}
			}
			else {
				pollo->movZ(-3 * cos(pollo->rot * PI / 180.f) * delta / 1000);
				pollo->movX(-3 * sin(pollo->rot * PI / 180.f) * delta / 1000);
				if (abs(pollo->getPos().getX()) > 4) {
					pollo->movZ(3 * cos(pollo->rot * PI / 180.f) * delta / 1000);
					pollo->movX(3 * sin(pollo->rot * PI / 180.f) * delta / 1000);
				}
				for (Object* obj : gameObjects->objectsElementos) {
					if (obj->meshId == 3 && pollo->colition(obj)) { // Arbol
						pollo->movZ(3 * cos(pollo->rot * PI / 180.f) * delta / 1000);
						pollo->movX(3 * sin(pollo->rot * PI / 180.f) * delta / 1000);
					}
				}
			}
		}
		else if (keyDownPressed && !pausa) {
			if (modo == ORTHO) {
				pollo->setRot(180);
				pollo->movZ(3 * delta / 1000);
				for (Object* obj : gameObjects->objectsElementos) {
					if (obj->meshId == 3 && pollo->colition(obj)) // Arbol
						pollo->movZ(-3 * delta / 1000);
				}
			}
			else if (abs(pollo->getPos().getX()) < 4) {
				pollo->movZ(3 * cos(pollo->rot * PI / 180.f) * delta / 1000);
				pollo->movX(3 * sin(pollo->rot * PI / 180.f) * delta / 1000);
				if (abs(pollo->getPos().getX()) > 4) {
					pollo->movZ(-3 * cos(pollo->rot * PI / 180.f) * delta / 1000);
					pollo->movX(-3 * sin(pollo->rot * PI / 180.f) * delta / 1000);
				}
				for (Object* obj : gameObjects->objectsElementos) {
					if (obj->meshId == 3 && pollo->colition(obj)) {// Arbol
						pollo->movZ(-3 * cos(pollo->rot * PI / 180.f) * delta / 1000);
						pollo->movX(-3 * sin(pollo->rot * PI / 180.f) * delta / 1000);
					}
				}
			}
		}
		else if (keyRightPressed && !pausa) {
			if (modo == ORTHO) {
				pollo->setRot(270);
				if (pollo->getPos().getX() < 4) {
					pollo->movX(3 * delta / 1000);
					for (Object* obj : gameObjects->objectsElementos) {
						if (obj->meshId == 3 && pollo->colition(obj)) // Arbol
							pollo->movX(-3 * delta / 1000);
					}
				}
			}
			else if (abs(pollo->getPos().getX()) < 4) {
				pollo->movZ(-3 * sin(pollo->rot * PI / 180.f) * delta / 1000);
				pollo->movX(3 * cos(pollo->rot * PI / 180.f) * delta / 1000);
				if (abs(pollo->getPos().getX()) > 4) {
					pollo->movZ(3 * sin(pollo->rot * PI / 180.f) * delta / 1000);
					pollo->movX(-3 * cos(pollo->rot * PI / 180.f) * delta / 1000);
				}
				for (Object* obj : gameObjects->objectsElementos) {
					if ((obj->meshId == 3 && pollo->colition(obj))) {// Arbol
						pollo->movZ(3 * sin(pollo->rot * PI / 180.f) * delta / 1000);
						pollo->movX(-3 * cos(pollo->rot * PI / 180.f) * delta / 1000);
					}
				}

			}
		}
		else if (keyLeftPressed && !pausa) {
			if (modo == ORTHO) {
				pollo->setRot(90);
				if (pollo->getPos().getX() > -4) {
					pollo->movX(-3 * delta / 1000);
					for (Object* obj : gameObjects->objectsElementos) {
						if (obj->meshId == 3 && pollo->colition(obj)) // Arbol
							pollo->movX(3 * delta / 1000);
					}
				}
			}
			else if (abs(pollo->getPos().getX()) < 4) {
				pollo->movZ(3 * sin(pollo->rot * PI / 180.f) * delta / 1000);
				pollo->movX(-3 * cos(pollo->rot * PI / 180.f) * delta / 1000);
				if (abs(pollo->getPos().getX()) > 4) {
					pollo->movZ(-3 * sin(pollo->rot * PI / 180.f) * delta / 1000);
					pollo->movX(3 * cos(pollo->rot * PI / 180.f) * delta / 1000);
				}
				for (Object* obj : gameObjects->objectsElementos) {
					if ((obj->meshId == 3 && pollo->colition(obj))) {// Arbol
						pollo->movZ(-3 * sin(pollo->rot * PI / 180.f) * delta / 1000);
						pollo->movX(3 * cos(pollo->rot * PI / 180.f) * delta / 1000);
					}
				}
			}
		}

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (pausa) {
			estadoInterface = interfaz->run();
			if (estadoInterface == REANUDAR) {
				pausa = !pausa;
				gameObjects->pausa();
			}
			else if (estadoInterface == CERRAR) {
				fin = true;
			}
			else if (estadoInterface == WIREFRAME) {
				wireframe = !wireframe;
			}
			else if (estadoInterface == INTERPOLADO_FACETEADO) {
				interpolado = !interpolado;
			}
			else if (estadoInterface == TEXTURA) {
				texture = !texture;
			}
			else if (estadoInterface == CAMBIARLUZ) {
				tipoLuz = (tipoLuz + 1)%10;
			}
			else if (estadoInterface == MASVELOCIDAD) {
				if(gameObjects->velocidadJuego<3)
					gameObjects->velocidadJuego += 0.1;
			}
			else if (estadoInterface == MENOSVELOCIDAD) {
				if(gameObjects->velocidadJuego>0.1)
					gameObjects->velocidadJuego -= 0.1;
			}
		}
		
		RenderText(font, "Puntaje: " + std::to_string(gameObjects->puntajeMaximo), color, 0, 0, 20, 1200, 720);
		RenderText(font, "Tiempo: " + std::to_string((int)gameObjects->tiempo/1000), color, 720, 0, 20, 1200, 720);
		cam.modoUpdate();

		SDL_GL_SwapWindow(win);
		/*
		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
		SDL_Rect dstrect = { 0, 0, texW, texH };
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderPresent(renderer);*/
	} while (!fin);
	//FIN LOOP PRINCIPAL
	// LIMPIEZA
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	//SDL_DestroyTexture(texture);
	//SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

