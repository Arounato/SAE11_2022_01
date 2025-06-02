#ifndef _MenuPrincipal_
#define _MenuPrincipal_

void Niveau4(void);
void Niveau6(void);
void Niveau8(void);

int FonctionImageDejaPrise1fois(int numimageTableau[], int numcase, int numcarte);
int FonctionImageDejaPrise2fois(int numimageTableau[], int numcase, int numcarte);
int FonctionGagne(int tab[], int taille);

int FonctionRandom(int max);
void AfficherTemps(int sec);

int Niveau(int DIM);

int Menu(void);

#endif
