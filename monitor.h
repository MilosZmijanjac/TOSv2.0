// monitor.h -- Defines the interface for monitor.h
//              From JamesM's kernel development tutorials.

#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"
#include "rtc.h"

// Write a single character out to the screen.
void putc(char c);

// Clear the screen to all black.
void cls();

// Moves the cursor
void move_csr();
// Output a null-terminated ASCII string to the monitor.
void puts(char *c);

// Output a decimal number
void putd(u32int n);

// Output a hexidecimal number
void puthex(u32int n);

// Output time
void putt(RTC*rt);

// Fix the shell cursor
void shell_csr_fix();

// Install monitor
extern void monitor_install(void);
#endif // MONITOR_H
