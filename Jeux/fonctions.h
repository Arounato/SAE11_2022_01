/* fonctions.h */
#ifndef FICHIER_H
#define FICHIER_H

/* Prototypes des fonctions : */
int FonctionMenu(void);
int FonctionImageDejaPrise1fois(int numimageTableau[], int numcase, int numcarte);
int FonctionImageDejaPrise2fois(int numimageTableau[], int numcase, int numcarte);
int FonctionGagnee(int tab[], int taille);
void AfficherTemps(int sec);
int FonctionNiveaux(int DIM);

#endif /* FICHIER_H */