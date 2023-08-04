#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "ZGBMain.h"

extern uint8_t difficult;//Medidor de dificultad
//Para medir cuantas veces seguidas ganas/pierdes
extern uint8_t goodCombo;
extern uint8_t badCombo;

void START() {
    
}

void UPDATE() {
    SetFrame(THIS,difficult);
}

void DESTROY() {
}