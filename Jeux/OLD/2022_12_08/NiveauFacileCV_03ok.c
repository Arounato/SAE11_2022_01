/* NiveauFacile.c */
#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
//#define FondEcran "/home/bob/SAE11_2022/Jeux"
#define IMAGE_FOND_ECRAN "./fondjeux.jpg"
#define DOSSIER_CARTES_VERSO "./PhotoCarteDeJeuxVerso"
#define IMAGE_CARTE_VERSO "./PhotoCarteDeJeuxVerso/136/symboleberserk.jpg"
#define DOSSIER_CARTES_RECTO "./PhotoCarteDeJeuxRecto/cartes136"
#define NBCARTES 53 //nombre de cartes dans les dossiers images
#define L 1070 //longueur de la page de la fenêtre
#define H 601 //hauteur de la page de la fenêtre
#define DIM 4 //dimension des carrés
#define NB_IMAGES_UNIQUES DIM*DIM/2
#define LHCARTE 136 //longueur et largeur des images dans les carrés associés à DIM=4
#define LHCARRE 144 //petit espace avant le petit carré + taille du petit carré - longueur et larger des carrés associés à DIM=4

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

int main()
{
int Xcarre = 255;//x du premier petit carré (carte de jeux)
int Ycarre = 20.5;//y du premier petit carré (carte de jeux)
int x,y;//carré avec leurs espaces = 144 longueur et 144 largeur 
int ligne;//indice de numero de ligne
int colonne;//indice de numero de colonne
char nomFichier[300];//taille du stockage du chemin complet jusqu'au fichier FondEcran
int X_Clk;//coordonnée x du click 
int Y_Clk;//coordonnée y du click
int Click[DIM][DIM];
int Image[DIM][DIM];
char FichiersImage[DIM*DIM][300];
int TabNumImagesUniques[NB_IMAGES_UNIQUES];
int TabNumImages[DIM*DIM];
int NumeroImage = 0;
int i,j;//compteurs
int TabNumCartesJouees[DIM*DIM];

InitialiserGraphique();
CreerFenetre(0,0,L,H);
ChargerImageFond(IMAGE_FOND_ECRAN);
//GrandCarré
DessinerRectangle(247,12.5,576+8,576+8);//x, y, xl, yh de la table de jeux et +8 est la marge de fin des derniers carré

//DessinerRectangle(255,20.5,144,144);
for(ligne=0;ligne<DIM;ligne++){
	for(colonne=0;colonne<DIM;colonne++){
		x=Xcarre + colonne*LHCARRE;//ligne*144 = petit espace avant le petit carré + taille du petit carré
		y=Ycarre + ligne*LHCARRE;//colonne*144 = petit espace avant le petit carré  + taille du petit carré
		DessinerRectangle(x,y,LHCARTE,LHCARTE);//136 = taille des côtés du petit carré
		ChargerImage(IMAGE_CARTE_VERSO,x,y,0,0,LHCARTE,LHCARTE);
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
for(i=1; i<=NB_IMAGES_UNIQUES ; i++){
	do {
		NumeroRandomImage = rand() % (NBCARTES+1);
		TabNumImagesUniques[i] = NumeroRandomImage;
	} while (NumeroRandomImage==0 || ftn_ImageDejaPrise1fois(TabNumImagesUniques,i,NumeroRandomImage)==1);
}
for(i=1; i<=(DIM*DIM) ; i++){
	do {
		NumeroRandomImage = rand() % (NB_IMAGES_UNIQUES+1);
		TabNumImages[i] = NumeroRandomImage;
	} while (NumeroRandomImage==0 || ftn_ImageDejaPrise2fois(TabNumImages,i,NumeroRandomImage)==2);
	printf("Indices TabNumImages(%d)= %d\n",i,TabNumImages[i]);
}
for(i=1; i<=(DIM*DIM) ; i++){
	TabNumImages[i] = TabNumImagesUniques[TabNumImages[i]];
	printf("Valeurs TabNumImages(%d)= %d\n",i,TabNumImages[i]);
	sprintf(FichiersImage[i],"%s/%d.jpg",DOSSIER_CARTES_RECTO,TabNumImages[i]);
}

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

while(1)
{
	if (SourisCliquee())
	{
		X_Clk=_X;
		Y_Clk=_Y;
		NumeroImage = 0;
		for(ligne=0;ligne<DIM;ligne++){
			for(colonne=0;colonne<DIM;colonne++){
				NumeroImage++;
				x=Xcarre + colonne*LHCARRE;
				y=Ycarre + ligne*LHCARRE;
				if(X_Clk>=x && X_Clk<=(x+LHCARTE) && Y_Clk>=y && Y_Clk<=(y+LHCARTE)){
					if(Click[ligne][colonne]==0){
						ChargerImage(FichiersImage[NumeroImage],x,y,0,0,LHCARTE,LHCARTE);
						Click[ligne][colonne]==1;
					}
					printf("(NumeroImage = %d) - Coo : (%d;%d) (ligne=%d ; colonne=%d) (Image Num = %d) \n",NumeroImage, X_Clk,Y_Clk,ligne,colonne,Image[ligne][colonne]);
					printf("FichiersImage(%d ; %d) = %s\n",ligne,colonne,FichiersImage[NumeroImage]);
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