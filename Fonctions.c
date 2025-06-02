#include <stdio.h>
#include <stdlib.h>
#include<graph.h>

/* numimageTableau = tableau d'entiers
 * numcase = numero de la case correspondant à une ligne et une colonne
 * num carte = indice de la carte*/
/*FonctionImageDejaPrise1Fois = Si l'image "numcarte.jpg" est deja prise une fois dans le tableau*/
int FonctionImageDejaPrise1fois(int numimageTableau[], int numcase, int numcarte){ /*num case=18*/
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
/*FonctionImageDejaPrise2Fois = Si l'image "numcarte.jpg" est deja prise deux fois dans le tableau*/
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

/*Fonction qui vérifie si toutes les cartes sont retournés, si oui alors gagné et donc fin*/
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
/*Fonction qui génére un nombre aléatoire entre 1 et max pour l'attribuer au numéro de l'image*/
int FonctionRandom(int max){
	FILE * fichier;/*variable de type FILE */
	int nombre;/* variable recevant un entier aléatoire créé par l ouverture de /dev/random */
	fichier = fopen("/dev/random", "r");
	fread(&nombre, sizeof(int), 1, fichier);
	if(nombre<0)
		nombre = - nombre;
	return nombre %max + 1;
}

