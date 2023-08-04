#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "rand.h"
#include "Sound.h"

extern uint8_t enemieCount;
extern uint8_t difficult;
//const uint8_t enemIdle[] = {1,0};
const uint8_t enemDestroy[] = {5,1,2,3,4,4};   //Destruir cuando el frame sea 4

//Habra mas de un enemigo
typedef struct 
{
    UBYTE destroy;
    UBYTE right;
    int8_t vx;
} EnemieData;

UBYTE left;

void START() {
    EnemieData* data = (EnemieData*)THIS->custom_data;
    data->destroy = 0;
    
    left = (rand() % 2);
    

    switch (difficult)
    {
    //Dificultad Dificil
    case 2:
		data->vx = 3;
        break;

    //Dificultad normal
    case 1:
		data->vx = (rand() % 3)+1;//el +1 es para evitar que llegue a 0
        break;
    
    //Dificultad facil
    default:
		data->vx = (rand() % 2)+1;//el +1 es para evitar que llegue a 0
        break;
    }

    if (left == 1) data->vx *=-1;
}

void UPDATE() {
    EnemieData* data = (EnemieData*)THIS->custom_data;
    uint8_t i;
	Sprite* spr;

    if (data->destroy == 0){
        //Moverse izquierda o derecha
        TranslateSprite(THIS, data->vx << delta_time, 0);
        //Comprobar colision con la pantalla para cambiar la direccion
        if ((THIS->x > 160-16 && data->vx > 0) | (THIS->x < 5 && data->vx < 0)) data->vx *= -1;

        //Comprobar colision con la bala
        SPRITEMANAGER_ITERATE(i, spr)
        {
            if (spr->type == M05SpriteShoot)
            {
                if (CheckCollision(THIS, spr))
                {
                    
                    SpriteManagerRemoveSprite(spr);//Destruir la bala del jugador
                    //Establecer el "estado" de destruccion
                    SetSpriteAnim(THIS, enemDestroy, 30);
                    enemieCount--;//Descontar el enemigo aqui
                    //SFX Destruirse
		            PlayFx(CHANNEL_4, 1, 0x1B, 0xF3, 0x90, 0xC0, 0xC6);
                    data->destroy = 1;
                    
                }
            }
        }
    } else {
        if (THIS->anim_frame == 4){
            SpriteManagerRemoveSprite(THIS);//Destruir el enemigo
        } 
    }
    
}

void DESTROY() {
}