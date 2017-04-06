/*
  Nom: 
  Copyright: 
  Auteur: 
  Date: 05/04/07 18:19
  Description: 
*/
#include "charger.h"
void charger(GtkWidget *widget,gpointer data)
{
GtkWidget *fenetre;

GtkWidget *vBox;
GtkWidget *texte;
GtkWidget *valider;

fenetre=gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(fenetre), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(fenetre), 320, 200);
gtk_window_set_title(GTK_WINDOW(fenetre), "choix de la partie");
 
vBox=gtk_vbox_new(TRUE,0);
gtk_container_add(GTK_CONTAINER(fenetre),vBox);

texte=gtk_entry_new();
gtk_box_pack_start(GTK_BOX(vBox),texte,FALSE,TRUE,0);

valider=gtk_button_new_from_stock("valider");
gtk_box_pack_start(GTK_BOX(vBox),valider,FALSE,FALSE,0);


g_signal_connect(G_OBJECT(fenetre),"destroy", G_CALLBACK(Quitter),fenetre);
g_signal_connect(G_OBJECT(valider),"clicked", G_CALLBACK(validerTexte),texte);
g_signal_connect(G_OBJECT(texte  ),"activate",G_CALLBACK(validerTexte),texte);

gtk_widget_show_all(fenetre);
gtk_main();
}
void validerTexte(GtkWidget *widget,gpointer data)
{
const gchar *recupTxt;
GtkWidget *fenetre;
GtkWidget *info;

FILE *fichier=NULL;
char extension[2000]={0};
recupTxt=gtk_entry_get_text(GTK_ENTRY(data));

fenetre=gtk_widget_get_toplevel(GTK_WIDGET(data));

sprintf(extension,"data/parties/%s.sav",recupTxt);
fichier=fopen(extension,"r+");
if(fichier!=NULL)
{
info = gtk_message_dialog_new (GTK_WINDOW(fenetre),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "commencer");
switch(gtk_dialog_run(GTK_DIALOG(info)))
{
case GTK_RESPONSE_OK:
Quitter(NULL,info);
jeu(extension);
} 
fclose(fichier);
}
else
{
info = gtk_message_dialog_new (GTK_WINDOW(fenetre),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "sauvegarde inexistante");
switch(gtk_dialog_run(GTK_DIALOG(info)))
{
case GTK_RESPONSE_OK:
Quitter(NULL,info);
} 
gtk_main();

}

gtk_widget_destroy(fenetre);

}

