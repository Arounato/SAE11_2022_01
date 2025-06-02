#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#define Seconde 1000000UL

#define L_ECRAN 1070
#define H_ECRAN 601

void AfficherTemps(int sec){
	char temps[500];
	ChoisirEcran(1);
	CopierZone(2,1,0,0,L_ECRAN,H_ECRAN,0,0);
	if (sec%60 < 10)
		sprintf(temps, "POPO<10 : %d:0%d", sec/60, sec%60);
	else
		sprintf(temps, "POPO>=10 : %d:%d", sec/60, sec%60);
	EcrireTexte(0,100,temps,1);
	CopierZone(1,0,0,0,L_ECRAN,H_ECRAN,0,0);
}

int main(void){
	int temps = 0;
	unsigned long Cycle;
	InitialiserGraphique();
	CreerFenetre(0,0,L_ECRAN,H_ECRAN);
	ChoisirEcran(2);
	ChargerImageFond("./Jeux/luigi.jpg");
	Cycle = Microsecondes()+Seconde;
	while (1){
		if (Microsecondes()>Cycle){
			AfficherTemps(temps);
			temps += 1;
			Cycle = Microsecondes()+Seconde;
		}
	}
	ChoisirEcran(1);
}