#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"

IMPORT_MAP(hud);//HUD
IMPORT_MAP(M08map);

/* extern uint8_t winPoints;
extern uint8_t failPoints; */
extern uint8_t frame;
extern uint8_t countdown;
extern uint8_t difficult;

void UpdateHudTime() BANKED;

UBYTE createSprite;

void UpdateM08Map(){
	UpdateMapTile(0, 7,6, 21, 0, 0);
	UpdateMapTile(0, 8,6, 22, 0, 0);
	UpdateMapTile(0, 9,6, 22, 0, 0);
	UpdateMapTile(0, 10,6, 22, 0, 0);
	UpdateMapTile(0, 11,6, 22, 0, 0);
	UpdateMapTile(0, 12,6, 23, 0, 0);

	UpdateMapTile(0, 7,7, 28, 0, 0);
	UpdateMapTile(0, 8,7, 0, 0, 0);
	UpdateMapTile(0, 9,7, 0, 0, 0);
	UpdateMapTile(0, 10,7, 0, 0, 0);
	UpdateMapTile(0, 11,7, 0, 0, 0);
	UpdateMapTile(0, 12,7, 24, 0, 0);

	UpdateMapTile(0, 7,8, 28, 0, 0);
	UpdateMapTile(0, 8,8, 0, 0, 0);
	UpdateMapTile(0, 9,8, 0, 0, 0);
	UpdateMapTile(0, 10,8, 0, 0, 0);
	UpdateMapTile(0, 11,8, 0, 0, 0);
	UpdateMapTile(0, 12,8, 24, 0, 0);

	UpdateMapTile(0, 7,9, 28, 0, 0);
	UpdateMapTile(0, 8,9, 0, 0, 0);
	UpdateMapTile(0, 9,9, 0, 0, 0);
	UpdateMapTile(0, 10,9, 0, 0, 0);
	UpdateMapTile(0, 11,9, 0, 0, 0);
	UpdateMapTile(0, 12,9, 24, 0, 0);

	UpdateMapTile(0, 7,10, 28, 0, 0);
	UpdateMapTile(0, 8,10, 0, 0, 0);
	UpdateMapTile(0, 9,10, 0, 0, 0);
	UpdateMapTile(0, 10,10, 0, 0, 0);
	UpdateMapTile(0, 11,10, 0, 0, 0);
	UpdateMapTile(0, 12,10, 24, 0, 0);

	UpdateMapTile(0, 7,11, 25, 0, 0);
	UpdateMapTile(0, 8,11, 26, 0, 0);
	UpdateMapTile(0, 9,11, 26, 0, 0);
	UpdateMapTile(0, 10,11, 26, 0, 0);
	UpdateMapTile(0, 11,11, 26, 0, 0);
	UpdateMapTile(0, 12,11, 27, 0, 0);
}


void START() {
	frame = 60;
	countdown = 4;
	createSprite = 0;
	
	//Iniciar Hud del tiempo
	INIT_HUD(hud);
	UpdateHudTime();
	//Iniciar mapa
	InitScroll(BANK(M08map), &M08map, 0, 0);
}

void UPDATE() {
	frame--;
	if (frame <= 0 && (countdown > 0)){
		frame=60;
		countdown--;
		UpdateHudTime();
		//SFX Contador de tiempo
		if (countdown <=3 && countdown!=0){
			PlayFx(CHANNEL_1, 1, 0x44, 0xA1, 0x4F, 0xBE, 0xC6);
		} else if (countdown == 0){
			PlayFx(CHANNEL_1, 1, 0x45, 0xA1, 0x4F, 0xBE, 0xC6);
		}
	}

	//Cuando queden X segundos, crear el sprite
	if (countdown == (3-difficult) && createSprite == 0){
		createSprite = 1;
		//Transformar el fondo
		UpdateM08Map();

		//Crear el sprite
		SpriteManagerAdd(M08SpriteKeys, 64, 56);
	}
}
