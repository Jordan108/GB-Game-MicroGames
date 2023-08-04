#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateGame)\
_STATE(StateMainMenu)\
_STATE(StateMidGame)\
_STATE(StateMenuInfinite)\
_STATE(StateM01)\
_STATE(StateM02)\
_STATE(StateM03)\
_STATE(StateM04)\
_STATE(StateM05)\
_STATE(StateM06)\
_STATE(StateM07)\
_STATE(StateM08)\
_STATE(StateM09)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(M01SpriteLog, M01logSprite)\
_SPRITE_DMG(M01SpriteBall, M01ballSprite)\
_SPRITE_DMG(M02SpritePlayer, M02playerSprite)\
_SPRITE_DMG(M02SpriteVehicleA, M02vehicleASprite)\
_SPRITE_DMG(M02SpriteVehicleB, M02vehicleBSprite)\
_SPRITE_DMG(M02SpriteBackground, M02backgroundSprite)\
_SPRITE_DMG(M03SpritePlayer, M03playerSprite)\
_SPRITE_DMG(M03SpriteStar, M03starSprite)\
_SPRITE_DMG(M03SpriteBlock, M03blockSprite)\
_SPRITE_DMG(M05SpritePlayer, M05playerSprite)\
_SPRITE_DMG(M05SpriteShoot, M05playerShootSprite)\
_SPRITE_DMG(M05SpriteEnemie, M05enemieSprite)\
_SPRITE_DMG(M05SpriteBackground, M05backgroundSprite)\
_SPRITE_DMG(M06SpriteOvni, M06ovniSprite)\
_SPRITE_DMG(M06SpritePlayer, M06playerSprite)\
_SPRITE_DMG(M07SpriteFrog, M07frogSprite)\
_SPRITE_DMG(M07SpriteArrow, M07arrowSprite)\
_SPRITE_DMG(M08SpriteKeys, M08keysSprite)\
_SPRITE_DMG(M09SpritePlayer, M09playerSprite)\
_SPRITE_DMG(M09SpriteOvni, M09ovniSprite)\
_SPRITE_DMG(SpritedifficultyMeter, difficultyMeterSprite)\
SPRITE_DEF_END


#include "ZGBMain_Init.h"

#endif