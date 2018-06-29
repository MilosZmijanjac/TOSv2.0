// timer.c -- Initialises the PIT, and handles clock updates.
//            Written for JamesM's kernel development tutorials.

#include "timer.h"
#include "isr.h"
#include "monitor.h"

u32int tick = 0;

static void timer_callback(Registers_t regs)
{
    tick++;
    puts("Tick: ");
    putd(tick);
    puts("\n");
}
void timer_wait(int ticks)
/// Hold the system until specified time is reached
{
    unsigned long eticks;

    eticks = tick + ticks;
    while(tick < eticks);
}
u32int timer_get_ticks(){
    return tick;
}

void timer_set_ticks(u32int init_ticks){
    tick=init_ticks;
}
void init_timer(u32int frequency)
{
    // Firstly, register our timer callback.
    register_interrupt_handler(IRQ0, &timer_callback);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    u32int divisor = 1193180 / frequency;

    // Send the command byte.
    outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    u8int l = (u8int)(divisor & 0xFF);
    u8int h = (u8int)( (divisor>>8) & 0xFF );

    // Send the frequency divisor.
    outb(0x40, l);
    outb(0x40, h);
}
void sleep(u32int secs){
    //init_timer(1000);//1000 Hz
    timer_set_ticks(secs*1000);
    while(1){
        if(timer_get_ticks()==0){
            break;
        }
    }
    
}
