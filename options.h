 /*
  Nom: 
  Copyright: 
  Auteur: 
  Date: 01/04/07 13:56
  Description: 
*/
#include <stdlib.h>
#include <gtk/gtk.h>
#include "fonctionsAutres.h"
#include <string.h>

//fonction appelee depuis le main
void options(void);

//modifie le label si la barre est bougee
void barreChange(GtkWidget *widget, gpointer data);

//destruction d une fenetre
void destroy(GtkWidget *widget, gpointer data);

//enregistre le volume de la musique dans un fichier
void enregistrerMusique(GtkWidget *widget, gpointer data);

//enregistre le volume des bruitages dans un fichier
void enregistrerBruitage(GtkWidget *widget, gpointer data);
