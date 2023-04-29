#include "cmp.h"

int compare(char a, char b, int flag){
    if (a==b){
        return 1;
    }
    if (flag ==1){
        if (tolower(a)==tolower(b)){
            return 1;
    }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    FILE *fp1;
    FILE *fp2;
    char *filename1;
    char *filename2;
    char *flag1 = NULL;
    char *flag2 = NULL;
    char char1;
    char char2;
    
    filename1 = argv[1];
    filename2 = argv[2];
    if (argc>3){
        flag1 = argv[3];
    }
    if (argc>4){
        flag2 = argv[4];
    }

    fp1 = fopen(filename1,"rb");
    fp2 = fopen(filename2,"rb");

    if (fp1==NULL){
        fprintf(stdout,"file 1 did not opened successfully\n");
        return 1;
    }

    if (fp2==NULL){
        fprintf(stdout,"file 2 did not opened successfully\n");
        return 1;
    }

    fseek(fp1, 0, SEEK_END);
    long size1 = ftell(fp1);
    fseek(fp2, 0, SEEK_END);
    long size2 = ftell(fp2);
    rewind(fp1);
    rewind(fp2);

    if (size1>size2){
        if (!strcmp(flag1, "-v") || !strcmp(flag2,"-v")){
            fprintf(stdout,"distinct\n");
            fclose(fp1);
            fclose(fp2);
            return 1;
        }
        fclose(fp2);
        fclose(fp1);
        return 1;
    }
    
    while ((char1 = fgetc(fp1)) !=EOF && (char2 = fgetc(fp2))!=EOF){
        int result = 0;
        if ((flag1 != NULL && (!strcmp(flag1, "-i")))||(flag2!=NULL && !strcmp(flag2,"-i"))){
            result = compare(char1,char2,1);
        }
        else{
            result = compare(char1,char2,0);
        }
        if (result == 0){
            if ((flag1 != NULL && (!strcmp(flag1, "-v")))||(flag2!=NULL && !strcmp(flag2,"-v"))){
                fprintf(stdout,"distinct\n");
                fclose(fp2);
                fclose(fp1);
                return 1;
            }
            fclose(fp2);
            fclose(fp1);
            return 1;
        }
    }
    
if ((flag1 != NULL && (!strcmp(flag1, "-v")))||(flag2!=NULL && !strcmp(flag2,"-v"))){
    fprintf(stdout,"equal\n");
    fclose(fp2);
    fclose(fp1);
    return 0;
}

fclose(fp2);
fclose(fp1);
return 0;
}