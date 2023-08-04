#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "rand.h"

//IMPORT_MAP(window);
extern uint8_t winPoints;
extern uint8_t failPoints;
extern uint8_t frame;
extern uint8_t countdown;
extern uint8_t life;
extern uint8_t gameSelect;

uint8_t randomGame;

IMPORT_MAP(hud);//HUD
IMPORT_MAP(MidGameMap);

void UpdateWinNum(){
	uint8_t num = winPoints;
	uint8_t it = 0;
	uint8_t mod = 0;

	while(num > 0)
    {
        mod = num % 10;  //Sacar el ultimo digito del numero
		UpdateMapTile(0, 14-it, 2, 91+(2*mod), 0, 0); 
		UpdateMapTile(0, 14-it, 3, 92+(2*mod), 0, 0);
    
        num = num / 10;   //Dividir num en 10
		it++;
    }
}

void UpdateFailNum(){
	uint8_t num = failPoints;
	uint8_t it = 0;
	uint8_t mod = 0;

	while(num > 0)
    {
        mod = num % 10;  //Sacar el ultimo digito del numero
		UpdateMapTile(0, 17-it, 5, 91+(2*mod), 0, 0); 
		UpdateMapTile(0, 17-it, 6, 92+(2*mod), 0, 0);
    
        num = num / 10;   //Dividir num en 10
		it++;
    }
}

void UpdateLife(){
	//Los tiles empiezan con la vida llena, por lo que solo hay que quitarselo
	//Corazon 1
	if (life < 1){
		UpdateMapTile(0, 4, 10, 54, 0, 0); UpdateMapTile(0, 5, 10, 55, 0, 0); UpdateMapTile(0, 6, 10, 56, 0, 0);
		UpdateMapTile(0, 4, 11, 57, 0, 0); UpdateMapTile(0, 5, 11, 58, 0, 0); UpdateMapTile(0, 6, 11, 59, 0, 0);
		UpdateMapTile(0, 4, 12, 60, 0, 0); UpdateMapTile(0, 5, 12, 61, 0, 0); UpdateMapTile(0, 6, 12, 62, 0, 0);
	}
	//Corazon 2
	if (life < 2){
		UpdateMapTile(0, 10, 10, 54, 0, 0); UpdateMapTile(0, 11, 10, 55, 0, 0); UpdateMapTile(0, 12, 10, 56, 0, 0);
		UpdateMapTile(0, 10, 11, 57, 0, 0); UpdateMapTile(0, 11, 11, 58, 0, 0); UpdateMapTile(0, 12, 11, 59, 0, 0);
		UpdateMapTile(0, 10, 12, 60, 0, 0); UpdateMapTile(0, 11, 12, 61, 0, 0); UpdateMapTile(0, 12, 12, 62, 0, 0);
	}
	//Corazon 3
	if (life < 3){
		UpdateMapTile(0, 7, 13, 54, 0, 0); UpdateMapTile(0, 8, 13, 55, 0, 0); UpdateMapTile(0, 9, 13, 56, 0, 0);
		UpdateMapTile(0, 7, 14, 57, 0, 0); UpdateMapTile(0, 8, 14, 58, 0, 0); UpdateMapTile(0, 9, 14, 59, 0, 0);
		UpdateMapTile(0, 7, 15, 60, 0, 0); UpdateMapTile(0, 8, 15, 61, 0, 0); UpdateMapTile(0, 9, 15, 62, 0, 0);
	}
}

void START() {
	InitScroll(BANK(MidGameMap), &MidGameMap, 0, 0);
	HIDE_WIN;//Esconder HUD
	frame = 60;

	if (life > 0) countdown = 1;
	else countdown = 2;

	randomGame = rand() % 9;

	//Iniciar medidor de dificultad
	SpriteManagerAdd(SpritedifficultyMeter,40,40);

	UpdateWinNum();
	UpdateFailNum();
	UpdateLife();
}

void UPDATE() {
	frame--;
	if (frame <= 0 && countdown > 0){
		frame=60;
		countdown--;
	}
	
	
	//Seleccionar un nuevo minijuego al azar Si la vida es mayor a 0
	if (countdown == 0) {
		if (life > 0){
			//elegir un minijuego al azar
			if (gameSelect == 0){
				switch (randomGame)
				{
				case 8:
					SetState(StateM09);
					break;
				case 7:
					SetState(StateM08);
					break;
				case 6:
					SetState(StateM07);
					break;
				case 5:
					SetState(StateM06);
					break;
				case 4:
					SetState(StateM05);
					break;
				case 3:
					SetState(StateM04);
					break;
				case 2:
					SetState(StateM03);
					break;
				case 1:
					SetState(StateM02);
					break;
				default: //caso 0 o errores
					SetState(StateM01);
					break;
				}
			} else {//Modo de minijuego infinito
				switch (gameSelect)
				{
				case 9:
					SetState(StateM09);
					break;
				case 8:
					SetState(StateM08);
					break;
				case 7:
					SetState(StateM07);
					break;
				case 6:
					SetState(StateM06);
					break;
				case 5:
					SetState(StateM05);
					break;
				case 4:
					SetState(StateM04);
					break;
				case 3:
					SetState(StateM03);
					break;
				case 2:
					SetState(StateM02);
					break;
				default: //caso 1 o errores
					SetState(StateM01);
					break;
				}
			}
			
		} else {
			SetState(StateMainMenu);
		}
		
	}
}
