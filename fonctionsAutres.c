 /*
  Nom: 
  Copyright: 
  Auteur: 
  Date: 01/04/07 13:56
  Description: 
*/
#include "fonctionsAutres.h"
int chargerOptions(int *volumeMusique,int *volumeBruitage)
{
FILE *fichier=NULL,*fichier1=NULL,*fichier2=NULL;

if((fichier1=fopen("data/options.opt","rb"))==NULL)
exit(0);
fichier2=fopen("data/options_.opt","wb");
xoring(fichier1,fichier2,"cle_Aukwar");
fclose(fichier1);
fclose(fichier2);
fichier=fopen("data/options_.opt","r");
if(fichier==NULL)
 {
return ERR_FICHIER_ABS;
 }
else
 {
fscanf(fichier,"[FICHIER D OPTION]\nvolumeMusique=%ld\nvolumeBruitage=%ld",volumeMusique,volumeBruitage);
fclose(fichier);
remove("data/options_.opt");
return OK;
 }
}
int chargerpartie(char *nomFichier,char *difficulte,char *race,int *nbMaisons,int *nbUnite,int*nbFermes)
{
FILE *fichier=NULL,*fichier1=NULL,*fichier2=NULL;
char extension[200];

if((fichier1=fopen(nomFichier,"rb"))==NULL)
{
return ERR_FICHIER_ABS;
}
sprintf(extension,"%s_",nomFichier);
fichier2=fopen(extension,"wb");
xoring(fichier1,fichier2,"cle_Aukwar");
fclose(fichier1);
fclose(fichier2);
fichier=fopen(extension,"r");
if(fichier==NULL)
 {
return ERR_FICHIER_ABS;
 }
else
 {
fscanf(fichier,"[FICHIER DE SAUVEGARDE]\ndifficulte=%s\nrace=%s\nnbMaison=%ld\nnbUnite=%ld\nnbFerme=%ld\n",difficulte,race,nbMaisons,nbUnite,nbFermes);
fclose(fichier);
remove(extension);
return OK;
 }

}


int sauverPartie(char *nomFichier,char *difficulte,char *race,int nbMaisons,int nbUnite,int nbFermes)
{
FILE *fichier=NULL,*fichier1=NULL,*fichier2=NULL;
char extension[200];

if((fichier1=fopen(nomFichier,"wb"))==NULL)
{
return ERR_FICHIER_ABS;
}
sprintf(extension,"%s_",nomFichier);
fichier=fopen(extension,"r");
if(fichier==NULL)
 {
return ERR_FICHIER_ABS;
 }
else
 {
fprintf(fichier,"[FICHIER DE SAUVEGARDE]\ndifficulte=%s\nrace=%s\nnbMaison=%ld\nnbUnite=%ld\nnbFerme=%ld\n",difficulte,race,nbMaisons,nbUnite,nbFermes);
fclose(fichier);
fichier1=fopen(extension,"rb");
fichier2=fopen(nomFichier,"wb");
xoring(fichier1,fichier2,"cle_Aukwar");
remove(nomFichier);
fclose(fichier1);
fclose(fichier2);
return OK;
 }
}

void chargerNiveau(const char *nom,int posMatiere[][500],int posBatiment[][500])
{
FILE *fichier=NULL,*fichier1=NULL,*fichier2=NULL;
char extension[200];
int i=0,j=0;

fichier=fopen(nom,"r");
if(fichier!=NULL)
{
fclose(fichier);
fichier1 = fopen(nom,"rb");
sprintf(extension,"%s_",nom);
fichier2 = fopen(extension,"wb");
xoring(fichier,fichier2,"cle_Aukwar");
fclose(fichier1);
fclose(fichier2);
fichier=fopen(extension,"r");
for(i=0;i<NB_BLOCS_X+1;i++)
 {
 fscanf(fichier,"\n");
 for(j=0;j<=NB_BLOCS_Y;j++)
  {
  fscanf(fichier,"|%ld %ld|",&posMatiere[i][j],&posBatiment[i][j]);
  }
 }
}
fclose(fichier);
fclose(fichier1);
fclose(fichier2);
remove(extension);
}
void sauvegarderNiveau(const char *nom,int posMatiere[][500],int posBatiment[][500])
{
FILE *fichier=NULL,*fichier1=NULL,*fichier2=NULL;
int i=0,j=0;
char extension[200];

sprintf(extension,"%s_",nom); 
fichier=fopen(extension,"w");

for(i=0;i<=NB_BLOCS_X+1;i++)
 {
 fprintf(fichier,"\n");
 for(j=0;j<=NB_BLOCS_Y;j++)
  {
 fprintf(fichier,"|%ld %ld|",posMatiere[i][j],posBatiment[i][j]);
  } 
}
fclose(fichier);
fichier1 = fopen(extension,"rb");
fichier2 = fopen(nom,"wb");
xoring(fichier,fichier2,"cle_Aukwar");
fclose(fichier1);
fclose(fichier2);
remove(extension);

}
void xoring(FILE*fichier1,FILE*fichier2,char key[35])
{
    
    int xoring;
    int i=0;
    char octet;
    
    while(1)
    {

        if(!fread(&octet,sizeof(char),1,fichier1))
            break;
        else
        {
           
            if(key[i] == '\0')
            {
                
                i = 0;
            }

            xoring = octet ^ key[i];

           
            fwrite(&xoring,sizeof(char),1,fichier2);
        }
       
        i++;
    }
}
