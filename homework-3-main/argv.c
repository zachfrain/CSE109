#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int i; int j; char* temp;
    printf("argv address: %p\n", &**argv);
    for(i = 0; i < argc; i++)
        printf("argv[%d] address: %p\n",i, &*(argv + i));
    i = 0;
    while(i < argc){
        j = 0;
        while(*(argv[i]+j) != '\0'){
            printf("argv[%d][%d] address: %p\n", i,j,&*(argv[i]+(j)));
            j++;
        }
        i++;
    }
    return 0;
}