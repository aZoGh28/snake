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
int running=1;


typedef struct{
    int id;
    int case_x;
    int case_y;
}Pomme;

typedef struct{
    int x;
    int y;
}dir;

typedef struct snake{
    int case_prec_x;
    int case_prec_y;
    int case_x;
    int case_y;
    dir d;
    int frame;
    struct snake* next;
}snake;

Pomme pommes[Nb_Pommes];

void add_snake(snake* head){
    snake* new = malloc(sizeof(snake));
    new->next = NULL;
    snake* cur = head;
    while (cur->next != NULL){
        cur = cur->next;
    }
    cur->next = new;
    new->case_x = cur->case_x;
    new->case_y = cur->case_y;
    new->case_prec_x = cur->case_prec_x;
    new->case_prec_y = cur->case_prec_y;
}


void draw_circle(SDL_Renderer* r, int cx, int cy, int rad){
    for (int dy =-rad; dy<=rad;dy++){
        int dx = (int)sqrt(rad*rad-dy*dy);
        SDL_RenderDrawLine(r, cx-dx,cy+dy,cx+dx,cy+dy);
    }
}

void update_pomme(Pomme* P, snake* s){
    int case_x= rand()% 9;
    int case_y= rand()% 9;
    int free = 1;
    for(int i=0;i<Nb_Pommes;i++){
        Pomme P1 = pommes[i];
        if (case_x==P1.case_x && case_y==P1.case_y){
            free =0;
            update_pomme(P,s);
            break;
        }
    }
    if (free){
        snake* cur=s;
        while (cur->next != NULL){
            if (case_x==cur->case_x && case_y==cur->case_y){
                free =0;
                update_pomme(P,s);
                break;
            }
        cur = cur->next;
        }
    }
    if(free){
        P->case_x=case_x;
        P->case_y=case_y;
    }
}

void update_snake(snake* s, dir pending){
    if (s->frame==10){
        s->frame=-1;
        s->case_prec_x=s->case_x;
        s->case_prec_y=s->case_y;
        s->d= pending;
        s->case_x= (s->case_x+(s->d).x+Nb_case)%Nb_case;
        s->case_y= (s->case_y+(s->d).y+Nb_case)%Nb_case;
        snake* cur=s;
        while (cur->next != NULL){
            int tempx= cur->case_prec_x;
            int tempy= cur->case_prec_y;
            cur = cur->next;
            cur->case_prec_x=cur->case_x;
            cur->case_prec_y=cur->case_y;
            cur->case_x=tempx;
            cur->case_y=tempy;
        }
        for(int i=0;i<Nb_Pommes;i++){
            Pomme* P=&pommes[i];
            if(s->case_x==P->case_x && s->case_y==P->case_y){
                update_pomme(P, s);
                add_snake(s);
                }
            }
        snake* cur2=s->next;
        int case_x=s->case_x;
        int case_y=s->case_y;
        while (cur2 != NULL){
            if(cur2->case_x==case_x && cur2->case_y==case_y){
                running=0;
                break;
            }
            cur2=cur2->next;
        }
    }
    s->frame++;
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

    /*Initialisation du snake*/
    snake s;
    s.case_prec_x=2;
    s.case_prec_y=4;
    s.case_x=2;
    s.case_y=4;
    s.d.x=1;
    s.d.y=0;
    s.frame=5;
    s.next= NULL;

    add_snake(&s);
    add_snake(&s);
    add_snake(&s);

    Uint64 freq = SDL_GetPerformanceFrequency();               // fréquence du compteur de performance pour la gestion du framerate, c'est à dire le nombre de ticks par seconde
    Uint64 debut = SDL_GetPerformanceCounter();                // compteur de performance au début de la boucle, c'est à dire le nombre de ticks depuis le démarrage de SDL != 0
    
    dir pending = s.d;

    while(running){
        SDL_Event e;
        while (SDL_PollEvent(&e)){              
            if (e.type == SDL_QUIT) running = 0;
        }
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderClear(r);
        


        const Uint8* state = SDL_GetKeyboardState(NULL);
        

        if (state[SDL_SCANCODE_UP] && s.d.x != 0)        {pending = (dir){0,-1}; printf("haut");}
        else if (state[SDL_SCANCODE_DOWN] && s.d.x != 0) {pending = (dir){0, 1}; printf("bas");}
        else if (state[SDL_SCANCODE_LEFT] && s.d.y != 0) {pending = (dir){-1,0}; printf("gauche");}
        else if (state[SDL_SCANCODE_RIGHT] && s.d.y != 0){pending = (dir){ 1,0}; printf("droite");
}


        update_snake(&s, pending);

        SDL_SetRenderDrawColor(r,180,30,30,255);
        /* dessine les pommes*/
        for(int i=0; i<Nb_Pommes; i++){
            Pomme P=pommes[i];
            draw_circle(r, P.case_x*taille_case+taille_case/2, P.case_y*taille_case+taille_case/2, rayon_pomme);
        }

        /*dessine le snake*/
        SDL_SetRenderDrawColor(r,30,180,30,255);
        snake* cur=&s;
        while (cur != NULL){
            draw_circle(r, cur->case_x*taille_case+taille_case/2, cur->case_y*taille_case+taille_case/2, rayon_pomme);
            cur = cur->next;
        }

        Uint64 fin = SDL_GetPerformanceCounter();                   // compteur de performance à la fin de la boucle
        Uint64 elapsed_ticks = fin - debut;                      // nombre de ticks écoulés depuis le début de la boucle                                            
        Uint64 target_ticks = (Uint64)((double)freq / 60);  // nombre de ticks visés pour atteindre 60 FPS
        if (elapsed_ticks < target_ticks){                        // si le temps écoulé est inférieur au temps visé, on attend
            Uint64 remaining = target_ticks - elapsed_ticks;      
            Uint32 delay_ms = (Uint32)(remaining * 1000 / freq); //*1000 pour convertir en millisecondes
            if (delay_ms > 0){       // si il y a un délai, on attend (ici c'est grossier pour éviter d'utiliser trop de CPU)
                SDL_Delay(delay_ms);
            }
            while ((SDL_GetPerformanceCounter() - fin) < remaining){}  // on est plus précis là mais ça utilise du CPU
            fin = SDL_GetPerformanceCounter();
            elapsed_ticks = fin - debut;
        }


        double delta = (double)elapsed_ticks/(double)(freq);       // temps écoulé en secondes
        double fps = 1.0/delta; // calcul du FPS
        //printf("%f\n", fps);


        SDL_RenderPresent(r);

        debut = fin;
    }

    SDL_DestroyWindow(w);

return 0;
}