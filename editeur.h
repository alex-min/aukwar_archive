#ifndef DEF_EDITEUR_H
#define DEF_EDITEUR_H 

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <SDL\SDL.h>
#include "nouvellePartie.h" 
#include "fonctionsAutres.h"
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
#define SOLDAT_ALLIE  19
#define SOLDAT_ENNEMI 18
//***********************
/*
#define IMG0  'a'
#define IMG1  'z'
#define IMG2  'e'
#define IMG3  'r'
#define IMG4  't'
#define IMG5  'y'
#define IMG6  'u'
#define IMG7  'i'
#define IMG8  'o'
#define IMG9  'p'
#define IMG10 'q'
#define IMG11 's'
#define IMG12 'd'
#define IMG13 'f'
#define IMG14 'g'
#define IMG15 'h'
#define IMG16 'j'
#define IMG17 'k'
#define IMG18 'w'
#define IMG19 'x'
*/
//***********************


//lancement de l editeur de niveaux
void editeurNiv(void);

//afficher les blocs  avec timer 
Uint32 afficherCarte(Uint32 intervalle, void *parametre);

void sauvegarderNiv(void);
  
void quitter_editeur(gpointer data);
     
void sauver_texte(GtkWidget *widget,gpointer data);

void chargerNiv(void);

void charger_texte(GtkWidget *widget,gpointer data); 

void sauver_direct(GtkWidget *widget,gpointer* data);

void initPos(SDL_Rect *pos);

#endif
