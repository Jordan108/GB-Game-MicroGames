#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Keys.h"
#include "Sound.h"

uint8_t countBullet;
UBYTE shoot;

void START() {
    shoot = 0;
    countBullet = 0;//Lo usare para que no haya mas que X balas en el mapa
}

void UPDATE() {
    //Moverse de izquierda a derecha
    if (KEY_PRESSED(J_LEFT) && (THIS->x > 0))
	{
		TranslateSprite(THIS, -2 << delta_time, 0);
	}
	if (KEY_PRESSED(J_RIGHT) && (THIS->x < 160-16))//le resto 16 que es el ancho del sprite
	{
		TranslateSprite(THIS, 2 << delta_time, 0);
	}

    //Disparar con b
    if (KEY_PRESSED(J_B) && (shoot == 0) && (countBullet < 3)){
        SpriteManagerAdd(M05SpriteShoot, THIS->x+4, THIS->y - 4);
        //SFX Destruirse
        PlayFx(CHANNEL_1, 1, 0x1F, 0xCA, 0xA3, 0x9A, 0x86);
        shoot = 1;
        countBullet++;
    }

    //Soltar el boton de disparo
    if (KEY_RELEASED(J_B)){
        shoot = 0;
    }
}

void DESTROY() {
}