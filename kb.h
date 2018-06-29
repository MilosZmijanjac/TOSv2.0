/*
** Keyboard Header File
*/

#ifndef KB_H
#define KB_H
#include "isr.h"
#define ScrollLock (unsigned char)0x01
#define NumLock (unsigned char)0x02
#define CapsLock (unsigned char)0x04

int kb_special(unsigned char key);
void UpdateLeds(char led);
void FlushBuffer();
extern char getchar_int();
extern int getchar();
extern char *gets (char *s);
extern void waitKey();
extern void keyboard_install();
void keyboard_handler(Registers_t *r);

#endif
