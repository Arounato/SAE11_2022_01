#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#define DOSSIER_CARTES_VERSO "./CartesJeuxVerso"
#define IMAGE_CARTES_VERSO "./CartesJeuxVerso/symboleberserk136.jpg"
#define DOSSIER_CARTES_RECTO "./CartesJeuxRecto/136"
#define IMAGE_FOND_ECRAN "./fondjeux.jpg"
#define L 1070 //longueur de la page de la fenêtre
#define H 601 //hauteur de la page de la fenêtre
#define LH_CARRE 144 // Longueur et Hauteur de la taille carte + espace en plus
#define LH_CARTE 136 // Longueur et Hauteur de la taille des cotés d'une carte
#define DIM 4 //dimension des carré (carte + espace vide)
#define NB_IMAGES_UNIQUES DIM*DIM/2
#define NBCARTES 53//nombre de cartes dans le dossier images

int FonctionImageDejaPrise1fois(int ima[], int imaIndice, int imaValue){
	int i;
	int ValeurReturn=0;
	for(i=1;i<imaIndice;i++){
		if(imaValue==ima[i]){
			ValeurReturn = 1;
			break;
		}
	}
	return ValeurReturn;
}
int FonctionImageDejaPrise2fois(int ima[], int imaIndice, int imaValue){
	int i;
	int valReturn=0;
	for(i=1;i<imaIndice;i++){
		if(imaValue==ima[i]){
			valReturn++;//oubli de ajouter valReturn ************************************************************
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
	int i,j;//compteur
	int TabNumCartesJouees[DIM*DIM];

	InitialiserGraphique();
	CreerFenetre(0,0,L,H);
	ChargerImageFond(IMAGE_FOND_ECRAN);
	DessinerRectangle(247,12.5,576+8,576+8);//x, y, xl, yh de la table de jeux et le +8 est la marge de fin des derniers carré
	
	//Constuction de la table de jeux avec les carrés et leurs espacement
	for(ligne=0;ligne<DIM;ligne++){
		for(colonne=0;colonne<DIM;colonne++){
			x=Xcarre + colonne*LH_CARRE;
			y=Ycarre + ligne*LH_CARRE;
			DessinerRectangle(x,y,LH_CARTE,LH_CARTE);
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
for(i=1; i<=NB_IMAGES_UNIQUES ; i++){
	do {
		NumeroRandomImage = rand() % (NBCARTES+1);
		TabNumImagesUniques[i] = NumeroRandomImage;
	} while (NumeroRandomImage==0 || FonctionImageDejaPrise1fois(TabNumImagesUniques,i,NumeroRandomImage)==1);
	printf("NumeroRandomImage TabNumImagesUniques(%d)= %d\n",i,TabNumImagesUniques[i]);
}
for(i=1; i<=(DIM*DIM) ; i++){
	do {
		NumeroRandomImage = rand() % (NB_IMAGES_UNIQUES+1);
		TabNumImages[i] = NumeroRandomImage;
	} while (NumeroRandomImage==0 || FonctionImageDejaPrise2fois(TabNumImages,i,NumeroRandomImage)==2);
	printf("Indices TabNumImages(%d)= %d\n",i,TabNumImages[i]);
}
for(i=1; i<=(DIM*DIM) ; i++){
	TabNumImages[i] = TabNumImagesUniques[TabNumImages[i]];
	printf("Valeurs TabNumImages(%d)= %d\n",i,TabNumImages[i]);
	sprintf(FichiersImage[i],"%s/%d.jpg",DOSSIER_CARTES_RECTO,TabNumImages[i]);
}

	//attribution des images pour carrés
	NumeroImage=0;
	for(ligne=0;ligne<DIM;ligne++){
		for(colonne=0;colonne<DIM;colonne++){
			NumeroImage++;
			Click[ligne][colonne]=0;
			Image[ligne][colonne]=TabNumImages[NumeroImage];
		}
	}

while(1)
{
	if (SourisCliquee())
	{
		X_Clk=_X;
		Y_Clk=_Y;
		
		NumeroImage=0;
		for(ligne=0;ligne<DIM;ligne++){//inversion ligne colonne
			for(colonne=0;colonne<DIM;colonne++){//inversion ligne colonne
				NumeroImage++;
				x=Xcarre + colonne*LH_CARRE;
				y=Ycarre + ligne*LH_CARRE;
				if(X_Clk>=x && X_Clk<=(x+LH_CARTE) && Y_Clk>=y && Y_Clk<=(y+LH_CARTE)){
					if(Click[ligne][colonne]==0){
						ChargerImage(FichiersImage[NumeroImage],x,y,0,0,LH_CARTE,LH_CARTE);
						Click[ligne][colonne]==1;
					}
					printf("(NumeroImage = %d) - Coo : (%d;%d) (ligne=%d ; colonne=%d) (Image Num = %d) \n",NumeroImage, X_Clk,Y_Clk,ligne,colonne,Image[ligne][colonne]);
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
