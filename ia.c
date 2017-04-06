#include "ia.h"
void construireNouvelleUnite(int nature,int x,int y,int posBatiment[][500])
{
switch(nature)
 {
 case FERME_ALLIE:
 posBatiment[x][y]=FERME_ALLIE;
 break; 
 case FERME_OPPOSANT:
 posBatiment[x][y]=FERME_OPPOSANT;
 break;
 case BARRIERE:
 posBatiment[x][y]=BARRIERE;
 break;
 case SOLDAT_ALLIE:
 posBatiment[x][y]=SOLDAT_ALLIE;
 break;
 case SOLDAT_ENNEMI:
 posBatiment[x][y]=SOLDAT_ENNEMI;
 break;
 }
}
void bougerSoldat(int x_pre,int y_pre,int x,int y,int posBatiment[][500])
{
switch(posBatiment[x_pre][y_pre])
 {
 case SOLDAT_ALLIE:
 if(posBatiment[x][y]!=FERME_ALLIE && posBatiment[x][y]!=FERME_OPPOSANT && posBatiment[x][y]!=BARRIERE && posBatiment[x][y]!=SOLDAT_ALLIE && posBatiment[x][y]!=SOLDAT_ENNEMI)
 {
 posBatiment[x_pre][y_pre]=VIDE;
 posBatiment[x][y]=SOLDAT_ALLIE;
 }
 break;
 case SOLDAT_ENNEMI:
 if(posBatiment[x][y]!=FERME_ALLIE && posBatiment[x][y]!=FERME_OPPOSANT && posBatiment[x][y]!=BARRIERE && posBatiment[x][y]!=SOLDAT_ALLIE && posBatiment[x][y]!=SOLDAT_ENNEMI)
 {
 posBatiment[x_pre][y_pre]=VIDE;
 posBatiment[x][y]=SOLDAT_ENNEMI;
 }
 break;
 default:
 break;
 }
}
void initJoueur(Joueur *joueur)
{
joueur->nbOr=0;
joueur->nbBois=0;
joueur->nbFer=0;
joueur->nbPtsVictoire=100;
joueur->nbNourriture=0;
joueur->nbPopulation=0;
joueur->nbSoldat=1;
joueur->nbFerme=1;
joueur->nom="joueur";
}
void setOr(Joueur *joueur,int nbOr)
{
joueur->nbOr=nbOr;
}
void setFer(Joueur *joueur,int nbFer)
{
joueur->nbFer=nbFer;
}
void setPtsVictoire(Joueur *joueur,int nbPtsVictoire)
{
joueur->nbPtsVictoire=nbPtsVictoire;
}
void setBois(Joueur *joueur,int nbBois)
{
joueur->nbBois=nbBois;
}
void setPopulation(Joueur *joueur,int nbPopulation)
{
joueur->nbPopulation=nbPopulation;
}
void setNourriture(Joueur *joueur,int nbNourriture)
{
joueur->nbNourriture=nbNourriture;
}
void setSoldat(Joueur *joueur,int nbSoldat)
{
joueur->nbSoldat=nbSoldat;
}
void setFerme(Joueur *joueur,int nbFerme)
{ 
joueur->nbFerme=nbFerme;
}


void actionia(int posMatiere[][500],int posBatiment[][500],Joueur *ia)
{
int i=0,j=0;
SDL_Rect posFerme[200],posSoldat[200],arrivee0,arrivee1,arrivee2;
arrivee0.x=50;
arrivee0.y=10;
arrivee1.x=30;
arrivee2.y=30;
arrivee2.x=15;
arrivee2.y=15;
//si y a plus rien...
if(0/*ia->nbPtsVictoire==0 || (ia->nbSoldat==0 && ia->nbFerme==0)*/)
 { 
 fprintf(stdout,"GAGNE!!\n");
 }
//si y a encore de l'ia
else
 {
 setSoldat(ia,0);
 setFerme(ia,0);     
 for(i=0;i<500;i++)
  {
  for(j=0;j<500;j++)
   {
  switch(posBatiment[i][j])
     {
     case SOLDAT_ENNEMI:
     posSoldat[ia->nbSoldat].x=i;
     posSoldat[ia->nbSoldat].y=j;
     ia->nbSoldat+=1;
     break;
     case FERME_OPPOSANT:
     posFerme[ia->nbFerme].x=i;
     posFerme[ia->nbFerme].y=j;
     ia->nbFerme+=1;
     break;
     }
   }
  }//FIN FOR
  
  
  // deplacerIA(posSoldat[1],arrivee2,posBatiment,posMatiere);
  
  if(ia->nbFerme/3 > ia->nbSoldat)
   {
   //construireSoldat(ia,posMatiere,posBatiment);
   }
   if(ia->nbFerme/3 < ia->nbSoldat)
   {
   //attaquer(ia,posMatiere,posBatiment);
   //construreFerme(ia,posMatiere,posBatiment);
   }
   if(ia->nbFerme/3 == ia->nbSoldat)
   {
   //soldats...
   }
 }
}


int aucun(int nature,int posMatiere[][500],int posBatiment[][500])
{
int i=0,j=0;
int aucun=1;
for(i=0;i<500;i++)
 {
  for(i=0;j<500;j++)
  {
  if(posMatiere[i][j]==nature || posBatiment[i][j]==nature)
   {
   aucun=1;
   }
  }
 }
return aucun;
}
void attaquer(Joueur *ia,int posMatiere[][101],int posBatiment[][500])
{
int nbAEnvoyer=ia->nbSoldat/3;
int i=0,j=0;
SDL_Rect posSoldat[200];
SDL_Rect posFerme[200];
SDL_Rect posFermeAllie;
for(i=0;i<500;i++)
 {
  for(j=0;j<500;j++)
   {
   switch(posBatiment[i][j])
     {
     case SOLDAT_ENNEMI:
     posSoldat[ia->nbSoldat].x=i;
     posSoldat[ia->nbSoldat].y=j;
     break;
     case FERME_OPPOSANT:
     posFerme[ia->nbFerme].x=i;
     posFerme[ia->nbFerme].y=j;
     break;
     case FERME_ALLIE:
     posFermeAllie.x=1;
     posFermeAllie.y=j;
     break;
     }
   }
  for(i=0;i<nbAEnvoyer;i++)
   {
   if(posFermeAllie.x>posSoldat[i].x)
    {
    }
   }
 }
}
void deplacerIA(SDL_Rect caseDepart,SDL_Rect caseArrivee,int posBatiment[][500],int posMatiere[][500])
{
int horizontal=0,vertical=0,i=0,j=0;
int decalageDroite=0,decalageHaut=0,decalageBas=0,decalageGauche=0;

if(posBatiment[caseDepart.x][caseDepart.y]!=SOLDAT_ENNEMI ||posMatiere[caseArrivee.x][caseArrivee.y]==EAU ){}
else
 {
 if(caseDepart.x>caseArrivee.x)
   {
   if(posMatiere[caseDepart.x-1][caseDepart.y]!=EAU && posBatiment[caseDepart.x-1][caseDepart.y]!=BARRIERE && posBatiment[caseDepart.x-1][caseDepart.y]!=FERME_ALLIE && posBatiment[caseDepart.x-1][caseDepart.y]!=FERME_OPPOSANT && posBatiment[caseDepart.x-1][caseDepart.y]!=SOLDAT_ALLIE && posBatiment[caseDepart.x-1][caseDepart.y]!=SOLDAT_ENNEMI)
     {
   posBatiment[caseDepart.x-1][caseDepart.y]=SOLDAT_ENNEMI;
   posBatiment[caseDepart.x][caseDepart.y]=VIDE;
     }
   else
    {
    vertical=1;
    }
   }
  if(caseDepart.x<caseArrivee.x)
   {
   if(posMatiere[caseDepart.x+1][caseDepart.y]!=EAU && posBatiment[caseDepart.x+1][caseDepart.y]!=BARRIERE && posBatiment[caseDepart.x+1][caseDepart.y]!=FERME_ALLIE && posBatiment[caseDepart.x+1][caseDepart.y]!=FERME_OPPOSANT && posBatiment[caseDepart.x+1][caseDepart.y]!=SOLDAT_ALLIE && posBatiment[caseDepart.x+1][caseDepart.y]!=SOLDAT_ENNEMI)
     {
   posBatiment[caseDepart.x+1][caseDepart.y]=SOLDAT_ENNEMI;
   posBatiment[caseDepart.x][caseDepart.y]=VIDE;
     }
   else
    {
    vertical=1;
    }
   } 
    if(caseDepart.y>caseArrivee.y)
   {
   if(posMatiere[caseDepart.x][caseDepart.y-1]!=EAU && posBatiment[caseDepart.x][caseDepart.y+1]!=BARRIERE && posBatiment[caseDepart.x][caseDepart.y+1]!=FERME_ALLIE && posBatiment[caseDepart.x][caseDepart.y+1]!=FERME_OPPOSANT && posBatiment[caseDepart.x][caseDepart.y+1]!=SOLDAT_ALLIE && posBatiment[caseDepart.x][caseDepart.y+1]!=SOLDAT_ENNEMI)
     {
   posBatiment[caseDepart.x][caseDepart.y-1]=SOLDAT_ENNEMI;
   posBatiment[caseDepart.x][caseDepart.y]=VIDE;
     }
   else
     {
     horizontal=1;
     }
   } 
    if(caseDepart.y<caseArrivee.y)
   {
    if(posMatiere[caseDepart.x][caseDepart.y+1]!=EAU && posBatiment[caseDepart.x][caseDepart.y-1]!=BARRIERE && posBatiment[caseDepart.x][caseDepart.y-1]!=FERME_ALLIE && posBatiment[caseDepart.x][caseDepart.y-1]!=FERME_OPPOSANT && posBatiment[caseDepart.x][caseDepart.y-1]!=SOLDAT_ALLIE && posBatiment[caseDepart.x][caseDepart.y-1]!=SOLDAT_ENNEMI)
     {
   posBatiment[caseDepart.x][caseDepart.y+1]=SOLDAT_ENNEMI;
   posBatiment[caseDepart.x][caseDepart.y]=VIDE;
     }
   else
    {
    horizontal=1;
    }
   } 
  if(horizontal)
   {
   for(i=1;i<=NB_BLOCS_X - caseDepart.x;i++)
    {
    if(posBatiment[caseDepart.x +i][caseDepart.y]!=VIDE || posMatiere[caseDepart.x +i][caseDepart.y]==EAU)
     {
     decalageDroite=i;
     i=NB_BLOCS_X - caseDepart.x +1;
     }
    }
     for(i=caseDepart.x-1;i>=0;i--)
     {
      if(posBatiment[caseDepart.x-i][caseDepart.y]!=VIDE || posMatiere[caseDepart.x -i][caseDepart.y]==EAU)
      {
      decalageGauche=i;
      
      }
     }
     if(decalageGauche > decalageDroite)
     {
      posBatiment[caseDepart.x-1][caseDepart.y]=SOLDAT_ENNEMI;
      posBatiment[caseDepart.x][caseDepart.y]=VIDE;
     }
     if(decalageGauche <= decalageDroite)
     {
      posBatiment[caseDepart.x+1][caseDepart.y]=SOLDAT_ENNEMI;
      posBatiment[caseDepart.x][caseDepart.y]=VIDE;
     } 
    
   }
   if(vertical)
   {
   for(i=1;i<=NB_BLOCS_Y - caseDepart.y;i++)
    {
    if(posBatiment[caseDepart.x ][caseDepart.y+i]!=VIDE || posMatiere[caseDepart.x ][caseDepart.y+i]==EAU)
     {
     decalageBas=i;
     i=NB_BLOCS_X -  caseDepart.y +1;
     }
    }
     for(i=caseDepart.y-1;i>=0;i--)
     {
      if(posBatiment[caseDepart.x][caseDepart.y-i]!=VIDE || posMatiere[caseDepart.x -i][caseDepart.y]==EAU)
      {
      decalageHaut=i;
      }
     } 
      if(decalageHaut> decalageBas)
     {
      posBatiment[caseDepart.x][caseDepart.y-1]=SOLDAT_ENNEMI;
      posBatiment[caseDepart.x][caseDepart.y]=VIDE;
     }
     if(decalageHaut < decalageBas)
     {
      posBatiment[caseDepart.x][caseDepart.y+1]=SOLDAT_ENNEMI;
      posBatiment[caseDepart.x][caseDepart.y]=VIDE;
     }  
  
  }
   
 }
}
