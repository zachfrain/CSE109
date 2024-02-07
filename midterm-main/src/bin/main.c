#include "myls.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    int a_flag = 0; int l_flag = 0;
    if(argc == 1)
        ls(".", 0, 0);
    else if(argc == 2){
       if(argv[1][0] ==  '-'){
           if(argv[1][1] == 'a'){
               a_flag = 1;
           } else if(argv[1][1] == 'l') {
               l_flag = 1;
           } else if(argv[1][1] == '-'){
               if(argv[1][2] == 'v'){
                   version();
                   exit(0);
               } else if(argv[1][2] == 'h'){
                   usage();
                   exit(0);
               } else if(argv[1][2] == 'a'){
                   a_flag = 1;
               } else {
                   perror("Error: Unknown option"); [0]
                   exit(1);
               }
           } else {
               perror("Error: Unknown option"); [0]
               exit(1);
           }
           ls(".",a_flag,l_flag);
       } else {
           ls(argv[1], a_flag, l_flag);
       }
    } else if(argc == 3){
       if(argv[1][0] ==  '-'){
           if(argv[1][1] == 'a'){
               a_flag = 1;
           } else if(argv[1][1] == 'l') {
               l_flag = 1;
           } else if(argv[1][1] == '-'){
               if(argv[1][2] == 'v'){
                   version();
                   exit(0);
               } else if(argv[1][2] == 'h'){
                   usage();
                   exit(0);
               }
           } else {
               perror("Error: Unknown option"); [0]
               exit(1);
           }
           ls(argv[2],a_flag,l_flag);
       } else {
           perror("Error: Incorrect Usage"); [0]
           exit(1);
       }
    } else {
        perror("Error: Incorrect Usage."); [0]
        exit(1);
    }
    return 0;
}

[0]: https://www.tutorialspoint.com/c_standard_library/c_function_perror.htm
