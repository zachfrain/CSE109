#include <stdio.h>
#include <stdlib.h>

int strlen(char* str){
    int len = 0;
    while(*str != '\0'){
        str++; len++;
    }
    return len;
}

int main(){
    char input[256];
    printf("Enter a word or sentence: ");
    gets (input);
    printf("The size of the string entered is %d\n",strlen(input));
    return 0;
}