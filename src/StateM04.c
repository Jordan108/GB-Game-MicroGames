#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "BankManager.h"
#include "rand.h"
#include "Keys.h"
#include "Sound.h"

IMPORT_MAP(hud);//HUD
IMPORT_MAP(M04map);

extern uint8_t frame;
extern uint8_t countdown;
extern uint8_t difficult;

void UpdateHudTime() BANKED;
void Victory() BANKED;
void Fail() BANKED;

// 0-Espacio en blanco, 1-Letra B, 2-Letra A}
uint8_t Gametext[] = {0,0,0,0,0,0}; 
uint8_t yourText[] = {0,0,0,0,0,0};
uint8_t textCount;
uint8_t textX;
uint8_t textY;
UBYTE write;

void printLetter(uint8_t x, uint8_t y, UBYTE letterA){
	//Decidir si se imprime la letra A o B
	if (letterA){
		UpdateMapTile(0, x,y,     28, 0, 0);
		UpdateMapTile(0, x+1,y,   29, 0, 0);
		UpdateMapTile(0, x,y+1,   30, 0, 0);
		UpdateMapTile(0, x+1,y+1, 31, 0, 0);
	} else {
		UpdateMapTile(0, x,y,     24, 0, 0);
		UpdateMapTile(0, x+1,y,   25, 0, 0);
		UpdateMapTile(0, x,y+1,   26, 0, 0);
		UpdateMapTile(0, x+1,y+1, 27, 0, 0);
	}
	//SFX Escribir
    PlayFx(CHANNEL_1, 1, 0x23, 0x03, 0xAA, 0x22, 0xC6);

	//Detectar si escribimos bien la letra
	if (Gametext[textCount] != letterA){
		//failPoints++;
		Fail();
		SetState(StateMidGame);
		
	} else {
		if (textCount == 4){
			//winPoints++;
			Victory();
			SetState(StateMidGame);
		}
	}


	textX+=2;
	textCount++;
	write = 1;
	//Imprimir la barrita de escribir
	if (textCount < 5){
		UpdateMapTile(0, x+2,y+1, 32, 0, 0);
	}
	
}

void START() {
	uint8_t i;

	//Iniciar Hud del tiempo
	INIT_HUD(hud);
	UpdateHudTime();
	InitScroll(BANK(M04map), &M04map, 0, 0);
	
	for(i=0; i<5;i++){
		Gametext[i] = rand() % 2;
		if (Gametext[i] == 1){
			UpdateMapTile(0, 2+i,7, 23, 0, 0);
		} else{
			UpdateMapTile(0, 2+i,7, 22, 0, 0);
		}
	}
	//Posicion del texto
	textCount = 0;
	textX = 5;
	textY = 12;
	//Escribiendo
	write = 0;

	//Tiempo
	frame = 60;
	
	switch (difficult)
    {
    //Dificultad Dificil
    case 2:
		countdown = 2;
        break;

    //Dificultad normal
    case 1:
		countdown = 3;
        break;
    
    //Dificultad facil
    default:
		countdown = 4;
        break;
    }

	//Barrita de escribir
	UpdateMapTile(0, textX,textY+1, 32, 0, 0);
}


void UPDATE() {
	frame--;
	if (frame <= 0 && (countdown > 0)){
		frame=60;
		countdown--;
		UpdateHudTime();
		//SFX Contador de tiempo
		if (countdown <=3 && countdown!=0){
			PlayFx(CHANNEL_1, 1, 0x44, 0xA1, 0x4F, 0xBE, 0xC6);
		} else if (countdown == 0){
			PlayFx(CHANNEL_1, 1, 0x45, 0xA1, 0x4F, 0xBE, 0xC6);
		}
	}

	//Si logras el objetivo, ganaras automaticamente
	if (countdown <= 0){
		//failPoints++;
		Fail();
		SetState(StateMidGame);
	}

	if (!write && textCount < 5){
		if (KEY_PRESSED(J_A)){
			printLetter(textX,textY,1);
		} else if (KEY_PRESSED(J_B)){
			printLetter(textX,textY,0);
		}
	} else {
		if (!KEY_PRESSED(J_A) && !KEY_PRESSED(J_B)){
			write = 0;
		}
	}
}
