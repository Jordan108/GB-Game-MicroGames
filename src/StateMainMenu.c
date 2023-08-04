#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Keys.h"

IMPORT_MAP(MainMap);
//IMPORT_MAP(window);
//extern winPoints;
//extern failPoints;
//uint8_t frame = 60;
//uint8_t countdown = 0;

UBYTE select;
UBYTE option;
UBYTE keyPressed;

//Datos a resetear
extern uint8_t winPoints;
extern uint8_t failPoints;
extern uint8_t difficult;
extern uint8_t goodCombo;
extern uint8_t gameSelect;
extern uint8_t life;

void START(){
	InitScroll(BANK(MainMap), &MainMap, 0, 0);

	select = 0;
	option = 0;
	keyPressed = 0;

	//Datos a resetear
	winPoints = 0;
	failPoints = 0;
	difficult = 0;
	goodCombo = 0;
	gameSelect = 0;
	life = 3;
}

void UPDATE() {
	if (select == 0){
		if (KEY_PRESSED(J_START)){
			uint8_t i;
			//Crear el tile de la flechita
			UpdateMapTile(0, 5, 12, 75, 0, 0); 
			//Borrar los tiles de press start
			for (i=0;i<9;i++){
				UpdateMapTile(0, 5+i, 13, 0, 0, 0); 
				//UpdateMapTile(0, 0, 13, 8, 0, 0); 
			}
			//Iniciar los tiles de normal
			for (i=0;i<5;i++){
				UpdateMapTile(0, 6+i, 12, 76+i, 0, 0); 
			}
			//Iniciar los tiles de de Infinite
			for (i=0;i<7;i++){
				UpdateMapTile(0, 6+i, 14, 81+i, 0, 0); 
			}
			
			select = 1;
			keyPressed = 1;
		}
		
	} else {
		if (keyPressed == 0){
			if (KEY_PRESSED(J_DOWN) | KEY_PRESSED(J_UP)){
				if (option == 0){
					//Borrar y Crear el tile de la flechita
					UpdateMapTile(0, 5, 12, 0, 0, 0); 
					UpdateMapTile(0, 5, 14, 75, 0, 0); 
					option = 1;
				} else {
					//Borrar y Crear el tile de la flechita
					UpdateMapTile(0, 5, 14, 0, 0, 0); 
					UpdateMapTile(0, 5, 12, 75, 0, 0); 
					option = 0;
				}

				keyPressed = 1;
			}

			if (KEY_PRESSED(J_A) | KEY_PRESSED(J_START) | KEY_PRESSED(J_SELECT)){
				if (option == 0){
					SetState(StateMidGame);
				} else {
					SetState(StateMenuInfinite);
				}

				keyPressed = 1;
			}
		} else {
			if (keys == 0){
				keyPressed = 0;
			}
		}
		
	}
}
