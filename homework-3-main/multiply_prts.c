#include <stdio.h>
#include <stdlib.h>

void multiply_prts(int* x, int* y, int *z){
    *z = *x * *y;
    printf("The product is: %d\n", *z);
}

int main(){
    int z;
    char buffer[256];
    printf("Enter a number: ");
    fgets(buffer, 256, stdin);
    int x = atoi (buffer);

    printf("Enter another number: ");
    fgets(buffer, 256, stdin);
    int y = atoi (buffer);

    multiply_prts(&x,&y,&z);
}