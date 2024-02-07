#include "myls.h"
#include <stdio.h>
#include <dirent.h> [1]
#include <stdlib.h>

void ls(char* path, int a_flag, int l_flag){
    DIR * dp = opendir(path);[1]
    struct dirent * ep;[1]
    if(!dp){
        perror("Error: This directory cannot be read");[2]
        exit(1);
    }
    if(a_flag == 1){
        while((ep = readdir(dp)) != NULL){ [0]
            printf("\n%s", ep->d_name);
        }
    } else if(l_flag == 1){
        while((ep = readdir(dp)) != NULL){ [0]
            if(ep->d_name[0] != '.'){
                printf("\n%s", ep->d_name);
            }   
        }
    } else {
        while((ep = readdir(dp)) != NULL){ [0]
            if(ep->d_name[0] != '.')
                printf("\n%s", ep->d_name);
        }
    }
    printf("\n");
}

void usage(){
    printf("ls is used to list the contents of a directory. \n");
    printf("The correct usage for the ls command is '[OPTION] [PATH]'\n");
    printf("The options for the ls are as follows:\n");
    printf("'-a'/'--all'\t\tDoes not ignore entries starting with '.'.\n");
    printf("'-l'\t\tUses a long listing format.\n");
    printf("'--help'\t\tDisplays this message.\n");
    printf("'--version'\t\tDisplays version information and exit.\n");
}

void version(){
    printf("Zachary Frain v.0.0.1\n");
}

[0]: https://www.man7.org/linux/man-pages/man0/dirent.h.0p.html
[1]: https://www.ibm.com/docs/en/i/7.1?topic=ssw_ibm_i_71/apis/readdir.htm
[2]: https://www.tutorialspoint.com/c_standard_library/c_function_perror.htm
