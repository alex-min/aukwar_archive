 /*
  Nom: 
  Copyright: 
  Auteur: 
  Date: 01/04/07 13:56
  Description: 
*/
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include "jeu.h"
#define ERR_FICHIER_ABS -1
#define OK 0

//fonction qui charge option.opt
int chargerOptions(int *volumeMusique,int *volumeBruitage);

//charger une partie .SAV
int chargerpartie(char *nomFichier,char *difficulte,char *race,int *nbMaisons,int *nbUnite,int*nbFermes);

//sauvegarder une partie en .SAV
int sauverPartie(char *nomFichier,char *difficulte,char *race,int nbMaisons,int nbUnite,int nbFermes);

//fonction de xoring (pour le cryptage)
void xoring(FILE *fichier1,FILE*fichier2,char cle[35]);

//charger des niveaux .NIV
void chargerNiveau(const char *nom,int posMatiere[][500],int posBatiment[][500]); 

//sauvegarder des niveaux en .NIV
void sauvegarderNiveau(const char *nom,int posMatiere[][500],int posBatiment[][500]); 
