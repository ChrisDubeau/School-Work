/* This program take in a file of assembley code and outputs the command as a hex number
one bit at a time that is intertreted by a seperate file and then executed in the second file*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ass2.h"

/* get input recives two arrays that are used to store store the standard input that is cat'ed 
get input then goes through and reduces all gaps between words to one space to prevent un wanted input
from strtok() */
int getinput(char sinput[][200], char binput[][200]){
	char temp; // used to hold a single character temperarily
	int current=0,y,x,count=0; // current point to the point in sinput that temp will be put into, count is the number of lines read in, y is a switch that is 0 if spaces are not being deleted
	while((fgets(sinput[count],200,stdin)) != NULL){ // adds the stdin into sinput untill the end of file is reached
		current = 0;  // resets the current after each run
		for(x = 0; x < (strlen(sinput[count])); x++){ // fun through the current string from 0-length
			temp = sinput[count][x]; // loads the xth bit
			if (temp == ' '){ // if its a space
				if (y == 0){ // checks if the program is ignoring spaces now
					y = 1; // sets y to ignore consecutive spaces
					sinput[count][current] = temp; // sets the one space into sinput
					current += 1; 
				}
			}
			else if (temp != ' ') { // if it was not a space
				if (temp == '\n'){ // if the temp value was a next line character
					sinput[count][current] = ' '; // sets a space in its spot for strtok to work
					current += 1; 
					sinput[count][current] = '\n'; // sets the next character to \n
					x = (strlen(sinput[count])); // sets x to end the for loop
				}
				else{ // if it was not a \n
					sinput[count][current] = temp; // put in the character
					current += 1;
					y = 0; // sets y to not ignore the next space
				}
			}
		}
		count += 1; // moves to the next line

	}
	count -= 1; // needed to stop a segmentation fault does not effect the output
	sinput[count][current] = ' '; // this and the next line add a space into the last line and then \0 to end the file in sinput needed encase the last line does not end in a space
	sinput[count][current+1] = '\0';
	binput[count][current] = ' '; // this and the next line add a space into the last line and then \0 to end the file in binput needed encase the last line does not end in a space
	binput[count][current+1] = '\0';
	return count; // returns the count
}
	
	
	
/* find labels works its way through sinput and finds all of the labels that are in the input and then adds them into inst_reg and put their address into labels for future use*/
int findlabels(char sinput[][200],char inst_reg[][10],int num_of_bytes[], int end, int labels[], int count){
	int bytecount = 0, x, y,i; // bytecount keeps track of the address of each line
	char *tok1; // used to hold the result of strtok()
	for(i = 0; i <= count; i++){ // for the number of inputed lines it will loop
		tok1 = strtok(sinput[i]," "); // pulls the first word uptill the first space after
		for(x = 0; x < end; x++){ // runs through the length of inst_reg comparing the value there with tok1
			if((strcmp(inst_reg[x],tok1)) == 0){ // if tok1 equals the value at inst_reg[x]
				bytecount += num_of_bytes[x]; // increases the bytecount by the corresponding length in num_of_bytes
				x = end; // end the x for loop
			}
			else if(x == (end-1)){ // if the loop reaches the final value in the array and it does not match the parced value
				strcpy(inst_reg[end],tok1); // copys the parsed word in to inst_reg
				labels[end] = bytecount; // sets the corresponding spot in labels to the current address
				num_of_bytes[end] = 0; // sets num of bytes to 0 to prevent a segmentation fault
				tok1 = strtok(NULL," "); // tokenises the opcode that came after the label
				for(y = 0; y < end; y++){ // a second loop to go through the opcodes again
					if(tok1 != NULL && (strcmp(inst_reg[y],tok1)) == 0){ // if tok1 is not a null and tok1 matches an opcode
						bytecount += num_of_bytes[y]; // adds the num_of_bytes value to the bytecount increases the address incase there are more labels
					}
				}
				end += 1; // adds 1 to the length of the opcode array for use in loops
				x = end; // end the x loop
			}
		}
	}
	return end; // returns the new length of inst_reg
}
	
/* makeout() take in the binput that has an original copy of the input then goes through and tokenises line by line and outputs the
related values of the tokens (ex load = 0x80) and then outputs the values byte by byte for each line using putchar() ex (81 then 01)
makeout uses all the values that were found in getlabels and the predetermined values of opcodes. */
void makeout(char binput[][200],int end, char inst_reg[][10], int num_of_bytes[], int labels[],int num_of_args[],int count){
	int i,x,finish,temp,y; // i,x and y are counters, temp is used to hold a register in 2 byte 2 register commands, finish is used to hold the output
	char *tok1; 
	for(i = 0; i <= (count); i++){ // loops from the start of the input till the end (THE I LOOP)
		tok1 = strtok(binput[i]," "); // pulls the first word out of the line
		for(x = 0; x < end; x++){ // loops through the entire inst_reg array(THE X LOOP)
			if((strcmp(inst_reg[x],tok1)) == 0){ // if the current inst_reg[x] value matches the tokenized word
				if(num_of_bytes[x] == 0){ // runs in the event that the input is a label
					tok1 = strtok(NULL," "); // pulls the next word after the label(which should be the opcode)
					x = -1; // sets it so that when x is incremented it starts back at 0
				}
				// The bellow else if handles all outputs that are 2bytes in length(no label uses)
				else if(num_of_bytes[x] == 2){
					if(x == 23){ // if the opcode equals to DATA
						tok1 = strtok(NULL," "); // pulls the next word from the string
						for(y = 18; y < end; y++){ // compares it to all the values after the opcodes(registers and labels)(THE Y LOOP)
							if(strcmp(inst_reg[y],tok1)==0){ // if the token is a label or register in inst_reg
								finish = labels[y]; // pulls the address from labels
								finish &= 255; //  the address is ored with 255 to leave only the first 8bits as they were
								putchar(finish); // outputs the first byte of the data
								finish = labels[y]; // reloads the value from labels
								finish >>= 8; // shifts it 8bits right leaving the second byte or 0's if it was under 255
								putchar(finish); // outputs the data's second byte
								y = end; // end the y loop
							}
							else if(y == (end-1)){ // if the token was not a label but a number value
								finish = atoi(tok1); // converts the token into a number
								finish &= 255; // gets the first byte of the number
								putchar(finish);
								finish = atoi(tok1); // reloads the token number
								finish >>= 8; // sets finish to the second byte of the number
								putchar(finish);
							}
						}
					}
					else if(x == 0){ // else if the opcode was halt
						finish = labels[x]; //outputs halts 0x61 value
						putchar(finish);
						putchar(0); // the second byte will always be 00
					}
					else if(num_of_args[x] == 1){ //this else if statment runs if the opcode only uses one argument
						finish = labels[x]; // gets the value of the opcode
						putchar(finish); // outputs the opcode byte
						tok1 = strtok(NULL," "); // loads the one argument string
						for(y = 18; y < 23; y++){ // checks if the argument is in inst_reg
							if(strcmp(inst_reg[y],tok1)==0){ // if a match in inst_reg is found
								finish = labels[y]; // loads the byte value of the argument and outputs it
								putchar(finish);
							}
						}
					}
					else if(num_of_args[x] == 2){ // this else if statment runs if the opcode uses 2 arguments(R1,A1)
						finish = labels[x]; // loads the opcodes value
						putchar(finish); // outputs the opcode byte
						tok1 = strtok(NULL,","); // loads the first argument up till a comma
						for(y = 16; y < 24; y++){ // goes through all the register values in inst_reg
							if(strcmp(inst_reg[y],tok1)==0){ // when a match is found 
								finish = labels[y]; // puts the value of the register into finish
							}
						}
						tok1 = strtok(NULL," "); // loads the second argument after the comma
						for(y = 16; y < 24; y++){ // goes through all the registers again
							if(strcmp(inst_reg[y],tok1)==0){ // when a match is found
								temp = labels[y]; // loads the second registers value into temp
								temp <<= 6; // shifts temp 6bits left
								finish |= temp; // ors finish with temp
								putchar(finish); // outputs the result
							}
						}
					}
				x = end; // ends the x loop
				}
				// This else if section runs if the opcode had a 4byte configuration
				else if(num_of_bytes[x] == 4){
					if(num_of_args[x] == 0){ // if the argument is a number then this if statment runs
						finish = labels[x]; // finds the opcodes value in labels
						putchar(finish); // outputs the opcode byte
						putchar(0); // outputs a byte of 0 as there are no registers
						tok1 = strtok(NULL," "); // tokenizes the next string section( the number value)
						finish = atoi(tok1); // converts the string into an int
						finish &= 255; // sets finish to the first byte only
						putchar(finish); // outputs the first data byte
						finish = atoi(tok1); // reloads the number value
						finish >>= 8; // sets finish to the second byte only
						putchar(finish); // outputs the second byte
					}
					else if(num_of_args[x] == 1){ // this if statment runs if the opcode has one argument(non number)
						finish = labels[x]; // loads the opcode value
						putchar(finish); // outputs the opcode byte
						putchar(0); // outputs a 0byte as the second byte will always be 0
						tok1 = strtok(NULL," "); // loads the arguments string value
						for(y = 20; y < end; y++){ // compares it with all of the labels that were found
							if(strcmp(inst_reg[y],tok1)==0){ // when a match is found
								finish = labels[y]; // loads the labels address
								finish &= 255; // loads the first byte into finish
								putchar(finish); // outputs the first data byte
								finish = labels[y]; // reloads the address value
								putchar(finish>>8); // outputs the addresses second byte
							}
						}
					}
					else if(num_of_args[x] == 2){ // this if statment runs if the opcode has 2 arguments( one being a label/number)
						finish = labels[x]; // loads the opcode value
						putchar(finish); // ouputs the opcode byte
						tok1 = strtok(NULL,","); // loads the first argument(a register)
						for(y = 16; y < 24; y++){ // loops through the register string in inst_reg
							if(strcmp(inst_reg[y],tok1)==0){ // if a match is found
								finish = labels[y]; // loads the registers value out of labels
								putchar(finish); // outputs the registers value as a byte
							}
						}
						tok1 = strtok(NULL," "); // loads the seond argument from the string
						for(y = 20; y < end; y++){ // loops through all the labels found in the program (NEW Y LOOP)
							if(strcmp(inst_reg[y],tok1)==0){ // if a match is found in the labels
								finish = labels[y]; // loads the labels address into finsih
								finish &= 255; // sets finsih to the first byte of the address
								putchar(finish); // outputs the first byte
								finish = labels[y]; // reloads the labels address
								finish >>= 8; // sets finish to the second byte of the address
								putchar(finish); // outputs the second byte
								y = end; // end the Y LOOP
							}
							else if(y == (end-1)){ // if the second argument is a number
								finish = atoi(tok1); // converts from a string into an int
								finish &= 255; // sets finish to the first byte of the integer
								putchar(finish); // outputs the first byte of the integer
								finish = atoi(tok1); // re loads the integer value
								finish >>= 8; // sets finish to the second byte of the integer
								putchar(finish); // outputs the second byte
							}
						}
					}
				x = end; // end the x loops so it does not cause a segmentation fault
				}
			}
		}
	}
	return; // returns to end the program
}
