#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <math.h>


#define width 1080
#define height 720
void draw_circle(SDL_Renderer* r, int cx, int cy, int rad){
    for (int dy =-rad; dy<=rad;dy++){
        int dx = (int)sqrt(rad*rad-dy*dy);
        SDL_RenderDrawLine(r, cx-dx,cy+dy,cx+dx,cy+dy);
    }
}

int main(){
    SDL_Window* w = NULL;
    w = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                                SDL_WINDOWPOS_UNDEFINED,
                                                                width,
                                                                height,
                                                                SDL_WINDOW_SHOWN);
    SDL_Renderer* r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED); 
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);

    int running=1;
    while(running){
        SDL_Event e;
        while (SDL_PollEvent(&e)){              
            if (e.type == SDL_QUIT) running = 0;}
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderClear(r);

        SDL_SetRenderDrawColor(r,180,30,30,255);
        draw_circle(r, width/2, height/2, 10);

        SDL_RenderPresent(r);
    }

    SDL_DestroyWindow(w);

return 0;
}