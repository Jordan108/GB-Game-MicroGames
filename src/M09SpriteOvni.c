#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Scroll.h"
#include "Keys.h"
#include "rand.h"
#include "Sound.h"

extern uint8_t frame;
extern uint8_t countdown;
extern uint8_t difficult;

void Victory() BANKED;
void Fail() BANKED;

uint8_t beamX;
uint8_t beamY;
uint8_t moveFrame;
UBYTE beam;
UBYTE direction;

void createOvniBeam(){
	Sprite* spr;
    uint8_t i;
    //SFX Rayo lanzado
    PlayFx(CHANNEL_4, 1, 0x32, 0xFF, 0x1F, 0x80, 0xc6);
    for(i=0;i<10;i++){
        UpdateMapTile(0, beamX,beamY+i, 8, 0, 0); 
        UpdateMapTile(0, beamX+1,beamY+i, 9, 0, 0);
    }
    i=0;
    //Despues de que se cree el rayo, comprobar posicion del jugador y comprobar si el rayo lo choco o no
    SPRITEMANAGER_ITERATE(i, spr){
		if(spr->type == M09SpritePlayer){
            if ((spr->x >= beamX*8  && spr->x <= (beamX+1)*8) | (spr->x+32 >= beamX*8  && spr->x+32 <= (beamX+1)*8) | (spr->x <= beamX*8  && spr->x+32 >= (beamX+1)*8)){
                //failPoints++;
                Fail();
            } else {
                //winPoints++;
                Victory();
            }
		}
	}
    //independiente si gano o no, se manda hacia aqui
    SetState(StateMidGame);
}

void START() {
    beamX = (THIS->x/8)+1;
    beamY = (THIS->y/8)+3;
    beam = 0;
    direction = rand() % 2;
    frame = 60;
	countdown = rand() % 20 + 10;

    switch (difficult)
    {
    //Dificultad Dificil
    case 2:
		moveFrame = 52;
        break;

    //Dificultad normal
    case 1:
		moveFrame = 50;
        break;
    
    //Dificultad facil
    default:
		moveFrame = 50;
        break;
    }
}

void UPDATE() {
    frame-=2;
	if (frame <= moveFrame && beam==0){
		frame=60;
		countdown--;

        //Moverse
        if (direction==1){
            if (THIS->x < 128){
                TranslateSprite(THIS,8,0);
            } else {
                direction = 0;
            }
        } else {
            if (THIS->x > 0){
                TranslateSprite(THIS,-8,0);
            } else {
                direction = 1;
            }
        }

	} else if (frame<=30 && beam==1){
        countdown--;
    }

    if (countdown==0){
        if (beam==0){
            beam=1;
            countdown=10;
            frame=60;

            //Actualizar posicion del rayo
            beamX = (THIS->x/8)+1;
            beamY = (THIS->y/8)+3;

            //Advertencia del rayo
            PlayFx(CHANNEL_4, 1, 0x31, 0xAF, 0x0F, 0x80, 0xc6);
            UpdateMapTile(0, beamX,beamY, 8, 0, 0); 
            UpdateMapTile(0, beamX+1,beamY, 9, 0, 0);
            
        } else if (beam==1){
            createOvniBeam();
        }
    }

    

    /*if (beam == 0){
        createOvniBeam();
    }*/
    
    
}

void DESTROY() {
}