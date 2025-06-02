/* fonctions.c */
#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#include "fonctions.h"

int FonctionMenu(void)
{
/* #define FondEcranPrincipal "./Jeux" */
#define IMAGE_FOND_ECRAN_MENU "./luigi.jpg"//AJOUT ************
/* #define FondBouton "./Jeux"//MODIF ************ */
#define IMAGE_NIVEAU_FAC "./champignonvert_140x40.jpg"//AJOUT ************
#define IMAGE_NIVEAU_MOY "./champignonorange_140x40.jpg"//AJOUT ************
#define IMAGE_NIVEAU_DIF "./champignonrouge_140x40.jpg"//AJOUT ************
#define L 1070
#define H 601

	int FtrPpl1 = 0; //positionx de la fenetrePrincipal
	int FtrPpl2 = 0;//positiony de la fenetre principal
	int TFtrPpl1 = L; //Taille de la Fenetre Principal en largeur
	int TFtrPpl2 = H; //Taille de la Fenetre Principal en hauteur
	char nomFichier[10];//Nombre de caractere du nom du fichier
	int x,y;//variable pour le texte principale
	char *T="Jeux de paires";
	char *T1="Menu 1";
	char *T2="Menu 2";
	char *T3="Menu 3";

	InitialiserGraphique();
	//Création du fond d'écran de la fenetre principal
	CreerFenetre(0,0,L,H);
	ChargerImageFond(IMAGE_FOND_ECRAN_MENU);

	ChoisirCouleurDessin(CouleurParNom("white"));//couleur du rectangle qui se situera derriere le titre
	RemplirRectangle(250,60,300,60);
	ChoisirCouleurDessin(CouleurParNom("black"));//titre qui se situera devant le rectangle
	y=H/5;
	x=(L-TailleChaineEcran(T,2))/2;
	EcrireTexte(x,y,T,2);
	
	int rH=50;//hauteur des rectangles
	int rL=150;//largeur des rectangles
	int imH=40;//hauteur des rectangles
	int imL=140;//largeur des rectangles
	int espaceEntreRectangles = (L-rL*3)/4;

	//Coordonnees du rectangle 1 cliquer
	int xa1 = 1 * espaceEntreRectangles + 0 * rL;//coordonnee x du point haut gauche
	int xb1 = xa1+rL;//coordonnee x du point bas droite
	int ya1 = espaceEntreRectangles + rL;//coordonnee y du point haut gauche
	int yb1 = ya1+rH;//coordonnee y du point bas droite

	//Coordonnees du rectangle 2 cliquer
	int xa2 = 2 * espaceEntreRectangles + 1 * rL;//coordonnee x du point haut gauche
	int xb2 = xa2+rL;//coordonnee x du point bas droite
	int ya2 = espaceEntreRectangles + rL;//coordonnee y du point haut gauche
	int yb2 = ya2+rH;//coordonnee y du point bas droite

	//Coordonnees du rectangle 3 cliquer
	int xa3 = 3 * espaceEntreRectangles + 2 * rL;//coordonnee x du point haut gauche
	int xb3 = xa3+rL;//coordonnee x du point bas droite
	int ya3 = espaceEntreRectangles + rL;//coordonnee y du point haut gauche
	int yb3 = ya3+rH;//coordonnee y du point bas droite

	ChoisirCouleurDessin(CouleurParNom("black"));
	RemplirRectangle(xa1,ya1,rL,rH);
	ChargerImage(IMAGE_NIVEAU_FAC, xa1+5,ya1+5,0,0,imL,imH);

	ChoisirCouleurDessin(CouleurParNom("black"));
	RemplirRectangle(xa2,ya2,rL,rH);
	ChargerImage(IMAGE_NIVEAU_MOY, xa2+5,ya2+5,0,0,imL,imH);

	ChoisirCouleurDessin(CouleurParNom("black"));
	RemplirRectangle(xa3,ya3,rL,rH);
	ChargerImage(IMAGE_NIVEAU_DIF, xa3+5,ya3+5,0,0,imL,imH);

	int X_Clk=0;//x du click
	int Y_Clk=0;//y du click

	while(!SourisCliquee()){
		X_Clk=_X;
		Y_Clk=_Y;
	}
	while(1)
	{
		if (SourisCliquee()) 
		{
			X_Clk=_X;
			Y_Clk=_Y;

			if (X_Clk>=xa1 && X_Clk<xb1 && Y_Clk>=ya1 && Y_Clk<=yb1){
				printf("Rectangle vert clickée (X=%d ; Y=%d)\n", X_Clk, Y_Clk);
				FonctionNiveaux(4);
			}
			if (X_Clk>=xa2 && X_Clk<xb2 && Y_Clk>=ya2 && Y_Clk<=yb2){
				printf("Rectangle orange clickée (X=%d ; Y=%d)\n", X_Clk, Y_Clk);
				FonctionNiveaux(6);
			}
			if (X_Clk>=xa3 && X_Clk<xb3 && Y_Clk>=ya3 && Y_Clk<=yb3){
				printf("Rectangle rouge clickée (X=%d ; Y=%d)\n", X_Clk, Y_Clk);
				FonctionNiveaux(8);
			}

		}
		if (ToucheEnAttente()) break;
	}

	Touche();
	FermerGraphique();
	return EXIT_SUCCESS;
}


//Fonction aidant le remplissage d images uniques
int FonctionImageDejaPrise1fois(int numimageTableau[], int numcase, int numcarte){
	int i;
	int ValeurReturn=0;
	for (i=1 ; i<numcase ; i++){
		if (numcarte==numimageTableau[i]){
			ValeurReturn = 1;
			break;
		}
	}
	return ValeurReturn;
}
//Fonction aidant le remplissage des paires d images
int FonctionImageDejaPrise2fois(int numimageTableau[], int numcase, int numcarte){
	int i;
	int ValeurReturn=0;
	for (i=1 ; i<numcase ; i++){
		if (numcarte==numimageTableau[i]){
			ValeurReturn++;
			if(ValeurReturn==2)
				break;
		}
	}
	return ValeurReturn;
}
//Fonction aidant le remplissage des paires d images
int FonctionGagnee(int tab[], int taille){
	int i;
	int ValeurReturn=1;
	for (i=1 ; i<=taille ; i++){
		if (tab[i]==0){
			ValeurReturn=0;
			break;
		}
	}
	return ValeurReturn;
}

int FonctionNiveaux(int DIM)
{
if (DIM!=4 && DIM!=6 && DIM!=8){
	printf("DIM = 4, 6 ou 8 uniquement\n");
	return EXIT_SUCCESS;
}

#define IMAGE_FOND_ECRAN "./fondjeux.jpg"
#define NBCARTES 53 //nombre de cartes dans les dossiers bibliothèque d images
#define ESPACEMENT 8 //dimension des carrés
#define LH_GRAND_CARRE 576
#define LH_CARRE LH_GRAND_CARRE/DIM //petit espace avant le petit carré + taille du petit carré - longueur et larger des carrés associés à DIM=4
#define LH_CARTE LH_CARRE-ESPACEMENT //longueur et largeur des images dans les carrés associés à DIM=4

char DOSSIER_CARTES_RECTO[100];
sprintf(DOSSIER_CARTES_RECTO,"%s%d","./CartesJeuxRecto/",LH_CARTE);
printf("DOSSIER_CARTES_RECTO = %s\n",DOSSIER_CARTES_RECTO);

char IMAGE_CARTES_VERSO[100];
sprintf(IMAGE_CARTES_VERSO,"%s%d.jpg","./CartesJeuxVerso/symboleberserk",LH_CARTE);
printf("IMAGE_CARTES_VERSO = %s\n",IMAGE_CARTES_VERSO);

#define L 1070 //longueur de la page de la fenêtre
#define H 601 //hauteur de la page de la fenêtre
#define NB_IMAGES_UNIQUES DIM*DIM/2
#define CYCLE 1000000L//attente après un jeu erroné 1 seconde

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
char TabFichiersImage[DIM*DIM][300];
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
unsigned long TempsDernierClick;
unsigned long t1;
int nbClicksTotales;

InitialiserGraphique();
CreerFenetre(0,0,L,H);
ChargerImageFond(IMAGE_FOND_ECRAN);
//GrandCarré
DessinerRectangle(247,12.5,576+8,576+8);//x, y, xl, yh de la table de jeux et +8 est la marge de fin des derniers carré

// Paramètres du rectangle de retour au menu
int rH=50;//hauteur des rectangles
int rL=150;//largeur des rectangles
int imH=40;//hauteur des rectangles
int imL=140;//largeur des rectangles
int espaceEntreRectangles = 10;
//Coordonnees du rectangle de retour au menu
int xa1 = 1 * espaceEntreRectangles + 0 * rL;//coordonnee x du point haut gauche
int xb1 = xa1+rL;//coordonnee x du point bas droite
int ya1 = espaceEntreRectangles + rL;//coordonnee y du point haut gauche
int yb1 = ya1+rH;//coordonnee y du point bas droite
// Dessiner le rectangle de retour au menu
ChoisirCouleurDessin(CouleurParNom("black"));
RemplirRectangle(xa1,ya1,rL,rH);
//ChargerImage(IMAGE_NIVEAU_FAC, xa1+5,ya1+5,0,0,imL,imH);

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
	} while (NumeroRandomImage==0 || FonctionImageDejaPrise1fois(TabNumImagesUniques,i,NumeroRandomImage)==1);
}
//Remplissage intermédiaire du tableau TabNumImages avec les indices disposés aleatoirement pour assigner les images de manière différente à chaque jeu
for(i=1; i<=(DIM*DIM) ; i++){
	do {
		NumeroRandomImage = rand() % (NB_IMAGES_UNIQUES+1);
		TabNumImages[i] = NumeroRandomImage;
	} while (NumeroRandomImage==0 || FonctionImageDejaPrise2fois(TabNumImages,i,NumeroRandomImage)==2);
	//printf("Indices TabNumImages(%d)= %d\n",i,TabNumImages[i]);
}
//Remplissage du tableau TabNumImages[] avec les numéros d'images définitifs
//Remplissage du tableau TabFichiersImage[] avec les chemins des fichiers choisis aléatoirement
for(i=1; i<=(DIM*DIM) ; i++){
	TabNumImages[i] = TabNumImagesUniques[TabNumImages[i]];
	//printf("Valeurs TabNumImages(%d)= %d\n",i,TabNumImages[i]);
	sprintf(TabFichiersImage[i],"%s/%d.jpg",DOSSIER_CARTES_RECTO,TabNumImages[i]);
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
		printf("TabFichiersImage(%d ; %d) = %s\n",ligne,colonne,TabFichiersImage[NumeroImage]);
	}
}

//Initialisation des tableaux Jeu en cours
for(i=1; i<=(DIM*DIM) ; i++){
	TabNumCartesJouees[i] = 0;
	TabNumCartesGagnees[i] = 0;
}

nbClicksJouees = 0;
numCarteJouee1 = 0;
numCarteJouee2 = 0;
nbClicksTotales = 0;
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
				x=Xcarre + colonne*LH_CARRE;
				y=Ycarre + ligne*LH_CARRE;
				if(X_Clk>=x && X_Clk<=(x+LH_CARTE) && Y_Clk>=y && Y_Clk<=(y+LH_CARTE)){
					if(Click[ligne][colonne]==0){
						ChargerImage(TabFichiersImage[NumeroImage],x,y,0,0,LH_CARTE,LH_CARTE);
						Click[ligne][colonne]==1;
						//********************************************
						//********************************************
						//********************************************
						nbClicksJouees++;
						nbClicksTotales++;
						printf("nbClicksJouees = %d\n",nbClicksJouees);
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
							if(FonctionGagnee(TabNumCartesJouees,DIM*DIM)==1){
								//c'est gagné
								//fin de partie
								printf("C'est gagné !!!!!!!!!!!!!!!!!!!!!!!!!\n");
								printf("en %d clicks sur les cartes\n", nbClicksTotales);
							} else {
								//c'est pas gagné
								//printf("C'est pas encore gagné !!!!!!!!!!!!!!!!!!!!!!!!!\n");
								if(TabNumImages[numCarteJouee1]==TabNumImages[numCarteJouee2]){
									printf("C'est pas encore gagné. Une paire trouvé, c'est bien !\n");
									//on continue - on active les deux cartes jouées dans TabNumCartesJouees
									TabNumCartesJouees[numCarteJouee1]=1;
									TabNumCartesJouees[numCarteJouee2]=1;
									//on garde les cartes les cartes retournees
								} else {
									printf("C'est raté, allez mon petit, courage !\n");
									//on continue - on reinitialise les deux cartes jouées dans TabNumCartesJouees
									TabNumCartesJouees[numCarteJouee1]=0;
									TabNumCartesJouees[numCarteJouee2]=0;
									//on retourne les cartes
									//On doit attendre 1 seconde selon le,projet
									TempsDernierClick = Microsecondes();
									while ((Microsecondes()-TempsDernierClick)<CYCLE){
										t1=Microsecondes();
									}
									//
									//printf("IMAGE_CARTES_VERSO = %s\n",IMAGE_CARTES_VERSO);
									ChargerImage(IMAGE_CARTES_VERSO,linCJ1,colCJ1,0,0,LH_CARTE,LH_CARTE);
									ChargerImage(IMAGE_CARTES_VERSO,linCJ2,colCJ2,0,0,LH_CARTE,LH_CARTE);
								}
								//
								nbClicksJouees = 0;
							}
							nbClicksJouees = 0;
							numCarteJouee1 = 0;
							numCarteJouee2 = 0;
						}
						//********************************************
						//********************************************
						//********************************************
					}
					//printf("(NumerodOrdreImage = %d) - Coo : (%d;%d) (ligne=%d ; colonne=%d) (Image Num = %d) \n",NumeroImage, X_Clk,Y_Clk,ligne,colonne,Image[ligne][colonne]);
					//printf("TabFichiersImage(%d) = %s\n",NumeroImage,TabFichiersImage[NumeroImage]);
					break;
				}
			}
		}
		//Bouton retour Menu principal
		if (X_Clk>=xa1 && X_Clk<xb1 && Y_Clk>=ya1 && Y_Clk<=yb1){
			printf("Rectangle vert clickée (X=%d ; Y=%d)\n", X_Clk, Y_Clk);
			FonctionMenu();
			return EXIT_SUCCESS;
		}
	}
}

Touche();
FermerGraphique();
return EXIT_SUCCESS;
}
