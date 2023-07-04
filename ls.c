#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char const *argv[]){
    char *temp;
    // printf("%d\n",argc);
    // printf("<%s> <%s> <%s>\n",argv[0],argv[1],argv[2]);
    if (argv[2]==NULL){
        struct dirent **dirlist;
        int num;
        num = scandir(".", &dirlist, 0, alphasort);
        int i = 0;
        for(i=0; i < num; i++){
            char *nm;
            nm = dirlist[i]->d_name;
            if(nm[0] != '.'){
                printf("%s\n", dirlist[i]->d_name);
                free(dirlist[i]);
            }
        }
        free(dirlist);
    }
    else if(!strcmp(argv[2],"-a")){
        struct dirent **dirlist;
        int num;
        num = scandir(".", &dirlist, 0, alphasort);
        int i = 0;
        for(i=0; i < num; i++){
            char *nm;
            nm = dirlist[i]->d_name;
            printf("%s\n", dirlist[i]->d_name);
            free(dirlist[i]);
        }
        free(dirlist);
    }
    else if(!strcmp(argv[2],"-r")){
        struct dirent **dirlist;
        int num;
        num = scandir(".", &dirlist, 0, alphasort);
        int i = 0;
        for(i=num-1; i >= 0; i--){
            char *nm;
            nm = dirlist[i]->d_name;
            if(nm[0] != '.'){
                printf("%s\n", dirlist[i]->d_name);
                free(dirlist[i]);
            }
        }
        free(dirlist);
    }
}