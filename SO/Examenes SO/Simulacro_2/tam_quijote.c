#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<ftw.h>

#define MAXLEVEL 1

struct FTW {
  int base;
  int level;
};

int busquedaDirectorio(const char *pathname, const struct stat* stat, int flags, struct FTW* ftw){
  if(ftw->level > MAXLEVEL){
    return 0;
  }

  if(S_ISREG(stat->st_mode) && (stat->st_mode & S_IRWXU) && !(stat->st_mode & S_IRWXG) && (stat->st_mode & S_IWOTH)){
    char *last= strrchr(pathname, '/');
    char fichero[100];
    last = last+1;

    if(strcmp(last, "quijote.txt") == 0){
      int n = (int) stat->st_size;
      write(STDOUT_FILENO, &n, sizeof(n));
    }/*else{
      printf("%s\n", last);
    }*/
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
