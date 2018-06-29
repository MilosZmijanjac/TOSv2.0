#include "monitor.h"
#include "descriptor_tables.h"
#include "kb.h"
#include "timer.h"
#include "paging.h"
#include "shell.h"
#include "rtc.h"
#include "fpu.h"
#include "draw.h"
#include "testspeaker.h"
char username [32];
int prompt;

int main(struct multiboot *mboot_ptr)
{
    // Initialise all the ISRs and segmentation
    init_descriptor_tables();
    // Initialise the screen (by clearing it)
     monitor_install();
// Initialise paging 
    initialise_paging();
   // Initialise time
        rtc_init();
   // Initialise keyboard
   	keyboard_install();
enable_fpu();

  
   	__asm__ __volatile__ ("sti");


//Initialise shell
	initShell();

       puts("\n\t\t\tWelcome to TOS 0.1.5!\n");
   	puts("\t\t\t(C)2018 TOS Developers\n\n");
int on=1;
   	while(on) {
		on=runShell();
	}



    return 0;
}
