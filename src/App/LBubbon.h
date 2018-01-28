
#pragma once
#include <SDL.h>
#include <LTexture.h>

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

class LButton
{
    SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ]={
        {0, 0, BUTTON_WIDTH, BUTTON_HEIGHT},
        {0, 100, BUTTON_WIDTH, BUTTON_HEIGHT},
        {0, 200, BUTTON_WIDTH, BUTTON_HEIGHT},
        {0, 300, BUTTON_WIDTH, BUTTON_HEIGHT},
    };
        public:
                //Initializes internal variables
                LButton();

                //Sets top left position
                void setPosition( int x, int y );

                //Handles mouse event
                void handleEvent( SDL_Event* e );

                //Shows button sprite
                void render(SDL_Renderer* gRenderer, LTexture *tex)
                {
                    //Show current button sprite
                        tex->render(gRenderer, mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
                }

        private:
                //Top left position
                SDL_Point mPosition;

                //Currently used global sprite
                LButtonSprite mCurrentSprite;
};
