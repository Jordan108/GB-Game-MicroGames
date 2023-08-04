#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"

IMPORT_MAP(hud);//HUD
IMPORT_MAP(M07map);

extern uint8_t frame;
extern uint8_t countdown;
extern uint8_t difficult;

void Victory() BANKED;
void Fail() BANKED;

void UpdateHudTime() BANKED;

UBYTE frogJump;
uint8_t M07collision_tiles[] = {1,7,8,9,0};

/* void UpdateHudTime() {
	for (uint8_t i = 0; i < 18; ++i){//Comprobar ancho del hud
		UPDATE_HUD_TILE(1+i, 0, i < countdown ? 127 : 0);
	}
		
} */

void START() {
	frame = 60;
	frogJump = 0;
	
	switch (difficult)
    {
    //Dificultad Dificil
    case 2:
		countdown = 3;
        break;

    //Dificultad normal
    case 1:
		countdown = 4;
        break;
    
    //Dificultad facil
    default:
		countdown = 5;
        break;
    }

	//Establecer mira del jugador
	SpriteManagerAdd(M07SpriteArrow, 104, 80);
	SpriteManagerAdd(M07SpriteFrog, 16, 80);
	
	//Iniciar Hud del tiempo
	INIT_HUD(hud);
	UpdateHudTime();

	//Iniciar mapa
	InitScroll(BANK(M07map), &M07map, M07collision_tiles, 0);
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

	//Si no logras el objetivo a tiempo, pierdes
	if (countdown <= 0 && (frogJump == 0)){
		//failPoints++;
		Fail();
		SetState(StateMidGame);
	}
}
