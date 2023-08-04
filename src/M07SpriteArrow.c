#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Keys.h"
#include "rand.h"
#include "Sound.h"

typedef struct 
{
    uint8_t arrowXPositions[3];
    uint8_t iterator;
    uint8_t frameIterator;
    uint8_t maxIterator;
} ArrowData;

//Puntero de la rana
typedef struct 
{
    int8_t vy;
    int8_t vx;
    uint8_t gravity;
    UBYTE jump;
    UBYTE succes;
} FrogData;

extern uint8_t frame;
extern UBYTE frogJump;
extern uint8_t difficult;

void START() {
    ArrowData* data = (ArrowData*)THIS->custom_data;
    data->arrowXPositions[0] = 72;
    data->arrowXPositions[1] = 104;
    data->arrowXPositions[2] = 136;
    data->iterator = rand() % 3;
    
    switch (difficult)
    {
    //Dificultad Dificil
    case 2:
		data->frameIterator = 8;//Iterara cada 8 frames
        data->maxIterator = 8;
        break;

    //Dificultad normal
    case 1:
		data->frameIterator = 15;//Iterara cada 16 frames
        data->maxIterator = 15;
        break;
    
    //Dificultad facil
    default:
		data->frameIterator = 20;//Iterara cada 20 frames
        data->maxIterator = 20;
        break;
    }
}

void UPDATE() {
    uint8_t i;
    Sprite* spr;

    ArrowData* data = (ArrowData*)THIS->custom_data;
    
    data->frameIterator--;
	if (data->frameIterator <= 0){
		data->frameIterator=data->maxIterator;

		if (frogJump == 0) data->iterator++;

        if (data->iterator > 2) data->iterator = 0;
	}

    THIS->x = data->arrowXPositions[data->iterator];

    SPRITEMANAGER_ITERATE(i, spr){
        if(spr->type == M07SpriteFrog){
            if (KEY_PRESSED(J_A) && (frogJump == 0)){
                frogJump = 1;
                FrogData* frog = (FrogData*)spr->custom_data;
                frog->jump = 1;
                

                switch (data->iterator)
                {
                case 2:
                    frog->vy = -9;
                    frog->vx = 6;
                    frog->succes = 0;
                    //SFX Caida
                    PlayFx(CHANNEL_1, 1, 0x2F, 0xC5, 0xF3, 0xA4, 0x86);
                    break;

                case 1:
                    
                    frog->vy = -8;
                    frog->vx = 5;
                    frog->succes = 1;
                    //SFX Salto
                    PlayFx(CHANNEL_1, 1, 0x27, 0xC5, 0xF3, 0xA4, 0x86);
                    break;
                
                //caso 0
                default:
                    frog->vy = -8;
                    frog->vx = 3;
                    frog->succes = 0;
                    //SFX Caida
                    PlayFx(CHANNEL_1, 1, 0x2F, 0xC5, 0xF3, 0xA4, 0x86);
                    break;
                }
            }
        }
    }

    

    
}

void DESTROY() {
}