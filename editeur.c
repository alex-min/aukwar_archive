#include "editeur.h"

//pour le calcul des cposBlocase en x et en y
static  SDL_Rect posBloc[500][500]; 
//premiere couche de surface
static  int posMatiere[500][500]={VIDE};
//deuxieme couche de surface
static  int posBatiment[500][500]={VIDE};
  

void editeurNiv(void)
{ 
FILE *fichier1;
if((fichier1=fopen("data/options.opt","rb"))==NULL)
exit(0);

FILE *fichier2 = fopen("data/option2.opt","wb");
xoring(fichier1,fichier2,"cle_Aukwar");
fclose(fichier1);
fclose(fichier2);

SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
SDL_Surface *ecran;  
SDL_WM_SetCaption("Editeur De Niveau",NULL);
ecran=SDL_SetVideoMode(LARGEUR_FENETRE,HAUTEUR_FENETRE,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
SDL_Event event;
int continuer=1,i=0,j=0,clicGaucheEnfonce=0,clicDroitEnfonce=0;
int surfaceActuelle=TERRE;
//choix pour les batiments allies et enemis
int choix=BATIMENTS_ALLIE; 
int nbCases=0;
int tempsPrecedent,tempsActuel;
int priorite=0;

//chargement des surfaces
SDL_Surface *blanc,*terre,*herbe,*eau,*ferme_allie,*ferme_opposant,*barriere,*choixSurface;
SDL_Surface *choixSurfaceRectangle,*fondu_herbe_terre,*fondu_terre_herbe,*fondu_terre_herbe_haut,*fondu_herbe_terre_haut;
SDL_Surface *fondu_eau_terre,*fondu_terre_eau,*fondu_terre_eau_haut,*fondu_eau_terre_haut;
SDL_Surface *fondu_herbe_eau,*fondu_eau_herbe,*fondu_herbe_eau_haut,*fondu_eau_herbe_haut;
SDL_Surface *large,*arbre,*soldat_allie,*soldat_ennemi;
//SDL_Surface *img[20];
//***********************
char compt[20];

/*
for(i=0;i<20;i++)
{
sprintf(compt,"data/images/img_%ld.bmp",i);
img[i]=SDL_LoadBMP(compt);
SDL_SetColorKey(img[i], SDL_SRCCOLORKEY, SDL_MapRGB(img[i]->format,0,0,255));
}
*/

//*************************
blanc=SDL_LoadBMP("data/images/blanc.bmp");
terre=SDL_LoadBMP("data/images/terre.bmp");
herbe=SDL_LoadBMP("data/images/herbe.bmp");
eau=SDL_LoadBMP("data/images/eau.bmp");

fondu_herbe_terre=SDL_LoadBMP("data/images/fondu_herbe_terre.bmp");
fondu_terre_herbe=SDL_LoadBMP("data/images/fondu_terre_herbe.bmp");
fondu_terre_herbe_haut=SDL_LoadBMP("data/images/fondu_terre_herbe_haut.bmp");
fondu_herbe_terre_haut=SDL_LoadBMP("data/images/fondu_herbe_terre_haut.bmp");

fondu_eau_terre=SDL_LoadBMP("data/images/fondu_eau_terre.bmp");
fondu_terre_eau=SDL_LoadBMP("data/images/fondu_terre_eau.bmp");
fondu_terre_eau_haut=SDL_LoadBMP("data/images/fondu_terre_eau_haut.bmp");
fondu_eau_terre_haut=SDL_LoadBMP("data/images/fondu_eau_terre_haut.bmp");

fondu_herbe_eau=SDL_LoadBMP("data/images/fondu_herbe_eau.bmp");
fondu_eau_herbe=SDL_LoadBMP("data/images/fondu_eau_herbe.bmp");
fondu_herbe_eau_haut=SDL_LoadBMP("data/images/fondu_herbe_eau_haut.bmp");
fondu_eau_herbe_haut=SDL_LoadBMP("data/images/fondu_eau_herbe_haut.bmp");

barriere=SDL_LoadBMP("data/images/barriere.bmp");
ferme_allie=SDL_LoadBMP("data/images/ferme_allie.bmp");
ferme_opposant=SDL_LoadBMP("data/images/ferme_opposants.bmp");
soldat_allie=SDL_LoadBMP("data/images/soldat_allie.bmp");
soldat_ennemi=SDL_LoadBMP("data/images/soldat_ennemi.bmp");
large=SDL_LoadBMP("data/images/large.bmp");
choixSurfaceRectangle=SDL_LoadBMP("data/images/choix.bmp");
arbre=SDL_LoadBMP("data/images/arbre.bmp");

//transparence
SDL_SetColorKey(ferme_opposant, SDL_SRCCOLORKEY, SDL_MapRGB(ferme_opposant->format, 255, 0,0));
SDL_SetColorKey(ferme_allie, SDL_SRCCOLORKEY, SDL_MapRGB(ferme_allie->format,0, 0,255));
SDL_SetColorKey(barriere, SDL_SRCCOLORKEY, SDL_MapRGB(barriere->format,0,0,255));
SDL_SetColorKey(arbre, SDL_SRCCOLORKEY, SDL_MapRGB(arbre->format,0,0,255));
SDL_SetColorKey(soldat_allie, SDL_SRCCOLORKEY, SDL_MapRGB(soldat_allie->format,0,0,255));
SDL_SetColorKey(soldat_ennemi, SDL_SRCCOLORKEY, SDL_MapRGB(soldat_ennemi->format,0,0,255));


SDL_Rect posSouris,posTemp,posSelect,posLarge,posChoix;
posLarge.x=900;
posLarge.y=900;

posChoix.x=0;
posChoix.y=0;
SDL_TimerID timer;

//appel de afficherCarte toutes les 150ms
timer = SDL_AddTimer(150,afficherCarte,&posSouris);


while(continuer) 
{
SDL_PollEvent(&event);
priorite=0; 
switch(event.type)
 {
 case SDL_QUIT:
 continuer=0;
 //on quite donc on met tout a vide
 for(i=0;i<101;i++)
 {
 for(j=0;j<101;j++)
  {
  posMatiere[i][j]=VIDE;
  posBatiment[i][j]=VIDE;
  posBloc[i][j].x=0;
  posBloc[i][j].y=0;
  }
 }
 
 break;
 case SDL_ACTIVEEVENT:
 if(event.active.gain ==0)
 {
 posSouris.x=200;//si la souris est sortie de la fenetre 
 posSouris.y=200;//on la met en(200,200) pour que la carte ne bouge plus
 }
 break; 
 case SDL_MOUSEMOTION:
 posSouris.x=event.motion.x;//on met les position de la souris
 posSouris.y=event.motion.y;//dans posSouris
 //si on bouge avec le clic gauche enfoncé
 if(clicGaucheEnfonce)
 {
 //si on a selectionné un batiment
 if((surfaceActuelle==FERME_ALLIE || surfaceActuelle==FERME_OPPOSANT || surfaceActuelle==BARRIERE || surfaceActuelle==ARBRE || surfaceActuelle==SOLDAT_ALLIE || surfaceActuelle==SOLDAT_ENNEMI /*****|| surfaceActuelle==IMG0 ||surfaceActuelle==IMG1||surfaceActuelle==IMG2||surfaceActuelle==IMG3||surfaceActuelle==IMG4||surfaceActuelle==IMG5||surfaceActuelle==IMG6||surfaceActuelle==IMG7||surfaceActuelle==IMG8||surfaceActuelle==IMG9||surfaceActuelle==IMG10||surfaceActuelle==IMG11||surfaceActuelle==IMG12||surfaceActuelle==IMG13||surfaceActuelle==IMG14||surfaceActuelle==IMG15||surfaceActuelle==IMG16||surfaceActuelle==IMG17||surfaceActuelle==IMG18||surfaceActuelle==IMG19*/))
  {
  // posBatiment[calcul de l endroit.x][calcul de l endroit.y]=surfaceActuelle
   posBatiment[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle; 
   
  }
  
  else 
  {
for(i=0;i<=nbCases;i++)
   {
  posMatiere[(event.button.x/TAILLE_BLOC+i)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC+i)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle; 
  posMatiere[(event.button.x/TAILLE_BLOC-i)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC-i)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle;
  posMatiere[(event.button.x/TAILLE_BLOC-i)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC+i)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle;      
  posMatiere[(event.button.x/TAILLE_BLOC+i)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC-i)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle;    
  posMatiere[(event.button.x/TAILLE_BLOC-i)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle;
  posMatiere[(event.button.x/TAILLE_BLOC+i)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle;        
  posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC-i)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle;
  posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC+i)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle;        
   } 
   if(surfaceActuelle==EAU && posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC+1)-(posBloc[0][0].y/TAILLE_BLOC)]==HERBE || surfaceActuelle==HERBE && posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC-1)-(posBloc[0][0].y/TAILLE_BLOC)]==EAU)
   {
   posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=FONDU_EAU_HERBE_HAUT;
   }
   
   if(surfaceActuelle==HERBE && posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC+1)-(posBloc[0][0].y/TAILLE_BLOC)]==EAU || surfaceActuelle==EAU && posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC-1)-(posBloc[0][0].y/TAILLE_BLOC)]==HERBE)
   {
   posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=FONDU_HERBE_EAU_HAUT;
   } 
   
    if(surfaceActuelle==EAU && posMatiere[(event.button.x/TAILLE_BLOC+1)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]==HERBE|| surfaceActuelle==HERBE && posMatiere[(event.button.x/TAILLE_BLOC-1)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]==EAU)
   {
   posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=FONDU_EAU_HERBE;
   }  
    
    if(surfaceActuelle==HERBE && posMatiere[(event.button.x/TAILLE_BLOC+1)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]==EAU || surfaceActuelle==EAU && posMatiere[(event.button.x/TAILLE_BLOC-1)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]==HERBE)
   {
   posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=FONDU_HERBE_EAU;
   }  
   
   if(surfaceActuelle==EAU && posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC+1)-(posBloc[0][0].y/TAILLE_BLOC)]==TERRE || surfaceActuelle==TERRE && posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC-1)-(posBloc[0][0].y/TAILLE_BLOC)]==EAU)
   {
   posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=FONDU_EAU_TERRE_HAUT;
   }  
   
   if(surfaceActuelle==TERRE && posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC+1)-(posBloc[0][0].y/TAILLE_BLOC)]==EAU || surfaceActuelle==EAU && posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC-1)-(posBloc[0][0].y/TAILLE_BLOC)]==TERRE)
   {
   posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=FONDU_TERRE_EAU_HAUT;
   }  
   
   if(surfaceActuelle==TERRE && posMatiere[(event.button.x/TAILLE_BLOC+1)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]==EAU || surfaceActuelle==EAU && posMatiere[(event.button.x/TAILLE_BLOC-1)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]==TERRE)
   {
   posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=FONDU_TERRE_EAU;
   }  
  
  if(surfaceActuelle==EAU && posMatiere[(event.button.x/TAILLE_BLOC+1)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]==TERRE || surfaceActuelle==TERRE && posMatiere[(event.button.x/TAILLE_BLOC-1)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]==EAU)
   {
    posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=FONDU_EAU_TERRE;
   }  
  
  if(surfaceActuelle==TERRE && posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC+1)-(posBloc[0][0].y/TAILLE_BLOC)]==HERBE || surfaceActuelle==HERBE && posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC-1)-(posBloc[0][0].y/TAILLE_BLOC)]==TERRE)
   {
   posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=FONDU_TERRE_HERBE_HAUT;
   }  
  
  if(surfaceActuelle==HERBE && posMatiere[(event.button.x/TAILLE_BLOC+1)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]==TERRE || surfaceActuelle==TERRE && posMatiere[(event.button.x/TAILLE_BLOC-1)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]==HERBE)
   {
   posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=FONDU_HERBE_TERRE;
   priorite=1;
   }         
  
  if(surfaceActuelle==TERRE && posMatiere[(event.button.x/TAILLE_BLOC+1)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]==HERBE || surfaceActuelle==HERBE && posMatiere[(event.button.x/TAILLE_BLOC-1)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]==TERRE)
   {
   if(priorite==0)
     {
   posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=FONDU_TERRE_HERBE;
     priorite=1;
     }
   }  
  if(surfaceActuelle==HERBE && posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC+1)-(posBloc[0][0].y/TAILLE_BLOC)]==TERRE || surfaceActuelle==TERRE && posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC-1)-(posBloc[0][0].y/TAILLE_BLOC)]==HERBE)
   {
   if(priorite==0)
     {
   posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=FONDU_HERBE_TERRE_HAUT;
    priorite=1;  
     }
   }  
  }
 }
 if(clicDroitEnfonce)
 {
 posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=VIDE;

 }
 break;
 case SDL_MOUSEBUTTONDOWN:
 if(event.button.button==SDL_BUTTON_LEFT)
 {
  if((surfaceActuelle==FERME_ALLIE || surfaceActuelle==FERME_OPPOSANT || surfaceActuelle==BARRIERE || surfaceActuelle==ARBRE || surfaceActuelle==SOLDAT_ALLIE || surfaceActuelle==SOLDAT_ENNEMI /*****|| surfaceActuelle==IMG0 ||surfaceActuelle==IMG1||surfaceActuelle==IMG2||surfaceActuelle==IMG3||surfaceActuelle==IMG4||surfaceActuelle==IMG5||surfaceActuelle==IMG6||surfaceActuelle==IMG7||surfaceActuelle==IMG8||surfaceActuelle==IMG9||surfaceActuelle==IMG10||surfaceActuelle==IMG11||surfaceActuelle==IMG12||surfaceActuelle==IMG13||surfaceActuelle==IMG14||surfaceActuelle==IMG15||surfaceActuelle==IMG16||surfaceActuelle==IMG17||surfaceActuelle==IMG18||surfaceActuelle==IMG19*/))
  {
  posBatiment[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle;  
 }
 else
 {
  
  
 for(i=0;i<=nbCases;i++)
   {
  posMatiere[(event.button.x/TAILLE_BLOC+i)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC+i)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle; 
  posMatiere[(event.button.x/TAILLE_BLOC-i)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC-i)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle;
  posMatiere[(event.button.x/TAILLE_BLOC-i)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC+i)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle;      
  posMatiere[(event.button.x/TAILLE_BLOC+i)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC-i)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle;    
  posMatiere[(event.button.x/TAILLE_BLOC-i)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle;
  posMatiere[(event.button.x/TAILLE_BLOC+i)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle;        
  posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC-i)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle;
  posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC+i)-(posBloc[0][0].y/TAILLE_BLOC)]=surfaceActuelle;        
   }
 }
 clicGaucheEnfonce=1;
 }
 if(event.button.button==SDL_BUTTON_RIGHT)
 {
 
 posBatiment[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=VIDE;
 

 posBatiment[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=VIDE;
 posMatiere[(event.button.x/TAILLE_BLOC)-(posBloc[0][0].x/TAILLE_BLOC)][(event.button.y/TAILLE_BLOC)-(posBloc[0][0].y/TAILLE_BLOC)]=VIDE;
 
 clicDroitEnfonce=1;
 }
 break;
 case SDL_MOUSEBUTTONUP:
 if(event.button.button==SDL_BUTTON_LEFT)
 {
 clicGaucheEnfonce=0;
 }
 if(event.button.button==SDL_BUTTON_RIGHT)
 {
 clicDroitEnfonce=0;
 }
 break;
 case SDL_KEYDOWN:
 switch(event.key.keysym.sym)
 {
 case SDLK_ESCAPE:
 continuer=0;
 for(i=0;i<101;i++)
 {
 for(j=0;j<101;j++)
  {
  posMatiere[i][j]=VIDE;
  posBatiment[i][j]=VIDE;
  posBloc[i][j].x=0;
  posBloc[i][j].y=0;
  }
 }
 break;
 case SDLK_KP1:
 surfaceActuelle=TERRE;
 choixSurface=terre;
 break;
 case SDLK_KP2:
 surfaceActuelle=HERBE;
 choixSurface=herbe;
 break;
 case SDLK_KP_PLUS:
 choix=BATIMENTS_ALLIE;
 switch(surfaceActuelle)
 {
 case FERME_OPPOSANT:
 surfaceActuelle=FERME_ALLIE;
 choixSurface=ferme_allie;
 break;
 case SOLDAT_ENNEMI:
 surfaceActuelle=SOLDAT_ALLIE;
 choixSurface=soldat_allie;
 break;
 }
 break;
 case SDLK_KP_MINUS:
 choix=BATIMENTS_OPPOSANT;
 switch(surfaceActuelle)
 {
 case FERME_ALLIE:
 surfaceActuelle=FERME_OPPOSANT;
 choixSurface=ferme_opposant;
 break;
 case SOLDAT_ALLIE:
 surfaceActuelle=SOLDAT_ENNEMI;
 choixSurface=soldat_ennemi;
 break;
 }
 break;
 case SDLK_KP3:
 surfaceActuelle=EAU;
 choixSurface=eau;
 break;
 case SDLK_KP4:
 if(choix==BATIMENTS_ALLIE)
 {
 surfaceActuelle=FERME_ALLIE; 
 choixSurface=ferme_allie;
 }
 if(choix==BATIMENTS_OPPOSANT)
 {
 surfaceActuelle=FERME_OPPOSANT;
 choixSurface=ferme_opposant;
 }
 break;
 case SDLK_KP5:
 surfaceActuelle=ARBRE;
 choixSurface=arbre;
 break;
 case SDLK_KP6:
 if(choix==BATIMENTS_ALLIE)
 {
 surfaceActuelle=SOLDAT_ALLIE; 
 choixSurface=soldat_allie;
 }
 if(choix==BATIMENTS_OPPOSANT)
 {
 surfaceActuelle=SOLDAT_ENNEMI;
 choixSurface=soldat_ennemi;
 }
 break;
 case SDLK_KP9:
 surfaceActuelle=BARRIERE;
 choixSurface=barriere;
 break;
 case SDLK_l:
 nbCases+=1;
 posLarge.x=100;
 posLarge.y=0;
 if(nbCases==2)
 {
 posLarge.x=900;
 posLarge.y=900;
 nbCases=0;
 }
 break;
 case SDLK_s:
 sauvegarderNiv();
 break; 
 case SDLK_c:
 chargerNiv();
 break; 
 case SDLK_TAB:
 //si apui sur tab on met tout a vide
 for(i=0;i<101;i++)
 {
 for(j=0;j<101;j++)
  {
  posMatiere[i][j]=VIDE;
  posBatiment[i][j]=VIDE;
  }
 }
 break; 
 
 break;
 case SDLK_e:
 posBloc[0][0].x=0;//si appuie sur e:
 posBloc[0][0].y=0;//on remet la carte a (0,0)
 break;
//**************************
/*
case SDLK_q:
surfaceActuelle=IMG0;
choixSurface=img[0];
break;
case SDLK_z:
surfaceActuelle=IMG1;
choixSurface=img[1];
break;
case SDLK_b:
surfaceActuelle=IMG2;
choixSurface=img[2];
break;
case SDLK_r:
surfaceActuelle=IMG3;
choixSurface=img[3];
break;
case SDLK_t:
surfaceActuelle=IMG4;
choixSurface=img[4];
break;
case SDLK_y:
surfaceActuelle=IMG5;
choixSurface=img[5];
break;
case SDLK_u:
surfaceActuelle=IMG6;
choixSurface=img[6];
break;
case SDLK_i:
surfaceActuelle=IMG7;
choixSurface=img[7];
break;
case SDLK_o:
surfaceActuelle=IMG8;
choixSurface=img[8];
break;
case SDLK_p:
surfaceActuelle=IMG9;
choixSurface=img[9];
break;
case SDLK_a:
surfaceActuelle=IMG10;
choixSurface=img[10];
break;
case SDLK_n:
surfaceActuelle=IMG11;
choixSurface=img[11];
break;
case SDLK_d:
surfaceActuelle=IMG12;
choixSurface=img[12];
break;
case SDLK_f:
surfaceActuelle=IMG13;
choixSurface=img[13];
break;
case SDLK_g:
surfaceActuelle=IMG14;
choixSurface=img[14];
break;
case SDLK_h:
surfaceActuelle=IMG15;
choixSurface=img[15];
break;
case SDLK_j:
surfaceActuelle=IMG16;
choixSurface=img[16];
break;
case SDLK_k:
surfaceActuelle=IMG17;
choixSurface=img[17];
break;
case SDLK_DOLLAR:
surfaceActuelle=IMG18;
choixSurface=img[18];    
break;
case SDLK_v:
surfaceActuelle=IMG19;
choixSurface=img[19];
break;
*/
//**************************
}
 }
SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));
for(i=0;i<=NB_BLOCS_X;i++)
 {
  for(j=0;j<=NB_BLOCS_Y;j++)
  {
  if((posBloc[i][j].x>-TAILLE_BLOC/4 && posBloc[i][j].x<LARGEUR_FENETRE)&&(posBloc[i][j].y>-TAILLE_BLOC/4 && posBloc[i][j].y<HAUTEUR_FENETRE))
   {
   switch(posMatiere[i][j])
   {
   case FONDU_HERBE_EAU_HAUT:
   SDL_BlitSurface(fondu_herbe_eau_haut,NULL,ecran,&posBloc[i][j]);
   break;
   case FONDU_EAU_HERBE_HAUT:
   SDL_BlitSurface(fondu_eau_herbe_haut,NULL,ecran,&posBloc[i][j]);
   break;
   case FONDU_EAU_HERBE:
   SDL_BlitSurface(fondu_eau_herbe,NULL,ecran,&posBloc[i][j]);
   break;
   case FONDU_HERBE_EAU:
   SDL_BlitSurface(fondu_herbe_eau,NULL,ecran,&posBloc[i][j]);
   break;
   case FONDU_EAU_TERRE_HAUT:
   SDL_BlitSurface(fondu_eau_terre_haut,NULL,ecran,&posBloc[i][j]);
   break;
   case FONDU_TERRE_EAU_HAUT:
   SDL_BlitSurface(fondu_terre_eau_haut,NULL,ecran,&posBloc[i][j]);
   break;
   case FONDU_TERRE_EAU:
   SDL_BlitSurface(fondu_terre_eau,NULL,ecran,&posBloc[i][j]);
   break;
   case FONDU_EAU_TERRE: 
   SDL_BlitSurface(fondu_eau_terre,NULL,ecran,&posBloc[i][j]);
   break;
   case FONDU_TERRE_HERBE_HAUT:
   SDL_BlitSurface(fondu_terre_herbe_haut,NULL,ecran,&posBloc[i][j]);
   break;
   case FONDU_HERBE_TERRE_HAUT: 
   SDL_BlitSurface(fondu_herbe_terre_haut,NULL,ecran,&posBloc[i][j]);
   break;
   case FONDU_HERBE_TERRE:
   SDL_BlitSurface(fondu_herbe_terre,NULL,ecran,&posBloc[i][j]);
   break;
    case FONDU_TERRE_HERBE:
   SDL_BlitSurface(fondu_terre_herbe,NULL,ecran,&posBloc[i][j]);
   break; 
   case TERRE:
   SDL_BlitSurface(terre,NULL,ecran,&posBloc[i][j]);
   break;
   case HERBE:
   SDL_BlitSurface(herbe,NULL,ecran,&posBloc[i][j]);
   break;
   case EAU:
   SDL_BlitSurface(eau,NULL,ecran,&posBloc[i][j]);
   break;
   case VIDE:
   SDL_BlitSurface(blanc,NULL,ecran,&posBloc[i][j]);
   break;
    }
   }
  }
 }
  for(i=0;i<=NB_BLOCS_X;i++)
 {
  for(j=0;j<=NB_BLOCS_Y;j++)
  {
  if((posBloc[i][j].x>-TAILLE_BLOC/4 && posBloc[i][j].x<LARGEUR_FENETRE)&&(posBloc[i][j].y>-TAILLE_BLOC/4 && posBloc[i][j].y<HAUTEUR_FENETRE))
   {
  switch(posBatiment[i][j])
    {
    case FERME_ALLIE:
    SDL_BlitSurface(ferme_allie,NULL,ecran,&posBloc[i][j]);
    break;
    case FERME_OPPOSANT:
    SDL_BlitSurface(ferme_opposant,NULL,ecran,&posBloc[i][j]);
    break;
    case BARRIERE:
    posTemp.x=posBloc[i][j].x-barriere->w+TAILLE_BLOC;
    posTemp.y=posBloc[i][j].y-barriere->h+TAILLE_BLOC;
    SDL_BlitSurface(barriere,NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case ARBRE:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-arbre->h+TAILLE_BLOC;
    SDL_BlitSurface(arbre,NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case SOLDAT_ENNEMI:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-soldat_ennemi->h+TAILLE_BLOC;
    SDL_BlitSurface(soldat_ennemi,NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case SOLDAT_ALLIE:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-soldat_allie->h+TAILLE_BLOC;
    SDL_BlitSurface(soldat_allie,NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    //*********************************
    /*
    case IMG0:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[0]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[0],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG1:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[1]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[1],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG2:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[2]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[2],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG3:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[3]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[3],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG4:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[4]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[4],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG5:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[5]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[5],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG6:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[6]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[6],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG7:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[7]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[7],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG8:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[8]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[8],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG9:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[9]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[9],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG10:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[10]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[10],NULL,ecran,&posTemp);
    initPos(&posTemp);
    case IMG11:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[11]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[11],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG12:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[12]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[12],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG13:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[13]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[13],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG14:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[14]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[14],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG15:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[15]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[0],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG16:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[16]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[16],NULL,ecran,&posTemp);
    initPos(&posTemp);
    case IMG17:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[17]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[17],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    case IMG18:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[18]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[18],NULL,ecran,&posTemp);
    initPos(&posTemp);
    case IMG19:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-img[19]->h+TAILLE_BLOC;
    SDL_BlitSurface(img[19],NULL,ecran,&posTemp);
    initPos(&posTemp);
    break;
    */
    //**********************************
    
    }
   }
  }
 }

SDL_BlitSurface(choixSurfaceRectangle,NULL,ecran,&posChoix);
SDL_BlitSurface(choixSurface,NULL,ecran,&posChoix);
SDL_BlitSurface(large,NULL,ecran,&posLarge);
initPos(&posSelect);
SDL_Flip(ecran);
tempsActuel = SDL_GetTicks();


SDL_Delay(10);

}
SDL_RemoveTimer(timer);

//un paquet de SDL_FreeSurface ......
SDL_FreeSurface(blanc);
SDL_FreeSurface(terre);
SDL_FreeSurface(eau);
SDL_FreeSurface(herbe);
SDL_FreeSurface(ferme_allie);
SDL_FreeSurface(ferme_opposant);
SDL_FreeSurface(barriere);
SDL_FreeSurface(choixSurface);
SDL_FreeSurface(choixSurfaceRectangle);
SDL_FreeSurface(fondu_herbe_terre);
SDL_FreeSurface(fondu_terre_herbe);
SDL_FreeSurface(fondu_terre_herbe_haut);
SDL_FreeSurface(fondu_herbe_terre_haut);
SDL_FreeSurface(fondu_eau_terre);
SDL_FreeSurface(fondu_terre_eau);
SDL_FreeSurface(fondu_terre_eau_haut);
SDL_FreeSurface(fondu_eau_terre_haut);
SDL_FreeSurface(fondu_herbe_eau);
SDL_FreeSurface(fondu_eau_herbe);
SDL_FreeSurface(fondu_herbe_eau_haut);
SDL_FreeSurface(fondu_eau_herbe_haut);
SDL_FreeSurface(large);
SDL_FreeSurface(arbre);

SDL_Quit();
}

Uint32 afficherCarte(Uint32 intervalle, void *parametre)
{
SDL_Rect *posSouris=(SDL_Rect*)parametre;

int i=0,j=0;

if(posSouris->x<TAILLE_BLOC/4)
 {
 if(posBloc[0][0].x <TAILLE_BLOC*2)
  {
 posBloc[0][0].x+=TAILLE_BLOC;
  }
 }
 if(posSouris->x>LARGEUR_FENETRE-(TAILLE_BLOC/2)&& (posBloc[NB_BLOCS_X][0].x>LARGEUR_FENETRE-(3*TAILLE_BLOC)))
 {
 posBloc[0][0].x-=TAILLE_BLOC;
 }
 if(posSouris->y<TAILLE_BLOC && (posBloc[0][0].y <TAILLE_BLOC*2))
 {
 posBloc[0][0].y+=TAILLE_BLOC;
 }
 if(posSouris->y>HAUTEUR_FENETRE-(TAILLE_BLOC/2) && (posBloc[0][NB_BLOCS_Y].y>HAUTEUR_FENETRE-(3*TAILLE_BLOC)))
 {
 posBloc[0][0].y-=TAILLE_BLOC;
 }
for(i=0;i<=NB_BLOCS_X+1;i++)
 {
 for(j=0;j<=NB_BLOCS_Y;j++)
  {
  posBloc[i+1][j].x= posBloc[i][j].x+TAILLE_BLOC;
  posBloc[i][j+1].x= posBloc[i][j].x;
  posBloc[i+1][j].y= posBloc[i][j].y;
  posBloc[i][j+1].y= posBloc[i][j].y+TAILLE_BLOC;   
  }   
 }
return intervalle;
 
}
void sauvegarderNiv(void)
{
GtkWidget *fenetre;
GtkWidget *valider;
GtkWidget *vBox;
GtkWidget *texte;

fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(fenetre), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(fenetre), 320, 200);
gtk_window_set_title(GTK_WINDOW(fenetre), "Sauvegarder le niveau");


vBox=gtk_vbox_new(TRUE,0);
gtk_container_add(GTK_CONTAINER(fenetre),vBox);

texte=gtk_entry_new();
gtk_entry_set_text(GTK_ENTRY(texte),"nom de votre niveau");
gtk_box_pack_start(GTK_BOX(vBox),texte,TRUE,FALSE,0);

valider=gtk_button_new_from_stock("valider");
gtk_box_pack_start(GTK_BOX(vBox),valider,TRUE,FALSE,0);

g_signal_connect(G_OBJECT(fenetre), "destroy", G_CALLBACK(quitter_editeur),fenetre);
g_signal_connect(G_OBJECT(texte), "activate",G_CALLBACK(sauver_texte),texte);
g_signal_connect(G_OBJECT(valider),"clicked", G_CALLBACK(sauver_texte),texte);

gtk_widget_show_all(fenetre);
gtk_main(); 
}  
void quitter_editeur(gpointer data)
{
GtkWidget *fenetre;
fenetre=gtk_widget_get_toplevel(GTK_WIDGET(data));
gtk_widget_destroy(fenetre); 
editeurNiv();//si la fenetre est detruite on retourne a l editeur
}
void sauver_texte(GtkWidget *widget,gpointer data)
{
int i=0,j=0;
GtkWidget *fenetre,*info,*label,*vBox,*valider,*annuler;
FILE *fichier=NULL,*test=NULL;
const gchar *recupTxt,*utf8;
char extension[2000];
recupTxt=gtk_entry_get_text(GTK_ENTRY(data));
sprintf(extension,"data/niveaux/%s.niv",recupTxt);
test=fopen(extension,"r");

fenetre=gtk_widget_get_toplevel(GTK_WIDGET(data));

if(test!=NULL)
{
GtkWidget *texte;
label=gtk_label_new(g_locale_to_utf8("le niveau existe déjà,écraser ?.",-1,NULL,NULL,NULL));
info = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(info), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(info), 320, 200);
gtk_window_set_title(GTK_WINDOW(info), "Confirmation");
 
vBox=gtk_vbox_new(TRUE,0);
gtk_container_add(GTK_CONTAINER(info),vBox);    

texte=gtk_entry_new();
gtk_box_pack_start(GTK_BOX(vBox),texte,FALSE,FALSE,0);  
gtk_entry_set_text(GTK_ENTRY(texte),extension);

gtk_box_pack_start(GTK_BOX(vBox),label,TRUE,FALSE,0);  
  
valider=gtk_button_new_from_stock("valider");
gtk_box_pack_start(GTK_BOX(vBox),valider,TRUE,FALSE,0);  
  
annuler=gtk_button_new_from_stock("annuler");
gtk_box_pack_start(GTK_BOX(vBox),annuler,TRUE,FALSE,0);    

g_signal_connect(G_OBJECT(fenetre), "destroy", G_CALLBACK(Quitter),info);
g_signal_connect(G_OBJECT(valider), "clicked", G_CALLBACK(sauver_direct),texte);
g_signal_connect(G_OBJECT(annuler), "clicked", G_CALLBACK(Quitter),info);                                


gtk_widget_show_all(info);
gtk_main();
fclose(test);
}
if(test==NULL)
{
GtkWidget *entry;
entry=gtk_entry_new();
gtk_entry_set_text(GTK_ENTRY(entry),extension);
sauver_direct(fenetre,(gpointer*)entry);
}
}
void chargerNiv(void)
{
GtkWidget *fenetre;
GtkWidget *valider;
GtkWidget *vBox;
GtkWidget *texte;

fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(fenetre), GTK_WIN_POS_CENTER);
gtk_window_set_default_size(GTK_WINDOW(fenetre), 320, 200);
gtk_window_set_title(GTK_WINDOW(fenetre), "Charger un niveau");


vBox=gtk_vbox_new(TRUE,0);
gtk_container_add(GTK_CONTAINER(fenetre),vBox);

texte=gtk_entry_new();
gtk_entry_set_text(GTK_ENTRY(texte),"nom de votre niveau");
gtk_box_pack_start(GTK_BOX(vBox),texte,TRUE,FALSE,0);

valider=gtk_button_new_from_stock("valider");
gtk_box_pack_start(GTK_BOX(vBox),valider,TRUE,FALSE,0);

g_signal_connect(G_OBJECT(fenetre), "destroy", G_CALLBACK(quitter_editeur),fenetre);
g_signal_connect(G_OBJECT(texte), "activate",G_CALLBACK(charger_texte),(gpointer*)texte);
g_signal_connect(G_OBJECT(valider),"clicked", G_CALLBACK(charger_texte),texte);

gtk_widget_show_all(fenetre);
gtk_main(); 
}  
void charger_texte(GtkWidget *widget,gpointer data)
{
int i=0,j=0,continuer=1;
GtkWidget *fenetre;
GtkWidget *info;
FILE *fichier=NULL,*fichier1=NULL,*fichier2=NULL;
const gchar *recupTxt;
char extension[2000],texteDialogue[2000],extension2[200];
recupTxt=gtk_entry_get_text(GTK_ENTRY(data));
sprintf(extension,"data/niveaux/%s.niv",recupTxt);
sprintf(texteDialogue,"le niveau %s n'existe pas.",recupTxt);
fichier=fopen(extension,"r");
if(fichier!=NULL)
{

fclose(fichier);
chargerNiveau(extension,posMatiere,posBatiment);

}
fenetre=gtk_widget_get_toplevel(GTK_WIDGET(data));
if(fichier==NULL)
{
info = gtk_message_dialog_new (GTK_WINDOW(fenetre),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        texteDialogue);

switch(gtk_dialog_run(GTK_DIALOG(info)))
  {
case GTK_RESPONSE_OK: 
gtk_widget_destroy(info);
  }
  
}
else if(fichier!=NULL)
{

quitter_editeur(fenetre);
}
gtk_main();
}
void sauver_direct(GtkWidget *widget,gpointer* data)
{
GtkWidget *fenetre;
FILE *fichier2;
SDL_Rect posTemp;
SDL_Rect posBloc_mini[101][101];
posBloc_mini[0][0].x=0; 
posBloc_mini[0][0].y=0;
SDL_Surface *ecranDeCapture;
ecranDeCapture= SDL_CreateRGBSurface(SDL_HWSURFACE,NB_BLOCS_X*10,NB_BLOCS_Y*10, 32, 0, 0, 0, 0);


SDL_Surface *blanc_mini,*terre_mini,*herbe_mini,*eau_mini;
SDL_Surface *ferme_allie_mini,*ferme_opposant_mini,*barriere_mini;
SDL_Surface *fondu_terre_herbe_haut_mini,*fondu_herbe_terre_haut_mini,*fondu_herbe_terre_mini,*fondu_terre_herbe_mini;
SDL_Surface *fondu_terre_eau_mini,*fondu_eau_terre_mini,*fondu_terre_eau_haut_mini,*fondu_eau_terre_haut_mini;
SDL_Surface *fondu_eau_herbe_mini,*fondu_eau_herbe_haut_mini,*fondu_herbe_eau_mini,*fondu_herbe_eau_haut_mini;
SDL_Surface *arbre_mini,*soldat_allie_mini,*soldat_ennemi_mini;
blanc_mini=SDL_LoadBMP("data/images/blanc_mini.bmp");
terre_mini=SDL_LoadBMP("data/images/terre_mini.bmp");
herbe_mini=SDL_LoadBMP("data/images/herbe_mini.bmp");
arbre_mini=SDL_LoadBMP("data/images/arbre_mini.bmp");

fondu_terre_herbe_haut_mini=SDL_LoadBMP("data/images/fondu_terre_herbe_haut_mini.bmp");
fondu_herbe_terre_haut_mini=SDL_LoadBMP("data/images/fondu_herbe_terre_haut_mini.bmp");
fondu_herbe_terre_mini=SDL_LoadBMP("data/images/fondu_herbe_terre_mini.bmp");
fondu_terre_herbe_mini=SDL_LoadBMP("data/images/fondu_terre_herbe_mini.bmp");

fondu_terre_eau_mini=SDL_LoadBMP("data/images/fondu_terre_eau_mini.bmp");
fondu_eau_terre_mini=SDL_LoadBMP("data/images/fondu_eau_terre_mini.bmp");
fondu_terre_eau_haut_mini=SDL_LoadBMP("data/images/fondu_terre_eau_haut_mini.bmp");
fondu_eau_terre_haut_mini=SDL_LoadBMP("data/images/fondu_eau_terre_haut_mini.bmp");

fondu_eau_herbe_mini=SDL_LoadBMP("data/images/fondu_eau_herbe_mini.bmp");
fondu_eau_herbe_haut_mini=SDL_LoadBMP("data/images/fondu_eau_herbe_haut_mini.bmp");
fondu_herbe_eau_mini=SDL_LoadBMP("data/images/fondu_herbe_eau_mini.bmp");
fondu_herbe_eau_haut_mini=SDL_LoadBMP("data/images/fondu_herbe_eau_haut_mini.bmp");

eau_mini=SDL_LoadBMP("data/images/eau_mini.bmp");
ferme_allie_mini=SDL_LoadBMP("data/images/ferme_allie_mini.bmp");
ferme_opposant_mini=SDL_LoadBMP("data/images/ferme_opposants_mini.bmp");
soldat_allie_mini=SDL_LoadBMP("data/images/soldat_allie_mini.bmp");
soldat_ennemi_mini=SDL_LoadBMP("data/images/soldat_ennemi_mini.bmp");
barriere_mini=SDL_LoadBMP("data/images/barriere_mini.bmp");

int i=0,j=0;

SDL_SetColorKey(ferme_opposant_mini, SDL_SRCCOLORKEY, SDL_MapRGB(ferme_opposant_mini->format, 255, 0,0));
SDL_SetColorKey(ferme_allie_mini, SDL_SRCCOLORKEY, SDL_MapRGB(ferme_allie_mini->format,0, 0,255));
SDL_SetColorKey(barriere_mini, SDL_SRCCOLORKEY, SDL_MapRGB(barriere_mini->format,0,0,255));
SDL_SetColorKey(arbre_mini, SDL_SRCCOLORKEY, SDL_MapRGB(arbre_mini->format,0,0,255));

const  char* recup=gtk_entry_get_text(GTK_ENTRY(data));
char extension[200]="",extension2[200]="";
FILE *fichier=NULL,*fichier1=NULL;




for(i=0;i<=NB_BLOCS_X+1;i++)
 {
 for(j=0;j<=NB_BLOCS_Y;j++)
  {
  posBloc_mini[i+1][j].x= posBloc_mini[i][j].x+TAILLE_BLOC-20;
  posBloc_mini[i][j+1].x= posBloc_mini[i][j].x;
  posBloc_mini[i+1][j].y= posBloc_mini[i][j].y;
  posBloc_mini[i][j+1].y= posBloc_mini[i][j].y+TAILLE_BLOC-20;   
  }
 }
for(j=0;j<=NB_BLOCS_X+1;j++)
 {
 for(i=0;i<=NB_BLOCS_Y;i++)
  {
 switch(posMatiere[i][j])
   {
    case FONDU_EAU_HERBE:
   SDL_BlitSurface(fondu_eau_herbe_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
    case FONDU_EAU_HERBE_HAUT:
   SDL_BlitSurface(fondu_eau_herbe_haut_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
    case FONDU_HERBE_EAU:
   SDL_BlitSurface(fondu_herbe_eau_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
    case FONDU_HERBE_EAU_HAUT:
   SDL_BlitSurface(fondu_herbe_eau_haut_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
   case FONDU_TERRE_EAU:
   SDL_BlitSurface(fondu_terre_eau_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
   case FONDU_TERRE_EAU_HAUT:
   SDL_BlitSurface(fondu_terre_eau_haut_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
   case FONDU_EAU_TERRE:
   SDL_BlitSurface(fondu_eau_terre_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
   case FONDU_EAU_TERRE_HAUT:
   SDL_BlitSurface(fondu_eau_terre_haut_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
   case FONDU_TERRE_HERBE_HAUT:
   SDL_BlitSurface(fondu_terre_herbe_haut_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
   case FONDU_HERBE_TERRE_HAUT:
   SDL_BlitSurface(fondu_herbe_terre_haut_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
   case FONDU_HERBE_TERRE:
   SDL_BlitSurface(fondu_herbe_terre_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
    case FONDU_TERRE_HERBE:
   SDL_BlitSurface(fondu_terre_herbe_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
   case VIDE:
   SDL_BlitSurface(blanc_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
   case TERRE:
   SDL_BlitSurface(terre_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
   case HERBE:
   SDL_BlitSurface(herbe_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
   case EAU:
   SDL_BlitSurface(eau_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break; 
    }
   switch(posBatiment[i][j])
   {
   case FERME_ALLIE:
   SDL_BlitSurface(ferme_allie_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
   case FERME_OPPOSANT:
   SDL_BlitSurface(ferme_opposant_mini,NULL,ecranDeCapture,&posBloc_mini[i][j]);
   break;
   case BARRIERE:
   posTemp.x=posBloc_mini[i][j].x-barriere_mini->w+TAILLE_BLOC-20;
   posTemp.y=posBloc_mini[i][j].y-barriere_mini->h+TAILLE_BLOC-20;
   SDL_BlitSurface(barriere_mini,NULL,ecranDeCapture,&posTemp);
   initPos(&posTemp);
   break;
   case ARBRE:
   posTemp.x=posBloc_mini[i][j].x;
   posTemp.y=posBloc_mini[i][j].y-arbre_mini->h+TAILLE_BLOC-20;
   SDL_BlitSurface(arbre_mini,NULL,ecranDeCapture,&posTemp);
   initPos(&posTemp);
   break;
    case SOLDAT_ENNEMI:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-soldat_ennemi_mini->h+TAILLE_BLOC;
    SDL_BlitSurface(soldat_ennemi_mini,NULL,ecranDeCapture,&posTemp);
    initPos(&posTemp);
    break;
    case SOLDAT_ALLIE:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-soldat_allie_mini->h+TAILLE_BLOC;
    SDL_BlitSurface(soldat_allie_mini,NULL,ecranDeCapture,&posTemp);
    initPos(&posTemp);
    break; 
   }
  } 
}
sprintf(extension,"%scapture.bmp",recup);
SDL_SaveBMP(ecranDeCapture,extension);

sauvegarderNiveau(recup,posMatiere,posBatiment);


fenetre=gtk_widget_get_toplevel(GTK_WIDGET(data));
gtk_widget_destroy(fenetre);
gtk_widget_destroy(GTK_WIDGET(data));
gtk_widget_destroy(widget); 
}
void initPos(SDL_Rect *pos)
{
pos->x=0;
pos->y=0;
}
