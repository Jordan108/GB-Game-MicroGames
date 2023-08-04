#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"

IMPORT_MAP(hud);//HUD
IMPORT_MAP(M05map);

void Victory() BANKED;
void Fail() BANKED;
extern uint8_t frame;
extern uint8_t countdown;
void UpdateHudTime() BANKED;

uint8_t enemieCount;

void START() {
	frame = 60;
	countdown = 4;

	enemieCount = 4;

	//Spawnear al jugador
	SpriteManagerAdd(M05SpritePlayer,72,110);

	//Spawnear enemigos
	SpriteManagerAdd(M05SpriteEnemie,30,20);
	SpriteManagerAdd(M05SpriteEnemie,60,40);
	SpriteManagerAdd(M05SpriteEnemie,90,60);
	SpriteManagerAdd(M05SpriteEnemie,120,80);
	//SpriteManagerAdd(M05SpriteShoot, 72, 70);

	//Spawnear solo 2 decorativos del fondo
	SpriteManagerAdd(M05SpriteBackground, 100, 50);
	SpriteManagerAdd(M05SpriteBackground, 40, 0);

	//Iniciar Hud del tiempo
	INIT_HUD(hud);
	UpdateHudTime();
	//Iniciar mapa
	InitScroll(BANK(M05map), &M05map, 0, 0);

	
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

	if (enemieCount <= 0){
		//winPoints++;
		Victory();
		SetState(StateMidGame);
	}

	//Si no logras el objetivo a tiempo, pierdes
	if (countdown <= 0 && enemieCount > 0){
		//failPoints++;
		Fail();
		SetState(StateMidGame);
	}
}
