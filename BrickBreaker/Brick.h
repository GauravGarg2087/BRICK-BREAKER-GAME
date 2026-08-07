#ifndef BRICK_H
#define BRICK_H

#include <SDL2/SDL.h>
#include "Constants.h"

class Brick{

public:

    SDL_Rect rect;

    bool alive;

    bool unbreakable;

    SDL_Color color;

    Brick(int x,int y,SDL_Color c,bool strong=false){

        rect={
            x,
            y,
            BRICK_WIDTH,
            BRICK_HEIGHT
        };

        alive=true;

        unbreakable=strong;

        color=c;

    }

    void draw(SDL_Renderer* renderer){

        if(!alive)
            return;

        SDL_SetRenderDrawColor(
            renderer,
            color.r,
            color.g,
            color.b,
            color.a
        );

        SDL_RenderFillRect(renderer,&rect);

    }

};

#endif