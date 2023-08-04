#include "Banks/SetAutoBank.h"
#include "Keys.h"//KeyPressed
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
//numeros aleatorios
#include "rand.h"

typedef struct 
{
    UBYTE rightTrack;//Determina si estan en la parte izquierda (0) o en la derecha (1) de la carretera
} BGData;

void START() {
	SetFrame(THIS, rand() % 4 + 1);

	if (THIS->x >= 98){
		BGData* data = (BGData*)THIS->custom_data;
    	data->rightTrack = 1;//Determina que estaran en el lado derecho de la carretera
	}
}

void UPDATE() {
	BGData* data = (BGData*)THIS->custom_data;
	
	TranslateSprite(THIS, 0, 1 << delta_time);

	if (THIS->y > 140){
        THIS->y = 0;

		THIS->x = (rand() % 48);

		if (data->rightTrack){
			THIS->x += 98;
		}
		
		SetFrame(THIS, rand() % 4 + 1);
    }
}

void DESTROY() {
}