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
        char* dirname = argv[2];
        check = rmdir(dirname);
        if (!check){
            printf("Removed %s directory\n",argv[3]);
        }
        else if (check == -1){
            printf("Failed to remove directory\n");
            exit(0);
        }
    }
    else if(!strcmp(argv[2],"-i")){
        char* dirname = argv[3];
        char c;
        printf("Remove %s [y/n] ", argv[3]);
        scanf("%c",&c);
        if (c=='y'){
            check = rmdir(dirname);
            if (check == -1){
                printf("Failed to remove directory\n");
                exit(0);
            }
        }
        else{
            exit(0);
        }
    }
    else if(argv[2][0]=='-'){
        printf("Invalid command\n");
    }
    else{
        char* dirname = argv[2];
        check = rmdir(dirname);
        if (check == -1){
            printf("Failed to remove directory\n");
            exit(0);
        }
    }
}