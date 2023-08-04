#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"

IMPORT_MAP(hud);//HUD
IMPORT_MAP(M02map);


/* extern uint8_t winPoints;
extern uint8_t failPoints; */
extern uint8_t frame;
extern uint8_t countdown;
void UpdateHudTime() BANKED;
void Victory() BANKED;
//void Fail() BANKED;

uint8_t M02collision_tiles[] = {3,4,0};

//Para los vehiculos
uint8_t trackX[3] = {66,74,82};

uint8_t chooseRandomTrack(){
    int8_t rnd = rand() % 3;
    uint8_t returned = trackX[rnd];
    return returned;
}

uint8_t bkgE = 1;

/* void UpdateHudTime() {
	for (uint8_t i = 0; i < 18; ++i){//Comprobar ancho del hud
		UPDATE_HUD_TILE(1+i, 0, i < countdown ? 127 : 0);
	}
		
} */

//extern void UpdateHudTime();

void START() {
	//Iniciar Hud del tiempo
	INIT_HUD(hud);
	UpdateHudTime();

	frame = 60;
	countdown = 8;

	//Iniciar minijuego 2
	SpriteManagerAdd(M02SpritePlayer,73,120);
	SpriteManagerAdd(M02SpriteVehicleA,82,0);
	SpriteManagerAdd(M02SpriteVehicleB,66,-32);
	//Elementos de la carretera para que paresca que el auto avanza
	SpriteManagerAdd(M02SpriteBackground,20,120);
	SpriteManagerAdd(M02SpriteBackground,40,75);
	SpriteManagerAdd(M02SpriteBackground,98,60);
	SpriteManagerAdd(M02SpriteBackground,114,0);
	InitScroll(BANK(M02map), &M02map, M02collision_tiles, 0);
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

	//Si el auto choca fallara y cambiara el estado automaticamente (dentro de M02SpritePlayer)
	if (countdown <= 0){
		//winPoints++;
		Victory();
		SetState(StateMidGame);
	}
}
