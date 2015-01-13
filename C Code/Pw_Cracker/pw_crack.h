/*###########################3
Name: Christopher Dubeau
Student #: 1793075
username: Dubeauc3
##############################*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pthread.h>
#include <string.h>
#include "memwatch.h"
#include "bcrypt/bcrypt.h"

void * threadrun();
int compMD5Hash(char goodHash[], char posHash[]);
int getinput(FILE * fp, char ** filein);

