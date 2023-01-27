#include <Interface.h>

// Dibujado de textura

void RenderText(std::string message, SDL_Color color, int x, int y, int size, int screenw, int screenh) {
	//ENABLE2D
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0, screenw, screenh, 0, 1, -1); //left,right,bottom,top

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();


	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	const char* final = message.c_str();
	TTF_Font* font = TTF_OpenFont("../fuentes/Kenney Blocks.ttf", size);

	SDL_Surface* sFont = TTF_RenderText_Blended(font, final, color);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0); glVertex2f(x - sFont->w/2, y - sFont->h/2);
		glTexCoord2f(1, 0); glVertex2f(x + sFont->w/2, y - sFont->h/2);
		glTexCoord2f(1, 1); glVertex2f(x + sFont->w/2, y + sFont->h/2);
		glTexCoord2f(0, 1); glVertex2f(x - sFont->w/2, y + sFont->h/2);
	}
	glEnd();

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
}

/*
 *   Dibuja la interfaz
 */
void Frame::draw() {
	if (visible) {
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, textId);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glDisable(GL_LIGHTING);

		glBegin(GL_QUADS);
		// Abajo izquierda
		glTexCoord2f(uvs[0].getX(), uvs[0].getY());
		glVertex2f(pos.getX() - xSize, pos.getY() - ySize);
		// Abajo derecha
		glTexCoord2f(uvs[1].getX(), uvs[1].getY());
		glVertex2f(pos.getX() + xSize, pos.getY() - ySize);
		// Arriba derecha
		glTexCoord2f(uvs[2].getX(), uvs[2].getY());
		glVertex2f(pos.getX() + xSize, pos.getY() + ySize);
		// Arriba izquierda
		glTexCoord2f(uvs[3].getX(), uvs[3].getY());
		glVertex2f(pos.getX() - xSize, pos.getY() + ySize);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}
}

/*
	*   Se fija si el mouse lo clickeo, hace lo que tiene que hacer y retorna si fue clickeado
	*/
bool Frame::click(SDL_Event event) {
	return abs(event.motion.x - pos.getX()) < xSize && abs(screenH - event.motion.y - pos.getY()) < ySize;
}



void Window::draw() {
	if (visible) {
		glEnable(GL_TEXTURE_2D);

		Frame::draw(); // Llama a la clase del padre
		for (Frame* i : items) {
			i->draw();
		}
		glDisable(GL_TEXTURE_2D);
	}
}

Estado Window::getEstado() {
	Estado aRetornar = estado;
	estado = SIN_ESTADO;
	return aRetornar;
}


Config::Config(GLuint textId, int w, int h) {
	estado = SIN_ESTADO;
	// Seteo de UV
	uvs[0] = vec2(0, 0.166667); uvs[1] = vec2(1, 0.166667);
	uvs[2] = vec2(1, 1); uvs[3] = vec2(0, 1);

	visible = true;
	// Seteo text id
	this->textId = textId;

	this->screenW = w;
	this->screenH = h;

	// Posiciones
	this->pos = vec2(w/2, h/2);
	this->xSize = 200; // Del centro a el borde hay 200x
	this->ySize = 240; // Del centro a el borde hay 200y
	
	reanudarB = new Button(textId, vec2(screenW/2, screenH/2 + 100), screenW, screenH);
	Label * reanudarL = new Label("Reanudar", vec2(screenW/2, screenH/2 + 100), screenW, screenH);

	ajustesB = new Button(textId, vec2(screenW/2, screenH/2), screenW, screenH);
	Label * ajustesL = new Label("Ajustes", vec2(screenW/2, screenH/2), screenW, screenH);
	
	salirB = new Button(textId, vec2(screenW / 2, screenH / 2 - 100), screenW, screenH);
	Label* salirL = new Label("Salir", vec2(screenW / 2, screenH / 2 - 100), screenW, screenH);

	items.push_back(reanudarB);
	items.push_back(reanudarL);

	items.push_back(ajustesB);
	items.push_back(ajustesL);

	items.push_back(salirB);
	items.push_back(salirL);


}

bool Config::click(SDL_Event event) {
	bool click = Frame::click(event);
	if (reanudarB->click(event)) {
		estado = REANUDAR;
	}
	else if(ajustesB->click(event)){
		estado = AJUSTES;
	} else if (salirB->click(event)) {
		estado = CERRAR;
	}
	return click;
}


Ajustes::Ajustes(GLuint textId, int w, int h) {
	estado = SIN_ESTADO;
	// Seteo de UV
	uvs[0] = vec2(0, 0.166667); uvs[1] = vec2(1, 0.166667);
	uvs[2] = vec2(1, 1); uvs[3] = vec2(0, 1);

	visible = true;
	// Seteo text id
	this->textId = textId;

	this->screenW = w;
	this->screenH = h;

	// Posiciones
	this->pos = vec2(w/2, h/2);
	this->xSize = 200; // Del centro a el borde hay 200x
	this->ySize = 240; // Del centro a el borde hay 200y
	
	wireFrameB = new Button(textId, vec2(screenW / 2 - 80, screenH / 2 + 160), screenW, screenH, 70, 25);
	Label* wireFrameL = new Label("WireFrame", vec2(screenW / 2 - 80, screenH / 2 + 160), screenW, screenH, 15);

	interpoladoB = new Button(textId, vec2(screenW / 2 + 80, screenH / 2 + 160), screenW, screenH, 70, 25);
	Label* interpoladoL = new Label("Interpolado", vec2(screenW / 2 + 80, screenH / 2 + 160), screenW, screenH, 15);

	texturaB = new Button(textId, vec2(screenW / 2 + 80, screenH / 2 + 60), screenW, screenH, 70, 25);
	Label* texturaL = new Label("Textura", vec2(screenW / 2 + 80, screenH / 2 + 60), screenW, screenH, 15);

	luzB = new Button(textId, vec2(screenW / 2 - 80, screenH / 2 + 60), screenW, screenH, 70, 25);
	Label* luzL = new Label("Luz", vec2(screenW / 2 - 80, screenH / 2 + 60), screenW, screenH, 15);

	menosVelocidadB = new Button(textId, vec2(screenW / 2 - 85, screenH / 2 - 30), screenW, screenH, 20, 25);
	masVelocidadB = new Button(textId, vec2(screenW / 2 + 85, screenH / 2 - 30), screenW, screenH, 20, 25);
	velocidadB = new Button(textId, vec2(screenW / 2, screenH / 2 - 30), screenW, screenH, 70, 25);
	Label* velocidadL = new Label("Velocidad", vec2(screenW / 2 , screenH / 2 - 30), screenW, screenH, 15);
	Label* flechaMenosL = new Label("<", vec2(screenW / 2 - 85, screenH / 2-25), screenW, screenH, 25);
	Label* flechaMasL = new Label(">", vec2(screenW / 2 + 85, screenH / 2 - 25), screenW, screenH, 25);

	regresarB = new Button(textId, vec2(screenW / 2, screenH / 2 - 150), screenW, screenH);
	Label* regresarL = new Label("Regresar", vec2(screenW / 2, screenH / 2 - 150), screenW, screenH);
	

	items.push_back(wireFrameB);
	items.push_back(wireFrameL);

	items.push_back(interpoladoB);
	items.push_back(interpoladoL);

	items.push_back(texturaB);
	items.push_back(texturaL);

	items.push_back(luzB);
	items.push_back(luzL);

	items.push_back(masVelocidadB);
	items.push_back(menosVelocidadB);
	items.push_back(velocidadB);
	items.push_back(velocidadL);
	items.push_back(flechaMenosL);
	items.push_back(flechaMasL);

	items.push_back(regresarB);
	items.push_back(regresarL);
}

bool Ajustes::click(SDL_Event event) {
	bool click = Frame::click(event);

	if (wireFrameB->click(event)) {
		estado = WIREFRAME;
		if (wireFrameB->color[0] == 1) {
			wireFrameB->color[0] = .8; wireFrameB->color[1] = .8; wireFrameB->color[2] = .8;
		}
		else {
			wireFrameB->color[0] = 1; wireFrameB->color[1] = 1; wireFrameB->color[2] = 1;
		}
	}

	if (interpoladoB->click(event)) {
		estado = INTERPOLADO_FACETEADO;
		if (interpoladoB->color[0] == 1) {
			interpoladoB->color[0] = .8; interpoladoB->color[1] = .8; interpoladoB->color[2] = .8;
		}
		else {
			interpoladoB->color[0] = 1; interpoladoB->color[1] = 1; interpoladoB->color[2] = 1;
		}
	}
	if (texturaB->click(event)) {
		estado = TEXTURA;
		if (texturaB->color[0] == 1) {
			texturaB->color[0] = .8; texturaB->color[1] = .8; texturaB->color[2] = .8;
		}
		else {
			texturaB->color[0] = 1; texturaB->color[1] = 1; texturaB->color[2] = 1;
		}
	}
	if (luzB->click(event)) {
		estado = CAMBIARLUZ;
	}

	if (masVelocidadB->click(event)) {
		estado = MASVELOCIDAD;
	}

	if (menosVelocidadB->click(event)) {
		estado = MENOSVELOCIDAD;
	}

	if (regresarB->click(event)) {
		estado = PAUSA;
	}

	return click;
}


Inicio::Inicio(GLuint textId, int screenW, int screenH) {
	estado = SIN_ESTADO;
	// Seteo de UV
	uvs[0] = vec2(0, 0.166667); uvs[1] = vec2(1, 0.166667);
	uvs[2] = vec2(1, 1); uvs[3] = vec2(0, 1);

	visible = true;
	// Seteo text id
	this->textId = textId;

	this->screenW = screenW;
	this->screenH = screenH;

	// Posiciones
	this->pos = vec2(screenW/2, screenH/2);
	this->xSize = 200; // Del centro a el borde hay 200x
	this->ySize = 240; // Del centro a el borde hay 200y
	
	SDL_Color col = { 0, 0, 0 };
	Label* JuegoL = new Label("Crossy Road", vec2(screenW / 2, screenH / 2 + 100), screenW, screenH, 40, col);

	inicioB = new Button(textId, vec2(screenW / 2, screenH / 2 ), screenW, screenH);
	Label* inicioL = new Label("Inicio", vec2(screenW / 2, screenH / 2), screenW, screenH);

	salirB = new Button(textId, vec2(screenW / 2, screenH / 2 - 100), screenW, screenH);
	Label* salirL = new Label("Salir", vec2(screenW / 2, screenH / 2 - 100), screenW, screenH);

	items.push_back(JuegoL);

	items.push_back(inicioB);
	items.push_back(inicioL);

	items.push_back(salirB);
	items.push_back(salirL);
}

bool Inicio::click(SDL_Event event) {
	bool click = Frame::click(event);
	if (inicioB->click(event)) {
		estado = REANUDAR;
	}
	if (salirB->click(event)) {
		estado = CERRAR;
	}
	return click;
}


Button::Button(GLuint textId, vec2 pos, int screenW, int screenH, double sizeX, double sizeY) {
	uvs[0] = vec2(0, 0); uvs[1] = vec2(0.468, 0);
	uvs[2] = vec2(0.468, 0.167); uvs[3] = vec2(0, 0.167);

	this->screenW = screenW;
	this->screenH = screenH;

	color[0] = 1;
	color[1] = 1;
	color[2] = 1;

	this->pos = pos;
	visible = true;
	// Seteo text id
	this->textId = textId;

	this->xSize = sizeX;
	this->ySize = sizeY;
}

Button::Button(GLuint textId, vec2 pos, int screenW, int screenH) {
	uvs[0] = vec2(0, 0); uvs[1] = vec2(0.468, 0);
	uvs[2] = vec2(0.468, 0.167); uvs[3] = vec2(0, 0.167);

	this->screenW = screenW;
	this->screenH = screenH;

	color[0] = 1;
	color[1] = 1;
	color[2] = 1;

	this->pos = pos;
	visible = true;
	// Seteo text id
	this->textId = textId;

	this->xSize = 94 * .8; // Del centro a el borde hay 200x
	this->ySize = 40 * .8; // Del centro a el borde hay 200y
}

void Button::draw() {
	glColor3fv(this->color);
	Frame::draw();
	GLfloat blanco[3] = { 1,1,1 };
	glColor3fv(blanco);
}

void Button::setColor(GLfloat color[3]) {
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
}


bool Button::click(SDL_Event event) {
	bool click = Frame::click(event);
	return click;
}

Label::Label(std::string texto, vec2 pos, int screenW, int screenH) {
	uvs[0] = vec2(0, 0); uvs[1] = vec2(1, 0);
	uvs[2] = vec2(1, 1); uvs[3] = vec2(0, 1);
	this->texto = texto;
	this->color = { 250, 250, 250 };
	
	this->screenW = screenW;
	this->screenH = screenH;
	this->pos = pos;
	this->size = 20;
}

Label::Label(std::string texto, vec2 pos, int screenW, int screenH, int size) {
	uvs[0] = vec2(0, 0); uvs[1] = vec2(1, 0);
	uvs[2] = vec2(1, 1); uvs[3] = vec2(0, 1);
	this->texto = texto;
	this->color = { 250, 250, 250 };

	this->screenW = screenW;
	this->screenH = screenH;
	this->pos = pos;
	this->size = size;
}

Label::Label(std::string texto, vec2 pos, int screenW, int screenH, int size, SDL_Color color){
	uvs[0] = vec2(0, 0); uvs[1] = vec2(1, 0);
	uvs[2] = vec2(1, 1); uvs[3] = vec2(0, 1);
	this->texto = texto;
	this->color = color;

	this->screenW = screenW;
	this->screenH = screenH;
	this->pos = pos;
	this->size = size;
}

bool Label::click(SDL_Event event) {
	return Frame::click(event);
}

void Label::draw() {
	RenderText(this->texto, this->color, this->pos.getX(), screenH - this->pos.getY(), this->size, screenW, screenH);
}

Interfaz::Interfaz(int screenW, int screenH) {
	/**
		Cargado de textura
	*/
	std::string dir = "../objetos/ventana.png";
	//CARGAR IMAGEN
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(dir.c_str());
	FIBITMAP* bitmap = FreeImage_Load(fif, dir.c_str());
	bitmap = FreeImage_ConvertTo24Bits(bitmap);
	int w = FreeImage_GetWidth(bitmap);
	int h = FreeImage_GetHeight(bitmap);
	void* datos = FreeImage_GetBits(bitmap);
	//FIN CARGAR IMAGEN
	glGenTextures(1, &textId);
	glBindTexture(GL_TEXTURE_2D, textId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, datos);

	this->screenW = screenW;
	this->screenH = screenH;
	// Cargo ventana
	this->inicio = new Inicio(textId, screenW, screenH);
	this->pausa = new Config(textId, screenW, screenH);
	this->ajustes = new Ajustes(textId, screenW, screenH);
	this->activa = this->inicio;
}


Estado Interfaz::run() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1200, 0, 720);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	activa->draw();
	Estado estado = activa->getEstado();
	if (estado == AJUSTES) {
		activa = ajustes;
	}
	else if (estado == PAUSA) {
		activa = pausa;
	}
	else if (estado == REANUDAR) {
		activa = pausa;
	}
	return estado;
}

void Interfaz::click(SDL_Event event) {
	activa->click(event);
}

