#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

//#define NULL 0
#define PROC_DEV_PATH	"/proc/dev"


int main(int argc, char ** argv)
{

    DIR *pDir;
    struct dirent    *pEnt;

    struct stat fstat;

    
    pDir = opendir (PROC_DEV_PATH);
    
    if(!pDir) {
       fprintf(stdout, "Error to read proc/dev path\n");
    }

    while (pDir) {
       if ( (pEnt = readdir (pDir)) != NULL) {
           fprintf(stdout, "System dev: %s\n", pEnt->d_name); 
       }
    }



    return 0;

}

