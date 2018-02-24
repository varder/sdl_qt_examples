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
#include<iostream>
struct vec2{
    float x;
    float y;
};

static  vec2 rotate(vec2 point, vec2 shift, float rad){
    float cosF = cos(rad);
    float sinF = sin(rad);
    return{
        point.x*cosF+(-point.y*sinF)+(-shift.x*(cosF-1)+shift.y*sinF),
        point.x*sinF+point.y*cosF+(-shift.y*(cosF-1)-shift.x*sinF)
    };
}

static  vec2 shift(vec2 point, vec2 shift){
    return {
        point.x+shift.x,point.y+shift.y
    };
}

static  vec2 scaleF(vec2 point, float factor){
    return {
        point.x*factor,point.y*factor
    };
}
void affineVec2(vec2 &v){
    v = {5.f*v.x+3.f*v.y, 0.2f*v.x+5.f*v.y};
}

vec2 getAffineVec2(vec2 v){
    return {5.f*v.x+3.f*v.y, 0.2f*v.x+5.f*v.y};
}

void renderObject1(SDL_Renderer *gRenderer, float x = 100.f, float y =100.f, float scale=1.0f, float rot=0){
    SDL_SetRenderDrawColor(gRenderer, 0x88, 0xaa, 0xaa, 0xff);
    int arr[][4]={
        {30,0, 60,70},
        {0,70, 30,0},
        {0,70, 60,70},
        {50,70, 30,0},
        {10,70, 43,45},
    };

    for(int i =0; i <5;i++){
        vec2 psX = {arr[i][0], arr[i][1]};
        vec2 psY = {arr[i][2], arr[i][3]};
        affineVec2(psX);
        affineVec2(psY);
        SDL_RenderDrawLine( gRenderer, psX.x, psX.y,
         psY.x,psY.y);
    }



        float rad=rot*0.0174533f;
        for(int i =0; i <5;i++){
            vec2 point1 = {float(arr[i][0]), float(arr[i][1])};
            vec2 point2 = {float(arr[i][2]), float(arr[i][3])};
            point1 = shift(point1, {x,y});
            point2 = shift(point2, {x,y});
            point1 = scaleF(point1, scale);
            point2 = scaleF(point2, scale);
//            point2 = rotate(point2, { 100.f, 100.f}, rad);
//            point1 = rotate(point1, { 100.f, 100.f}, rad);
            vec2 hotspot = {200,200};
            point2 = rotate(point2, hotspot, rad);
            point1 = rotate(point1, hotspot, rad);

            arr[i][0] = point1.x;
            arr[i][1] = point1.y;
            arr[i][2] = point2.x;
            arr[i][3] = point2.y;

    }

//    SDL_RenderClear(gRenderer);
    for(int i =0; i <5;i++){
        SDL_RenderDrawLine( gRenderer, arr[i][0], arr[i][1],
         arr[i][2], arr[i][3]);
//        std::cout<<arr[i][1]<<arr[i][2];
    }


//    void affineVec2(vec2 &v){
//        v = {5.f*v.x+3.f*v.y,0.f*v.x+5.f*v.y};
//    }

        // x' = x cos b - y sin b
        // y' = x sin b + y cos b                             Equation 3.3
        // z' = z
    static int arr1[][4]={
        {130,220, 160,170},
        {100,170, 130,220},
        {100,170, 160,170},
        {150,170, 130,220},
//        {70,10, 30,0},
        {110,170, 143,145},
    };


//    rad +=10;
//    if(rad>360)rad=0;
    static int isIn =false;
    if(!isIn){
        isIn=true;
        for(int i =0; i <5;i++){
         float x = arr1[i][0];
         float y = arr1[i][1];
        // x' = x cos b - y sin b
         arr1[i][0] = x*cos(rad)-y*sin(rad);
//         y' = x sin b + y cos b
         arr1[i][1] = x*sin(rad)+y*cos(rad);

         x = arr1[i][2];
         y = arr1[i][3];

         arr1[i][2] = x*cos(rad)-y*sin(rad);
//         y' = x sin b + y cos b
         arr1[i][3] = x*sin(rad)+y*cos(rad);
        }
    }
    for(int i =0; i <5;i++){
//        SDL_RenderDrawLine( gRenderer, arr1[i][0], arr1[i][1],
//         arr1[i][2], arr1[i][3]);
    }
}


void renderObject1(SDL_Renderer *gRenderer){
    SDL_SetRenderDrawColor(gRenderer, 0x88, 0xaa, 0xaa, 0xff);
//    SDL_RenderDrawLine( gRenderer, 0, 10, 600, 10);
    static int arr[][4]={
        {30,0, 60,70},
        {0,70, 30,0},
        {0,70, 60,70},
        {50,70, 30,0},
//        {70,10, 30,0},
        {10,70, 43,45},
    };
        static float rad = -45.f*0.0174533f;
    static int isIn1 =false;
    if(!isIn1){
        isIn1=true;
        for(int i =0; i <5;i++){
//            SDL_RenderDrawLine( gRenderer, arr[i][0]*5, arr[i][1]*5,
//             arr[i][2]*5, arr[i][3]*5);
//            vec2 point1 = rotate({float(arr[i][0]), float(arr[i][1])}, { 0.f, 0.f}, rad);
//            vec2 point2 = rotate({float(arr[i][2]), float(arr[i][3])}, { 0.f, 0.f}, rad);

            vec2 point1 = {float(arr[i][0]), float(arr[i][1])};
            vec2 point2 = {float(arr[i][2]), float(arr[i][3])};

            point1 = shift(point1, { 100.f, 200.f});
            point2 = shift(point2, { 100.f, 200.f});
            point1 = rotate(point1, { 0.f, 0.f}, rad);
            point2 = rotate(point2, { 0.f, 0.f}, rad);

            arr[i][0] = point1.x;
            arr[i][1] = point1.y;
            arr[i][2] = point2.x;
            arr[i][3] = point2.y;

        }

    }


    for(int i =0; i <5;i++){
        SDL_RenderDrawLine( gRenderer, arr[i][0], arr[i][1],
         arr[i][2], arr[i][3]);
//        std::cout<<arr[i][1]<<arr[i][2];
    }

        // x' = x cos b - y sin b
        // y' = x sin b + y cos b                             Equation 3.3
        // z' = z
    static int arr1[][4]={
        {130,220, 160,170},
        {100,170, 130,220},
        {100,170, 160,170},
        {150,170, 130,220},
//        {70,10, 30,0},
        {110,170, 143,145},
    };


//    rad +=10;
//    if(rad>360)rad=0;
    static int isIn =false;
    if(!isIn){
        isIn=true;
        for(int i =0; i <5;i++){
         float x = arr1[i][0];
         float y = arr1[i][1];
        // x' = x cos b - y sin b
         arr1[i][0] = x*cos(rad)-y*sin(rad);
//         y' = x sin b + y cos b
         arr1[i][1] = x*sin(rad)+y*cos(rad);

         x = arr1[i][2];
         y = arr1[i][3];

         arr1[i][2] = x*cos(rad)-y*sin(rad);
//         y' = x sin b + y cos b
         arr1[i][3] = x*sin(rad)+y*cos(rad);
        }
    }
    for(int i =0; i <5;i++){
//        SDL_RenderDrawLine( gRenderer, arr1[i][0], arr1[i][1],
//         arr1[i][2], arr1[i][3]);
    }
}


void renderPrimitives(SDL_Renderer *gRenderer, int width, int height){

    //    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    //    SDL_RenderClear(gRenderer);
    //        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_Rect rect = {50, 50, 100, 100};
//    SDL_RenderDrawRect(gRenderer, &rect);

//    SDL_SetRenderDrawColor(gRenderer, 0x88, 0xaa, 0xaa, 0xff);
//    SDL_RenderFillRect(gRenderer, &rect);

    for(int y=0;y<600;y=y+10){
        vec2 x1 = {0.f,y};
        vec2 x2 = {600.f,y};
        vec2 y1 = {y,0.f};
        vec2 y2 = {y,600.f};

        SDL_SetRenderDrawColor(gRenderer, 0x11, 0x11, 0x11, 0);
        SDL_RenderDrawLine( gRenderer, x1.x, x1.y, x2.x,x2.y);
        SDL_RenderDrawLine( gRenderer, y1.x, y1.y, y2.x,y2.y);
//        std::cout<< "got pos before" <<x1.x << "|" << x1.y << " " <<x2.x << "|" <<x2.y;
//        std::cout<< "got pos before" <<y1.x << "|" << y1.y << " " <<y2.x << "|" <<y2.y <<std::endl;
        x1 = getAffineVec2(x1);
        x2 = getAffineVec2(x2);
        y1 = getAffineVec2(y1);
        y2 = getAffineVec2(y2);
//        affineVec2(x1);
//        affineVec2(x2);
//        affineVec2(y1);
//        affineVec2(y2);
//        std::cout<< "got pos " <<x1.x << "|" << x1.y << " affine " <<x2.x << "|" <<x2.y <<std::endl;
//        std::cout<< "got pos " <<y1.x << "|" << y1.y << " affine " <<y2.x << "|" <<y2.y <<std::endl;

//   SDL_SetRenderDrawColor(gRenderer, 0xff, 0x77, 0xaa, 0);
    SDL_SetRenderDrawColor(gRenderer, 0xaa, 0xff, 0x11, 0);
        SDL_RenderDrawLine( gRenderer, x1.x, x1.y, x2.x,x2.y);
        SDL_RenderDrawLine( gRenderer, y1.x, y1.y, y2.x,y2.y);
//        SDL_RenderDrawLine( gRenderer, y, 0, y, 600);
    }


//    SDL_SetRenderDrawColor( gRenderer, 0xaa, 0x00, 0x00, 0xFF );
//    for( int i = 0; i < height; i += 4 )
//    {
//        SDL_RenderDrawPoint( gRenderer, width / 2, i );
//    }
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
