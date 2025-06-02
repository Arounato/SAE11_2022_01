/* NiveauFacile.c */
#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#define FondEcran "/home/bob/SAE11_2022/Jeux"
#define IMAGE_FOND_ECRAN "/home/bob/SAE11_2022/Jeux/fondjeux.jpg"//AJOUT ************
#define CarteVerso "/home/bob/SAE11_2022/Jeux/PhotoCarteDeJeuxVerso"
#define IMAGE_CARTE_VERSO "/home/bob/SAE11_2022/Jeux/PhotoCarteDeJeuxVerso/136/symboleberserk.jpg"//AJOUT ************
#define CarteRecto "/home/bob/SAE11_2022/Jeux/PhotoCarteDeJeuxRecto/cartes136"//MODIF ************
#define L 1070 //longueur de la page de la fenêtre
#define H 601 //hauteur de la page de la fenêtre
#define DIM 4 //dimension des carrés
#define NB_IMAGES_UNIQUES DIM*DIM/2 //AJOUT ************
#define LHCARTE 136 //longueur et larger des images dans les carrés associés à DIM=4 //AJOUT ************
#define LHCARRE 144 //petit espace avant le petit carré + taille du petit carré - longueur et larger des carrés associés à DIM=4 //AJOUT ************

int imageDejaPrise2fois(int ima[DIM][DIM], int imaIndiceLigne, int imaIndiceColonne, int imaValue){
	int i,j;
	int valReturn=0;
	int nbIma=0;
	for (i=1 ; i<imaIndiceLigne ; i++){
		for (j=1 ; j<imaIndiceColonne ; j++){
			if (imaValue==ima[i][j]){
				nbIma++;				
				if (nbIma==2){
					valReturn = 1;
					break;
				}
			}
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
int NumeroImage = 0;

InitialiserGraphique();
CreerFenetre(0,0,L,H);
ChargerImageFond(IMAGE_FOND_ECRAN);
//GrandCarré
DessinerRectangle(247,12.5,576+8,576+8);//x, y, xl, yh de la table de jeux et +8 est la marge de fin des derniers carré



//DessinerRectangle(255,20.5,144,144);
for(ligne=0;ligne<DIM;ligne++){
	x=Xcarre + ligne*LHCARRE;//ligne*144 = petit espace avant le petit carré + taille du petit carré
	for(colonne=0;colonne<DIM;colonne++){
		y=Ycarre + colonne*LHCARRE;//colonne*144 = petit espace avant le petit carré  + taille du petit carré
		DessinerRectangle(x,y,LHCARTE,LHCARTE);//136 = taille des côtés du petit carré
		//sprintf(nomFichier,"%s/%s",CarteVerso,"symboleberserk136.jpg");//MODIF ************
		ChargerImage(IMAGE_CARTE_VERSO,x,y,0,0,LHCARTE,LHCARTE);//MODIF ************
	}
}

//Initialisation de la distribution de car-tes aléatoires
int NumeroRandomImage;//numero de l image choisie au hasard parmi le NB_IMAGES_UNIQUES
int TabRandomImages[DIM][DIM];
int first = 0;
//pour eviter d avoir les memes numeros à chaque fois avec la fonction rand()
if (first == 0)
{
  srand (Microsecondes());
  first = 1;
}
for(ligne=0;ligne<DIM;ligne++){
	for(colonne=0;colonne<DIM;colonne++){
		do {
			NumeroRandomImage = rand() % (NB_IMAGES_UNIQUES+1);
			TabRandomImages[ligne][colonne] = NumeroRandomImage;
		} while (NumeroRandomImage==0 || imageDejaPrise2fois(TabRandomImages,ligne,colonne,NumeroRandomImage)==1);
		printf("%02d - ", NumeroRandomImage);
	}
}

for(ligne=0;ligne<DIM;ligne++){
	for(colonne=0;colonne<DIM;colonne++){
		Click[ligne][colonne]=0;
		Image[ligne][colonne]=TabRandomImages[ligne][colonne];
	}
}

while(1)
{
	if (SourisCliquee())
	{
		X_Clk=_X;
		Y_Clk=_Y;
		
		for(colonne=0;colonne<DIM;colonne++){
			x=Xcarre + colonne*LHCARRE;
			for(ligne=0;ligne<DIM;ligne++){
				y=Ycarre + ligne*LHCARRE;
				if(X_Clk>=x && X_Clk<=(x+LHCARTE) && Y_Clk>=y && Y_Clk<=(y+LHCARTE)){
					if(Click[ligne][colonne]==0){
						sprintf(nomFichier,"%s/%s%d%s",CarteRecto,"carte-",Image[ligne][colonne],".jpg");//MODIF ************
						ChargerImage(nomFichier,x,y,0,0,LHCARTE,LHCARTE);
						Click[ligne][colonne]==1;
					}
					printf("Coordonnées : (%d;%d) ligne=%d colonne=%d)\n", X_Clk,Y_Clk,ligne,colonne);
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
