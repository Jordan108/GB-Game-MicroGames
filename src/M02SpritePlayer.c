#include "Banks/SetAutoBank.h"
#include "Keys.h"//KeyPressed
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Sound.h"

/* extern uint8_t failPoints;
void Victory() BANKED; */
void Fail() BANKED;
UBYTE MOVE;
void START() {
	MOVE = 0;
}

void UPDATE() {
    uint8_t i;
	Sprite* spr;
	
    if(KEY_PRESSED(J_LEFT) && !MOVE && (THIS->x > 66)) {
		TranslateSprite(THIS, -8, 0);
		//SFX Cambiar de pista
		PlayFx(CHANNEL_4, 1, 0x3B, 0x91, 0x11, 0x80, 0xC6);
		MOVE = 1;
	}
	if(KEY_PRESSED(J_RIGHT) && !MOVE && (THIS->x < 82)) {
		TranslateSprite(THIS, 8, 0);
		//SFX Cambiar de pista
		PlayFx(CHANNEL_4, 1, 0x3B, 0x91, 0x11, 0x80, 0xC6);
		MOVE = 1;
	}

	if(keys == 0) {
		MOVE = 0;
	}

    SPRITEMANAGER_ITERATE(i, spr){
		if(spr->type == M02SpriteVehicleA | spr->type == M02SpriteVehicleB){
			if(CheckCollision(THIS, spr)){
				//SFX Choque
				PlayFx(CHANNEL_4, 1, 0x1B, 0xF3, 0x70, 0xC0, 0xC6);
				//failPoints++;
				Fail();
                SetState(StateMidGame);
			}
		}
	}
}

void DESTROY() {
}