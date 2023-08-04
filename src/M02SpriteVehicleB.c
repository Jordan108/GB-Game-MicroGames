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
    data->vy = rand() % difficult + 2;


}

void UPDATE() {
    vehicleData* data = (vehicleData*)THIS->custom_data;

    //Mover la pelota
    TranslateSprite(THIS, 0, data->vy << delta_time);

    if (THIS->y > 140){
        THIS->x = trackX[rand() % 3];//chooseRandomTrack();
        THIS->y = 0;
        data->vy = rand() % difficult + 2;
    }
}

void DESTROY() {
}