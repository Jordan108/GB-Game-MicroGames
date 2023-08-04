#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Keys.h"
#include "Sound.h"

extern uint8_t failPoints;

//Copia de la structura creada en SpriteOvni para poder hacer referencia a su puntero
typedef struct 
{
    int8_t vy;
    int8_t vx;
    UBYTE move;
    UBYTE hit;
} OvniData;

void START() {
}

void UPDATE() {
    uint8_t i;
    Sprite* spr;
    

    SPRITEMANAGER_ITERATE(i, spr){
        if(spr->type == M06SpriteOvni){
            OvniData* ovnidata = (OvniData*)spr->custom_data;
            if (ovnidata->hit == 0){
                if (spr->y > (THIS->y)+4) THIS->y += 4;
                if (spr->y < (THIS->y)-4) THIS->y -= 4;
            }

            if (KEY_PRESSED(J_A)){
                if(CheckCollision(THIS, spr)){
                    ovnidata->hit = 1;
                    //SFX Disparo acertado
				    PlayFx(CHANNEL_4, 1, 0x1B, 0xF3, 0x61, 0x80, 0xC6);
                } else {
                //SFX Disparo erroneo
				    PlayFx(CHANNEL_4, 1, 0x1B, 0xF3, 0x66, 0xC0, 0xC6);
                    failPoints++;
                    SetState(StateMidGame);
            }
            } 
            
        }
    }
}

void DESTROY() {
}