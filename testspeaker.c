

#define SPEAKER_PORT 0x61;
#define PIT_CONTROL = 0x43;
#define PIT_CHANNEL_2 = 0x42;


#include "timer.h"
#include "common.h"

void sound(u32int frequency){

    u32int divisor = 1193180 / frequency;

    // Send the command byte.
    outb(0x43, 0xB6);//

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    u8int l = (u8int)(divisor & 0xFF);
    u8int h = (u8int)( (divisor>>8) & 0xFF );

    // Send the frequency divisor.
    outb(0x42, l);
    outb(0x42, h);

//Connect the speaker to the PIT
//Port[SPEAKER_PORT] := Port[SPEAKER_PORT] or 3;
u8int speakerport = inb(0x61);
speakerport = speakerport | 3;
outb(0x61,speakerport);
}

void stop_sound(){
u8int speakerport = inb(0x61);
speakerport = speakerport & 0xFC;
outb(0x61,speakerport);
}

void testspeaker(){
init_timer(10);
sound(100);
sleep(1);
stop_sound();
sound(50);
sleep(1);
stop_sound();
}

