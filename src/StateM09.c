#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"

IMPORT_MAP(M09map);

extern uint8_t frame;
extern uint8_t countdown;

void START() {
	frame = 60;
	countdown = 4;

	SpriteManagerAdd(M09SpritePlayer,64,88);
	SpriteManagerAdd(M09SpriteOvni,64,16);

	HIDE_WIN;//Esconder el HUD
	//Iniciar mapa
	InitScroll(BANK(M09map), &M09map, 0, 0);
}

void UPDATE() {
}
