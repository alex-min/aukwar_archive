 /*
  Nom: 
  Copyright: 
  Auteur: 
  Date: 01/04/07 13:56
  Description: 
*/
#include "credits.h"
void credits(void)
{
GtkWidget *fenetre;       
GtkWidget *valider;       
GtkWidget *vBox;  
GtkWidget *label; 
fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(fenetre), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(fenetre), 320, 200);
gtk_window_set_title(GTK_WINDOW(fenetre), "Aukwar");

vBox=gtk_vbox_new(TRUE,0);
gtk_container_add(GTK_CONTAINER(fenetre),vBox);

label=gtk_label_new("prog:\n-cendre\n-bobs\n-masterdr14\n");
gtk_box_pack_start(GTK_BOX(vBox),label, FALSE, FALSE, 0);
gtk_label_set_markup(GTK_LABEL(label), "<span font_desc=\"Arial 15\"><b>Programmation C/C++:</b></span>\n"
"<span font_desc=\"Arial 15\" foreground=\"#0000FF\">-Bobs\n-Masterdr14\n-Cendre\n\n</span>\n<span font_desc=\"Arial 15\"><b>Programmation PHP/HTML:</b></span>\n"
"<span font_desc=\"Arial 15\" foreground=\"#0000FF\">-Amras(Kevin88)\n\n</span>\n""<span font_desc=\"Arial 15\"><b>Graphismes:</b></span>\n""<span font_desc=\"Arial 15\" foreground=\"#0000FF\">-Sniper88\n\n</span>\n""<span font_desc=\"Arial 10\" foreground=\"#0000FF\">ce programme est sous lisence GPL\n et doit etre acompagne de sa license sous le nom license_GPL.txt \npour connaitre les droit de distributions de ce logiciel lisez ce texte.</span>");

valider=gtk_button_new_from_stock("OK");
gtk_box_pack_start(GTK_BOX(vBox),valider, FALSE, FALSE, 0);

g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(Quitter), fenetre);

gtk_widget_show_all(fenetre);
gtk_main();
}
