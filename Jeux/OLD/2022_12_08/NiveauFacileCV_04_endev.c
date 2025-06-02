/* NiveauFacile.c */
#include<stdio.h>
#include<stdlib.h>
#include<graph.h>

#define DOSSIER_CARTES_VERSO "./CartesJeuxVerso"
#define IMAGE_CARTES_VERSO "./CartesJeuxVerso/136/symboleberserk.jpg"
#define DOSSIER_CARTES_RECTO "./CartesJeuxRecto/136"
#define IMAGE_FOND_ECRAN "./fondjeux.jpg"
#define NBCARTES 53 //nombre de cartes dans les dossiers bibliothèque d images
#define L 1070 //longueur de la page de la fenêtre
#define H 601 //hauteur de la page de la fenêtre
#define DIM 4 //dimension des carrés
#define NB_IMAGES_UNIQUES DIM*DIM/2
#define LH_CARTE 136 //longueur et largeur des images dans les carrés associés à DIM=4
#define LH_CARRE 144 //petit espace avant le petit carré + taille du petit carré - longueur et larger des carrés associés à DIM=4

//Fonction aidant le remplissage d images uniques
int ftn_ImageDejaPrise1fois(int ima[], int imaIndice, int imaValue){
	int i;
	int valReturn=0;
	for (i=1 ; i<imaIndice ; i++){
		if (imaValue==ima[i]){
			valReturn = 1;
			break;
		}
	}
	return valReturn;
}
//Fonction aidant le remplissage des paires d images
int ftn_ImageDejaPrise2fois(int ima[], int imaIndice, int imaValue){
	int i;
	int valReturn=0;
	for (i=1 ; i<imaIndice ; i++){
		if (imaValue==ima[i]){
			valReturn++;
			if(valReturn==2)
				break;
		}
	}
	return valReturn;
}
//Fonction aidant le remplissage des paires d images
int ftn_Gagne(int tab[], int taille){
	int i;
	int valReturn=1;
	for (i=1 ; i<=taille ; i++){
		if (tab[i]==0){
			valReturn=0;
			break;
		}
	}
	return valReturn;
}

int main()
{
int Xcarre = 255;//x du premier petit carré (carte de jeux)
int Ycarre = 20.5;//y du premier petit carré (carte de jeux)
int x,y;//carré avec leurs espaces = 144 longueur et 144 largeur 
int ligne;//indice de numero de ligne
int colonne;//indice de numero de colonne
char nomFichier[100];//taille du stockage du chemin complet jusqu'au fichier FondEcran
int X_Clk;//coordonnée x du click 
int Y_Clk;//coordonnée y du click
int Click[DIM][DIM];
int Image[DIM][DIM];
char FichiersImage[DIM*DIM][300];
int TabNumImagesUniques[NB_IMAGES_UNIQUES];
int TabNumImages[DIM*DIM];
int NumeroImage = 0;
int i,j;//compteurs
//
int TabNumCartesJouees[DIM*DIM];
int TabNumCartesGagnees[DIM*DIM];
int nbClicksJouees;
int numCarteJouee1,linCJ1,colCJ1;
int numCarteJouee2,linCJ2,colCJ2;

InitialiserGraphique();
CreerFenetre(0,0,L,H);
ChargerImageFond(IMAGE_FOND_ECRAN);
//GrandCarré
DessinerRectangle(247,12.5,576+8,576+8);//x, y, xl, yh de la table de jeux et +8 est la marge de fin des derniers carré

//DessinerRectangle(255,20.5,144,144);
for(ligne=0;ligne<DIM;ligne++){
	for(colonne=0;colonne<DIM;colonne++){
		x=Xcarre + colonne*LH_CARRE;//ligne*144 = petit espace avant le petit carré + taille du petit carré
		y=Ycarre + ligne*LH_CARRE;//colonne*144 = petit espace avant le petit carré  + taille du petit carré
		DessinerRectangle(x,y,LH_CARTE,LH_CARTE);//136 = taille des côtés du petit carré
		ChargerImage(IMAGE_CARTES_VERSO,x,y,0,0,LH_CARTE,LH_CARTE);
	}
}

//Initialisation de la distribution de cartes aléatoires
int NumeroRandomImage;//numero de l image choisie au hasard parmi le NB_IMAGES_UNIQUES
int first = 0;
//pour eviter d avoir les memes numeros à chaque fois avec la fonction rand()
if (first == 0)
{
  srand (Microsecondes());
  first = 1;
}
//Remplissage du tableau TabNumImagesUniques de taille moitié des cartes nécessaires pour générer des paires
for(i=1; i<=NB_IMAGES_UNIQUES ; i++){
	do {
		NumeroRandomImage = rand() % (NBCARTES+1);
		TabNumImagesUniques[i] = NumeroRandomImage;
	} while (NumeroRandomImage==0 || ftn_ImageDejaPrise1fois(TabNumImagesUniques,i,NumeroRandomImage)==1);
}
//Remplissage intermédiaire du tableau TabNumImages avec les indices disposés aleatoirement pour assigner les images de manière différente à chaque jeu
for(i=1; i<=(DIM*DIM) ; i++){
	do {
		NumeroRandomImage = rand() % (NB_IMAGES_UNIQUES+1);
		TabNumImages[i] = NumeroRandomImage;
	} while (NumeroRandomImage==0 || ftn_ImageDejaPrise2fois(TabNumImages,i,NumeroRandomImage)==2);
	//printf("Indices TabNumImages(%d)= %d\n",i,TabNumImages[i]);
}
//Remplissage du tableau TabNumImages[] avec les numéros d'images définitifs
//Remplissage du tableau FichiersImage[] avec les chemins des fichiers choisis aléatoirement
for(i=1; i<=(DIM*DIM) ; i++){
	TabNumImages[i] = TabNumImagesUniques[TabNumImages[i]];
	printf("Valeurs TabNumImages(%d)= %d\n",i,TabNumImages[i]);
	sprintf(FichiersImage[i],"%s/%d.jpg",DOSSIER_CARTES_RECTO,TabNumImages[i]);
}
//Initialisation des tableaux Click[][]=Non clické et Image[][]=Num Image réél dans notre bibliothèque
NumeroImage = 0;
for(ligne=0;ligne<DIM;ligne++){
	for(colonne=0;colonne<DIM;colonne++){
		NumeroImage++;
		Click[ligne][colonne]=0;
		Image[ligne][colonne]=TabNumImages[NumeroImage];
		//printf("Image(%d ; %d) = %d\n",ligne,colonne,Image[ligne][colonne]);
		//printf("TabNumImages(%d) = %d\n",NumeroImage,TabNumImages[NumeroImage]);
		//printf("FichiersImage(%d ; %d) = %s\n",ligne,colonne,FichiersImage[NumeroImage]);
	}
}

//Remplissage Jeu en cours
for(i=1; i<=(DIM*DIM) ; i++){
	TabNumCartesJouees[i] = 0;
	TabNumCartesGagnees[i] = 0;
}

while(1)
{
	nbClicksJouees = 0;
	numCarteJouee1 = 0;
	numCarteJouee2 = 0;
	if (SourisCliquee())
	{
		X_Clk=_X;
		Y_Clk=_Y;
		NumeroImage = 0;
		for(ligne=0;ligne<DIM;ligne++){
			for(colonne=0;colonne<DIM;colonne++){
				NumeroImage++;
				x=Xcarre + colonne*LH_CARRE;
				y=Ycarre + ligne*LH_CARRE;
				if(X_Clk>=x && X_Clk<=(x+LH_CARTE) && Y_Clk>=y && Y_Clk<=(y+LH_CARTE)){
					if(Click[ligne][colonne]==0){
						ChargerImage(FichiersImage[NumeroImage],x,y,0,0,LH_CARTE,LH_CARTE);
						Click[ligne][colonne]==1;
						//********************************************
						//********************************************
						//********************************************
						nbClicksJouees++;
						if (nbClicksJouees==1 && numCarteJouee1==0){
							numCarteJouee1=NumeroImage;
							linCJ1 = x;
							colCJ1 = y;
							TabNumCartesJouees[numCarteJouee1]=1;
						}
						if (nbClicksJouees==2 && numCarteJouee2==0){
							numCarteJouee2=NumeroImage;
							linCJ2 = x;
							colCJ2 = y;
							TabNumCartesJouees[numCarteJouee2]=1;
						}
						if (numCarteJouee2!=0){
							if(ftn_Gagne(TabNumCartesJouees,DIM*DIM)==1){
								//c'est gagné
								//fin de partie
								printf("C'est gagné.\n",NumeroImage,FichiersImage[NumeroImage]);
							} else {
								//c'est pas gagné
								//on continue - on reinitialise les deux cartes jouées dans TabNumCartesJouees
								TabNumCartesJouees[numCarteJouee1]=0;
								TabNumCartesJouees[numCarteJouee2]=0;
								//on retourne les cartes
								//On doit attendre 1 seconde selon le,projet
								ChargerImage(FichiersImage[NumeroImage],x,y,0,0,LH_CARTE,LH_CARTE);
								ChargerImage(FichiersImage[NumeroImage],x,y,0,0,LH_CARTE,LH_CARTE);
							}
						}
						//********************************************
						//********************************************
						//********************************************
					}
					printf("(NumerodOrdreImage = %d) - Coo : (%d;%d) (ligne=%d ; colonne=%d) (Image Num = %d) \n",NumeroImage, X_Clk,Y_Clk,ligne,colonne,Image[ligne][colonne]);
					printf("FichiersImage(%d) = %s\n",NumeroImage,FichiersImage[NumeroImage]);
					break;
				}
			}
		}

	}
}

Touche();
FermerGraphique();
return EXIT_SUCCESS;
}