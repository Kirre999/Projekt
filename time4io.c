//
//  time4io.c
//  
//
//  Created by Erik Svärd on 2023-02-14.
//

#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw( void )
{
    int switches;
    
    switches = (PORTD >> 8) & 0xF;
    
    return switches;
}

int getbtns(void)
{
    int buttons;
    
    buttons = (PORTD >> 5) & 0x7;
    
    return buttons;
}
