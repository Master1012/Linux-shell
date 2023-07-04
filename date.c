#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char const *argv[]){
	char arr[150];
	struct tm *lt;
	if(argv[2] != NULL){
		if(!strcmp(argv[2],"-I")){
            time_t tm;
            time(&tm);
            char datei[256];
	        memset(datei, 0, sizeof(datei));
            lt=localtime(&tm);
            strftime(datei,256,"%F",lt);
            printf("%s\n",datei);
            exit(EXIT_SUCCESS);
        }
        else if(!strcmp(argv[2],"-u")){
            time_t tm;
            time(&tm);
            tm=mktime(gmtime(&tm));
            printf("%s",ctime(&tm));
            exit(EXIT_SUCCESS);
        }
        else{
		    printf("Invalid command\n");
            exit(EXIT_FAILURE);
        }
	}
    else{
        time_t tm;
        time(&tm);
        printf("%s", ctime(&tm));
        exit(EXIT_SUCCESS);
    }
}