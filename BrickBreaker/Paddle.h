#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>
#include "Constants.h"

class Paddle{
public:

    SDL_Rect rect;
    int speed;

    Paddle(){

        rect={
            350,
            550,
            PADDLE_WIDTH,
            PADDLE_HEIGHT
        };

        speed=PADDLE_SPEED;
    }

    void moveLeft(){

        if(rect.x>0){

            rect.x-=speed;
        }

    }

    void moveRight(){

        if(rect.x+rect.w<SCREEN_WIDTH){

            rect.x+=speed;

        }

    }

    void draw(SDL_Renderer* renderer){

        SDL_RenderFillRect(renderer,&rect);

    }

};

#endif