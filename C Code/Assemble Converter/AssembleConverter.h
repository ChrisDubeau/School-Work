/* opcodes for 80d201 processor */ 
#define HALT 0x61 
#define LOAD 0x80 
#define LOADI 0x81 
#define STORE 0x82 
#define STOREI 0x83 
#define JMP 0x84 
#define JMPO 0x85 
#define JMPZ 0x86 
#define JMPN 0x87 
#define ADD 0x88 
#define ADDR 0x89 
#define SUB 0x8a 
#define SUBR 0x8b 
#define OUTI 0x8c 
#define OUTR 0x8d 
#define OUTIC 0x8e 
#define OUTRC 0x8f 
#define OUT 0x90 
#define OUTC 0x91 
/* Registers for 80d201 processor */ 
#define A1 0 
#define R1 1 
#define A2 2 
#define R2 3 
// bellow is the declarations of the 3 functions in Ass2.c
int getinput(char sinput[][200], char binput[][200]);
int findlabels(char sinput[][200],char inst_reg[][10],int num_of_bytes[], int end, int labels[], int count);
void makeout(char binput[][200],int end, char inst_reg[][10], int num_of_bytes[], int labels[],int num_of_args[],int count);
