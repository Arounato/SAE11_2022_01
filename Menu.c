#include <stdio.h>
#include <stdlib.h>
#include<graph.h>
#include"Niveaux.h"

int Menu(void)
{

#define FondEcranPrincipal "./MenuPrincipal"
#define FondBouton "./MenuPrincipal"
#define L_MENU 1070
#define H_MENU 601

	int FtrPpl1 = 0; /*position x de la fenetrePrincipal*/
	int FtrPpl2 = 0;/*position y de la fenetre principal*/
	int TFtrPpl1 = L_MENU; /*Taille de la Fenetre Principal en largeur*/
	int TFtrPpl2 = H_MENU; /*Taille de la Fenetre Principal en hauteur*/
	char nomFichier[10];/*Nombre de caractere du nom du fichier*/
	int x,y;/*variable pour le texte principale*/
	char *T="Jeux de paires";
	char *N1="Niveau Facile";
	char *N2="Niveau Moyen";
	char *N3="Niveau Difficile";
	int X_Clk;/*positionnement du clique par rapport au x de la fenetre*/
	int Y_Clk;/*positionnement du clique par rapport au y de la fenetre*/

	InitialiserGraphique();
	/*Création du fond d'écran de la fenetre principal*/
	CreerFenetre(0,0,L_MENU,H_MENU);
	sprintf(nomFichier,"%s/%s",FondEcranPrincipal,"luigi.jpg");
	ChargerImageFond(nomFichier);

	ChoisirCouleurDessin(CouleurParNom("black"));/*couleur qui se situera derriere le rectangle "white"*/
	RemplirRectangle(380,55,310,70);
	ChoisirCouleurDessin(CouleurParNom("white"));/*couleur du rectangle qui se situera derriere le titre*/
	RemplirRectangle(385,60,300,60);
	ChoisirCouleurDessin(CouleurParNom("black"));/*titre qui se situera devant le rectangle de couleur*/
	y=H_MENU/6;
	x=(L_MENU-TailleChaineEcran(T,2))/2;
	EcrireTexte(x,y,T,2);

	/*Creation du bouton pour, le niveaux facile*/
	ChoisirCouleurDessin(CouleurParNom("black"));/*couleur de fond pour l'image champivert*/
	RemplirRectangle(187.5,350,150,50);
	sprintf(nomFichier,"%s/%s",FondBouton,"champivert.jpg");
	ChargerImage(nomFichier,192.5,355,0,0,140,40);
	EcrireTexte(202.5,383,N1,1);

	/*Creation du bouton pour, le niveau moyen*/
	ChoisirCouleurDessin(CouleurParNom("black"));/*couleur de fond pour l'image champiorange*/
	RemplirRectangle(455,350,150,50);
	sprintf(nomFichier,"%s/%s",FondBouton,"champiorange.jpg");
	ChargerImage(nomFichier,460,355,0,0,140,40);
	EcrireTexte(467,382,N2,1);/*../383*/

	/*Creation du bouton pour, le niveau difficile*/
	ChoisirCouleurDessin(CouleurParNom("black"));/*couleur de fond pour l'image champirouge*/
	RemplirRectangle(720.5,350,150,50);
	sprintf(nomFichier,"%s/%s",FondBouton,"champirouge.jpg");
	ChargerImage(nomFichier,725.5,355,0,0,140,40);
	EcrireTexte(728.5,383,N3,1);

	while(1)
	{
		if (SourisCliquee())
		{
			X_Clk=_X;/*positionnement du clique par rapport au x de la fenetre*/
			Y_Clk=_Y;/*positionnement du clique par rapport au y de la fenetre*/

			/*Code pour le clique du bouton vert*/
			if(X_Clk>=187.5 && X_Clk<=337.5 && Y_Clk>=350 && Y_Clk<=400){
			Niveau(4);

			}
			/*Code pour le clique du bouton orange*/
			if(X_Clk>=455 && X_Clk<=605 && Y_Clk>=350 && Y_Clk<=400){
			Niveau(6);
			}
			/*Code pour le clique du bouton rouge*/
			if(X_Clk>=720.5 && X_Clk<=870.5 && Y_Clk>=350 && Y_Clk<=400){
			Niveau(8);
			}
		}
	}
	Touche();
	FermerGraphique();
	return EXIT_SUCCESS;
}
