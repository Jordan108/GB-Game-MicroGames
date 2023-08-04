#include "Banks/SetAutoBank.h"
#include "Keys.h"//KeyPressed
#include "SpriteManager.h"
#include "ZGBMain.h"
//Para manejar el HUD
#include "Scroll.h"
#include "Print.h"
#include "Sound.h"

//Copia de la structura creada en SpriteBall para poder hacer referencia a su puntero
typedef struct 
{
    int8_t vy;
    UBYTE hit;
} ballData;

const uint8_t logIdle[] = {1,0};
const uint8_t logRoll[] = {8,0,1,2,2,2,1,0,0};   //Cambiar al idle cuando este sea 7 {8,1,2,3,4,5,6,7,7};
UBYTE roll;
const uint8_t animationSpeed = 30; 
//Almacenara desde donde comenzara el palo, para que al terminar su animacion no se descoordine
uint8_t startX;
uint8_t startY;

/* extern uint8_t winPoints;
extern uint8_t badCombo;
extern uint8_t goodCombo; */
void Victory() BANKED;
//void Fail() BANKED;

void START() {
    roll = 0;
    startX = THIS->x;
    startY = THIS->y;
}

void UPDATE() {
    uint8_t i;
    Sprite* spr;
    
    if(KEY_PRESSED(J_A) && (!roll)) {
        SetSpriteAnim(THIS, logRoll, animationSpeed);
        roll = 1;
    }


    if (roll){
        if (THIS->anim_frame == 7){
            SetSpriteAnim(THIS, logIdle, animationSpeed); 
            roll = 0;
            THIS->x = startX;
            THIS->y = startY;
        } 
        
        SPRITEMANAGER_ITERATE(i, spr){
            if(spr->type == M01SpriteBall){
                if(CheckCollision(THIS, spr) && (THIS->anim_frame >= 2 && THIS->anim_frame <=4)){
                    ballData* ball = (ballData*)spr->custom_data;
                    if (ball->vy > 0){
                        //SFX golpear la pelota
                        PlayFx(CHANNEL_1, 1, 0x25, 0x03, 0xAA, 0x2F, 0xC6);
                        //winPoints++;
                        //goodCombo++;
                        Victory();
                        ball->hit = 1;
                        ball->vy = -3;
                    } 
                    
                }
            }
        }
        
    }
}

void DESTROY() {
}