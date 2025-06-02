#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#define Seconde 1000000UL

#define L_ECRAN 230
#define H_ECRAN 100

/*Affichage du temps quand un niveau est ouvert*/
void AfficherTemps(int sec){
	char temps[50];
	ChoisirEcran(1);
	CopierZone(2,1,0,0,L_ECRAN,H_ECRAN,0,0);
	sprintf(temps, "Chrono : %d:%02d", sec/60, sec%60);
	EcrireTexte(0,0,temps,1);
	CopierZone(1,0,0,0,L_ECRAN,H_ECRAN,0,0);
}

/*exemple d'utilisation de l'affichage du temps*/
int Temps(void){
	int temps = 0;
	unsigned long Cycle;
	/* InitialiserGraphique(); */
	/* CreerFenetre(0,0,1700,601); */
	ChoisirEcran(2);
	ChargerImageFond("./Jeux/paysage.jpg");
	Cycle = Microsecondes()+Seconde;
	while (1){
		if (Microsecondes()>Cycle){
			AfficherTemps(temps);
			temps += 1;
			Cycle = Microsecondes()+Seconde;
		}
	}
}
