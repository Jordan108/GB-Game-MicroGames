#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "ZGBMain.h"

//Se tiene que ocupar una estructura por que puede haber mas de 1 bala en pantalla
typedef struct 
{
    uint8_t vy;
} BulletData;

extern uint8_t countBullet;//Llamar al countBullet del jugador

void START() {
    BulletData *data = (BulletData *)THIS->custom_data;
    data->vy = -3;
}

void UPDATE() {
    BulletData *data = (BulletData *)THIS->custom_data;
    TranslateSprite(THIS, 0, data->vy << delta_time);
}

void DESTROY() {
    countBullet--;//Descontar el count del jugador
}