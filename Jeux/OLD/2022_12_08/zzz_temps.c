#include<stdio.h>
#include<stdlib.h>
#include<graph.h>

#define CYCLE 10000L

int main()
{
unsigned long suivant;
unsigned long t1;

/* on marque le debut du cycle */
suivant = Microsecondes()+CYCLE;
printf("suivant = %d\n",suivant);

t1 = Microsecondes();
while ((Microsecondes()-t1)<80000L) /* boucle principale du programme */
{
	if (Microsecondes()>suivant)
	{
		/* une periode s'est écoulé */
		/* prochaine date */
		suivant= Microsecondes()+CYCLE;
		printf("suivant = %d\n",suivant);	
	}
}

printf("Hello c est fini\n");

return EXIT_SUCCESS;
}