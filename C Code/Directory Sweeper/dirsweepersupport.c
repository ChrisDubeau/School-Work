/*###########################3
Name: Christopher Dubeau
Student #: 1793075
username: Dubeauc3
##############################*/
#define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include "memwatch.h"

/* Declaration of all functions used to stop errors when compiling*/
int getTime(char input[]);
void getLine(char string[],char line[][50]);
int childfunction(char line[][50],char filename[],char countf[]);
void curTime(char temp[]);
void printout(char filename[], char time[], char name[]);

/* getTime Takes in a string in the form hh:mm:ss and returns the
total number of seconds the string represents*/
int getTime(char input[]){
	int runtime = 0; 	/*the integer that will hold the return value*/
	char *tok; 	/*A char pointer used to hold tokenized parts of the passed sting*/
	tok = strtok(input,":");	/*tokenizes the number of hours*/
	runtime += ((atoi(tok))*3600);	/*finds the value of the hours in seconds*/
	tok = strtok(NULL,":");	/*gets the number of minutes*/
	runtime += ((atoi(tok))*60);	/*finds the value of the miniutes in seconds*/
	tok = strtok(NULL," \n\0");	/*gets the number of seconds*/
	runtime += (atoi(tok));	/*adds the number of seconds*/
	return runtime;
}

/* getLine takes in a line from the config document
and splits it into the 4 main parts of the line, dir path,
sleeptime,function type, and size or time*/
void getLine(char string[],char line[][50]){
	char *tok;
	tok = strtok(string," ");	/*gets the dir pathway*/
	strcpy(line[0],tok);	/*puts the pathwau into line*/
	tok = strtok(NULL," ");	/*gets the time interval between checks*/
	strcpy(line[1],tok);	/*puts the string into line*/
	tok = strtok(NULL," ");	/*gets what type of clean will be done*/
	strcpy(line[2],tok);	/*puts the string into line*/
	tok = strtok(NULL," \n\0");	/*gets the size or time to compare with*/
	strcpy(line[3],tok);	/*puts the string into line*/
}

/* Childfunction is the main function that is called by each child process to check 
and remove from a directory*/
int childfunction(char line[][50],char filename[],char countf[]){
	time_t initial = time(NULL); /*gets the current time*/
	int keyword = -1,maxtime,maxsize,cursize = -1,x;
	char dirpath[200],dirpathholder[200],temp[200],out[200],temp2[200],size;
	strcpy(dirpath,line[0]); /* gets the directory name into dirpath*/
	strcat(dirpath,"/"); /* preps the dir for the file name */
	strcpy(dirpathholder,dirpath); /* makes a back up of dirpath */
	DIR * dir; 
	struct dirent *test;
	struct stat dirinfo;
	
	if(strcmp(line[2],"lessthan") == 0){ /* checks if the program is to make a dir less than size */
		keyword = 1; /* if lessthan sets keyword to 1 */
		for(x = 0; x < strlen(line[3]); x++){ /* loops through the size of the size value */
			maxtime = 0; /* sets maxtime to 0 to prevent possible error */
			if(x+1 == strlen(line[3])){ /* if the current value is the end of the array */
				size = line[3][x]; /* puts the M or K into size */
			}
			else{
				temp[x] = line[3][x]; /* puts all the num into temp so we can compule size */
			}
		}
		if(size == 'M'){ /* if the dir is to be less than xM */
			maxsize = (atoi(temp) * (1024*1024)); /* multiplies the given number by the size of one megabyte */
		}
		else if(size == 'K'){ /* if the dir is to be less than xK */
			maxsize = (atoi(temp) * 1024); /* multiplies the given number by the size of one kilobyte */
		}
	}
	else{ /* if the program is to do mostrecent */
		keyword = 0; /* keyword is set to 0 to signal mostrecent */
		maxtime = getTime(line[3]); /* gets the number of second the file is alowed to be younger than */
	}
	if ((dir = opendir (line[0])) != NULL) { /* tries to open the directory given if no dir ends function */
		if(keyword == 0){ /* if doing most recent */
	/* print all the files and directories within directory */
			while ((test = readdir(dir)) != NULL) { /* reads through all file in the given directory */
				strcat(dirpath,test->d_name); /* add the file name to dirpath */
				stat(dirpath,&dirinfo); /* gets the stats on the current file */
				/* bellow  if finds if the file is older than allowed and that it is not "." or ".."*/
				if(((int)initial - (int)dirinfo.st_ctime) > maxtime && (strcmp(test->d_name,".") != 0) && (strcmp(test->d_name,"..") != 0)){
					curTime(temp2); /* gets the current time of day */
					strcpy(out,test->d_name);
					printout(filename,temp2,out); /* outputs the delete to a log file */
					printout(countf,temp2,out);	
					remove(dirpath); /* removes the file from the directory */
				}
				strcpy(dirpath,dirpathholder); /* resets the dirpath */
			}
		}
		else if(keyword == 1){ /* if the process is to do lessthan */
			while(cursize == -1){ /* loops till a file is not deleted */
				while ((test = readdir(dir)) != NULL) { /* reads all files in the directory */
					strcat(dirpath,test->d_name); /* adds the file name to dirpath */
					stat(dirpath,&dirinfo); /* gets the stats on the current file */
					/* checks if the current file is older than the oldes found so far and that it is not "." or ".." */
					if((((int)initial - (int)dirinfo.st_ctime) > maxtime) && (strcmp(test->d_name,".") != 0) && (strcmp(test->d_name,"..") != 0)){
						maxtime = ((int)initial - (int)dirinfo.st_ctime); /* sets the maxtime to the age of the file */
						x = 1; 
						strcpy(temp,dirpath); /* copies the file path to a temp holder */
						strcpy(out,test->d_name); /* copies the name to out which is used for fprintf */
						
					}
					/* if the file is not "." or ".." adds the size to cursize */
					if((strcmp(test->d_name,".") != 0) && (strcmp(test->d_name,"..") != 0)){
						cursize += (int)dirinfo.st_size;
					}
					strcpy(dirpath,dirpathholder); /* resets dirpath */
				}
				if(cursize > maxsize && x == 1){ /* if the dir is to large and a file was found */
					curTime(temp2); /* gets current time for a delete function */
					remove(temp); /* removes the oldest file */
					rewinddir(dir); /* resets the dir to the start */
					printout(filename,temp2,out); /* prints the deletion to the logfile*/
					printout(countf,temp2,out);
					maxtime = 0; /* resets maxtime to 0 */
					cursize = -1; /* sets cursize to -1 */
					x = 0;
				}
				else{
					cursize = 0;
				}
			}
		}
	closedir(dir);
	}
	return 0;
}

/* The bellow function takes in a file name and values to be printed to the file
it then opens writes to the file then  */
void printout(char filename[], char time[], char name[]){
	FILE *outfp;
	outfp = fopen(filename,"a");
	fprintf(outfp, "[ %s]  Action: File \" %s \" removed\n",time,name);
	fclose(outfp);
}

/* curtime takes in an array of the time then sets it to the output mode for log files*/
void curTime(char temp[]){
	int x;
	time_t start = time(NULL);
	strcpy(temp,ctime(&start));
	for(x = 0; x <= strlen(temp); x++){
		if(temp[x] == '\n'){
			temp[x] = ' ';
		}
	}
}