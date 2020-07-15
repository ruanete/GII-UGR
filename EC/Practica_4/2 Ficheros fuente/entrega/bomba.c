// gcc -Og bomba.c -o bomba -no-pie

#include <stdio.h>	// para printf(), fgets(), scanf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()
#include <sys/time.h>	// para gettimeofday(), struct timeval
#include <stdbool.h>

#define SIZE 100
#define TLIM 5

//Contraseña: abrelabomba
//PIN: 1997

//La contraseña codificada simplemente tiene cada par de elementos cambiados
//El pin codificado simplemente se saca como la resta de 9179 - 7182=1997

//Contraseña codificada: baeralobbma
//PIN Codificada: 9179

char password[]="baeralobbma\n";	// contraseña codificada
int  passcode  = 9179;			// pin codificado

int LongitudCadena (char *cadena){
	int j=0;
	while (cadena[j] != '\n') {
		j++;
	}

	return j;
}

bool compruebaPass(char pass[]){
	int tam = LongitudCadena(pass);
	int tamOriginal = LongitudCadena(password);
	char encryptedUserPass[tam+1];
	bool esCorrecta=false;

	if(tam==tamOriginal){
		for(int i=0; i<tam; i+=2){
			if(pass[i+1]=='\n')
				encryptedUserPass[i] = pass[i];
			else{
				encryptedUserPass[i] = pass[i+1];
				encryptedUserPass[i+1] = pass[i];
			}
		}

		if(strncmp(encryptedUserPass,password,sizeof(password)))
			esCorrecta=true;
		else
			esCorrecta=false;
	}else{
		esCorrecta=false;
	}
	return esCorrecta;
}

void boom(void){
	printf(	"\n"
		"***************\n"
		"*** BOOM!!! ***\n"
		"***************\n"
		"\n");
	exit(-1);
}

void defused(void){
	printf(	"\n"
		"·························\n"
		"··· bomba desactivada ···\n"
		"·························\n"
		"\n");
	exit(0);
}

int main(){
	char pw[SIZE];
	int  pc, n;

	struct timeval tv1,tv2;	// gettimeofday() secs-usecs
	gettimeofday(&tv1,NULL);

	do	printf("\nIntroduce la contraseña: ");
	while (	fgets(pw, SIZE, stdin) == NULL );
	if  	(!compruebaPass(pw))
	    boom();

	gettimeofday(&tv2,NULL);
	if    ( tv2.tv_sec - tv1.tv_sec > TLIM )
	    boom();

	do  {	printf("\nIntroduce el pin: ");
	 if ((n=scanf("%i",&pc))==0)
		scanf("%*s")    ==1;         }
	while (	n!=1 );
	if    (	pc != (passcode-7182) )
	    boom();

	gettimeofday(&tv1,NULL);
	if    ( tv1.tv_sec - tv2.tv_sec > TLIM )
	    boom();

	defused();
}
