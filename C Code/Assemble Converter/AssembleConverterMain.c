#include <stdio.h>
#include <string.h>
#include "AssembleConverter.h"
/* the main function assembles a source file using functions from AssembleConverter.c then outputs them using makeout()*/
int main(){
	int num_of_args[300] = {0,2,2,2,2,1,1,1,1,2,2,2,2,1,1,1,1,0,0};// This is a array that is in the same order as inst_reg that contains the number of arguments each opcode take
	int num_of_bytes[300] = {2,4,2,4,2,4,4,4,4,4,2,4,2,2,2,2,2,4,4,0,0,0,0,2};// an array that contains the number of bytes each opcode from labels has used to calculate addresses
	// bellow is an array of defined wordes that stores the value of each opcode/register and label addresses
	int labels[300] = {HALT,LOAD,LOADI,STORE,STOREI,JMP,JMPO,JMPZ,JMPN,ADD,ADDR,SUB,SUBR,OUTI,OUTR,OUTIC,OUTRC,OUT,OUTC,A1,R1,A2,R2,0};
	// bellow is a 2 dimensional array that contains the opcodes/registers represented as strings
	char inst_reg[300][10] = {{"HALT"},{"LOAD"},{"LOADI"},{"STORE"},{"STOREI"},{"JMP"},{"JMPO"},{"JMPZ"},{"JMPN"},{"ADD"},{"ADDR"},{"SUB"},{"SUBR"},{"OUTI"},{"OUTR"},{"OUTIC"},{"OUTRC"},{"OUT"},{"OUTC"},{"A1"},{"R1"},{"A2"},{"R2"},{"DATA"}};
	char sinput[5000][200], binput[5000][200]; // both arrays store the standard input then sinput is used to find all labels and corresponding addresses and binput is used to make the output
	int end = 24, count,x; // end is the length of inst_reg and keeps track of how many opcodes/labels/registers we have
	count = getinput(sinput,binput); // calls getinput to fill sinput and binput and get the returned count that has the number of lines
	end = findlabels(sinput,inst_reg,num_of_bytes,end,labels,count);
	makeout(binput,end,inst_reg,num_of_bytes,labels,num_of_args,count); // makeout() then is called and it compiles the output for the file
	return 0;
}