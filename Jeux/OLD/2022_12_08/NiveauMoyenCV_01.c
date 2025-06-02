#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#define FondEcran "/home/bob/SAE11_2022/Jeux"
#define IMAGE_FOND_ECRAN "/home/bob/SAE11_2022/Jeux/fondjeux.jpg"//AJOUT ************
#define CarteVerso "/home/bob/SAE11_2022/Jeux/PhotoCarteDeJeuxVerso"
#define IMAGE_CARTE_VERSO "/home/bob/SAE11_2022/Jeux/PhotoCarteDeJeuxVerso/88/symboleberserk.jpg"//AJOUT ************
#define CarteRecto "/home/bob/SAE11_2022/Jeux/PhotoCarteDeJeuxRecto/cartes88"//MODIF ************
#define L 1070 //longueur de la page de la fenêtre
#define H 601 //hauteur de la page de la fenêtre
#define DIM 6 //dimension des carrés
#define NB_IMAGES_UNIQUES DIM*DIM/2 //AJOUT ************
#define LHCARTE 88 //longueur et larger des images dans les carrés associés à DIM=4 //AJOUT ************
#define LHCARRE 96 //petit espace avant le petit carré + taille du petit carré - longueur et larger des carrés associés à DIM=4 //AJOUT ************

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
	//sprintf(nomFichier,"%s/%s",FondEcran,"fondjeux.jpg");//MODIF ************
	ChargerImageFond(IMAGE_FOND_ECRAN);//MODIF ************
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

	for(ligne=0;ligne<DIM;ligne++){
		for(colonne=0;colonne<DIM;colonne++){
			Click[ligne][colonne]=0;//MODIF ************
			NumeroImage++;
			Image[ligne][colonne]=NumeroImage;
			if (NumeroImage==NB_IMAGES_UNIQUES);
				NumeroImage=0;
		}
	}

while(1)
{
	if (SourisCliquee())
	{
		X_Clk=_X;
		Y_Clk=_Y;
		
		NumeroImage=0;
		for(colonne=0;colonne<DIM;colonne++){
			x=Xcarre + colonne*LHCARRE;
			for(ligne=0;ligne<DIM;ligne++){
				y=Ycarre + ligne*LHCARRE;
				NumeroImage++;
				if(X_Clk>=x && X_Clk<=(x+LHCARTE) && Y_Clk>=y && Y_Clk<=(y+LHCARTE)){
					if(Click[ligne][colonne]==0){
						sprintf(nomFichier,"%s/%s%d%s",CarteRecto,"carte-",NumeroImage,".jpg");//MODIF ************
						ChargerImage(nomFichier,x,y,0,0,LHCARTE,LHCARTE);
						Click[ligne][colonne]==1;
					}
					printf("Coordonnées : (%d;%d) ligne=%d colonne=%d)\n", X_Clk,Y_Clk,ligne,colonne);
					break;
				}
				if (NumeroImage==NB_IMAGES_UNIQUES)
					NumeroImage=0;
			}
		}

	}
}

	Touche();
	FermerGraphique();
	return EXIT_SUCCESS;
}
