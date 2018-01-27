
#include <QGuiApplication>

#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>


#include <SDL.h>
#include <LTexture.h>
#include <SDL_ttf.h>



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

    TTF_Font *gFont = TTF_OpenFont( "lazy.ttf", 58 );

    LTexture fontTex;
    SDL_Color textColor = { 255, 255, 255};
    if( !fontTex.loadFromRenderedText(gRenderer, "The quick brown fox jumps over the lazy dog", textColor, gFont) )
        printf( "Failed to render text texture!\n" );




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
        fontTex.render(gRenderer, 40, 40);
        SDL_RenderPresent(gRenderer);


        SDL_Delay(40);
    }

    return 0;
}

int main(int argc, char ** argv)
{
    QGuiApplication app(argc, argv);

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
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

