#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "ZGBMain.h"

extern uint8_t ground_collision;
/* extern uint8_t winPoints;
extern uint8_t failPoints; */
void Victory() BANKED;
void Fail() BANKED;

typedef struct 
{
    int8_t vy;
    int8_t vx;
    uint8_t gravity;
    UBYTE jump;
    UBYTE succes;
} FrogData;

void START() {
    FrogData* data = (FrogData*)THIS->custom_data;
    data->vx = 0;
    data->vy = 0;
    data->gravity = 1;
    data->jump = 0;
    data->succes = 0;
}

void UPDATE() {
    FrogData* data = (FrogData*)THIS->custom_data;
    
    if (data->vy < 10 && !ground_collision) data->vy+=data->gravity;
   
   if (ground_collision && data->jump == 0){
        data->vy = 0;
        data->vx = 0;
   }

   if (data->jump == 1){
        SetFrame(THIS,1);
        if(THIS->y < 60) data->jump = 0;
   }

    //Mover la rana en Y
    ground_collision =TranslateSprite(THIS, 0, data->vy << delta_time);

    //Delimitar a la rana en el tronco correcto
    if (data->succes == 1){
        if (THIS->y >= 80){
            data->vy = 0;
            data->gravity = 0;
            data->jump = 0;
            THIS->y = 80;
            if (THIS->x  != 92) THIS->x = 92;
            SetFrame(THIS,0);
            //declarar que ganaste
            //winPoints++;
            Victory();
            SetState(StateMidGame);
        }
    } else {
        if (THIS->y > 80){
            //declarar que perdiste
            //failPoints++;
            Fail();
            SetState(StateMidGame);
        }
    }

    //Mover a la rana en X solo si esta en el aire
    if (!ground_collision){
        TranslateSprite(THIS, data->vx << delta_time, 0);
    }
}

void DESTROY() {
}