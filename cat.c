#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc, char *argv[]) {
    FILE *file;
    char line[100];
    if(!strcmp(argv[2],"-n")){
        file = fopen(argv[3],"r");
        if(file==NULL){
            printf("File not found");
        }
        else{
            int i=1;
            while(fscanf(file,"%[^\n]\n",line)!=EOF) {
                printf("%d %s\n", i, line);
                i++;
            }
        }
        fclose(file);
    }
    else if(!strcmp(argv[2],"-E")){
        file = fopen(argv[3],"r");
        if(file==NULL){
            printf("File not found");
        }
        else{
            while(fscanf(file,"%[^\n]\n",line)!=EOF) {
                printf("%s$\n", line);
            }
        }
        fclose(file);
    }
    else if(argv[2][0]=='-'){
        printf("Invalid command\n");
    }
    else{
        file = fopen(argv[2],"r");
        if(file==NULL){
            printf("File not found");
        }
        else{
            while(fscanf(file,"%[^\n]\n",line)!=EOF) {
                printf("%s\n", line);
            }
        }
        fclose(file);
    }
}