#ifndef DEF_JEU_H
#define DEF_JEU_H 

#include <SDL/SDL_ttf.h> 
#include <stdlib.h>
#include <stdio.h>
#include "ia.h" 
#include "fonctionsAutres.h"
#include <SDL\SDL.h>
#define TAILLE_BLOC 30
#define NB_BLOCS_AFFICHABLE_X 30 
#define NB_BLOCS_AFFICHABLE_Y 20 
#define LARGEUR_FENETRE NB_BLOCS_AFFICHABLE_X*TAILLE_BLOC
#define HAUTEUR_FENETRE NB_BLOCS_AFFICHABLE_Y*TAILLE_BLOC 
#define VIDE                0
#define TERRE               1
#define HERBE               2  
#define EAU                 3 
#define FERME_ALLIE         4 
#define FERME_OPPOSANT      5
#define BATIMENTS_ALLIE     6
#define BATIMENTS_OPPOSANT  8 
#define BARRIERE            7
#define ARBRE               9
#define FONDU_HERBE_TERRE  -3 
#define FONDU_TERRE_HERBE  -2
#define FONDU_TERRE_HERBE_HAUT -1
#define FONDU_HERBE_TERRE_HAUT -8
#define FONDU_EAU_TERRE 10
#define FONDU_TERRE_EAU 11
#define FONDU_TERRE_EAU_HAUT 12
#define FONDU_EAU_TERRE_HAUT 13
#define FONDU_HERBE_EAU 14
#define FONDU_EAU_HERBE 15
#define FONDU_HERBE_EAU_HAUT 16
#define FONDU_EAU_HERBE_HAUT  17


Uint32 afficherCarteJeu(Uint32 intervalle, void *parametre);
void initPosJeu(SDL_Rect *pos);
int jeu(char *nomPartie);

#endif
