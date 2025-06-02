### VARIABLES ###
CC = gcc

EXE = projet
OFILES = Temps.o \
         Fonctions.o \
         Niveaux.o \
         Menu.o \
         main.o

### BUT PAR DEFAUT ###
but : ${EXE}

### REGLES ESSENTIELLES ###
Niveaux.o : Fonctions.h 
Menu.o : Niveaux.h
main.o : Menu.h

${EXE} : ${OFILES}
	$(CC) -o ${EXE} ${OFILES} -lgrapĥ
