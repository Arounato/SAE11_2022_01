#include <stdio.h>
#include <stdlib.h>
#include <graph.h>

/* Fonction aidant le remplissage d images uniques*/
int FonctionImageDejaPrise1fois(int numimageTableau[], int numcase, int numcarte){
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

/* Fonction aidant le remplissage des paires d images */
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

/* Fonction donnant  */
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
