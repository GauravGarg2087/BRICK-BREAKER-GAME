#ifndef BALL_H
#define BALL_H

#include<SDL2/SDL.h>
#include"Constants.h"

class Ball{
public:
    int x;
    int y;
    int radius;
    int vx;
    int vy;

    Ball(){
        x=400;
        y=300;
        radius=BALL_RADIUS;
        vx=BALL_SPEED;
        vy=-BALL_SPEED;
    }

    void move(){
        x+=vx;
        y+=vy;
    }

    void draw(SDL_Renderer*renderer){
        SDL_Rect rect={x-radius,y-radius,radius*2,radius*2};
        SDL_RenderFillRect(renderer,&rect);
    }

    SDL_Rect getRect(){
        SDL_Rect rect={x-radius,y-radius,radius*2,radius*2};
        return rect;
    }

    void bounce(){
        if(x-radius<=0){
            vx=-vx;
        }
        if(x+radius>=SCREEN_WIDTH){
            vx=-vx;
        }
        if(y-radius<=0){
            vy=-vy;
        }
    }
};

#endif