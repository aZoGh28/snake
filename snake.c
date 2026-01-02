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

typedef struct{
    int case_x;
    int case_y;
    char dir;
    struct snake* next;
}snake;

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

    Uint64 freq = SDL_GetPerformanceFrequency();               // fréquence du compteur de performance pour la gestion du framerate, c'est à dire le nombre de ticks par seconde
    Uint64 debut = SDL_GetPerformanceCounter();                // compteur de performance au début de la boucle, c'est à dire le nombre de ticks depuis le démarrage de SDL != 0


    int running=1;
    while(running){
        Uint64 fin = SDL_GetPerformanceCounter();                   // compteur de performance à la fin de la boucle
        Uint64 elapsed_ticks = fin - debut;                      // nombre de ticks écoulés depuis le début de la boucle                                            
        Uint64 target_ticks = (Uint64)((double)freq / 60);
        SDL_Event e;
        while (SDL_PollEvent(&e)){              
            if (e.type == SDL_QUIT) running = 0;}
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderClear(r);

        SDL_SetRenderDrawColor(r,180,30,30,255);
        /* dessine les pommes*/
        for(int i=0; i<Nb_Pommes; i++){
            Pomme P=pommes[i];
            draw_circle(r, P.case_x*taille_case+taille_case/2, P.case_y*taille_case+taille_case/2, rayon_pomme);
        }
        double delta = (double)elapsed_ticks/(double)(freq);       // temps écoulé en secondes
        double fps = 1.0/delta; // calcul du FPS
        printf("%f\n", fps);


        SDL_RenderPresent(r);

        debut = fin;
    }

    SDL_DestroyWindow(w);

return 0;
}