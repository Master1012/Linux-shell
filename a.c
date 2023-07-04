#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include<sys/stat.h>
#include <pthread.h>

int main(){
    char cwd[100];
    char str[200];
    while(1){
        printf(">> ");
        scanf("%[^\n]%*c",str);
        char *temp;
        temp = strtok(str," ");
        strcpy(temp,str);
        if(temp==NULL){
            continue;
        }
        else if (!(strcmp(temp,"echo"))){
            temp = strtok(NULL," ");
            int t=0;
            if (!strcmp(temp,"-e")){
                temp = strtok(NULL," ");
                while(temp != NULL){
                    for (int i=0;i<strlen(temp);i++){
                        if (temp[i]=='\\' && t==0){
                            t++;
                        }
                        else if(temp[i]=='\\' && t==1){
                            if(temp[i+1]=='n'){
                                printf("\n");
                            }
                            else if (temp[i+1]=='t'){
                                printf("    ");
                            }
                            else{
                                printf("\\");
                            }
                            i++;
                        }
                        else{
                            t=0;
                            printf("%c",temp[i]);
                        }
                    }
                    temp = strtok(NULL," ");
                }
                printf("\n");
            }
            else if(!strcmp(temp,"-n")){
                temp = strtok(NULL," ");
                while(temp!=NULL){
                    for (int i=0;i<strlen(temp);i++){
                        if (temp[i]=='\\' && t==0){
                            t++;
                        }
                        else if(temp[i]=='\\' && t==1){
                            printf("\\");
                            i++;
                        }
                        else{
                            t=0;
                            printf("%c",temp[i]);
                        }
                    }
                    temp = strtok(NULL," ");
                }
            }
            else if(temp[0]=='-'){
                printf("Invalid command\n");
            }
            else{
                while(temp!=NULL){
                    for (int i=0;i<strlen(temp);i++){
                        if (temp[i]=='\\' && t==0){
                            t++;
                        }
                        else if(temp[i]=='\\' && t==1){
                            printf("\\");
                            i++;
                        }
                        else{
                            t=0;
                            printf("%c",temp[i]);
                        }
                    }
                    temp = strtok(NULL," ");
                }
                printf("\n");
            }
        }
        else if(!(strcmp(temp,"pwd"))){
            getcwd(cwd, sizeof(cwd));
            temp = strtok(NULL," ");
            if(temp==NULL){
                printf(">> %s\n",cwd);
            }
            else if (!(strcmp(temp,"-P"))){
                printf(">> %s\n",cwd);
            }
            else if(!(strcmp(temp,"-L"))){
                char enwd[80];
                char *envvar = "PATH";
                if(!getenv(envvar)){
                    fprintf(stderr, "The environment variable %s was not found.\n", envvar);
                }
                printf("PATH: %s\n", enwd);
            }
            else{
                printf("Not a valid command\n");
            }
        }    
        else if(!(strcmp(temp,"cd"))){
            temp = strtok(NULL," ");
            if (!strcmp(temp,"..")){
                chdir("..");
            }
            else if(!(strcmp(temp,"~"))||!(strcmp(temp,"-L"))){
                chdir(getenv("HOME"));
            }
            else{
                int bool;
                bool=chdir(temp);
                if (bool==-1){
                    printf("Invalid command\n");
                }
            }
        }
        else if(!(strcmp(temp,"exit"))){
            return 0;
        }
        else if (!strcmp(temp,"ls")){
            int pid= fork();
            temp=strtok(NULL," ");
            if(temp==NULL){
                if (pid<0){
                    printf("forking error\n");
                    exit(EXIT_FAILURE);
                }
                else if(pid ==0){
                    execl("/mnt/d/os/ls","ls","ls",NULL);
                }
                else{
                    wait(NULL);
                }
            }
            else if(!strcmp(temp,"-a")){
                if (pid<0){
                    printf("forking error\n");
                    exit(EXIT_FAILURE);
                }
                else if(pid ==0){
                    execl("/mnt/d/os/ls","ls","ls","-a",NULL);
                }
                else{
                    wait(NULL);
                }
            }
            else if(!strcmp(temp,"-r")){
                if (pid<0){
                    printf("forking error\n");
                    exit(EXIT_FAILURE);
                }
                else if(pid ==0){
                    execl("/mnt/d/os/ls","ls","ls","-r",NULL);
                }
                else{
                    wait(NULL);
                }
            }
            else{
                printf("Invalid command\n");
            }
        }
        else if(!strcmp(temp,"date")){
            temp=strtok(NULL," ");
            if(temp==NULL){
                int pid= fork();
                if (pid<0){
                    printf("forking error\n");
                    exit(EXIT_FAILURE);
                }
                else if(pid ==0){
                    execl("/mnt/d/os/date","date","date",NULL);
                }
                else{
                    wait(NULL);
                }
            }
            else if(!strcmp(temp,"-u")){
                int pid= fork();
                if (pid<0){
                    printf("forking error\n");
                    exit(EXIT_FAILURE);
                }
                else if(pid ==0){
                    execl("/mnt/d/os/date","date","date","-u",NULL);
                    exit(0);
                }
                else{
                    wait(NULL);
                }
            }
            else if(!strcmp(temp,"-I")){
                int pid= fork();
                if (pid<0){
                    printf("forking error\n");
                    exit(EXIT_FAILURE);
                }
                else if(pid ==0){
                    execl("/mnt/d/os/date","date","date","-I",NULL);
                    exit(0);
                }
                else{
                    wait(NULL);
                }
            }
            else{
                printf("Invalid command\n");
            }
        }
        else if(!strcmp(temp,"cat")){
            char *arr[10];
            arr[0]="\0";
            int i=1;
            while(temp!=NULL){
                arr[i]=temp;
                i++;
                temp=strtok(NULL," ");
            }
            int pid= fork();
            if (pid<0){
                printf("forking error\n");
                exit(EXIT_FAILURE);
            }
            else if(pid ==0){
                execvp("/mnt/d/os/cat",arr);
                exit(0);
            }
            else{
                wait(NULL);
            }
        }
        else if(!strcmp(temp,"mkdir")){
            char *arr[10];
            arr[0]="\0";
            int i=1;
            while(temp!=NULL){
                arr[i]=temp;
                i++;
                temp=strtok(NULL," ");
            }
            int pid= fork();
            if (pid<0){
                printf("forking error\n");
                exit(EXIT_FAILURE);
            }
            else if(pid ==0){
                execvp("/mnt/d/os/mkdir",arr);
            }
            else{
                wait(NULL);
            }
        }
        else if(!strcmp(temp,"rm")){
            char *arr[10];
            arr[0]="\0";
            int i=1;
            while(temp!=NULL){
                arr[i]=temp;
                i++;
                temp=strtok(NULL," ");
            }
            int pid= fork();
            if (pid<0){
                printf("forking error\n");
                exit(EXIT_FAILURE);
            }
            else if(pid ==0){
                execvp("/mnt/d/os/rm",arr);
            }
            else{
                wait(NULL);
            }
        }
        else if(!strcmp(temp,"&t")){
                    temp=strtok(NULL," ");
                    if(temp==NULL){
                        continue;
                    }
                    else if (!(strcmp(temp,"echo"))){
                    temp = strtok(NULL," ");
                    int t=0;
                    if (!strcmp(temp,"-e")){
                        temp = strtok(NULL," ");
                        while(temp != NULL){
                            for (int i=0;i<strlen(temp);i++){
                                if (temp[i]=='\\' && t==0){
                                    t++;
                                }
                                else if(temp[i]=='\\' && t==1){
                                    if(temp[i+1]=='n'){
                                        printf("\n\n");
                                    }
                                    else if (temp[i+1]=='t'){
                                        printf("    ");
                                    }
                                    else{
                                        printf("\\");
                                    }
                                    i++;
                                }
                                else{
                                    t=0;
                                    printf("%c",temp[i]);
                                }
                            }
                            temp = strtok(NULL," ");
                        }
                        printf("\n");
                    }
                    else if(!strcmp(temp,"-n")){
                        temp = strtok(NULL," ");
                        while(temp!=NULL){
                            for (int i=0;i<strlen(temp);i++){
                                if (temp[i]=='\\' && t==0){
                                    t++;
                                }
                                else if(temp[i]=='\\' && t==1){
                                    printf("\\");
                                    i++;
                                }
                                else{
                                    t=0;
                                    printf("%c",temp[i]);
                                }
                            }
                            temp = strtok(NULL," ");
                        }
                    }
                    else if(temp[0]=='-'){
                        printf("Invalid command\n");
                    }
                    else{
                        while(temp!=NULL){
                            for (int i=0;i<strlen(temp);i++){
                                if (temp[i]=='\\' && t==0){
                                    t++;
                                }
                                else if(temp[i]=='\\' && t==1){
                                    printf("\\");
                                    i++;
                                }
                                else{
                                    t=0;
                                    printf("%c",temp[i]);
                                }
                            }
                            temp = strtok(NULL," ");
                        }
                        printf("\n");
                    }
                }
                else if(!(strcmp(temp,"pwd"))){
                    getcwd(cwd, sizeof(cwd));
                    temp = strtok(NULL," ");
                    if(temp==NULL){
                        printf(">> %s\n",cwd);
                    }
                    else if (!(strcmp(temp,"-P"))){
                        printf(">> %s\n",cwd);
                    }
                    else if(!(strcmp(temp,"-L"))){
                        char enwd[80];
                        char *envvar = "PATH";
                        if(!getenv(envvar)){
                            fprintf(stderr, "The environment variable %s was not found.\n", envvar);
                        }
                        printf("PATH: %s\n", enwd);
                    }
                    else{
                        printf("Not a valid command");
                    }
                }    
                else if(!(strcmp(temp,"cd"))){
                    temp = strtok(NULL," ");
                    if (!strcmp(temp,"..")){
                        chdir("..");
                    }
                    else if(!(strcmp(temp,"~"))||!(strcmp(temp,"-L"))){
                        chdir(getenv("HOME"));
                    }
                    else{
                        int bool;
                        bool=chdir(temp);
                        if (bool==-1){
                            printf("Invalid command\n");
                        }
                    }
                }
                else if(!(strcmp(temp,"exit"))){
                    return 0;
                }
                else if (!strcmp(temp,"ls")){
                    pthread_t p;
                    char s[100]="/mnt/d/os/ls";
                    int i=1;
                    while(temp!=NULL){
                        strcat(s," ");
                        strcat(s,temp);
                        temp=strtok(NULL," ");
                    }
                    if(temp==NULL){
                        pthread_create(&p,NULL,(void*)(*system),(void*)(s));
                        pthread_join(p,NULL);
                    }
                    else{
                        printf("Invalid command\n");
                    }
                }
                else if(!strcmp(temp,"date")){
                    pthread_t p;
                    char s[100]="/mnt/d/os/date";
                    int i=1;
                    while(temp!=NULL){
                        strcat(s," ");
                        strcat(s,temp);
                        temp=strtok(NULL," ");
                    }
                    if(temp==NULL){
                        pthread_create(&p,NULL,(void*)(*system),(void*)(s));
                        pthread_join(p,NULL);
                    }
                    else{
                        printf("Invalid command\n");
                    }
                }
                else if(!strcmp(temp,"cat")){
                    pthread_t p;
                    char s[100]="/mnt/d/os/cat";
                    int i=1;
                    while(temp!=NULL){
                        strcat(s," ");
                        strcat(s,temp);
                        temp=strtok(NULL," ");
                    }
                    if(temp==NULL){
                        pthread_create(&p,NULL,(void*)(*system),(void*)(s));
                        pthread_join(p,NULL);
                    }
                    else{
                        printf("Invalid command\n");
                    }
                }
                else if(!strcmp(temp,"mkdir")){
                    pthread_t p;
                    char s[100]="/mnt/d/os/mkdir";
                    int i=1;
                    while(temp!=NULL){
                        strcat(s," ");
                        strcat(s,temp);
                        temp=strtok(NULL," ");
                    }
                    if(temp==NULL){
                        pthread_create(&p,NULL,(void*)(*system),(void*)(s));
                        pthread_join(p,NULL);
                    }
                    else{
                        printf("Invalid command\n");
                    }
                }
                else if(!strcmp(temp,"rm")){
                    pthread_t p;
                    char s[100]="/mnt/d/os/rm";
                    int i=1;
                    while(temp!=NULL){
                        strcat(s," ");
                        strcat(s,temp);
                        temp=strtok(NULL," ");
                    }
                    if(temp==NULL){
                        pthread_create(&p,NULL,(void*)(*system),(void*)(s));
                        pthread_join(p,NULL);
                    }
                    else{
                        printf("Invalid command\n");
                    }
                }
        }
        else{
            printf("Invalid command\n");
        }
    }    
}
