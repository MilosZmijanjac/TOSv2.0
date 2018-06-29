#include "monitor.h"
#include "string.h"
#include "kb.h"
#include "command.h"
#include "shell.h"
#include "timer.h"
#include "rtc.h"
#include "kheap.h"
#include "draw.h"

#define KERN_VER "0.1.5"
#define SHELL_VER "0.6"
#define MaxCommands 20

int numCommands = -1;   /* Number of Registered Commands, we start at -1 so the first one registered is 0. */
char *cmdString;
char *cmdSwitch0;
char *cmdSwitch1;
char *cmdSwitch2;
char *cmdSwitch3;
char *cmdSwitch4;
char *cmdSwitch5;
char *cmdSwitch6;
commandEntry CommandTable[MaxCommands];
extern char prompt [32];

char *niz[10];
int freeNiz[10];
int size[10];
int power=1;
int  runShell()
{
	int i;
	char inputString[512];
	putc('\n');
	puts(prompt);
	gets(inputString);
	cmdString = strtok(inputString, " ");
	cmdSwitch0 = strtok(NULL, " ");
	cmdSwitch1 = strtok(NULL, " ");
	cmdSwitch2 = strtok(NULL, " ");
	cmdSwitch3 = strtok(NULL, " ");
	cmdSwitch4 = strtok(NULL, " ");
	cmdSwitch5 = strtok(NULL, " ");
	cmdSwitch6 = strtok(NULL, " ");
	void (*commandJump)(void);
	i = findCMD(cmdString);
	if(i >= 0)
	{
		commandJump = CommandTable[i].address;
		commandJump();
	}

	return power;
}

int findCMD(char *cmd)
{
	int i;
	int c;
	for(i=0; i < numCommands + 1; i++)
	{
		c = strcmp(CommandTable[i].command, cmd);
		if (c == 0)
		{
			return i;
		}
	}
	return -1;
}

void initShell()
{
	clearCommands();
	puts("Username: ");
	gets(prompt);
  
	strcat(prompt, "$ "); 
	cls();
	cmdString[0] = 0;
	cmdSwitch0[0] = 0;
	cmdSwitch1[0] = 0;
	cmdSwitch2[0] = 0;
	cmdSwitch3[0] = 0;
	cmdSwitch4[0] = 0;
	cmdSwitch5[0] = 0;
	cmdSwitch6[0] = 0;
	addCommand("help", "Lists all available commands.", help);
	addCommand("ahelp", "Lists all available commands with descriptions", ahelp);
	addCommand("print", "Outputs your chosen text", outputMe);
	addCommand("version", "Displays version information for TOS kernel and shell", version);
	addCommand("time", "Displays time and date", timeMe);
	addCommand("example", "Quick string to int conversion demo", example);
	addCommand("add", "Adds two numbers together", addMe);
	addCommand("sub", "Subtracts one number from another", subtractMe);
	addCommand("exp", "Multiplies a number against itself an exponential amount of times", exponentMe);
	addCommand("plot", "Graphs a function", plotMe);
	addCommand("allocate", "Allocate variable", allocateMe);
	addCommand("free", "Deallocate variable", freeMe);
	addCommand("aprint", "Deallocate variable", printAllocateMe);


	addCommand("allocateEx", "Allocate example", allocateExMe);
	addCommand("eval", "Evaluate an expression (only integers, no braces)", evalMe);


	addCommand("reset", "Reset shell", initShell);

		addCommand("exit", "Exit shell", exitMe);
	puts("\nTOS Shell ");
	puts(SHELL_VER);
	putc('\n');
}
void exitMe()
{
cls();

puts("It's now safe to turn off your device!!!");
power=0;

}
void clearCommands() /* Clear all address pointers of our Commands. */
{
	int i;
	for(i=0;i<MaxCommands;i++)
	{
		CommandTable[i].address = NULL;
		numCommands = -1;
	}
}


int addCommand(char *command, char *description, void *address)
{

	if(numCommands < MaxCommands)
	{
		numCommands++;
		strcpy(CommandTable[numCommands].command, command);
		strcpy(CommandTable[numCommands].description, description);
		CommandTable[numCommands].address = address;
		return numCommands;
	}
	return -1;
}

/*  Commands - This is where all commands for the shell are stored */

void help()
{
	int i;
	puts("\nCommand List: ");
	for(i=0;i<=numCommands;i++)
	{
		if(CommandTable[i].address != NULL)
		{
			puts(CommandTable[i].command);
			putc(',');
			putc(' ');
		}
	}
	putc('\n');
}

void ahelp()
{
	int i;
	for(i=0; i <= numCommands; i++)
	{
		puts(CommandTable[i].command);
		puts(" - ");
		puts(CommandTable[i].description);
		putc('\n');
	}
	return;
}

void version()
{
	puts("\nKernel Version:\t");
	puts(KERN_VER);
	puts("\nShell Version:\t");
	puts(SHELL_VER);
}


void outputMe()
{
	puts("\nYou typed:");
	putc('\n');
	puts(cmdSwitch0);
	putc(' ');
	puts(cmdSwitch1);
	putc(' ');
	puts(cmdSwitch2);
	putc(' ');
	puts(cmdSwitch3);
	putc(' ');
	puts(cmdSwitch4);
	putc(' ');
	puts(cmdSwitch5);
	putc(' ');
	puts(cmdSwitch6);
}

void example()
{
	char a[9], b[9];
	int c,d;
	puts("Input a number(1): ");
	gets(a);
	puts("Input a number(2): ");
	gets(b);
	c = atoi(a);
	d = atoi(b);
	puts("Addition: ");
	putd(c+d);
	puts("\nSubtraction: ");
	putd(c-d);
	puts("\nMultiply: ");
	putd(c*d);
	puts("\nDivide: ");
	putd(c/d);
	putc('\n');
}

		

void exponentMe()
{
	int a, b, c;
	a = atoi(cmdSwitch0);
	b = atoi(cmdSwitch0);
	c = atoi(cmdSwitch1);
	
	if (c == 0)
	{
		putd(1);
	}	
	else
	{
		for (; c > 1; c--)
		{
			a = a * b;
		}
		putd(a);
	}
}
// Evaluation
void evalMe()
{
  	char expr[50];
        puts("Enter valid expression: ");
        gets(expr);
	putd(eval(expr));
}
//Addition
void addMe()
{	
	int a, b;
	a = atoi(cmdSwitch0);
	b = atoi(cmdSwitch1);
	putc('\n');
	puts(cmdSwitch0);
	puts(" + ");
	puts(cmdSwitch1);
	puts(" = ");	
	putd(a+b);
}
//Subtraction
void subtractMe()
{
	int a, b;
	a = atoi(cmdSwitch0);
	b = atoi(cmdSwitch1);
	putc('\n');
	puts(cmdSwitch0);
	puts(" - ");
	puts(cmdSwitch1);
	puts(" = ");	
	putd(a-b);
}
//Time
void timeMe()
{
	putc('\n');
        putt(rtc_getRTC());
}

//Allocate example

void allocateExMe()
{
puts("Enter number of bytes for allocation of variable A: ");
char NoBytesa[10];
gets(NoBytesa);
int na = atoi(NoBytesa);
char* a = kalloc(na);
puts("Enter character to start filling from");
char c = getchar();
for(int i=0;i<na;i++)
{       putc('\n');
	a[i]=c+i;
	puthex(a+i);
	puts(" : ");
	putc(a[i]);

}
 puts("Enter number of bytes for allocation of variable B: ");
char NoBytesb[10];
gets(NoBytesb);
int nb = atoi(NoBytesb);
char* b = kalloc(nb);
puts("Enter character to start filling from");
 c = getchar();
for(int i=0;i<nb;i++)
{       putc('\n');
	b[i]=c+i;
	puthex(b+i);
	puts(" : ");
	putc(b[i]);

}
puts("\nFreeing variable A");
	kfree(a);
puts("\nAllocating new variable\n");
 puts("Enter number of bytes for allocation of variable C: ");
char NoBytesc[10];
gets(NoBytesc);
int nc = atoi(NoBytesc);
char* cm = kalloc(nc);
puts("Enter character to start filling from: ");
char t = getchar();
for(int i=0;i<nc;i++)
{       putc('\n');
	cm[i]=t+i;
	puthex(cm+i);
	puts(" : ");
	putc(cm[i]);

}
puts("\nFreeing variable B");
kfree(b);
puts("\nFreeing variable C");
kfree(cm);
}

int isFree(int n)
{return freeNiz[n]==0;
}

void allocateMe(){
puts("Enter position: ");
char po[3];
gets(po);
int position = atoi(po);
if(!isFree(position))
{
puts("Location is occupied!!!");
return ;
}
freeNiz[position]=1;
puts("Enter number of bytes for allocation of variable : ");
char NoBytesa[10];
gets(NoBytesa);
int na = atoi(NoBytesa);
char* a = kalloc(na);


for(int i=0;i<na;i++)
{       putc('\n');
puts("Enter character ");
putd(i+1);
puts(": ");
char c = getchar();
	niz[position][i]=c;
}
  size[position]=na;
}

void freeMe()
{
  puts("Enter position: ");
char po[3];
gets(po);
int position = atoi(po);
if(isFree(position))
{
puts("Location is free!!!");
return ;
}

freeNiz[position]=0;
kfree(niz[position]);
}

void printAllocateMe()
{
puts("Enter position: ");
char po[3];
gets(po);
int position = atoi(po);
if(isFree(position))
{
puts("Location is free!!!");
return ;
}
  
for(int i=0;i<size[position];i++)
{       putc('\n');
	
	puthex(niz[position][i]);
	puts(" : ");
	putc(niz[position][i]);

}
}


void plotMe()
{
int choice;
char ch[3];
puts("List of functions that can be graphed in TOS:\n");
puts("   (1) Linear function y=kx+n\n");
puts("   (2) Quadratic function y=ax^2+bx+c\n");
puts("   (3) Circle (x-p)^2+(y-q)^2=r^2\n");
puts("   (0) Return\n");
puts("Enter your choice: ");
gets(ch);
choice=atoi(ch);
if(choice==1)
	{ int k,n;
	  puts("\nk= ");
	  gets(ch);
	  k=atoi(ch);
	  puts("\nn= ");
	  gets(ch);
	  n=atoi(ch);
          draw_linear(k,n);
	}

else if(choice==2)
	{ int a,b,c;
	  puts("\na= ");
	  gets(ch);
	  a=atoi(ch);
	  puts("\nb= ");
	  gets(ch);
	  b=atoi(ch);
 	  puts("\nc= ");
	  gets(ch);
	  c=atoi(ch);
          draw_quad(a,b,c);
	}
else if(choice==3)
	{ int p,q,r;
	  puts("\np= ");
	  gets(ch);
	  p=atoi(ch);
	  puts("\nq= ");
	  gets(ch);
	  q=atoi(ch);
 	  puts("\nr= ");
	  gets(ch);
	  r=atoi(ch);
          draw_circle(p,q,r);
	}
else if(choice==0)
        return;
else puts("\nWrong input");

}



















