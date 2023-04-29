#include <stdio.h>
#include <unistd.h>
#include "string.h"

int main(int argc, char *argv[]) {
    FILE *fp1;
    FILE *fp2;
    char *filename1;
    char *filename2;
    char *flag1 = NULL;
    char *flag2 = NULL;
    char buffer[1024];
    size_t n;

    filename1 = argv[1];
    filename2 = argv[2];
    if (argc>3){
        flag1 = argv[3];
    }
    if (argc>4){
        flag2 =argv[4];
    }

    fp1 = fopen(filename1,"rb");
    if (access(filename2, F_OK) == 0){
        if ((flag1!=NULL && !strcmp(flag1, "-f"))||(flag2!=NULL && !strcmp(flag2, "-f"))){
            fp2 = fopen(filename2,"wb");
            if (fp2==NULL){
                if ((flag1!=NULL && !strcmp(flag1, "-v"))||(flag2!=NULL && !strcmp(flag2, "-v")))
                    printf("general failure\n");
                fclose(fp1);
                return 1;}
        }
        else{
            if ((flag1!=NULL && !strcmp(flag1, "-v"))||(flag2!=NULL && !strcmp(flag2, "-v"))){
                printf("target file exist\n");
        }
        fclose(fp1);
        return 1;}
    }
    else {
    fp2 = fopen(filename2,"wb");
    }

    while ((n = fread(buffer, 1, sizeof(buffer), fp1)) > 0) {
        fwrite(buffer, 1, n, fp2);
    }
    
if ((flag1!=NULL && !strcmp(flag1, "-v"))||(flag2!=NULL && !strcmp(flag2, "-v")))
    printf("success\n");

fclose(fp1);
fclose(fp2);
return 0;

}