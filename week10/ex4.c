#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void findLinks(const char* dirPath, ino_t inode, char* links){
	DIR* dirp = opendir (dirPath);
	if (dirp == NULL ) {printf("(findLinks) Error with open %s\n",dirPath); return;}
	
	struct dirent * dp;
	char first = 1;
	while ((dp = readdir ( dirp )) != NULL ) {
		if(dp->d_ino == inode){
			if(!first){
				strcat(links, ", ");
			} else first=0;
			strcat(links, dp->d_name);
		}
	}
}

int main(void) {
	DIR* dirp = opendir ("tmp");
	if (dirp == NULL ) {printf("Error with open 'tmp'\n"); return 1;}
	
	char first = 1;
	struct dirent * dp;
	struct stat sb;
	while ((dp = readdir ( dirp )) != NULL ) {
		char name[128] = "tmp/";
		strcat(name, dp->d_name);

		if (stat(name, &sb)  == -1) {
         printf("(%s):",name);
         perror("lstat");
         continue;
    }
		if (!S_ISREG(sb.st_mode)) continue;
		
		if(sb.st_nlink >= 2){
			if(first){
				printf("File — Hard Links\n");
				first = 0;
			}
			char links[512]="";
			findLinks("tmp", dp->d_ino, links);
			printf("%s — %s\n", dp->d_name, links);
		}
	}
  return 0;
}

