
#include <QGuiApplication>

#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>


#include <SDL.h>
#include "LTexture.h"
#include <SDL_ttf.h>

#include <QImage>

static int renderFunction1(void *data);

static int renderFunction(void *data){
    SDL_Window *window = static_cast<SDL_Window*>(data);
    SDL_Renderer* gRenderer = SDL_CreateRenderer(window, -1, 0);

//    for(;;){


//    SDL_RenderClear(gRenderer);
//    renderPrimitives(gRenderer, 500, 500);
//    SDL_RenderPresent(gRenderer);

//        SDL_Delay(30);
//    }



     SDL_Event e;
     Uint8 r,g,b; r=g=b=0;

    float scale=1.f, rot =0.f, x=100.f,y=100.f;
    while(true){

        SDL_PollEvent(&e);
        if(e.type==SDL_KEYDOWN){
//            SDL_RenderClear(gRenderer);

            switch (e.key.keysym.sym) {
            case SDLK_q:
                r+=32;
                rot+=10;
                break;
            case SDLK_w:
                g+=32;
                x+=5;
                y+=5;
                break;
            case SDLK_e:
                b+=4;
                scale+=0.1;
                qDebug() << "on kegy pressed " << b;
                break;
            default:
                break;
            }
        }
//        SDL_RenderClear(gRenderer);
         renderPrimitives(gRenderer, 500, 500);
        SDL_Rect rect = {0,20, 400,300};
        SDL_Point point = {50, 200};



// float x = 100.f, float y =100.f, float scale=1.0f, int rot=0){
        renderObject1(gRenderer, x,y,scale, rot);

        SDL_RenderPresent(gRenderer);


        SDL_Delay(40);
//        SDL_RenderClear(gRenderer);
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



static int renderFunction1(void *data){
    SDL_Window *window = static_cast<SDL_Window*>(data);
    SDL_Renderer* gRenderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Texture* tx[2];
    SDL_Texture* texture = loadTexture(gRenderer, "car.bmp");
    tx[0] = loadTexture(gRenderer, "car.bmp");
    tx[1] = loadTexture(gRenderer, "bg.bmp");

    int pitch = 600;
    char *pixels;

    SDL_Texture *sTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_YUY2, SDL_TEXTUREACCESS_STREAMING, 920, 520);
//    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

    int ret = SDL_LockTexture(sTexture, nullptr, (void**)&pixels, &pitch);
//    qDebug() << "created texture " << sTexture << pitch << ret << (int)pixels << QString(SDL_GetError());
    memset(pixels, std::rand()/255, 800);
    SDL_UnlockTexture(sTexture);

//    SDL_RenderCopy(gRenderer, sTexture, nullptr, nullptr);
    SDL_RenderPresent(gRenderer);

    SDL_Rect clipRect{0,0,920,780};

    int* pData =  static_cast<int*> ( malloc( clipRect.w * clipRect.h * 4 ) );
    SDL_QueryTexture(texture, NULL, pData, &clipRect.w, &clipRect.h);
//    int w = 1840;
    for(;;){


    static int frm = 0;
    frm ^=1;

//    SDL_LockTexture(sTexture, nullptr, (void**)&pixels, &pitch);
//    memset(pixels, std::rand()/255, 800);
//    SDL_UnlockTexture(sTexture);
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, tx[frm], nullptr, nullptr);
//    SDL_RenderCopy(gRenderer, sTexture, NULL, NULL);
    renderPrimitives(gRenderer, 500, 500);
    SDL_RenderPresent(gRenderer);

    SDL_RenderReadPixels(gRenderer, 0, 0, pData, clipRect.w*4);
    qDebug() << "got pdata " << pData << clipRect.w << clipRect.h << pData[0] << pData[100];
    static int cr = 0;
    if(++cr==800){
        cr -=cr+1;

//        SDL_RenderReadPixels(gRenderer, 0, 0, pData, clipRect.w);

        QImage yuvImage = QImage((uchar*)pData,
                        920,
                        520,
                        QImage::Format_RGB32);

        QVector<QRgb> m_colourMap;
        for(int i = 0; i < 256; i++)
        {
            m_colourMap.push_back(qRgb(i, i, i));
        }
        yuvImage.setColorTable(m_colourMap);

        yuvImage.save("test.jpg");
    }
        SDL_Delay(30);
    }


return 0;
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


