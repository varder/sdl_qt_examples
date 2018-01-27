//
// Created by v.chubar on 26.01.2018.
//

#ifndef JEOMETRY_TEST_LTEXTURE_H
#define JEOMETRY_TEST_LTEXTURE_H

#include <SDL.h>
#include <string>
class LTexture
{
public:
    //Initializes variables
    LTexture(){

    }

    //Deallocates memory
    ~LTexture(){
        free();
    }

    //Loads image at specified path
    bool loadFromFile(SDL_Renderer* gRenderer, std::string path );

    void free();

    //Renders texture at given point
    void render(SDL_Renderer *gRenderer, int x, int y );

    int getWidth();

    int getHeight();

    void render(SDL_Renderer *r, int x, int y, SDL_Rect* clip );

    void setColor( Uint8 red, Uint8 green, Uint8 blue )
    {
        //Modulate texture
        SDL_SetTextureColorMod( mTexture, red, green, blue );
    }

    void setBlendMode( SDL_BlendMode blending )
    {
        //Set blending function
        SDL_SetTextureBlendMode( mTexture, blending );
    }

    void setAlpha( Uint8 alpha )
    {
        //Modulate texture alpha
        SDL_SetTextureAlphaMod( mTexture, alpha );
    }


    void render4ClipAnimation(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip )
    {
        //Set rendering space and render to screen
        SDL_Rect renderQuad = { x, y, mWidth, mHeight };

        //Set clip rendering dimensions
        if( clip != NULL )
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        //Render to screen
        SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
    }

    void renderFlip(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
    {
        //Set rendering space and render to screen
        SDL_Rect renderQuad = { x, y, mWidth, mHeight };

        //Set clip rendering dimensions
        if( clip != NULL )
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        //Render to screen
        SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
    }

private:
    //The actual hardware texture
    SDL_Texture* mTexture = nullptr;

    //Image dimensions
    int mWidth = 0;
    int mHeight = 0;
};

#endif //JEOMETRY_TEST_LTEXTURE_H
