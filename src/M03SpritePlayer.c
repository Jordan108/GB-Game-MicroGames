#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Keys.h"
#include "Print.h"
#include "Sound.h"

extern uint8_t startCount;
extern uint8_t frame;

uint8_t anim_idle[] = {1, 0};
uint8_t anim_walk[] = {3, 1, 2, 3};
uint8_t anim_jump[] = {1, 4};
uint8_t animSpeed = 15;

int8_t vX;
int8_t vY;
uint8_t maxSpeedX;
uint8_t maxSpeedY;
uint8_t maxJumpHeight;
uint8_t yIncrement;
uint8_t gravity;

uint8_t ground_collision;

UBYTE checkJump;

typedef enum  {
	PLAYER_STATE_NORMAL,
	PLAYER_STATE_JUMPING,
    PLAYER_STATE_FALLING
}PLAYER_STATE;
PLAYER_STATE State;

void START() {
    vX = 0;
    vY = 0;
    maxSpeedX = 2;
    maxSpeedY = 3;
    yIncrement = 1;
    gravity = 1;
    checkJump = 0;

    maxJumpHeight = 6;
}

//Movimiento horizontal
void horizontalMovement(){
    if(KEY_PRESSED(J_LEFT) /* && (!CheckCollLeft) */) {
		if(vX > -maxSpeedX) {
			vX--;
		}
	} else if(KEY_PRESSED(J_RIGHT) /* && (!CheckCollRight) */) {
		if(vX < maxSpeedX) {
			vX++;
		}
    } else {
        vX = 0;
    }

    /* if (vX > 0 && CheckCollRight){
        vX = 0;
    }
    if (vX < 0 && CheckCollLeft){
        vX = 0;
    } */

    //Desactivar sistema de colision
    /* if (CheckCollLeft && !KEY_PRESSED(J_LEFT)) CheckCollLeft = 0;
    if (CheckCollRight && !KEY_PRESSED(J_RIGHT)) CheckCollRight = 0; */

    //Orientacion
    if(vX > 0) {
        THIS->mirror = NO_MIRROR;
		//THIS->mirror = vX > 0 ? NO_MIRROR : H_MIRROR;
	} else if (vX < 0){
        THIS->mirror = V_MIRROR;
    }

    //Mover al personaje en X
    TranslateSprite(THIS, vX << delta_time, 0);
    
}

//Calcular colisiones y gravedad
void verticalMovement(){
    switch (State)
    {
    case PLAYER_STATE_JUMPING:
        //Seguir subiendo
            if (checkJump == 1)
            {
                //Si no mantienes presionado el boton de salto, hacerlo bajar
                if (!KEY_PRESSED(J_A)) {
                    State   = PLAYER_STATE_FALLING;
                }
                checkJump = 0;
            }
            else {
                //Si la capaciadads 
                State   = PLAYER_STATE_FALLING;
            } // Fall through to next stage
        break;
    
    case PLAYER_STATE_FALLING:
            // Acelerar hacia abajo
            if (vY <= maxSpeedY) {
                if ((frame % 2) == 0)
                    vY += gravity;
            }

            // Check if player landed on GROUND *OR* hit CEILING
            if(TranslateSprite(THIS, 0, vY) /* | CheckCollUp */) {

                if (vY < 0) {//Si choco con el techo
                    
                    /* if (CheckCollUp){
                        CheckCollUp = 0;
                        THIS->y +=2;//Bajarlo un poco para que no siga detectando la colision con la caja
                    }  */
                    vY = 0;
                    State = PLAYER_STATE_FALLING;
                } else { // Si choco con el piso
                    State = PLAYER_STATE_NORMAL;
                }

                vY = 0;
            }
        break;
    
    default://PLAYER_STATE_NORMAL
        //Saltar
        if (KEY_PRESSED(J_A)){
            vY = -maxJumpHeight;
            //SFX saltar
            PlayFx(CHANNEL_1, 1, 0x4f, 0x01, 0x4f, 0x67, 0xc6);

            //Chequear colision encima del jugador
            if (TranslateSprite(THIS, 0, vY)) {
                //Si choco con algo, frenarlo y hacerlo caer
                vY = 0;
                State   = PLAYER_STATE_FALLING;
            }
            else
            {
                State      = PLAYER_STATE_JUMPING;
                checkJump = 1;
            }
        } else {
            //Comprobar caida
            // Intentar hacer caer al jugador con una "gravedad"
            /* if (!CheckCollDown){ */
                if (TranslateSprite(THIS, 0, 1) ) {
                    vY = 0;
                    State = PLAYER_STATE_NORMAL;
                }
                else{
                    State = PLAYER_STATE_FALLING;
                }
           /*  }   */ 
        }
        break;
    }
}

void UPDATE() {
    uint8_t i;
	Sprite* spr;
    
    horizontalMovement();
    verticalMovement();
    
    //Colision con estrellas
	SPRITEMANAGER_ITERATE(i, spr){
		if(spr->type == M03SpriteStar){
			if(CheckCollision(THIS, spr)){
                //SFX recoger estrellas
                PlayFx(CHANNEL_1, 1, 0x45, 0x01, 0x8f, 0x9e, 0xc6);

                startCount--;
				SpriteManagerRemove(i);
			}
		} 
	}


    //Animaciones
    if (State == PLAYER_STATE_NORMAL){
        SetSpriteAnim(THIS, vX ? anim_walk : anim_idle, animSpeed);
    } else if (State == PLAYER_STATE_JUMPING){
         SetSpriteAnim(THIS, anim_jump, animSpeed);
    }
    
}

void DESTROY() {
}