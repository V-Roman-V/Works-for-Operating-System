#include <dirent.h> 
#include <stdio.h> 

int main(void) {
  DIR *d;
  struct dirent *dir;
  if (!(d = opendir("/"))){
		printf("Error while open root directory");
		return(1);
	}
	
	while ((dir = readdir(d)) != NULL) {
		printf("%s\n", dir->d_name);
	}
	closedir(d);

  return(0);
}

