#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Keys.h"

IMPORT_MAP(InfiniteMap);

/* UBYTE select;
UBYTE option;
UBYTE keyPressed; */

extern UBYTE select;
extern UBYTE option;
extern UBYTE keyPressed;
extern uint8_t gameSelect;

void UpdateInfiniteMenu(){
	uint8_t cells[9][2] = {{2,1},{8,1},{14,1},{2,6},{8,6},{14,6},{2,11},{8,11},{14,11}};
	uint8_t i;
	
	//Actualizar todas las cuadriculas a su estado sin seleccionar
	for (i = 0; i < 9; i++)
	{
		//Actualizar las cuadriculas
		UpdateMapTile(0, cells[i][0], cells[i][1], 1, 0, 0); UpdateMapTile(0, cells[i][0]+1, cells[i][1], 2, 0, 0); UpdateMapTile(0, cells[i][0]+2, cells[i][1], 2, 0, 0); UpdateMapTile(0, cells[i][0]+3, cells[i][1], 3, 0, 0);
		UpdateMapTile(0, cells[i][0], cells[i][1]+1, 4, 0, 0);UpdateMapTile(0, cells[i][0]+3, cells[i][1]+1, 5, 0, 0);
		UpdateMapTile(0, cells[i][0], cells[i][1]+2, 4, 0, 0);UpdateMapTile(0, cells[i][0]+3, cells[i][1]+2, 5, 0, 0);
		UpdateMapTile(0, cells[i][0], cells[i][1]+3, 6, 0, 0); UpdateMapTile(0, cells[i][0]+1, cells[i][1]+3, 7, 0, 0); UpdateMapTile(0, cells[i][0]+2, cells[i][1]+3, 7, 0, 0); UpdateMapTile(0, cells[i][0]+3, cells[i][1]+3, 8, 0, 0);
	}

	//Despues, cambiar a por la cuadricula seleccionada sus tiles respectivos
	UpdateMapTile(0, cells[select-1][0], cells[select-1][1], 9, 0, 0);   UpdateMapTile(0, cells[select-1][0]+1, cells[select-1][1], 10, 0, 0); UpdateMapTile(0, cells[select-1][0]+2, cells[select-1][1], 10, 0, 0); UpdateMapTile(0, cells[select-1][0]+3, cells[select-1][1], 11, 0, 0);
	UpdateMapTile(0, cells[select-1][0], cells[select-1][1]+1, 12, 0, 0); UpdateMapTile(0, cells[select-1][0]+3, cells[select-1][1]+1, 13, 0, 0);
	UpdateMapTile(0, cells[select-1][0], cells[select-1][1]+2, 12, 0, 0); UpdateMapTile(0, cells[select-1][0]+3, cells[select-1][1]+2, 13, 0, 0);
	UpdateMapTile(0, cells[select-1][0], cells[select-1][1]+3, 14, 0, 0); UpdateMapTile(0, cells[select-1][0]+1, cells[select-1][1]+3, 15, 0, 0); UpdateMapTile(0, cells[select-1][0]+2, cells[select-1][1]+3, 15, 0, 0); UpdateMapTile(0, cells[select-1][0]+3, cells[select-1][1]+3, 16, 0, 0);

	//Dejar presionada la tecla automaticamente
	keyPressed = 1;	
}

void START(){
	InitScroll(BANK(InfiniteMap), &InfiniteMap, 0, 0);

	select = 1;
	option = 0;
	keyPressed = 0;
}

void UPDATE() {
	if (KEY_PRESSED(J_B)){
		SetState(StateMainMenu);
	}

	if (KEY_PRESSED(J_A) | KEY_PRESSED(J_START)){
		gameSelect = select;//Seleccionar el minijuego que sera infinito
		SetState(StateMidGame);
	}

	if (keyPressed == 0){
		if (KEY_PRESSED(J_UP)){
			if (select >=4) select -= 3;
			else select += 6;

			UpdateInfiniteMenu();
		} else if (KEY_PRESSED(J_DOWN)){
			if (select <=6) select += 3;
			else select -= 6;

			UpdateInfiniteMenu();
		} else if (KEY_PRESSED(J_LEFT)){
			if (select >=2) select --;
			else select = 9;
			
			UpdateInfiniteMenu();
		} else if (KEY_PRESSED(J_RIGHT)){
			if (select <=8) select++;
			else select = 1;

			UpdateInfiniteMenu();
		}
	} else {
		if (keys == 0){
			keyPressed = 0;
		}
	}
	
}
