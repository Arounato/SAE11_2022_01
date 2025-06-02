#include<stdlib.h>
#include<stdio.h>
#include<graph.h>
#define FondEcranPrincipal "/home/bob/sae11_2022/Jeux"
#define IMAGE_FOND_ECRAN "/home/bob/SAE11_2022/Jeux/fondjeux.jpg"//AJOUT ************
#define FondBouton "/home/bob/SAE11_2022/Jeux"//MODIF ************
#define IMAGE_NIVEAU_FAC "/home/bob/SAE11_2022/Jeux/champignonvert_140x40.jpg"//AJOUT ************
#define IMAGE_NIVEAU_MOY "/home/bob/SAE11_2022/Jeux/champignonorange_140x40.jpg"//AJOUT ************
#define IMAGE_NIVEAU_DIF "/home/bob/SAE11_2022/Jeux/champignonrouge_140x40.jpg"//AJOUT ************
#define L 1070
#define H 601

int main()
{
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
	ChargerImageFond(IMAGE_FOND_ECRAN);

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
	int espaceEntreRectangles = (L-rL)/4;

	//Coordonnees du rectangle 1 cliquer
	int xa1 = 100;//coordonnee x du point haut gauche
	int xb1 = xa1+rL;//coordonnee x du point bas droite
	int ya1 = 350;//coordonnee y du point haut gauche
	int yb1 = ya1+rH;//coordonnee y du point bas droite

	//Coordonnees du rectangle 2 cliquer
	int xa2 = 325;//coordonnee x du point haut gauche
	int xb2 = xa2+rL;//coordonnee x du point bas droite
	int ya2 = 350;//coordonnee y du point haut gauche
	int yb2 = ya2+rH;//coordonnee y du point bas droite

	//Coordonnees du rectangle 3 cliquer
	int xa3 = 550;//coordonnee x du point haut gauche
	int xb3 = xa3+rL;//coordonnee x du point bas droite
	int ya3 = 350;//coordonnee y du point haut gauche
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


	int xClk=0;//x du click
	int yClk=0;//y du click

	while(!SourisCliquee()){
		xClk=_X;
		yClk=_Y;
	}
	while(1)
	{
		if (SourisCliquee()) 
		{
			xClk=_X;
			yClk=_Y;

			if (xClk>=xa1 && xClk<xb1 && yClk>=ya1 && yClk<=yb1){
				printf("Rectangle vert clickée (X=%d ; Y=%d)\n", xClk, yClk);
			}
			if (xClk>=xa2 && xClk<xb2 && yClk>=ya2 && yClk<=yb2){
				printf("Rectangle orange clickée (X=%d ; Y=%d)\n", xClk, yClk);
			}
			if (xClk>=xa3 && xClk<xb3 && yClk>=ya3 && yClk<=yb3){
				printf("Rectangle rouge clickée (X=%d ; Y=%d)\n", xClk, yClk);
			}

		}
		if (ToucheEnAttente()) break;
	}

	Touche();
	FermerGraphique();
	return EXIT_SUCCESS;
}
