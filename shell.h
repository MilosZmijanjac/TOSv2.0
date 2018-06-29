#ifndef SHELL_H
#define SHELL_H
#include "command.h"
#include "eval.h"
typedef struct
{
	char command[64];	//command string
	char description[256];	//brief description
	void *address;		//the function it associates with
} commandEntry;
extern int atoi(const char *nptr);
extern int addCommand(char *command, char *description, void *address);
extern void initShell();			/* Populates the command list. 			*/
extern int runShell();				/* Runs one command on the shell. 		*/
extern void clearCommands();		/* Clear all entry's on the jump table. */
extern int isFree(int n);
//the commands are in commands.h

#endif
