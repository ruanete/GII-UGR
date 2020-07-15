#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<ftw.h>

struct FTW {
  int base;
  int level;
};

int busquedaDirectorio(const char *pathname, const struct stat* stat, int flags, struct FTW* ftw){
  //if(S_ISREG(stat->st_mode) && (stat->st_mode & S_IRWXU) && (stat->st_mode & S_IWOTH)){
    //Con estas 5 líneas se consigue solo el nombre del fichero ya que se separan con "/", en last estará almacenado el nombre del fichero
    //Si hacemos char *filename= strrchr(path, '/'); filename = filename + 1; obtiene la ultima ocurrencia
    /*char fichero[100]= {'\0'};
    char * token, * last;
    char s[100];
    strcpy(s, pathname);
    last = token = strtok(s, "/");
    for (;(token = strtok(NULL, "/")) != NULL; last = token);*/
    char *last= strrchr(pathname, '/');
    char fichero[100];
    if(last!=NULL){
      last = last+1;

      //Comprobamos que su tamaño sea mayor que 7 imprimimos lo que nos piden
      if(S_ISREG(stat->st_mode) && (stat->st_mode & S_IRWXU) && (stat->st_mode & S_IWOTH) && strlen(last) > 7){
        sprintf(fichero, "%s|%o|%d", last, stat->st_mode &~S_IFMT, (int) stat->st_size);
        write(STDOUT_FILENO, fichero, strlen(fichero));
      }
    }

  return 0;
}

int main(int argc, char *argv[]) {
  char *pathname;

	if(argc!=2){
		printf("No has pasado un argumento\n");
		exit(EXIT_FAILURE);
	}else{
		pathname = argv[1];
	}

  if(nftw(pathname, busquedaDirectorio, 10, 0) != 0){
    perror("ntfw");
  }

	return 0;
}
