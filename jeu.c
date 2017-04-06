#include "jeu.h"
static  SDL_Rect posBloc[500][500];
static  int posMatiere[500][500]={VIDE};
static  int posBatiment[500][500]={VIDE}; 
static  Joueur ia;

SDL_Surface *ecran = NULL; 
void pause();

int jeu(char *nomPartie)
{
    
    SDL_Surface *barre,*score;
    barre=SDL_LoadBMP("data/images/barre.bmp");
    score=SDL_LoadBMP("data/images/carre.bmp");
    if(TTF_Init() == -1)
{
    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
}
    SDL_Surface  *texteOr = NULL,*textePtsVictoire=NULL,*textePopulation=NULL;
    SDL_Surface *texteBois=NULL,*texteFer=NULL,*texteNourriture=NULL;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE+100, 32, SDL_HWSURFACE|SDL_FULLSCREEN);
    SDL_WM_SetCaption("Aukwar", NULL); 
    int i=0,j=0,g=0;
    FILE *fichier=NULL;
    Joueur joueur;
   
    initJoueur(&joueur);
    initJoueur(&ia);

TTF_Font *police = NULL;


SDL_Color couleurNoire = {0,0,0};
SDL_Color couleurBleu = {39,5,228};
SDL_Color couleurRouge = {255,0,0};
SDL_Color couleurOrange = {255,128,64};
SDL_Color couleurVerte = {67,204,21};
SDL_Color couleurEssai = {0,0,0};

police = TTF_OpenFont("data/police.ttf",20);



SDL_Surface *blanc,*terre,*herbe,*eau,*ferme_allie,*ferme_opposant,*barriere,*choixSurface=0;
SDL_Surface *choixSurfaceRectangle,*fondu_herbe_terre,*fondu_terre_herbe,*fondu_terre_herbe_haut,*fondu_herbe_terre_haut;
SDL_Surface *fondu_eau_terre,*fondu_terre_eau,*fondu_terre_eau_haut,*fondu_eau_terre_haut;
SDL_Surface *fondu_herbe_eau,*fondu_eau_herbe,*fondu_herbe_eau_haut,*fondu_eau_herbe_haut;
SDL_Surface *large,*arbre,*soldat_allie,*soldat_ennemi;
SDL_Rect positiontext,posBarre;

posBarre.x=0; 
posBarre.y=HAUTEUR_FENETRE;
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
large=SDL_LoadBMP("data/images/large.bmp");
choixSurfaceRectangle=SDL_LoadBMP("data/images/choix.bmp");
arbre=SDL_LoadBMP("data/images/arbre.bmp");
soldat_allie=SDL_LoadBMP("data/images/soldat_allie.bmp");
soldat_ennemi=SDL_LoadBMP("data/images/soldat_ennemi.bmp");

char chaineOr[200]="",chainePtsVictoire[200]="",chainePopulation[200]="",chaineBois[200]="";
char chaineFer[200]="",chaineNourriture[200]="";

  
SDL_SetColorKey(ferme_opposant, SDL_SRCCOLORKEY, SDL_MapRGB(ferme_opposant->format, 255, 0,0));
SDL_SetColorKey(ferme_allie, SDL_SRCCOLORKEY, SDL_MapRGB(ferme_allie->format,0, 0,255));
SDL_SetColorKey(barriere, SDL_SRCCOLORKEY, SDL_MapRGB(barriere->format,0,0,255));
SDL_SetColorKey(arbre, SDL_SRCCOLORKEY, SDL_MapRGB(arbre->format,0,0,255));
SDL_SetColorKey(soldat_ennemi, SDL_SRCCOLORKEY, SDL_MapRGB(soldat_ennemi->format,0,0,255));

SDL_Rect posSouris,posTemp,posSelect,posLarge,posChoix,posScore,posPts;
SDL_Rect posPtsVictoire,posPopulation,posBois,posFer,posNourriture;

posBloc[0][0].x=50;
posBloc[0][0].y=50;


posLarge.x=900;
posLarge.y=900;

posChoix.x=0;
posChoix.y=0;

posScore.x=800;
posScore.y=HAUTEUR_FENETRE;

posPts.x=0;
posPts.y=0;

posPtsVictoire.x=595;
posPtsVictoire.y=HAUTEUR_FENETRE+40;

posPopulation.x=455;
posPopulation.y=HAUTEUR_FENETRE+40;

posBois.x=355;
posBois.y=HAUTEUR_FENETRE+40;

posFer.x=95;
posFer.y=HAUTEUR_FENETRE+40;

posNourriture.x=185;
posNourriture.y=HAUTEUR_FENETRE+40;

positiontext.x =11;
positiontext.y = HAUTEUR_FENETRE+40; 

SDL_TimerID timer;
timer = SDL_AddTimer(150,afficherCarteJeu,&posSouris); 
         

    
    fichier=fopen("data/niveaux/map03.niv","r");
    if(fichier!=NULL)
    {
    fclose(fichier);
    chargerNiveau("data/niveaux/map03.niv",posMatiere,posBatiment);
    }
  
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
      
      sprintf(chainePopulation,"Population:%ld",joueur.nbPopulation);
      sprintf(chainePtsVictoire,"Pts De Victoire:%ld",joueur.nbPtsVictoire);
      sprintf(chaineOr,"Or:%ld",joueur.nbOr);
      sprintf(chaineBois,"Bois:%ld",joueur.nbBois);
      sprintf(chaineFer,"fer:%ld",joueur.nbFer);
      sprintf(chaineNourriture,"Nourriture:%ld",joueur.nbNourriture);
      
      if(joueur.nbOr>=0)
      texteOr = TTF_RenderText_Blended(police,chaineOr, couleurNoire);
      else
      texteOr = TTF_RenderText_Blended(police,chaineOr, couleurRouge);
    
      if(joueur.nbFer>=0)
      texteFer = TTF_RenderText_Blended(police,chaineFer, couleurNoire);
      else
      texteFer = TTF_RenderText_Blended(police,chaineFer, couleurRouge);
     
       if(joueur.nbNourriture>=0)
      texteNourriture = TTF_RenderText_Blended(police,chaineNourriture, couleurNoire);
      else
      texteNourriture= TTF_RenderText_Blended(police,chaineNourriture, couleurRouge);
     
      if(joueur.nbPtsVictoire>170)
      textePtsVictoire=TTF_RenderText_Blended(police,chainePtsVictoire,couleurVerte);
      if(joueur.nbPtsVictoire>70 && joueur.nbPtsVictoire<170)
      textePtsVictoire=TTF_RenderText_Blended(police,chainePtsVictoire,couleurBleu);
      if(joueur.nbPtsVictoire<70 && joueur.nbPtsVictoire>20)
      textePtsVictoire=TTF_RenderText_Blended(police,chainePtsVictoire,couleurOrange);
      if(joueur.nbPtsVictoire<20)
      textePtsVictoire=TTF_RenderText_Blended(police,chainePtsVictoire,couleurRouge);
      
      if(joueur.nbPopulation>0)
      textePopulation=TTF_RenderText_Blended(police,chainePopulation,couleurNoire);
      else
      textePopulation=TTF_RenderText_Blended(police,chainePopulation,couleurRouge);
      
      if(joueur.nbBois>=0)
      {
      texteBois=TTF_RenderText_Blended(police,chaineBois,couleurNoire);
      }
      else
      {
      texteBois=TTF_RenderText_Blended(police,chaineBois,couleurRouge);
      }
      
      
      SDL_PollEvent(&event);
     
        switch(event.type)
        {
           
            case SDL_QUIT:
            continuer = 0;
            posBloc[0][0].x=0;
            posBloc[0][0].y=0;
            for(i=0;i<NB_BLOCS_X;i++)
             {
             for(j=0;j<NB_BLOCS_Y;j++)
              {
              posMatiere[i][j]=VIDE;
              posBatiment[i][j]=VIDE;
              }
             }
            
            break;
            case SDL_MOUSEMOTION:
                 posSouris.x=event.motion.x;
                 posSouris.y=event.motion.y;    
            break;
            case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
            continuer=0;
            posBloc[0][0].x=0;
            posBloc[0][0].y=0;
            for(i=0;i<NB_BLOCS_X;i++)
             {
             for(j=0;j<NB_BLOCS_Y;j++)
              {
              posMatiere[i][j]=VIDE;
              posBatiment[i][j]=VIDE;
              }
             }
             break;
             case SDLK_o:
             joueur.nbOr+=1;
             joueur.nbPtsVictoire+=1;
             joueur.nbPopulation+=1;
             joueur.nbBois+=1;
             joueur.nbFer+=1;
             joueur.nbNourriture+=1;
             break;
             case SDLK_l:
             joueur.nbOr-=1;
             joueur.nbPtsVictoire-=1;
             joueur.nbPopulation-=1;
             joueur.nbBois-=1;
             joueur.nbFer-=1;
             joueur.nbNourriture-=1;
             if(joueur.nbPtsVictoire<0)
             joueur.nbPtsVictoire=0;
             if(joueur.nbPopulation<0)
             joueur.nbPopulation=0;
             break;
             if(joueur.nbBois<-100)
             joueur.nbBois=-99;
             if(joueur.nbOr<-100)
             joueur.nbOr=-99;
             if(joueur.nbNourriture<-100)
             joueur.nbNourriture=-99;
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
   case VIDE:
   SDL_BlitSurface(blanc,NULL,ecran,&posBloc[i][j]);
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
    initPosJeu(&posTemp);
    break;
    case ARBRE:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-arbre->h+TAILLE_BLOC;
    SDL_BlitSurface(arbre,NULL,ecran,&posTemp);
    initPosJeu(&posTemp);
    break;
     case SOLDAT_ALLIE:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-soldat_allie->h+TAILLE_BLOC;
    SDL_BlitSurface(soldat_allie,NULL,ecran,&posTemp);
    initPosJeu(&posTemp);
    break;
     case SOLDAT_ENNEMI:
    posTemp.x=posBloc[i][j].x;
    posTemp.y=posBloc[i][j].y-soldat_ennemi->h+TAILLE_BLOC;
    SDL_BlitSurface(soldat_ennemi,NULL,ecran,&posTemp);
    initPosJeu(&posTemp);
    break;
    default:
    break;
    }
   }
  }
 }

SDL_BlitSurface(barre,NULL,ecran,&posBarre);
SDL_BlitSurface(score,NULL,ecran,&posScore);
SDL_BlitSurface(score,NULL,ecran,&posPts);

SDL_BlitSurface(texteOr, NULL, ecran, &positiontext);
SDL_BlitSurface(textePtsVictoire, NULL,ecran,&posPtsVictoire);
SDL_BlitSurface(textePopulation, NULL,ecran,&posPopulation);
SDL_BlitSurface(texteBois, NULL,ecran,&posBois);
SDL_BlitSurface(texteFer, NULL,ecran,&posFer);
SDL_BlitSurface(texteNourriture, NULL,ecran,&posNourriture);

SDL_BlitSurface(large,NULL,ecran,&posLarge);
initPosJeu(&posSelect);
SDL_Flip(ecran);

    }
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
Uint32 afficherCarteJeu(Uint32 intervalle, void *parametre)
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
actionia( posMatiere, posBatiment,&ia);
return intervalle;

}
void initPosJeu(SDL_Rect *pos)
{
pos->x=0;
pos->y=0;
}

