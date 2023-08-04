#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "BankManager.h"
#include "rand.h"
#include "Sound.h"

IMPORT_MAP(hud);//HUD
IMPORT_MAP(M03mapA1);
IMPORT_MAP(M03mapA2);
IMPORT_MAP(M03mapA3);
IMPORT_MAP(M03mapB1);
IMPORT_MAP(M03mapB2);
IMPORT_MAP(M03mapB3);
IMPORT_MAP(M03mapC1);
IMPORT_MAP(M03mapC2);
IMPORT_MAP(M03mapC3);

extern uint8_t frame;
extern uint8_t countdown;
extern uint8_t difficult;

void UpdateHudTime() BANKED;
void Victory() BANKED;
void Fail() BANKED;

uint8_t M03collision_tiles[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
uint8_t blockCount = 0;
uint8_t startCount;


void replaceTiles(){
	uint8_t x, y, tile;
	//data = map->data;
	for(y = 0; y < 18; y++) {
		for(x = 0; x < 20; x++) {
			//tile = *(data++);
			tile = GetScrollTile(x,y);
			
			/* if(tile == 17) {//bloque
				//set_bkg_tiles(x,y,1,1,0x00);
				UpdateMapTile(0,x,y,0,0,0);//limpiar los bloques, despues se pondran con el script setRandomBlock
			} */

			if(tile == 18) {//Estrellas
				//set_bkg_tiles(x,y,1,1,0x00);
				UpdateMapTile(0,x,y,0,0,0);
				SpriteManagerAdd(M03SpriteStar,x*8,y*8);
			}
		}
	}
}

void setRandomBlock(int8_t map, int8_t subMap){

	switch (map)
	{
	case 2://Mapa c
		if (subMap == 0){
			SpriteManagerAdd(M03SpriteBlock,8*8,10*8);
			SpriteManagerAdd(M03SpriteBlock,9*8,9*8);
		} else if (subMap == 1){
			SpriteManagerAdd(M03SpriteBlock,14*8,9*8);
			SpriteManagerAdd(M03SpriteBlock,15*8,10*8);
		} else {
			SpriteManagerAdd(M03SpriteBlock,11*8,6*8);
			SpriteManagerAdd(M03SpriteBlock,12*8,6*8);
			SpriteManagerAdd(M03SpriteBlock,11*8,4*8);
			SpriteManagerAdd(M03SpriteBlock,12*8,4*8);
			SpriteManagerAdd(M03SpriteBlock,11*8,2*8);
			SpriteManagerAdd(M03SpriteBlock,12*8,2*8);
		}
		break;
	case 1://Mapa b
		if (subMap == 0){
			SpriteManagerAdd(M03SpriteBlock,8*8,10*8);
			SpriteManagerAdd(M03SpriteBlock,14*8,12*8);
			SpriteManagerAdd(M03SpriteBlock,15*8,12*8);
		} else if (subMap == 1){
			SpriteManagerAdd(M03SpriteBlock,8*8,10*8);
			SpriteManagerAdd(M03SpriteBlock,4*8,12*8);
			SpriteManagerAdd(M03SpriteBlock,5*8,12*8);
		} else {
			SpriteManagerAdd(M03SpriteBlock,5*8,12*8);
			SpriteManagerAdd(M03SpriteBlock,14*8,12*8);
		}
		break;
	default://Mapa a
		if (subMap == 0){
			SpriteManagerAdd(M03SpriteBlock,9*8,10*8);
			SpriteManagerAdd(M03SpriteBlock,10*8,10*8);
			SpriteManagerAdd(M03SpriteBlock,11*8,13*8);
		} else if (subMap == 1){
			SpriteManagerAdd(M03SpriteBlock,2*8,11*8);
			SpriteManagerAdd(M03SpriteBlock,3*8,11*8);
			SpriteManagerAdd(M03SpriteBlock,4*8,11*8);
			SpriteManagerAdd(M03SpriteBlock,15*8,6*8);
		} else {
			SpriteManagerAdd(M03SpriteBlock,9*8,2*8);
			SpriteManagerAdd(M03SpriteBlock,10*8,2*8);
			SpriteManagerAdd(M03SpriteBlock,15*8,11*8);
			SpriteManagerAdd(M03SpriteBlock,16*8,11*8);
			SpriteManagerAdd(M03SpriteBlock,17*8,11*8);
		}
		break;
	}
}

void initRandomMap(){
	int8_t rndMap = rand() % 3;
	int8_t rndSubMap = rand() % 3;

	//setRandomBlock(rndMap, rndSubMap);
	switch (rndMap)
	{
	case 2:
		if (rndSubMap == 0){
			//IMPORT_MAP(M03mapC1);
			InitScroll(BANK(M03mapC1), &M03mapC1, M03collision_tiles, 0);
		} else if (rndSubMap == 1){
			//IMPORT_MAP(M03mapC2);
			InitScroll(BANK(M03mapC2), &M03mapC2, M03collision_tiles, 0);
		} else {
			//IMPORT_MAP(M03mapC3);
			InitScroll(BANK(M03mapC3), &M03mapC3, M03collision_tiles, 0);
		}
		SpriteManagerAdd(M03SpritePlayer,88+4,104);
		
		//replaceTiles();
		break;
	case 1:
		if (rndSubMap == 0){
			//IMPORT_MAP(M03mapB1);
			InitScroll(BANK(M03mapB1), &M03mapB1, M03collision_tiles, 0);
		} else if (rndSubMap == 1){
			//IMPORT_MAP(M03mapB2);
			InitScroll(BANK(M03mapB2), &M03mapB2, M03collision_tiles, 0);
		} else {
			//IMPORT_MAP(M03mapB3);
			InitScroll(BANK(M03mapB3), &M03mapB3, M03collision_tiles, 0);
		}
		SpriteManagerAdd(M03SpritePlayer,72+4,112);
		//InitScroll(BANK(M03mapB), &M03mapB, M03collision_tiles, 0);
		//replaceTiles();
		break;
	
	default:
		if (rndSubMap == 0){
			//IMPORT_MAP(M03mapA1);
			InitScroll(BANK(M03mapA1), &M03mapA1, M03collision_tiles, 0);
		} else if (rndSubMap == 1){
			//IMPORT_MAP(M03mapA2);
			InitScroll(BANK(M03mapA2), &M03mapA2, M03collision_tiles, 0);
		} else {
			//IMPORT_MAP(M03mapA3);
			InitScroll(BANK(M03mapA3), &M03mapA3, M03collision_tiles, 0);
		}
		SpriteManagerAdd(M03SpritePlayer,72+4,104);
		//InitScroll(BANK(M03mapA), &M03mapA, M03collision_tiles, 0);
		//replaceTiles();
		break;
	}
	//Se encarga de eliminar los tiles de estrellas referenciales y cambiarlos por sprites
	replaceTiles();
	//setRandomBlock(rndMap, rndSubMap);
	
}


void START() {
	//Iniciar Hud del tiempo
	INIT_HUD(hud);
	UpdateHudTime();

	//Cantidad de estrellas que recolectar
	startCount = 12;
	//Tiempo
	frame = 60;
	
	switch (difficult)
    {
    //Dificultad Dificil
    case 2:
		countdown = 5;
        break;

    //Dificultad normal
    case 1:
		countdown = 7;
        break;
    
    //Dificultad facil
    default:
		countdown = 8;
        break;
    }

	//Instanciar al jugador
	//SpriteManagerAdd(M03SpritePlayer,72+4,104);
	//SpriteManagerAdd(M03SpriteBlock,70-8,104);
	
	initRandomMap();
	//PRINT_POS(3, 4);
	//Printf("SCORE:  %d00 ", winPoints);	

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

	//Si logras el objetivo ganas automaticamente y se cambia de minijuego
	if (startCount <= 0){
		//winPoints++;
		Victory();
		SetState(StateMidGame);
	}

	//Si no lograste el objetivo cuando el contador llego a 0 cambiara el minijuego automaticamente
	if (countdown <= 0){
		//failPoints++;
		Fail();
		SetState(StateMidGame);
	}
}
