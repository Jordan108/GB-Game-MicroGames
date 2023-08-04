#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "ZGBMain.h"

typedef struct 
{
    int8_t vy;
    UBYTE hit;
} BallData;

/* extern uint8_t failPoints;
extern uint8_t badCombo;
extern uint8_t goodCombo; */
void Fail() BANKED;

void START() {
    BallData* data = (BallData*)THIS->custom_data;
    data->vy = 2;
    data->hit = 0;
}

void UPDATE() {
    BallData* data = (BallData*)THIS->custom_data;

    if (THIS->y < 20){
        if (data->hit == 1){
            SetState(StateMidGame);
        }
        if (data->vy < 2){
            data->vy++;
            
        } 
    }

    //Mover la pelota
    TranslateSprite(THIS, 0, data->vy << delta_time);

    if (THIS->y > 140){
        SetState(StateMidGame);
        Fail();
        /* failPoints++;
        badCombo++;
        goodCombo = 0; */
    }
}

void DESTROY() {
}