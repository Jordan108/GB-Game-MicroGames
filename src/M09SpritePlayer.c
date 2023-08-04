#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Keys.h"
#include "rand.h"
#include "Sound.h"

/* extern uint8_t winPoints;
extern uint8_t failPoints; */

typedef struct 
{
    int8_t vx;
    UBYTE move;
    UBYTE hit;
} PlayerData;

void START() {
    //PlayFx(CHANNEL_4, 1, 0xA0, 0x1D, 0xB9, 0x80, 0xc6);//SFX Avanzar
}

void UPDATE() {
    if (KEY_PRESSED(J_B) && (THIS->x > 0)){
        TranslateSprite(THIS,-1,0);
        //PlayFx(CHANNEL_4, 1, 0x31, 0xFF, 0x93, 0x80, 0xc6);//SFX Frenar
    } else if (KEY_PRESSED(J_A) && (THIS->x < 128)){
        TranslateSprite(THIS,1,0);
        //PlayFx(CHANNEL_4, 1, 0x31, 0xFF, 0xA9, 0x80, 0xc6);//SFX Avanzar
    }
}

void DESTROY() {
}