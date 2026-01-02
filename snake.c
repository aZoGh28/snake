#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <math.h>


#define width 900
#define height 900
#define Nb_case 9
#define taille_case 100
#define rayon_pomme 45
#define Nb_Pommes 5


typedef struct{
    int id;
    int case_x;
    int case_y;
}Pomme;

Pomme pommes[Nb_Pommes];

void draw_circle(SDL_Renderer* r, int cx, int cy, int rad){
    for (int dy =-rad; dy<=rad;dy++){
        int dx = (int)sqrt(rad*rad-dy*dy);
        SDL_RenderDrawLine(r, cx-dx,cy+dy,cx+dx,cy+dy);
    }
}



int main(){
    SDL_Window* w = NULL;
    w = SDL_CreateWindow("Snake",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_SHOWN);
    SDL_Renderer* r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED); 
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);


    /* Initiailisation des pommes*/
    pommes[0].id=0;
    pommes[0].case_x=5;
    pommes[0].case_y=3;
    pommes[1].id=1;
    pommes[1].case_x=7;
    pommes[1].case_y=3;
    pommes[2].id=2;
    pommes[2].case_x=6;
    pommes[2].case_y=4;
    pommes[3].id=3;
    pommes[3].case_x=5;
    pommes[3].case_y=5;
    pommes[4].id=4;
    pommes[4].case_x=7;
    pommes[4].case_y=5;


    int running=1;
    while(running){
        SDL_Event e;
        while (SDL_PollEvent(&e)){              
            if (e.type == SDL_QUIT) running = 0;}
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderClear(r);

        SDL_SetRenderDrawColor(r,180,30,30,255);
        for(int i=0; i<Nb_Pommes; i++){
            Pomme P=pommes[i];
            draw_circle(r, P.case_x*taille_case+taille_case/2, P.case_y*taille_case+taille_case/2, rayon_pomme);
        }

        SDL_RenderPresent(r);
    }

    SDL_DestroyWindow(w);

return 0;
}