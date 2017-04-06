/*
  Nom:nouvellePartie.c 
  Copyright: 
  Auteur:cendre 
  Date:05/04/07 19:01
  Description:gére la création d une nouvelle partie 
*/

#include "nouvellePartie.h"
void Quitter_Principal(GtkWidget *widget, gpointer data)
{
GtkWidget *fenetre;
fenetre=gtk_widget_get_toplevel(GTK_WIDGET(data));
gtk_widget_destroy(fenetre); 
SDL_Quit();
exit(EXIT_SUCCESS);
} 
void Quitter(GtkWidget *widget, gpointer data)
{ 
GtkWidget *fenetre;
fenetre=gtk_widget_get_toplevel(GTK_WIDGET(data));
gtk_widget_destroy(fenetre); 
}
void nouvellePartie(void)
{
GtkWidget *fenetre;
GtkWidget *vBox;
GtkWidget *label;

GtkWidget *radioElfe;
GtkWidget *radioNain;
GtkWidget *radioHumain;

GtkWidget *valider;


fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(fenetre), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(fenetre), 320, 200);
gtk_window_set_title(GTK_WINDOW(fenetre), "Choix de race");

vBox=gtk_vbox_new(TRUE,0);
gtk_container_add(GTK_CONTAINER(fenetre),vBox);

label=gtk_label_new("Choix de la race:");
gtk_box_pack_start(GTK_BOX(vBox),label,FALSE,FALSE,0);

radioElfe= gtk_radio_button_new_with_label(NULL, "Elfe");
gtk_box_pack_start(GTK_BOX(vBox),radioElfe,FALSE,FALSE,0);

radioNain= gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radioElfe), "Nain");
gtk_box_pack_start(GTK_BOX(vBox),radioNain,FALSE,FALSE,0);

radioHumain= gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radioElfe), "Humain");
gtk_box_pack_start(GTK_BOX(vBox),radioHumain,FALSE,FALSE,0);

valider=gtk_button_new_from_stock(GTK_STOCK_OK);
gtk_box_pack_start(GTK_BOX(vBox),valider,FALSE,FALSE,0);

g_signal_connect(G_OBJECT(fenetre), "destroy", G_CALLBACK(Quitter),fenetre);
g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(validerChoix),radioElfe);

gtk_widget_show_all(fenetre);
gtk_main();
}
void validerChoix(GtkWidget *boutton, gpointer data)
{
    GtkWidget *info;
    GtkWidget *fenetre;
    GSList *liste;
    static  const gchar *label;

    liste = gtk_radio_button_get_group(GTK_RADIO_BUTTON(data));

    while(liste!=NULL)
    {
        /* chercher le boutton qui est selectioné*/
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(liste->data)))
        {
            //si c est celui la                                                            
            label = gtk_button_get_label(GTK_BUTTON(liste->data));
            liste = NULL;
        }
        else
        {   
            //si c est pas celui la , on essaie le suivant
            liste= g_slist_next(liste);
        }
    }
    
    fenetre = gtk_widget_get_toplevel(GTK_WIDGET(data));

    info = gtk_message_dialog_new (GTK_WINDOW(fenetre),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,
        "demarage d une nouvelle partie avec  %s", label);
    
    FILE* fichier=NULL;
    fichier=fopen("temp.txt","a");

    if((strcmp(label,"Facile")==0)||(strcmp(label,"Moyen")==0)||(strcmp(label,"Difficile")==0))
    {
    fprintf(fichier,"%s",label);
    fclose(fichier);
    gtk_widget_destroy(info);
    gtk_widget_destroy(fenetre); 
    nomSauvegarde();//si on a choisi la difficulte , on passe au nom de la sauvegarde
    }
    if((strcmp(label,"Nain")==0)||(strcmp(label,"Elfe")==0)||(strcmp(label,"Humain")==0))
    {
    fprintf(fichier,"%s\n",label);
    fclose(fichier);
    gtk_widget_destroy(info);
    gtk_widget_destroy(fenetre); 
    choixDifficulte();//si on a choisi la race , on passe au choix de la difficulté
    }
    gtk_dialog_run(GTK_DIALOG(info));  
}
void choixDifficulte(void)
{
GtkWidget *fenetre;
GtkWidget *vBox;
GtkWidget *label;

GtkWidget *radioFacile;
GtkWidget *radioMoyen;
GtkWidget *radioDifficile;

GtkWidget *valider;

gchar *convertUtf8;

fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(fenetre), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(fenetre), 320, 200);
gtk_window_set_title(GTK_WINDOW(fenetre), "Choix de  la difficulte");

vBox=gtk_vbox_new(TRUE,0);
gtk_container_add(GTK_CONTAINER(fenetre),vBox);

convertUtf8=g_locale_to_utf8("Choix de la difficulté:",-1,NULL,NULL,NULL);
label=gtk_label_new(convertUtf8);
gtk_box_pack_start(GTK_BOX(vBox),label,FALSE,FALSE,0);

radioFacile= gtk_radio_button_new_with_label(NULL, "Facile");
gtk_box_pack_start(GTK_BOX(vBox),radioFacile,FALSE,FALSE,0);

radioMoyen= gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radioFacile), "Moyen");
gtk_box_pack_start(GTK_BOX(vBox),radioMoyen,FALSE,FALSE,0);

radioDifficile= gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radioFacile), "Difficile");
gtk_box_pack_start(GTK_BOX(vBox),radioDifficile,FALSE,FALSE,0);

valider=gtk_button_new_from_stock(GTK_STOCK_OK);
gtk_box_pack_start(GTK_BOX(vBox),valider,FALSE,FALSE,0);

g_signal_connect(G_OBJECT(fenetre), "destroy", G_CALLBACK(Quitter),fenetre);
g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(validerChoix),radioFacile);

gtk_widget_show_all(fenetre);
gtk_main();
}
void nomSauvegarde(void)
{
GtkWidget *fenetre;
GtkWidget *texte;
GtkWidget *vBox;
GtkWidget *valider;
GtkWidget *labelS;

fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(fenetre), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(fenetre), 320, 200);
gtk_window_set_title(GTK_WINDOW(fenetre), "Nom de la sauvegarde");


vBox=gtk_vbox_new(TRUE,0);
gtk_container_add(GTK_CONTAINER(fenetre),vBox);

labelS=gtk_label_new("nom de la partie:");
gtk_box_pack_start(GTK_BOX(vBox),labelS,TRUE,TRUE,0);

texte=gtk_entry_new();
gtk_box_pack_start(GTK_BOX(vBox),texte,TRUE,TRUE,0);

g_signal_connect(G_OBJECT(fenetre), "destroy", G_CALLBACK(Quitter), NULL);

valider=gtk_button_new_from_stock(GTK_STOCK_OK);
gtk_box_pack_start(GTK_BOX(vBox),valider,FALSE,FALSE,0);

g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(sauvegarderPartie),texte);
g_signal_connect(G_OBJECT(texte  ), "activate",G_CALLBACK(sauvegarderPartie),texte);



gtk_widget_show_all(fenetre);
gtk_main();
}
void sauvegarderPartie(GtkWidget *label,gpointer data)
{
FILE*fichierRecup=NULL,*sauvegarde=NULL;
FILE *fichier1=NULL,*fichier2=NULL;
const gchar* recup;//pour la zone de texte->nom de la sauvegarde
char race[20];//pour le fichier temp->race
char difficulte[20];//pour le fichier temp->difficulte
char extension[200];//modif pour ajouter l extension
char extension2[200];
GtkWidget *fenetre;//fenetre pour la zone de texte
GtkWidget *info;//fenetre d info pour fichier déjà existant
gchar *utf8;

fenetre = gtk_widget_get_toplevel(GTK_WIDGET(data));

recup=gtk_entry_get_text(GTK_ENTRY(data));



fichierRecup=fopen("temp.txt","r+");
//--------------------------
//recup du fichier temporaire
if(fichierRecup!=NULL)
{
fscanf(fichierRecup,"%s\n%s",&difficulte,&race);
fclose(fichierRecup);
remove("temp.txt");
}
//--------------------------
sprintf(extension,"data/parties/%s_.sav",recup);//ajout de l extension + chemin
sprintf(extension2,"data/parties/%s.sav",recup);
//-----------------------------------------
sauvegarde=fopen(extension,"r");

if(sauvegarde!=NULL)
{
 //test pour savoir si le fichier existe déjà
 utf8=g_locale_to_utf8("Une partie de ce nom existe déjà.",-1,NULL,NULL,NULL);
 info = gtk_message_dialog_new (GTK_WINDOW(fenetre),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        utf8);

fclose(sauvegarde);//on ferme l' essai
switch(gtk_dialog_run(GTK_DIALOG(info)))
{
case GTK_RESPONSE_OK:
Quitter(NULL,info);
} 
gtk_main();
}    
else if(sauvegarde==NULL)                    
{
//-----------------------
//ecriture accordee->le fichier n existe pas encore
sauvegarde=fopen(extension,"w");

fprintf(sauvegarde,"[FICHIER DE SAUVEGARDE]\ndifficulte=%s\nrace=%s\nnbMaison=0\nnbUnite=5\nnbFerme=1\n",race,difficulte);

fclose(sauvegarde);

if((fichier1=fopen(extension,"rb"))==NULL)
exit(0);
fichier2=fopen(extension2,"wb");
xoring(fichier1,fichier2,"cle_Aukwar");
fclose(fichier1);
fclose(fichier2);
remove(extension);

remove("temp.txt");
Quitter(NULL,(gpointer*)fenetre);
jeu(extension);
}

}

