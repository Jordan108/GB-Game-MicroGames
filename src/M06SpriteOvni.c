#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "rand.h"

typedef struct 
{
    int8_t vy;
    int8_t vx;
    UBYTE move;
    UBYTE hit;
} OvniData;

uint8_t ovniDown[] = {1,1};

extern uint8_t frame;
extern uint8_t difficult;

void Victory() BANKED;
void Fail() BANKED;

uint8_t appearCount;

void START() {
    OvniData* data = (OvniData*)THIS->custom_data;
    //data->vx = -3;//Variara dependiendo de la dificultad
    data->vy = 0;
    data->move = 0;
    data->hit = 0;//saber si fue golpeado

    //Marcara cuantos segundos tardara en aparecer
    frame = 60;
    
    switch (difficult)
    {
    //Dificultad Dificil
    case 2:
		appearCount = (rand() % 8)+1;
        data->vx = -4;
        break;

    //Dificultad normal
    case 1:
		appearCount = (rand() % 6)+1;
        data->vx = -3;
        break;
    
    //Dificultad facil
    default:
		appearCount = (rand() % 5)+1;//De base, 1 segundo en aparecer, se le pueden añadir hasta 4 segundos mas
        data->vx = -3;
        break;
    }
}

void UPDATE() {

    frame--;
	if (appearCount > 0 && frame <= 0){
		frame=60;
		appearCount--;
	}

    OvniData* data = (OvniData*)THIS->custom_data;

    if (data->move == 1){
        if (data->hit == 0){
            data->vy = (rand() % 3)-1;

            //Controlar que perdiste
            if (THIS->x < 40){
                //failPoints++;
                Fail();
                SetState(StateMidGame);
            }
        } else {
            SetSpriteAnim(THIS, ovniDown, 1);
            data->vx = (rand() % 3)-1;
            data->vy = 1;

            //Controlar que ganaste
            if (THIS->y > 70){
                //winPoints++;
                Victory();
                SetState(StateMidGame);
            }
        }
        
        //Mover el ovni
        TranslateSprite(THIS, data->vx, data->vy << delta_time);

        
    } else {
        if (appearCount == 0) data->move = 1;
    }

    
}

void DESTROY() {
}