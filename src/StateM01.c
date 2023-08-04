#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

//IMPORT_MAP(window);
IMPORT_MAP(Blankmap);

extern uint8_t winPoints;
extern uint8_t failPoints;
extern uint8_t frame;
extern uint8_t countdown;

extern uint8_t difficult;

void START() {
	HIDE_WIN;//Esconder el HUD

	//frame = 60;
	//countdown = 10;

	switch (difficult)
    {
    //Dificultad Dificil
    case 2:
		SpriteManagerAdd(M01SpriteBall, 80,60);
        break;

    //Dificultad normal
    case 1:
		SpriteManagerAdd(M01SpriteBall, 80,50);
        break;
    
    //Dificultad facil
    default:
		SpriteManagerAdd(M01SpriteBall, 80,40);
        break;
    }
	
	SpriteManagerAdd(M01SpriteLog,72,120);
	InitScroll(BANK(Blankmap), &Blankmap, 0, 0);
}

void UPDATE() {
}
