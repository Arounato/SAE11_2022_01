#include <stdio.h>
#include <stdlib.h>
#include<graph.h>
#include "Fonctions.h"
#include "Temps.h"

int Niveau(int DIM)
{
#define LH_TABLE 576
#define ESPACEMENT 8
#define LH_CARRE LH_TABLE/DIM /* Longueur et Hauteur de la taille carte + espace en plus*/
#define LH_CARTE LH_CARRE-ESPACEMENT /* Longueur et Hauteur de la taille des cotés d'une carte*/
#define DOSSIER_CARTES_VERSO "./Jeux/CartesJeuxVerso"
char IMAGE_CARTES_VERSO [100];
sprintf(IMAGE_CARTES_VERSO,"./Jeux/CartesJeuxVerso/%d/symboleberserk.jpg", LH_CARTE);
char DOSSIER_CARTES_RECTO [100];
sprintf(DOSSIER_CARTES_RECTO,"./Jeux/CartesJeuxRecto/%d", LH_CARTE);
#define IMAGE_FOND_ECRAN "./Jeux/fondjeux.jpg"
#define IMAGE_RETOUR_MENU "./MenuPrincipal/retour.jpg"
#define L 1070 /*longueur de la page de la fenêtre*/
#define H 601 /*hauteur de la page de la fenêtre*/
#define NB_IMAGES_UNIQUES DIM*DIM/2
#define NBCARTES 33/*nombre de cartes dans le dossier images*/
#define CYCLE 1000000L
unsigned long Cycle;

	int Xcarre = 255;/*x du premier petit carré (carte de jeux)*/
	int Ycarre = 20.5;/*y du premier petit carré (carte de jeux)*/
	int x,y;/*carré avec leurs espaces = 144 longueur et 144 largeur*/
	int ligne;/*indice de numero de ligne*/
	int colonne;/*indice de numero de colonne*/
	char nomFichier[300];/*taille du stockage du chemin complet jusqu'au fichier FondEcran*/
	int X_Clk;/*coordonnée x du click*/
	int Y_Clk;/*coordonnée y du click*/
	int Click[DIM][DIM];/*Tableau en lignes et colonnes des images cliquées*/
	int Image[DIM][DIM];/*Tableau en lignes et colonnes des numéros d'images*/
	char FichiersImage[DIM*DIM+1][300];/*tableau contenant les chemins relatifs des images*/
	int TabNumImagesUniques[NB_IMAGES_UNIQUES];/*tableau contenant des images uniques*/
	int TabNumImages[DIM*DIM];/*tableau contenant les numéros d'images*/
	int NumeroImage = 0;/*indice pour les tableaux à une dimension*/
	int i,j;/*compteur de ligne et colonne*/

	int TabNumCartesJouees[DIM*DIM];/*tableau des cartes de jouées*/
	int TabNumCartesGagnees[DIM*DIM];/*tableau des cartes gagnées*/
	int nbClicksJouees;/*compteur de click*/
	int numCarteJouee1,linCJ1,colCJ1;/*numéro de carte, ligne et colonne de la 1ere carte jouée*/
	int numCarteJouee2,linCJ2,colCJ2;/*numero de carte, ligne et colonne de la 2eme carte jouéé*/
	unsigned long TempsAttente;/*mesure du temps d'attente*/
	unsigned long t1;/*variable de temps*/

	InitialiserGraphique();
	CreerFenetre(0,0,L,H);
	ChargerImageFond(IMAGE_FOND_ECRAN);
	DessinerRectangle(247,12.5,576+8,576+8);/*x, y, xl, yh de la table de jeux et le +8 est la marge de fin des derniers carré*/






/* Paramètres du rectangle de retour au menu */
int rH=50;/* hauteur des rectangles */
int rL=150;/* largeur des rectangles */
int imH=40;/* hauteur des rectangles */
int imL=140;/* largeur des rectangles */
int espaceEntreRectangles = 10;
/* Coordonnees du rectangle de retour au menu */
int xa1 = 840 + 1 * espaceEntreRectangles + 0 * rL;/* coordonnee x du point haut gauche */
int xb1 = xa1+rL;/* coordonnee x du point bas droite */
int ya1 = espaceEntreRectangles + rL;/* coordonnee y du point haut gauche */
int yb1 = ya1+rH;/* coordonnee y du point bas droite */
/* Dessiner le rectangle de retour au menu */
ChoisirCouleurDessin(CouleurParNom("black"));
RemplirRectangle(xa1,ya1,rL,rH);
ChargerImage(IMAGE_RETOUR_MENU, xa1+5,ya1+5,0,0,imL,imH);









	/*Constuction de la table de jeux avec les carrés et leurs espacement*/
	for(ligne=0;ligne<DIM;ligne++){
		for(colonne=0;colonne<DIM;colonne++){
			x=Xcarre + colonne*LH_CARRE;
			y=Ycarre + ligne*LH_CARRE;
			DessinerRectangle(x,y,LH_CARTE,LH_CARTE);
			ChargerImage(IMAGE_CARTES_VERSO,x,y,0,0,LH_CARTE,LH_CARTE);
		}
	}
/*Initialisation de la distribution de cartes aléatoires*/
int NumeroRandomImage;/*numero de l'image choisie au hasard parmi le NB_IMAGES_UNIQUES*/
for(i=1; i<=NB_IMAGES_UNIQUES ; i++){
	do {
		NumeroRandomImage = FonctionRandom(NBCARTES);
		TabNumImagesUniques[i] = NumeroRandomImage;
	} while (NumeroRandomImage==0 || FonctionImageDejaPrise1fois(TabNumImagesUniques,i,NumeroRandomImage)==1);
}
for(i=1; i<=(DIM*DIM) ; i++){
	do {
		NumeroRandomImage = FonctionRandom(NB_IMAGES_UNIQUES);
		TabNumImages[i] = NumeroRandomImage;
	} while (NumeroRandomImage==0 || FonctionImageDejaPrise2fois(TabNumImages,i,NumeroRandomImage)==2);
	/*printf("Indices TabNumImages(%d)= %d\n",i,TabNumImages[i]);*/
}
for(i=1; i<=(DIM*DIM) ; i++){
	TabNumImages[i] = TabNumImagesUniques[TabNumImages[i]];
	/*printf("Valeurs TabNumImages(%d)= %d\n",i,TabNumImages[i]);*/
	sprintf(FichiersImage[i],"%s/%d.jpg",DOSSIER_CARTES_RECTO,TabNumImages[i]);
}

	/*attribution des images pour carrés*/
	NumeroImage=0;
	for(ligne=0;ligne<DIM;ligne++){
		for(colonne=0;colonne<DIM;colonne++){
			NumeroImage++;
			Click[ligne][colonne]=0;
			Image[ligne][colonne]=TabNumImages[NumeroImage];
		}
	}

/*Initialisation*/
for(i=1;i<=(DIM*DIM);i++){
	TabNumCartesJouees[i] = 0;
	TabNumCartesGagnees[i] = 0;
}

nbClicksJouees = 0;
numCarteJouee1 = 0;
numCarteJouee2 = 0;


/* Timer */
/* Temps(); */
int temps=0;

	ChoisirEcran(2);
	ChargerImageFond("./Jeux/paysage.jpg");
	ChoisirEcran(0);

while(1)
{

	Cycle = Microsecondes() + CYCLE;
	if (Microsecondes()>Cycle){
		AfficherTemps(temps);
		temps += 1;
		Cycle = Microsecondes() + CYCLE;
		break;
	}



	if (SourisCliquee())
	{
		X_Clk=_X;
		Y_Clk=_Y;

		NumeroImage=0;
		for(ligne=0;ligne<DIM;ligne++){
			for(colonne=0;colonne<DIM;colonne++){
				NumeroImage++;
				x=Xcarre + colonne*LH_CARRE;
				y=Ycarre + ligne*LH_CARRE;
				if(X_Clk>=x && X_Clk<=(x+LH_CARTE) && Y_Clk>=y && Y_Clk<=(y+LH_CARTE)){
					if(Click[ligne][colonne]==0){
						ChargerImage(FichiersImage[NumeroImage],x,y,0,0,LH_CARTE,LH_CARTE);
						Click[ligne][colonne]==1;
						nbClicksJouees++;
						/*printf("nbClicksJouees = %d\n",nbClicksJouees);*/
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
							if(FonctionGagne(TabNumCartesJouees,DIM*DIM)==1){
								/*c'est gagné*/
								/*fin de partie*/
								/*printf("C'est gagné !!!!!!!!!!!!!!!!!!!!!!!!!\n");*/
							} else {
								/*c'est pas gagné*/
								/*printf("C'est pas encore gagné !!!!!!!!!!!!!!!!!!!!!!!!!\n");*/
								if(TabNumImages[numCarteJouee1]==TabNumImages[numCarteJouee2]){
									/*on continue - on active les deux cartes jouées dans TabNumCartesJouees*/
									TabNumCartesJouees[numCarteJouee1]=1;
									TabNumCartesJouees[numCarteJouee2]=1;
									/*on garde les cartes les cartes retournees*/
								} else {
									/*on continue - on reinitialise les deux cartes jouées dans TabNumCartesJouees*/
									TabNumCartesJouees[numCarteJouee1]=0;
									TabNumCartesJouees[numCarteJouee2]=0;
									/*on retourne les cartes*/
									/*On doit attendre 1 seconde selon le,projet*/
									TempsAttente = Microsecondes();
									while ((Microsecondes()-TempsAttente)<CYCLE){
										t1=Microsecondes();
									}
									ChargerImage(IMAGE_CARTES_VERSO,linCJ1,colCJ1,0,0,LH_CARTE,LH_CARTE);
									ChargerImage(IMAGE_CARTES_VERSO,linCJ2,colCJ2,0,0,LH_CARTE,LH_CARTE);
								}
								nbClicksJouees = 0;
							}
							nbClicksJouees = 0;
							numCarteJouee1 = 0;
							numCarteJouee2 = 0;
						}
						break;
					}
				}
			}
		}
	}



}

Touche();
FermerGraphique();
return EXIT_SUCCESS;
}
