/*
  Name: 
  Copyright: 
  Author: 
  Date: 25/03/07 14:35
  Description: 
*/

#include "options.h"


void options(void)
{
GtkWidget *fenetre;
GtkWidget *vBox;
GtkWidget *vBoxFrame;
GtkWidget *vBoxFrame2;
GtkWidget *separateur;
GtkWidget *barreMusique;
GtkWidget *barreBruitage;
GtkWidget *labelMusique;
GtkWidget *labelBruitage;
GtkWidget *valider;
GtkWidget *frameMusique;
GtkWidget *frameBruitage;
GtkObject *ajustMusique;
GtkObject *ajustBruitage;
gdouble valeurDepartMusique=50;
gdouble valeurDepartBruitage=35;
int volMusique=0;
int volBruitage=0;
gchar valBruitage[20];
gchar valMusique[20];

chargerOptions(&volMusique,&volBruitage);
sprintf(valMusique,"%ld",volMusique);
sprintf(valBruitage,"%ld",volBruitage);
//creation de la fenetre
fenetre=gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(fenetre), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(fenetre), 320, 200);
gtk_window_set_title(GTK_WINDOW(fenetre), "Choix des Options");

vBox=gtk_vbox_new(TRUE,0);
gtk_container_add(GTK_CONTAINER(fenetre),vBox);

frameMusique=gtk_frame_new("Volume de la musique");
gtk_frame_set_shadow_type(GTK_FRAME(frameMusique),GTK_SHADOW_ETCHED_IN);

frameBruitage=gtk_frame_new("Volume des bruitages");
gtk_frame_set_shadow_type(GTK_FRAME(frameBruitage),GTK_SHADOW_ETCHED_IN);

vBoxFrame=gtk_vbox_new(TRUE,0);
gtk_container_add(GTK_CONTAINER(frameMusique),vBoxFrame);

vBoxFrame2=gtk_vbox_new(TRUE,0);
gtk_container_add(GTK_CONTAINER(frameBruitage),vBoxFrame2);


//-------------------------
//creation de la barre musique avec le label

gtk_box_pack_start(GTK_BOX(vBox),frameMusique, TRUE, FALSE, 0);

labelMusique =gtk_label_new(valMusique);
ajustMusique=gtk_adjustment_new(volMusique,0,100,1,10,1);
gtk_box_pack_start(GTK_BOX(vBoxFrame),labelMusique, FALSE, FALSE, 0);

barreMusique=gtk_hscrollbar_new(GTK_ADJUSTMENT(ajustMusique));
gtk_box_pack_start(GTK_BOX(vBoxFrame),barreMusique, TRUE, FALSE, 0);
g_signal_connect(G_OBJECT(barreMusique), "value-changed",G_CALLBACK(barreChange), (GtkWidget*)labelMusique);

//-------------------------
//creation de la barre bruitage avec le label

gtk_box_pack_start(GTK_BOX(vBox),frameBruitage, TRUE, TRUE, 0);

labelBruitage=gtk_label_new(valBruitage);
ajustBruitage=gtk_adjustment_new(volBruitage,0,100,1,10,1);
gtk_box_pack_start(GTK_BOX(vBoxFrame2),labelBruitage, FALSE, FALSE, 0);

barreBruitage=gtk_hscrollbar_new(GTK_ADJUSTMENT(ajustBruitage));
gtk_box_pack_start(GTK_BOX(vBoxFrame2),barreBruitage, TRUE, TRUE, 0);
g_signal_connect(G_OBJECT(barreBruitage), "value-changed",G_CALLBACK(barreChange), (GtkWidget*)labelBruitage);
//------------------------

valider=gtk_button_new_from_stock(GTK_STOCK_OK);
gtk_box_pack_start(GTK_BOX(vBox),valider, TRUE,FALSE, 0);


g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(enregistrerMusique),labelMusique);
g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(enregistrerBruitage),labelBruitage);
g_signal_connect(G_OBJECT(fenetre), "destroy", G_CALLBACK(destroy), fenetre);

gtk_widget_show_all(fenetre);
gtk_main();
}
void barreChange(GtkWidget *widget, gpointer data)
{
  gchar* recup;
  gint valeur;
  valeur = gtk_range_get_value(GTK_RANGE(widget));
  recup = g_strdup_printf("%ld",valeur);
  gtk_label_set_text(GTK_LABEL(data), recup);
  g_free(recup);
}

void destroy(GtkWidget *widget, gpointer data)
{
GtkWidget *fenetre;
fenetre = gtk_widget_get_toplevel(GTK_WIDGET(data));
gtk_widget_destroy(fenetre);
}

void enregistrerMusique(GtkWidget *widget, gpointer data)
{

GtkWidget *fenetre;
const gchar *label;
FILE *fichier=NULL,*fichier1=NULL,*fichier2=NULL;
fenetre = gtk_widget_get_toplevel(GTK_WIDGET(data));
label=gtk_label_get_label(GTK_LABEL(data));


fichier=fopen("data/options_.opt","w");
fprintf(fichier,"[FICHIER D OPTION]\nvolumeMusique=%s\n",label);
fclose(fichier);
if((fichier1=fopen("data/options_.opt","rb"))==NULL)
exit(0);
fichier2=fopen("data/options.opt","wb");
xoring(fichier1,fichier2,"cle_Aukwar");
fclose(fichier1);
fclose(fichier2);
}
void enregistrerBruitage(GtkWidget *widget, gpointer data)
{

GtkWidget *fenetre;
const gchar *label;
FILE *fichier=NULL,*fichier1=NULL,*fichier2=NULL;
int valeur=0;

fenetre = gtk_widget_get_toplevel(GTK_WIDGET(data));
label=gtk_label_get_label(GTK_LABEL(data));


fichier=fopen("data/options_.opt","a");
fprintf(fichier,"volumeBruitage=%s",label);
fclose(fichier);

if((fichier1=fopen("data/options_.opt","rb"))==NULL)
exit(0);
fichier2=fopen("data/options.opt","wb");
xoring(fichier1,fichier2,"cle_Aukwar");
fclose(fichier1);
fclose(fichier2);
remove("data/options_.opt");
gtk_widget_destroy(fenetre);
}
