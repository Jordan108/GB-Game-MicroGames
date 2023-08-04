#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
//numeros aleatorios
#include "rand.h"

extern uint8_t trackX[3];
extern uint8_t chooseRandomTrack();
extern uint8_t difficult;

typedef struct 
{
    int8_t vy;
} vehicleData;


void START() {
    vehicleData* data = (vehicleData*)THIS->custom_data;
    

    switch (difficult)
    {
    //Dificultad Dificil
    case 2:
		data->vy = rand() % 1 + 3;
        break;

    //Dificultad normal
    case 1:
		data->vy = rand() % 2 + 2;
        break;
    
    //Dificultad facil
    default:
		data->vy = rand() % 2 + 1;
        break;
    }
}

void UPDATE() {
    vehicleData* data = (vehicleData*)THIS->custom_data;
    TranslateSprite(THIS, 0, data->vy << delta_time);

    //int8_t rnd = rand() % 3;
    //uint8_t returned = trackX[rnd];

    if (THIS->y > 140){
        THIS->x = trackX[rand() % 3];//chooseRandomTrack();
        THIS->y = 0;
        data->vy = rand() % difficult + 2;
    }
}

void DESTROY() {
}