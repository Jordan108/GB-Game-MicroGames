#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
//#include "Print.h"

//IMPORT_MAP(window);
uint8_t winPoints = 0;
uint8_t failPoints = 0;
uint8_t frame = 60;
uint8_t countdown = 0;
uint8_t difficult = 0;//Medidor de dificultad
//Para medir cuantas veces seguidas ganas/pierdes
uint8_t goodCombo = 0;

uint8_t gameSelect = 0;//Definira si se elige un minijuego al azar (0), o uno especifico (indicar numero)
uint8_t life = 3;


void UpdateHudTime() BANKED {
	for (uint8_t i = 0; i < 18; ++i){//Comprobar ancho del hud
		UPDATE_HUD_TILE(1+i, 0, i < countdown ? 127 : 0);
	}
		
}

void Victory() BANKED{
	winPoints++;
	goodCombo++;
	//badCombo = 0;
    
    //Actualizar dificultad
    if (difficult == 0 && goodCombo>=5) difficult++;
    else if (difficult == 1 && goodCombo>=10) difficult++;

    //Si el combo es divisible por 15 y tienes menos vida que el maximo, dar 1
    if ((goodCombo%15) == 0 && life < 3){
        life++;
    }
}

void Fail() BANKED {
	failPoints++;
	//badCombo++;
	goodCombo = 0;
    //Actualizar vida
    if (life>0)life--;
	
    //Actualizar dificultad
    if (difficult > 0) difficult--;

}

void START() {
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume

	SetState(StateMainMenu);//StateMainMenu
	
}

void UPDATE() {
	
}
