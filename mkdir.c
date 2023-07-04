#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
int main(int argc, char* argv[]){
    int check;
    if(!strcmp(argv[2],"-v")){
        char* dname = argv[3];
        check = mkdir(dname,0777);
        if (!check){
            printf("Directory created %s\n",argv[2]);
        }
        else if (check == -1){
            if(EEXIST==errno){
                printf("Directory already exists\n");
                exit(0);
            }
        }
        else {
            printf("Failed to create directory\n");
            exit(0);
        }
    }
    else if(!strcmp(argv[2],"-p")){
        int i=3;
        while(argv[i] != '\0'){
				char parr[300];
				char *p = NULL;
				size_t length;
				snprintf(parr, sizeof(parr), "%s", argv[i]);
				length = strlen(parr);
				if(parr[length-1] == '/'){
					parr[length-1] = 0;
				}
				for(p = parr+1; *p; p++){
					if(*p == '/'){
						*p = 0;
						mkdir(parr, S_IRWXU);
						*p = '/';
					}
				}
				mkdir(parr, S_IRWXU);
				i++;
			}
    }
    else if(argv[2][0]=='-'){
        printf("Invalid command\n");
    }
    else{
        char* dname = argv[2];
        check = mkdir(dname,0777);
        if (check == -1){
            if(EEXIST==errno){
                printf("Directory already exists\n");
                exit(0);
            }
            else {
                printf("Failed to create directory\n");
                exit(0);
            }
        }
    }
}