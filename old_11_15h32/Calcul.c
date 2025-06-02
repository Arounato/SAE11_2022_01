#include <stdio.h>
#include <stdlib.h>
#include<graph.h>
#include "Declaration.h"

void Niveau4(void){
  Niveau(4);
}
void Niveau6(void)
{
  Niveau(6);
}
void Niveau8(void){
  Niveau(8);
}
int Menu(void)
{

#define FondEcranPrincipal "./MenuPrincipal"
#define FondBouton "./MenuPrincipal"
#define L_MENU 1070
#define H_MENU 601
  
	int FtrPpl1 = 0; //position x de la fenetrePrincipal
	int FtrPpl2 = 0;//position y de la fenetre principal
	int TFtrPpl1 = L_MENU; //Taille de la Fenetre Principal en largeur
	int TFtrPpl2 = H_MENU; //Taille de la Fenetre Principal en hauteur
	char nomFichier[10];//Nombre de caractere du nom du fichier
	int x,y;//variable pour le texte principale
	char *T="Jeux de paires";
	char *N1="Niveau Facile";
	char *N2="Niveau Moyen";
	char *N3="Niveau Difficile";
	int X_Clk;
	int Y_Clk;

	InitialiserGraphique();
	//Création du fond d'écran de la fenetre principal
	CreerFenetre(0,0,L_MENU,H_MENU);
	sprintf(nomFichier,"%s/%s",FondEcranPrincipal,"luigi.jpg");
	ChargerImageFond(nomFichier);

	ChoisirCouleurDessin(CouleurParNom("black"));
	RemplirRectangle(380,55,310,70);
	ChoisirCouleurDessin(CouleurParNom("white"));//couleur du rectangle qui se situera derriere le titre
	RemplirRectangle(385,60,300,60);
	ChoisirCouleurDessin(CouleurParNom("black"));//titre qui se situera devant le rectangle de couleur
	y=H_MENU/6;
	x=(L_MENU-TailleChaineEcran(T,2))/2;
	EcrireTexte(x,y,T,2);

	//Creation du bouton pour, le niveaux facile
	ChoisirCouleurDessin(CouleurParNom("black"));
	RemplirRectangle(187.5,350,150,50);
	sprintf(nomFichier,"%s/%s",FondBouton,"champivert.jpg");
	ChargerImage(nomFichier,192.5,355,0,0,140,40);
	EcrireTexte(202.5,383,N1,1);

	//Creation du bouton pour, le niveau moyen
	ChoisirCouleurDessin(CouleurParNom("black"));
	RemplirRectangle(455,350,150,50);
	sprintf(nomFichier,"%s/%s",FondBouton,"champiorange.jpg");
	ChargerImage(nomFichier,460,355,0,0,140,40);
	EcrireTexte(467,382,N2,1);//../383

	//Creation du bouton pour, le niveau difficile
	ChoisirCouleurDessin(CouleurParNom("black"));
	RemplirRectangle(720.5,350,150,50);
	sprintf(nomFichier,"%s/%s",FondBouton,"champirouge.jpg");
	ChargerImage(nomFichier,725.5,355,0,0,140,40);
	EcrireTexte(728.5,383,N3,1);

	while(1)
	{
		if (SourisCliquee())
		{
			X_Clk=_X;
			Y_Clk=_Y;
			
			//Code pour le clique du bouton vert
			if(X_Clk>=187.5 && X_Clk<=337.5 && Y_Clk>=350 && Y_Clk<=400){
			Niveau(4);
			
			}
			//Code pour le clique du bouton orange
			if(X_Clk>=455 && X_Clk<=605 && Y_Clk>=350 && Y_Clk<=400){
			Niveau(6);
			}
			//Code pour le clique du bouton rouge
			if(X_Clk>=720.5 && X_Clk<=870.5 && Y_Clk>=350 && Y_Clk<=400){
			Niveau(8);
			}
		}
	}
	Touche();
	FermerGraphique();
	return EXIT_SUCCESS;
}

int FonctionImageDejaPrise1fois(int numimageTableau[], int numcase, int numcarte){ //num case=18
	int i;
	int ValeurReturn=0;
	for(i=1;i<numcase;i++){
		if(numcarte==numimageTableau[i]){
			ValeurReturn = 1; 
			break;
		}
	}
	return ValeurReturn;
}
int FonctionImageDejaPrise2fois(int numimageTableau[], int numcase, int numcarte){
	int i;
	int NumImageTrouvee=0;
	for(i=1;i<numcase;i++){
		if(numcarte==numimageTableau[i]){
			NumImageTrouvee++;
			if(NumImageTrouvee==2)
				break;
		}
	}
	return NumImageTrouvee;
}

//Fonction aidant le remplissage des paires d images
int FonctionGagne(int tab[], int taille){
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
int FonctionRandom(int max){
	FILE * fichier;/* variable de type FILE  */
	int nombre;/* variable recevant un entier aléatoire créé par l ouverture de /dev/random */
	fichier = fopen("/dev/random", "r");
	fread(&nombre, sizeof(int), 1, fichier);
	if(nombre<0)
		nombre = - nombre;
	return (nombre % max) + 1;
}


/*
#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#define Seconde 1000000L

#define L_ECRAN 1070
#define H_ECRAN 601

*/
void AfficherTemps(int sec){
	char temps[500];
	ChoisirEcran(5);
	CreerFenetre(0,0,L_MENU,H_MENU);
	CopierZone(2,1,0,0,230,150,0,0);
	sprintf(temps, "Temps ecoule : %d:%02d", sec/60, sec%60);
	EcrireTexte(0,100,"Temps ecoule :         ",1);	
	EcrireTexte(0,100,temps,1);
	CopierZone(1,0,0,0,230,150,0,0);
	ChoisirEcran(0);
}

int Niveau(int DIM)
{
#define LH_TABLE 576
#define ESPACEMENT 8
#define LH_CARRE LH_TABLE/DIM // Longueur et Hauteur de la taille carte + espace en plus
#define LH_CARTE LH_CARRE-ESPACEMENT // Longueur et Hauteur de la taille des cotés d'une carte
#define DOSSIER_CARTES_VERSO "./Jeux/CartesJeuxVerso"
char IMAGE_CARTES_VERSO [100];
sprintf(IMAGE_CARTES_VERSO,"./Jeux/CartesJeuxVerso/%d/symboleberserk.jpg", LH_CARTE);
char DOSSIER_CARTES_RECTO [100];
sprintf(DOSSIER_CARTES_RECTO,"./Jeux/CartesJeuxRecto/%d", LH_CARTE);
#define IMAGE_FOND_ECRAN "./Jeux/fondjeux.jpg"
#define L 1070 //longueur de la page de la fenêtre
#define H 601 //hauteur de la page de la fenêtre
/*#define DIM 4 //dimension des carré (carte + espace vide)*/
#define NB_IMAGES_UNIQUES DIM*DIM/2
#define NBCARTES 53//nombre de cartes dans le dossier images
#define CYCLE 1000000L

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
	char FichiersImage[DIM*DIM+1][300];
	int TabNumImagesUniques[NB_IMAGES_UNIQUES];
	int TabNumImages[DIM*DIM];
	int NumeroImage = 0;
	int i,j;//compteur

	int TabNumCartesJouees[DIM*DIM];	
	int TabNumCartesGagnees[DIM*DIM];
	int nbClicksJouees;
	int numCarteJouee1,linCJ1,colCJ1;
	int numCarteJouee2,linCJ2,colCJ2;
	unsigned long TempsAttente;
	unsigned long t1;

	InitialiserGraphique();
	CreerFenetre(0,0,L,H);
	ChargerImageFond(IMAGE_FOND_ECRAN);
	DessinerRectangle(247,12.5,LH_TABLE+ESPACEMENT,LH_TABLE+ESPACEMENT);//247,12.5,576+8,576+8 - x, y, xl, yh de la table de jeux et le +8 est la marge de fin des derniers carré
	
	//Construction de la table de jeux avec les carrés et leurs espacement
	for(ligne=0;ligne<DIM;ligne++){
		for(colonne=0;colonne<DIM;colonne++){
			x=Xcarre + colonne*LH_CARRE;
			y=Ycarre + ligne*LH_CARRE;
			DessinerRectangle(x,y,LH_CARTE,LH_CARTE);
			ChargerImage(IMAGE_CARTES_VERSO,x,y,0,0,LH_CARTE,LH_CARTE);
		}
	}
//Initialisation de la distribution de cartes aléatoires
int NumeroRandomImage;//numero de l'image choisir au hasard parmi le NB_IMAGES_UNIQUES
for(i=1; i<=NB_IMAGES_UNIQUES ; i++){
	do 
	{
		NumeroRandomImage = FonctionRandom(NBCARTES);
		TabNumImagesUniques[i] = NumeroRandomImage;
	} while (NumeroRandomImage==0 || FonctionImageDejaPrise1fois(TabNumImagesUniques,i,NumeroRandomImage)==1);
	//printf("TabNumImageUnique(%d)= %d\n",i,TabNumImagesUniques[i]);
}
for(i=1; i<=(DIM*DIM) ; i++){
	do {
		NumeroRandomImage = FonctionRandom(NB_IMAGES_UNIQUES);
		TabNumImages[i] = NumeroRandomImage;
	} while (NumeroRandomImage==0 || NumeroRandomImage>NB_IMAGES_UNIQUES || FonctionImageDejaPrise2fois(TabNumImages,i,NumeroRandomImage)==2);
	//printf("Indices TabNumImages(%d)= %d\n",i,TabNumImages[i]);
}
for(i=1; i<=(DIM*DIM) ; i++){
	TabNumImages[i] = TabNumImagesUniques[TabNumImages[i]];
	//printf("Valeurs TabNumImages(%d)= %d\n",i,TabNumImages[i]);
	sprintf(FichiersImage[i],"%s/%d.jpg",DOSSIER_CARTES_RECTO,TabNumImages[i]);
	//printf("FichiersImage(%d)= %s\n",i,FichiersImage[i]);
}

	//attribution des images pour carrés
	NumeroImage=0;
	for(ligne=0;ligne<DIM;ligne++){
		for(colonne=0;colonne<DIM;colonne++){
			NumeroImage++;
			Click[ligne][colonne]=0;
			Image[ligne][colonne]=TabNumImages[NumeroImage];
			//printf("Dans attribution - FichiersImage(%d)= %s\n",NumeroImage,FichiersImage[NumeroImage]);	
		}
	}

//Initialisation
for(i=1;i<=(DIM*DIM);i++){
	TabNumCartesJouees[i] = 0;
	TabNumCartesGagnees[i] = 0;
	//printf("Dans Initialisation - FichiersImage(%d)= %s\n",i,FichiersImage[i]);	
}

nbClicksJouees = 0;
numCarteJouee1 = 0;
numCarteJouee2 = 0;
/* Affichage du timer */
int temps = 0;
unsigned long Cycle;
/* Traitement de la touche triche */
int t;
	// Touche TRICHE, ramplissage de Ecran 3
	ChoisirEcran(3);
	//on retourne=affiche les cartes non gagnées encore
	NumeroImage=0;
	for(ligne=0;ligne<DIM;ligne++){
		for(colonne=0;colonne<DIM;colonne++){
			NumeroImage++;
			x=Xcarre + colonne*LH_CARRE;
			y=Ycarre + ligne*LH_CARRE;
			if (TabNumCartesJouees[NumeroImage]==0)
				ChargerImage(FichiersImage[NumeroImage],x,y,0,0,LH_CARTE,LH_CARTE);
		}
	}
	ChoisirEcran(0);

while(1)
{
	/* Affichage du timer *sur Ecran 1 */
	Cycle = Microsecondes() + CYCLE;
	ChoisirEcran(0);

	// Touche TRICHE
	if (ToucheEnAttente()) {
		t=Touche();
		switch(t){
			case XK_t://t
				//on retourne=affiche les cartes non gagnées encore Ecran 3
				ChoisirEcran(3);
				//On doit attendre 1 seconde selon le,projet
				TempsAttente = Microsecondes();
				while ((Microsecondes()-TempsAttente)<CYCLE){
					t1=Microsecondes();
				}
				//on retourne=cache les cartes non gagnées encore Ecran 1
				ChoisirEcran(0);
		}
	}

	//ChoisirEcran(2);
	if (Microsecondes() > Cycle){
		AfficherTemps(temps);
		temps += 1;
		Cycle = Microsecondes() + CYCLE;
		ChoisirEcran(0);
	}

	if (SourisCliquee())
	{

		X_Clk=_X;
		Y_Clk=_Y;
		
		NumeroImage=0;
		for(ligne=0;ligne<DIM;ligne++){
			for(colonne=0;colonne<DIM;colonne++){
				NumeroImage++;
				//printf("Dans SourisCliquee Apres for for - FichiersImage(%d)= %s\n",NumeroImage,FichiersImage[NumeroImage]);
				x=Xcarre + colonne*LH_CARRE;
				y=Ycarre + ligne*LH_CARRE;
				if(X_Clk>=x && X_Clk<=(x+LH_CARTE) && Y_Clk>=y && Y_Clk<=(y+LH_CARTE)){
					if(Click[ligne][colonne]==0){
						//printf("Dans SourisCliquee - FichiersImage(%d)= %s\n",NumeroImage,FichiersImage[NumeroImage]);
						ChargerImage(FichiersImage[NumeroImage],x,y,0,0,LH_CARTE,LH_CARTE);
						Click[ligne][colonne]==1;
						//********************************************
						nbClicksJouees++;
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
							if(FonctionGagne(TabNumCartesJouees,DIM*DIM)==1){
								//c'est gagné
								//fin de partie
								printf("C'est gagné !!!!!!!!!!!!!!!!!!!!!!!!!\n");
							} else {
								//c'est pas gagné
								printf("C'est pas encore gagné !!!!!!!!!!!!!!!!!!!!!!!!!\n");
								if(TabNumImages[numCarteJouee1]==TabNumImages[numCarteJouee2]){
									//on continue - on active les deux cartes jouées dans TabNumCartesJouees
									TabNumCartesJouees[numCarteJouee1]=1;
									TabNumCartesJouees[numCarteJouee2]=1;
									//on garde les cartes les cartes retournees
								} else {
									//on continue - on reinitialise les deux cartes jouées dans TabNumCartesJouees
									TabNumCartesJouees[numCarteJouee1]=0;
									TabNumCartesJouees[numCarteJouee2]=0;
									//on retourne les cartes
									//On doit attendre 1 seconde selon le,projet
									TempsAttente = Microsecondes();
									while ((Microsecondes()-TempsAttente)<CYCLE){
										t1=Microsecondes();
									}
									//
									ChargerImage(IMAGE_CARTES_VERSO,linCJ1,colCJ1,0,0,LH_CARTE,LH_CARTE);
									ChargerImage(IMAGE_CARTES_VERSO,linCJ2,colCJ2,0,0,LH_CARTE,LH_CARTE);
								}
								//
								nbClicksJouees = 0;
							}
							nbClicksJouees = 0;
							numCarteJouee1 = 0;
							numCarteJouee2 = 0;
							//******************
						}
						//printf("NumeroImage = %d) - Coo : (d%;%d) ligne=%d ; colonne=%d) (Image Num = %d) \n", NumeroImage, X_Clk,ligne,colonne,Image[ligne][colonne]);
						//printf("FichiersImage(%d) = %s\n",NumeroImage,FichiersImage[NumeroImage]);
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
