/*
  Nom: 
  Copyright: 
  Auteur: 
  Date: 01/04/07 13:56
  Description:  
*/
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include "jeu.h"
#include "fonctionsAutres.h"
 
//destruction de la fenetre principale
void Quitter(GtkWidget *widget, gpointer data);
void Quitter_Principal(GtkWidget *widget, gpointer data);

//fonction a apppeler dans le main
void nouvellePartie(void);

//valider le choix de la race
void validerChoix(GtkWidget *boutton, gpointer data);

void choixDifficulte(void);

//ajout de l extension
void nomSauvegarde(void);

//sauvegardement de la partie
void sauvegarderPartie(GtkWidget *label,gpointer data);

