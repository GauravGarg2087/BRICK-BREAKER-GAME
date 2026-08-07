#ifndef SDLSETUP_H
#define SDLSETUP_H

#include<SDL2/SDL.h>
#include<iostream>
#include"Constants.h"

using namespace std;

bool initializeSDL(SDL_Window*&window,SDL_Renderer*&renderer){
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        cout<<SDL_GetError()<<endl;
        return false;
    }

    window=SDL_CreateWindow(
        "Brick Breaker",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if(window==nullptr){
        cout<<SDL_GetError()<<endl;
        SDL_Quit();
        return false;
    }

    renderer=SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if(renderer==nullptr){
        cout<<SDL_GetError()<<endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

void destroySDL(SDL_Window*window,SDL_Renderer*renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

#endif