/*###########################3
Name: Christopher Dubeau
Student #: 1793075
username: Dubeauc3
##############################*/
#include "pw_crack.h"
#include "memwatch.h"
#include "bcrypt/bcrypt.h"


int hashCount = 0,currentH = 0,pasCount = 0;
char **hashes, **passes; /* a 2 dimension array of chars */
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; /* mutex used to lock */
pthread_cond_t c = PTHREAD_COND_INITIALIZER;/*signel to say the thread is done*/

/* This is the main function and acts as a hub for all data to output to the 
correct locations*/
int main(int argc, char *argv[]){
	/* this next block initializes all states needed of start */
	FILE *fp, *fp2; /* makes 2 file pointers for input */
	int threads, x;
	hashes = malloc(20000 * sizeof(char*)); /* mallocs 20000 char pointer array */
	passes = malloc(20000 * sizeof(char*)); /* mallocs 20000 char pointer array */
	fp = fopen(argv[1],"r"); /* opens the password file*/
	fp2 = fopen(argv[2],"r"); /*opens the hash file*/
	hashCount = getinput(fp2,hashes);/*puts the line from hash into the array*/
	threads = hashCount / 10; /* used to prevent errors that were found */
	threads += 1; /* makes threads one is input was less than 10 lines */
	if (threads > 20){
		threads = 20;
	}
	pasCount = getinput(fp,passes);/*puts the line from the password in array*/
	fclose(fp);
	fclose(fp2);
	char pass[pasCount][100]; /* a password holder */
	/* This block copies the found passwords to the array to pass to the threads*/
	for (x = 0; x < pasCount; x++){
		strcpy(pass[x],passes[x]);
	}
	
	pthread_t thread[threads];/*initializes the pthread with the new found value*/
	
	/* creates the threads*/
	for (x = 0; x < threads;x++){
		pthread_create(&thread[x], NULL,threadrun,pass);
	}
	pthread_mutex_lock(&m); /* locks m */
	/* while there are still lines keep waiting*/
	while(currentH < hashCount){
		pthread_cond_wait(&c, &m); /* gets a signel from the threads */
	}
	pthread_mutex_unlock(&m); /* unlocks m */
	/* outputs all of the hashes in order with found passwords*/
	for (x = 0; x < hashCount;x++){
		printf("%s\n",hashes[x]);
	}
	/* below frees all the memory and returns*/
	for(x = 0; x < hashCount; x++){
		free(hashes[x]);
	}for(x = 0; x < pasCount; x++){
		free(passes[x]);
	}
	free(hashes);
	free(passes);
	return 0;
}
	
/* Threadrun is the function that the threads execute which finds compares and
outputs relevent data as needed */
void * threadrun(char pass[][100]){
	int location;
	/* a loop that keep going till all lines from the file have been procesed*/
	while(currentH < hashCount){
		/* temps hold input hash salt and md5hash hold releent data to hashing*/
		char temp[64],temp2[64],type[4],salt[64],md5hash[35],password[200], *tok;
		int x=0,i=0;
		pthread_mutex_lock(&m); /* locks */
		/* incase there are no remaining lines an out */
		if (currentH >= hashCount){
			pthread_mutex_unlock(&m);
			break;
		}
		location = currentH;
		/* following gets the line from memory and adds : to line and unlocks */
		strcpy(temp,hashes[currentH]);
		strcpy(temp2,hashes[currentH]);
		strcat(hashes[location],": ");
		currentH += 1;
		pthread_mutex_unlock(&m);
		
		/* the following gets weather the hash is md5 or blowfish */
		tok = strtok(temp,"$");
		strcpy(type,tok);
		/* if the line was an MD5 hash*/
		if (strcmp(type,"1") == 0){
			tok = strtok(NULL,"$"); /* gets the salt from the line*/
			strcpy(salt,tok);
			for (i = 0; i < pasCount; i++){ /*goes through all paswords given*/
				strcpy(password,pass[i]); /*copies password into a local temp*/
				/* following lines make the hash using open ssl
				needed to be included in main as it would cause random segfault
				when in its own function with no solution found in gdb*/
				char string[100] = "openssl passwd -1 -salt ";
				strcat(string,salt);
				strcat(string," ");
				strcat(string,password);
				pthread_mutex_lock(&m);
				FILE *fp;
				fp = popen(string,"r");
				fgets(md5hash,35,fp);
				fclose(fp);
				pthread_mutex_unlock(&m);
				/* end get Md5 hash*/
				if(compMD5Hash(temp2,md5hash) != 1){/*if hash matches given*/
				/* adds password to the end of the given hash for output*/
					x = pasCount;
					pthread_mutex_lock(&m); /* locks */
					strcat(hashes[location],password);
					pthread_mutex_unlock(&m);
				}
			}
		}
		else{ /* else if it was a blowfish hash*/
			for (i = 0; i < pasCount; i++){ /* goes through all given words*/
				char outhash[BCRYPT_HASHSIZE]; /* holds found hash*/
				strcpy(password,pass[i]); /* makes temp password*/
				for (x = 0; x < 30; x++){ /* get the salt from the line*/
					salt[x] = temp2[x];
				}
				bcrypt_hashpw(password,salt,outhash); /* gets hash*/
				if (strcmp(temp2, outhash) == 0) { /* if hashes matched*/
				/*  add the found password onto the line for output*/
					x = pasCount;
					pthread_mutex_lock(&m); /* locks */
					strcat(hashes[location],password);
					pthread_mutex_unlock(&m); /* unlocks*/
				}
			}
		}
	}
	if (location+1 == hashCount){
		pthread_cond_signal(&c); /* signals end*/
	}
	return NULL;
}

/* compMd5Hash test if the hashes match and if not returns 1 */
int compMD5Hash(char goodHash[], char posHash[]){
	int x, returned = 0;
	for (x = 0; x < 35; x++){
		if (goodHash[x] != posHash[x]){
			returned = 1;
		}
	}
	return returned;
}

	
/* getinput takes in the file and adds to memory each line 
reallocating space as needed*/
int getinput(FILE * fp, char ** filein){
	int count = 0, size = 20000;
	char temp[100],*tok;
	while(fgets(temp,100,fp)){
		filein[count] = malloc(100 * sizeof(char));
		tok = strtok(temp,"\n\0");
		strcpy(temp,tok);
		strcpy(filein[count],temp);
		count++;
		if (count >= size){
			filein = realloc(filein, size*2);
			size = size*2;
		}
	}
	return count;
}
	