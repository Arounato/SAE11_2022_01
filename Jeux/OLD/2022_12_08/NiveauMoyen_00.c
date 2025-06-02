#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#define FondEcran "/home/vallejos/SAE11_2022/Jeux"
#define L 1070 //longueur de la page de la fenêtre
#define H 601 //hauteur de la page de la fenêtre

int main()
{
	int Xcarre = 255;//x du premier petit carré (carte de jeux)
	int Ycarre = 20.5;//y du premier petit carré (carte de jeux)
	int x,y;//carré avec leurs espaces = 96 longueur et 96 largeur 
	int ligne;//indice de numero de ligne
	int colonne;//indice de numero de colonne
	char nomFichier[300];//taille du stockage du chemin complet jusqu'au fichier FondEcran
	int X_Clk;
	int Y_Clk;

	InitialiserGraphique();
	CreerFenetre(0,0,L,H);
	sprintf(nomFichier,"%s/%s",FondEcran,"fondjeux.jpg");
	ChargerImageFond(nomFichier);
	//GrandCarré
	DessinerRectangle(247,12.5,576+8,576+8);//x, y, xl, yh de la table de jeux et +8 est la marge de fin des derniers carré
	
	//DessinerRectangle(255,20.5,144,144);
	for(ligne=0;ligne<=5;ligne++){
		x=Xcarre + ligne*96;//ligne*96 = petit espace avant le petit carré + taille du petit carré
		for(colonne=0;colonne<=5;colonne++){
			y=Ycarre + colonne*96;//colonne*96 = petit espace avant le petit carré  + taille du petit carré
			DessinerRectangle(x,y,88,88);//88 = taille des côtés du petit carré
		}
	}

while(1)
{
	if (SourisCliquee())
	{
		X_Clk=_X;
		Y_Clk=_Y;
		
		for(colonne=0;colonne<=5;colonne++){
			x=Xcarre + colonne*96;
			for(ligne=0;ligne<=5;ligne++){
				y=Ycarre + ligne*96;
				if(X_Clk>=x && X_Clk<=(x+88) && Y_Clk>=y && Y_Clk<=(y+88)){
				printf("Coordonnées : (%d/%d/%d/%d)\n", X_Clk,Y_Clk,ligne,colonne);
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
