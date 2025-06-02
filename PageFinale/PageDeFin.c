#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#define L 1070
#define H 601
#define THEEND "/home/vallejos/SAE11_2022/PageFinale/imagetheend.png"

int main()
{
	InitialiserGraphique();
	CreerFenetre(0,0,L,H);
	ChargerImageFond(THEEND);

	Touche();
	FermerGraphique();
	return EXIT_SUCCESS;

}
