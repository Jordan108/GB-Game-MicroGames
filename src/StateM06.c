#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

IMPORT_MAP(M06map);

/* extern uint8_t winPoints;
extern uint8_t failPoints; */


void START() {

	//Establecer mira del jugador
	SpriteManagerAdd(M06SpritePlayer, 74,47);
	SpriteManagerAdd(M06SpriteOvni, 170,47-4);


	HIDE_WIN;//Esconder el HUD
	//Iniciar mapa
	InitScroll(BANK(M06map), &M06map, 0, 0);


	
}

void UPDATE() {
}
