#include<SDL2/SDL.h>
#include<bits/stdc++.h>
using namespace std;

#include"Constants.h"
#include"Colors.h"
#include"SDLSetup.h"
#include"Paddle.h"
#include"Ball.h"
#include"Brick.h"

int main(){
    SDL_Window*window;
    SDL_Renderer*renderer;

    if(!initializeSDL(window,renderer)){
        return 1;
    }

    bool running=true;
    bool win=true;
    SDL_Event event;
    Paddle paddle;
    Ball ball;
    vector<Brick> bricks;

    for(int row=0;row<3;row++){
        SDL_Color color;

        if(row==0){
            color=RED_BRICK;
        }
        else if(row==1){
            color=GREEN_BRICK;
        }
        else{
            color=BLUE_BRICK;
        }

        for(int col=0;col<10;col++){
            bool strong=(col==3||col==6);
            SDL_Color brickColor=color;

            if(strong){
                brickColor=GRAY_BRICK;
            }

            bricks.push_back(
                Brick(
                    30+col*75,
                    50+row*35,
                    brickColor,
                    strong
                )
            );
        }
    }

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                running=false;
            }
        }

        const Uint8*keyboard=SDL_GetKeyboardState(NULL);

        if(keyboard[SDL_SCANCODE_LEFT]){
            paddle.moveLeft();
        }

        if(keyboard[SDL_SCANCODE_RIGHT]){
            paddle.moveRight();
        }

        ball.move();
        ball.bounce();

        if(ball.y+ball.radius>=SCREEN_HEIGHT){
            running=false;
        }

        SDL_Rect ballRect=ball.getRect();

        if(SDL_HasIntersection(&ballRect,&paddle.rect)){
            ball.vy=-abs(ball.vy);
            ball.y=paddle.rect.y-ball.radius;

            int paddleCenter=paddle.rect.x+paddle.rect.w/2;
            int ballCenter=ball.x;
            int diff=ballCenter-paddleCenter;

            ball.vx=diff/10;

            if(ball.vx==0){
                ball.vx=(rand()%2==0)?1:-1;
            }

            if(ball.vx>6){
                ball.vx=6;
            }

            if(ball.vx<-6){
                ball.vx=-6;
            }
        }

        for(auto &brick:bricks){
            if(!brick.alive){
                continue;
            }

            if(SDL_HasIntersection(&ballRect,&brick.rect)){
                if(!brick.unbreakable){
                    brick.alive=false;
                }

                ball.vy=-ball.vy;
                ball.vx+=rand()%3-1;

                if(ball.vx>6){
                    ball.vx=6;
                }

                if(ball.vx<-6){
                    ball.vx=-6;
                }

                if(ball.vx==0){
                    ball.vx=(rand()%2==0)?1:-1;
                }

                break;
            }
        }

        win=true;

        for(auto &brick:bricks){
            if(brick.alive&&!brick.unbreakable){
                win=false;
                break;
            }
        }

        if(win){
            running=false;
        }

        SDL_SetRenderDrawColor(
            renderer,
            BACKGROUND.r,
            BACKGROUND.g,
            BACKGROUND.b,
            BACKGROUND.a
        );

        SDL_RenderClear(renderer);

        for(auto &brick:bricks){
            brick.draw(renderer);
        }

        SDL_SetRenderDrawColor(
            renderer,
            PADDLE_COLOR.r,
            PADDLE_COLOR.g,
            PADDLE_COLOR.b,
            PADDLE_COLOR.a
        );

        paddle.draw(renderer);

        SDL_SetRenderDrawColor(
            renderer,
            BALL_COLOR.r,
            BALL_COLOR.g,
            BALL_COLOR.b,
            BALL_COLOR.a
        );

        ball.draw(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    if(win){
        cout<<"YOU WIN"<<endl;
    }
    else{
        cout<<"GAME OVER"<<endl;
    }

    destroySDL(window,renderer);
    return 0;
}
//COMPILE: g++ main.cpp -o game $(sdl2-config --cflags --libs)