/*
  Nom: 
  Copyright: 
  Auteur: 
  Date: 01/04/07 13:56
  Description: 
*/
#include <stdlib.h>
#include <gtk/gtk.h>
#include "nouvellePartie.h"
#include "charger.h"
#include "options.h"
#include "credits.h"
#include "editeur.h"

int main(int argc,char **argv)
{
    
    GtkWidget *fenetre;
    GtkWidget *vBox;
    GtkWidget *bouttonNouveau;
    GtkWidget *bouttonCharger;
    GtkWidget *bouttonEditeur;
    GtkWidget *bouttonOptions;
    GtkWidget *bouttonCredit;
    GtkWidget *bouttonQuitter;

    
    gtk_init(&argc,&argv);

    fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(fenetre), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(fenetre), 320, 200);
    gtk_window_set_title(GTK_WINDOW(fenetre), "Aukwar");

   vBox=gtk_vbox_new(TRUE,0);
   gtk_container_add(GTK_CONTAINER(fenetre),vBox);
   
   bouttonNouveau=gtk_button_new_with_mnemonic("_Nouvelle Partie");
   gtk_box_pack_start(GTK_BOX(vBox),bouttonNouveau,TRUE,TRUE,0);
  
   bouttonCharger=gtk_button_new_with_mnemonic("_Charger Partie");
   gtk_box_pack_start(GTK_BOX(vBox), bouttonCharger,TRUE,TRUE,0);
   
   bouttonEditeur=gtk_button_new_with_mnemonic("_Editeur De Niveaux");
   gtk_box_pack_start(GTK_BOX(vBox),bouttonEditeur,TRUE,TRUE,0);
   
   bouttonOptions=gtk_button_new_with_mnemonic("_Options");
   gtk_box_pack_start(GTK_BOX(vBox),bouttonOptions,TRUE,TRUE,0);
  
   bouttonCredit=gtk_button_new_with_mnemonic("_Credits");
   gtk_box_pack_start(GTK_BOX(vBox),bouttonCredit,TRUE,TRUE,0);
  
   bouttonQuitter=gtk_button_new_with_mnemonic("_Quitter");
   gtk_box_pack_start(GTK_BOX(vBox),bouttonQuitter,TRUE,TRUE,0);
    
    g_signal_connect(G_OBJECT(fenetre), "destroy", G_CALLBACK(Quitter_Principal), NULL);
     
    g_signal_connect(G_OBJECT(bouttonNouveau), "clicked", G_CALLBACK(nouvellePartie), NULL);
    g_signal_connect(G_OBJECT(bouttonCharger), "clicked", G_CALLBACK(charger),NULL);
    g_signal_connect(G_OBJECT(bouttonEditeur), "clicked", G_CALLBACK(editeurNiv), NULL);
    g_signal_connect(G_OBJECT(bouttonOptions), "clicked", G_CALLBACK(options), NULL);
    g_signal_connect(G_OBJECT(bouttonCredit), "clicked", G_CALLBACK(credits), NULL);
    g_signal_connect(G_OBJECT(bouttonQuitter), "clicked", G_CALLBACK(Quitter_Principal),(gpointer*)bouttonQuitter);
 
    gtk_widget_show_all(fenetre);
    gtk_main();
   
    return EXIT_SUCCESS;
}
