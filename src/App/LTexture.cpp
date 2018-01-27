//
// Created by v.chubar on 26.01.2018.
//

#include "LTexture.h"
bool LTexture::loadFromFile(SDL_Renderer *gRenderer, std::string path)
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());// IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(SDL_Renderer *gRenderer, int x, int y)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

void LTexture::render(SDL_Renderer *gRenderer, int x, int y, SDL_Rect *clip)
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

void renderPrimitives(SDL_Renderer *gRenderer, int width, int height){

    //    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    //    SDL_RenderClear(gRenderer);
    //        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xff);
    SDL_Rect rect = {50, 50, 100, 100};
    SDL_RenderDrawRect(gRenderer, &rect);

    SDL_SetRenderDrawColor(gRenderer, 0x88, 0xaa, 0xaa, 0xff);
    SDL_RenderFillRect(gRenderer, &rect);

    SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0x00, 0xff);
    SDL_RenderDrawLine( gRenderer, 0, height / 2, width, height / 2 );

    SDL_SetRenderDrawColor( gRenderer, 0xaa, 0x00, 0x00, 0xFF );
    for( int i = 0; i < height; i += 4 )
    {
        SDL_RenderDrawPoint( gRenderer, width / 2, i );
    }
}

SDL_Texture *loadTexture(SDL_Renderer *renderor, std::string path)
{
    //The final optimized image
    SDL_Texture* texture;

    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        //Convert surface to screen format
        texture = SDL_CreateTextureFromSurface(renderor, loadedSurface);
        if( texture== NULL )
        {
            printf( "Unable to optimize texture %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return texture;//optimizedSurface;
}

void updateSize(SDL_Surface *surface, int w, int h){
    SDL_Rect stretchRect;
    stretchRect.x=0;
    stretchRect.y=0;
    stretchRect.w=w;
    stretchRect.h=h;
    SDL_BlitScaled(surface, NULL, surface, &stretchRect);
}
