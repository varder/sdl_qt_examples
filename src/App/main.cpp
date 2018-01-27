
#include <QGuiApplication>

#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>


#include <SDL.h>
#include <LTexture.h>
//#include <SDL_ttf.h>


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

SDL_Texture* loadTexture(SDL_Renderer *renderor, std::string path)
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


void updateSize(SDL_Surface* surface, int w, int h){
    SDL_Rect stretchRect;
    stretchRect.x=0;
    stretchRect.y=0;
    stretchRect.w=w;
    stretchRect.h=h;
    SDL_BlitScaled(surface, NULL, surface, &stretchRect);
}

static int renderFunction(void *data){
    SDL_Window *window = static_cast<SDL_Window*>(data);
    SDL_Renderer* gRenderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Texture* texture = loadTexture(gRenderer, "car.bmp");

    SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0x00, 0xff);
    SDL_RenderCopy(gRenderer, texture, nullptr, nullptr);
    SDL_RenderPresent(gRenderer);



    LTexture tex;
    tex.loadFromFile(gRenderer, "car.bmp");
    tex.setBlendMode( SDL_BLENDMODE_BLEND );


     SDL_Event e;
     Uint8 r,g,b; r=g=b=0;
    while(true){
//        qDebug() << "video thread function " << data;

        SDL_PollEvent(&e);
        if(e.type==SDL_KEYDOWN){
            switch (e.key.keysym.sym) {
            case SDLK_q:
                r+=32;
                break;
            case SDLK_w:
                g+=32;
                break;
            case SDLK_e:
                b+=4;
                qDebug() << "on kegy pressed " << b;
                break;
            default:
                break;
            }
        }
//        tex.setColor(r, g, b);
//        tex.setAlpha( b );

        SDL_Rect rect = {0,20, 400,300};
        SDL_Point point = {50, 200};

        tex.renderFlip(gRenderer, 100, 200, &rect, 0., &point, SDL_FLIP_VERTICAL);
//        tex.render(gRenderer, 10, 10);

        renderPrimitives(gRenderer, 500, 500);
        SDL_RenderPresent(gRenderer);


        SDL_Delay(40);
    }

    return 0;
}


int main(int argc, char ** argv)
{
    QGuiApplication app(argc, argv);

    SDL_Init(SDL_INIT_VIDEO);
    QWindow view;
    view.setVisible(true);
    view.setGeometry(500,500, 1500, 1400);

    QWindow *cwindow = new QWindow(&view);
    cwindow->setGeometry(0,0,600,500);
    cwindow->setVisible(true);
    cwindow->setFlags(Qt::WindowTransparentForInput);
//    view.setFlags(Qt::WindowTransparentForInput);
    SDL_Window* window = SDL_CreateWindowFrom((void*)cwindow->winId());

    SDL_Thread *renderThread  = SDL_CreateThread(renderFunction, "Test Render ", (void*)window);


//    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
//    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
//    SDL_RenderFillRect(gRenderer, NULL);
//    SDL_RenderPresent(gRenderer);


//    QQmlContext *ctxt = view.rootContext();
//    view.show();

    return app.exec();
}

