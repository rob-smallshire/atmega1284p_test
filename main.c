// ATMega1284p_test  A simple test program for an ATMega1284p.
//
// Copyright (C) 2018  Robert Smallshire
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
//         the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>
//#include <util/atomic.h>

#include "uart.h"

#ifdef __GNUC__
#  define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#  define UNUSED(x) UNUSED_ ## x
#endif

#ifdef __GNUC__
#  define UNUSED_FUNCTION(x) __attribute__((__unused__)) UNUSED_ ## x
#else
#  define UNUSED_FUNCTION(x) UNUSED_ ## x
#endif

int uart0_send_byte(char data, FILE* UNUSED(stream))
{
    if (data == '\n')
    {
        uart0_putc('\r');
    }
    uart0_putc((uint8_t)data);
    return 0;
}

int uart0_receive_byte(FILE* UNUSED(stream))
{
    uint8_t data = uart0_getc();
    return data;
}

static FILE uart0_stream = FDEV_SETUP_STREAM(
        uart0_send_byte,
        uart0_receive_byte,
        _FDEV_SETUP_RW);



enum {
 BLINK_DELAY_MS = 500,
};


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main (void)
{
    sei();

    stdin = stdout = &uart0_stream;

    // USB Serial 0
    uart0_init(UART_BAUD_SELECT(9600, F_CPU));

    /* set bit 0 of PORTC (pin 20) for output*/
    DDRC |= _BV(DDC0);


    while (1) {
        /* set pin 20 high to turn led on */
        PORTC |= _BV(PORTC0);
        _delay_ms(BLINK_DELAY_MS);

        /* set pin 20 low to turn led off */
        PORTC &= ~_BV(PORTC0);
        _delay_ms(BLINK_DELAY_MS);

        printf("Hello, World!\n");
    }
}
#pragma clang diagnostic pop
