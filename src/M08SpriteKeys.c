#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Keys.h"
#include "rand.h"
#include "Sound.h"

/* extern uint8_t winPoints;
extern uint8_t failPoints; */
void Victory() BANKED;
void Fail() BANKED;
UBYTE pressed;

void START() {
    SetFrame(THIS,rand()%6);
    pressed = 0;
}

void UPDATE() {
    if (KEY_PRESSED(J_UP) && (pressed == 0)){
        pressed = 1;
        if (THIS->anim_frame == 0){
            //winPoints++;
            Victory();
            PlayFx(CHANNEL_1, 1, 0x46, 0xC5, 0xF3, 0xC2, 0x86); //SFX Exito
        } else {
            //failPoints++;
            Fail();
            PlayFx(CHANNEL_1, 1, 0x4E, 0xC5, 0xF3, 0xC2, 0x86); //SFX Fracaso
        }
        SetState(StateMidGame);
    }
    if (KEY_PRESSED(J_RIGHT) && (pressed == 0)){
        pressed = 1;
        if (THIS->anim_frame == 1){
            //winPoints++;
            Victory();
            PlayFx(CHANNEL_1, 1, 0x46, 0xC5, 0xF3, 0xC2, 0x86); //SFX Exito
        } else {
            //failPoints++;
            Fail();
            PlayFx(CHANNEL_1, 1, 0x4E, 0xC5, 0xF3, 0xC2, 0x86); //SFX Fracaso
        }
        SetState(StateMidGame);
    }
    if (KEY_PRESSED(J_DOWN) && (pressed == 0)){
        pressed = 1;
        if (THIS->anim_frame == 2){
            //winPoints++;
            Victory();
            PlayFx(CHANNEL_1, 1, 0x46, 0xC5, 0xF3, 0xC2, 0x86); //SFX Exito
        } else {
            //failPoints++;
            Fail();
            PlayFx(CHANNEL_1, 1, 0x4E, 0xC5, 0xF3, 0xC2, 0x86); //SFX Fracaso
        }
        SetState(StateMidGame);
    }
    if (KEY_PRESSED(J_LEFT) && (pressed == 0)){
        pressed = 1;
        if (THIS->anim_frame == 3){
            //winPoints++;
            Victory();
            PlayFx(CHANNEL_1, 1, 0x46, 0xC5, 0xF3, 0xC2, 0x86); //SFX Exito
        } else {
            //failPoints++;
            Fail();
            PlayFx(CHANNEL_1, 1, 0x4E, 0xC5, 0xF3, 0xC2, 0x86); //SFX Fracaso
        }
        SetState(StateMidGame);
    }
    if (KEY_PRESSED(J_A) && (pressed == 0)){
        pressed = 1;
        if (THIS->anim_frame == 4){
            //winPoints++;
            Victory();
            PlayFx(CHANNEL_1, 1, 0x46, 0xC5, 0xF3, 0xC2, 0x86); //SFX Exito
        } else {
            //failPoints++;
            Fail();
            PlayFx(CHANNEL_1, 1, 0x4E, 0xC5, 0xF3, 0xC2, 0x86); //SFX Fracaso
        }
        SetState(StateMidGame);
    }
    if (KEY_PRESSED(J_B) && (pressed == 0)){
        pressed = 1;
        if (THIS->anim_frame == 5){
            //winPoints++;
            Victory();
            PlayFx(CHANNEL_1, 1, 0x46, 0xC5, 0xF3, 0xC2, 0x86); //SFX Exito
        } else {
            //failPoints++;
            Fail();
            PlayFx(CHANNEL_1, 1, 0x4E, 0xC5, 0xF3, 0xC2, 0x86); //SFX Fracaso
        }
        SetState(StateMidGame);
    }
}

void DESTROY() {
}