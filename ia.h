#ifndef DEF_IA_H
#define DEF_IA_H 

#include <stdio.h>
#include <stdlib.h>
#include <SDL\SDL.h>
#define TAILLE_BLOC 30
#define NB_BLOCS_X 79
#define NB_BLOCS_Y 80 
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
#define SOLDAT_ALLIE  19
#define SOLDAT_ENNEMI 18
typedef struct _Joueur Joueur;

struct _Joueur
{
int nbOr;
int nbBois;
int nbFer;
int nbPtsVictoire;
int nbNourriture;
int nbPopulation;
int nbFerme;
int nbSoldat;
char *nom;

};

void construireNouvelleUnite(int nature,int x,int y,int posBatiment[][500]);

void bougerSoldat(int x_pre,int y_pre,int x,int y,int posBatiment[][500]);

void initJoueur(Joueur *joueur);

void setOr(Joueur *joueur,int nbOr);
void setFer(Joueur *joueur,int nbFer);
void setPtsVictoire(Joueur *joueur,int nbPtsVictoire);
void setBois(Joueur *joueur,int nbBois);
void setPopulation(Joueur *joueur,int nbPopulation);
void setNourriture(Joueur *joueur,int nbNourriture);

void actionia(int posMatiere[][500],int posBatiment[][500],Joueur *ia);

void attaquer(Joueur *ia,int posMatiere[][101],int posBatiment);

int aucun(int nature,int posMatiere[][500],int posBatiment[][500]);

void deplacerIA(SDL_Rect caseDepart,SDL_Rect caseArrivee,int posBatiment[][500],int posMatiere[][500]);
#endif
