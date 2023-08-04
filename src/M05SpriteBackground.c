#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
//numeros aleatorios
#include "rand.h"


void START() {

}

void UPDATE() {
    TranslateSprite(THIS, 0, 3 << delta_time);

    if (THIS->y > 140){
        THIS->y = 0;
		THIS->x = (rand() % 160);
    }
}

void DESTROY() {
}