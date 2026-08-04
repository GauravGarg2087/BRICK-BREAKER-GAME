#include <SDL2/SDL.h>
#include <bits/stdc++.h>
using namespace std;
class Paddle{
    public:
        SDL_Rect rect;
        int speed;
        Paddle(){
            rect = {350,550,100,20};
            speed=8;
        }
        void moveLeft(){
            if(rect.x>0) rect.x -= speed;
        }
        void moveRight(){
            if(rect.x + rect.w< 800){
                rect.x+= speed;
            }
        }
        void draw(SDL_Renderer* renderer){
            SDL_RenderFillRect(renderer,&rect);
        }
};
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
            radius=10;
            vx=4;
            vy=-4;
        }
        void move(){
            x+=vx;
            y+=vy;
        }
        void draw(SDL_Renderer * renderer){
            SDL_Rect rect ={x-radius,y-radius,radius*2,radius*2};
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
            if(x+radius>=800){
                vx=-vx;
            }
            if(y-radius<=0){
                vy=-vy;
            }
        }
};
class Brick{
    public:
        SDL_Rect rect;
        bool alive;
        Brick(int x,int y){
            rect={x,y,70,25};
            alive=true;
        }
        void draw(SDL_Renderer* renderer){
            if(alive){
                SDL_RenderFillRect(renderer,&rect);
            }
        }
};
int main(){
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        cout<<SDL_GetError()<<endl;
        return 1;
    }
    SDL_Window*window=SDL_CreateWindow(
        "Brick Breaker",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );
    if(window==nullptr){
        cout<<SDL_GetError()<<endl;
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer=SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if(renderer==nullptr){
        cout<<SDL_GetError()<<endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    bool running=true;
    SDL_Event event;
    Paddle paddle;
    Ball ball;
    vector <Brick> bricks;
    for(int row=0;row<3;row++){
        for(int col=0;col<10;col++){
            bricks.push_back(Brick(30+col*75,50+row*35));
        }
    }
    bool win=true;
    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                running=false;
            }
        }
        const Uint8* keyboard = SDL_GetKeyboardState(NULL);
        if(keyboard[SDL_SCANCODE_LEFT]){
            paddle.moveLeft();
        }
        if(keyboard[SDL_SCANCODE_RIGHT]){
            paddle.moveRight();
        }
        ball.move();
        ball.bounce();
        if(ball.y+ball.radius>=600){
            running=false;
        }
        SDL_Rect ballRect = ball.getRect();
        if(SDL_HasIntersection(&ballRect,&paddle.rect)){
            ball.vy=-ball.vy;
            ball.y=paddle.rect.y-ball.radius;
        }
        for(auto &brick: bricks){
            if(!brick.alive){
                continue;
            }
            if(SDL_HasIntersection(&ballRect,&brick.rect)){
                brick.alive=false;
                ball.vy=-ball.vy;
                break;
            }
        }
        win =true;
        for(auto &brick: bricks){
            if(brick.alive){
                win=false;
                break;
            }
        }
        if(win){
            running=false;
        }
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        for(auto &brick:bricks){
            brick.draw(renderer);
        }
        paddle.draw(renderer);
        
        ball.draw(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    if(win)cout<<"YOU WIN"<<endl;
    else cout<<"GAME OVER"<<endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
//g++ main.cpp -o game $(sdl2-config --cflags --libs)