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

int getTime(char input[]);
void getLine(char string[],char line[][50]);
int childfunction(char line[][50],char filename[],char countf[]);
void curTime(char temp[]);

/* Main is the main function of the dirsweeper executable*/
int main(int argc, char *argv[]){  
	FILE *fp,*pidfp,*counf; /* 3 file pointers*/
	DIR * dir;  /* the directory pointer*/
	char **filein; /* the outer pointer to be malloced for a multidimensional array */
	char temp[200],line[4][50],fileoutloc[500],pidfile[500],countf[500],numchar[10]; /* several arrays to store data for a short period*/
	pid_t pid[200]; /* an array that will hold pids of the parent and all children*/ 
	int runtime, timerun, count = 0, x,deleted = 0,cnum,cpids[200];
 	if(getenv("DIRSWEEPERLOGS") != NULL){ /* gets the path to the location for the logfiles*/
		strcpy(fileoutloc,getenv("DIRSWEEPERLOGS")); /* loads the path for log files*/
	}
	else{ 
		strcpy(fileoutloc,getenv("HOME")); /* else it loads the path to HOME*/
	}
	/*bellow is the pid checker*/
	strcpy(pidfile,getenv("HOME")); /* loads path to Home for the pidfile*/
	strcpy(countf,getenv("HOME")); /* loads the path to home for the countfile*/
	strcat(pidfile,"/ds_pid"); /* adds the file name to pidfile*/
	strcat(countf,"/cfile"); /* adds the file name to the countf*/
	pidfp = fopen(pidfile, "r"); /* opens the pidfile*/
	if (pidfp){ /* if it exists a dirsweeper is running*/
		while(fgets(temp,200,pidfp)){ /* loads the values in pidfile one at a time*/
			if((kill(atoi(temp),SIGKILL)) == -1){ /* tries to kill the program*/
				perror("could not kill a running program");
			}
		}
		remove(pidfile); /* removes the old pidfile*/
	}	
	pidfp = fopen(pidfile,"w"); /* creates a new pidfile*/
	fprintf(pidfp, "%d\n",(int)getpid()); /* prints teh parents pid first*/
	fflush(pidfp); /* prints the pid*/
	counf = fopen(countf,"w+"); /* creates the countfile*/
	fclose(counf); /* closes the count file*/
	fp = fopen(argv[1],"r"); /* opens the config file*/
	fgets(temp,200,fp); /* gets the run time from the first line*/
	runtime = getTime(temp); /* converts the run time to seconds*/
	filein = malloc(200 * sizeof(char*)); /* creates space for 200 spaces in filein*/
	
	/*gets all the file lines and allocates space for each then adds the line to file in*/
	while(fgets(temp,200,fp)){
		filein[count] = malloc(200 * sizeof(char));
		strcpy(filein[count],temp);
		count++;
	}
	
	/*loops and forks for the number of lines in the config not including the first*/
	for(x=0; x<count; x++){
		getLine(filein[x],line);
		pid[x] = fork();
		if(pid[x] != 0){ /* prints the pid to the pidfile*/
			fprintf(pidfp, "%d\n",(int)pid[x]);
			fflush(pidfp);
		}
		/* gets the number and pid of the file then breaks out of the loop to not repeat*/
		if(pid[x] == 0){
			cpids[x] = getpid();
			cnum = x;
			break;
		}
	}
	
	/* The Child function*/	
	if(pid[cnum] == 0){
		if ((dir = opendir(line[0])) == NULL) { /* opens the dir that was given to the child*/
			printf("dirsweeper: Warning: %s does not currently exist.\n",line[0]); /* output if dir does not exist*/
		}
		else{
			closedir(dir);
		}
		FILE *outfp;
		/* this block creats the path and names for the log files*/
		strcat(fileoutloc,"/dswplog."); 
		sprintf(numchar, "%d", (cnum+1));
		strcat(fileoutloc,numchar);
		outfp = fopen(fileoutloc,"w");
		/* end block*/
		/* this block puts the first line into the log file*/
		curTime(temp);
		fprintf(outfp, "[ %s]  Info: Initializing monitoring of directory %s\n",temp,line[0]);
		fflush(outfp);
		/* end block*/
		timerun = getTime(line[1]); /* gets the time between scans of the directory*/
		fclose(outfp); /* closes the file pointer*/
		while(runtime > 0){ /* while not at max runtime*/
			childfunction(line,fileoutloc,countf); /* runs the dir sweeping function*/
			if (timerun > runtime){ /* if the there is not enough time to repeat the check*/
				runtime = 0; /* set to end and wait for the end*/
				sleep(runtime);
			}
			/* if the check was only to be run once*/
			else if(timerun == 0){
				runtime = 0;
				sleep(runtime);
			}
			else{ /* else subtract the sleep time and sleep*/
				runtime -= timerun;
				sleep(timerun);
			}
		}
		for(x = 0; x < count; x++){ /* goes through the inherited malloced space and frees*/
			free(filein[x]);
		}
		free(filein);
		/* above needed to stop memwatch errors*/
		exit(1); /* end*/
	}
	
	
	
	else{ /* parent process*/
		while(wait(NULL)>0 && errno != ECHILD){ /* wait till all children finish*/
		}
		counf = fopen(countf,"r"); /* open teh count file*/
		x = 0; /* reset x to hold charvalues*/
		while ( (x=fgetc(counf)) != EOF ) { /* till end of file count all \n characters*/
			if ( x == '\n' ){
				deleted++; /* adds a file to the deleted counter*/
			}
		}
    }
	fclose(counf); /* closes teh file counter*/
	printf("%d deleted\n",deleted); /* prints the deleted statment*/
	fclose(fp); /* closes file pointer*/
	/*Memory freeing loop.*/
	for(x = 0; x < count; x++){ /* frees all the malloced space*/
		free(filein[x]);
	}
	free(filein);
	remove(countf); /* removes the counterfile*/
	remove(pidfile); /* removes the pid file*/
	return 0; /* END*/
}