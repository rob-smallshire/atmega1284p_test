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
    uint8_t data = (uint8_t) uart0_getc();
    return data;
}

static FILE uart0_stream = FDEV_SETUP_STREAM(
        uart0_send_byte,
        uart0_receive_byte,
        _FDEV_SETUP_RW);



enum {
 BLINK_DELAY_MS = 5000,
};

enum {
    SENSE0 = PORTA0,
    SENSE1 = PORTA1,
    SENSE2 = PORTA2,
    SENSE3 = PORTA3,
    NFAULT0 = PORTA4,
    NFAULT1 = PORTA5,
    NFAULT2 = PORTA6,
    NFAULT3 = PORTA7,
};

enum {
    ENC0A  = PORTB0,
    ENC1A  = PORTB1,
    ENC2A  = PORTB2,
    ENC3A  = PORTB3,
    ENC0B  = PORTB4,
    ENC1B  = PORTB5,
    ENC2B  = PORTB6,
    ENC3B  = PORTB7
};

enum {
    SCL    = PORTC0,  // Only used as GPIO during test
    SDA    = PORTC1,  // Only used as GPIO during test
    BRAKE1 = PORTC2,
    DIR1   = PORTC3,
    BRAKE2 = PORTC4,
    DIR2   = PORTC5,
    BRAKE3 = PORTC6,
    DIR3   = PORTC7
};


enum {
    RX     = PORTD0,
    TX     = PORTD1,
    BRAKE0 = PORTD2,
    DIR0   = PORTD3,
    PWM0   = PORTD4,
    PWM1   = PORTD5,
    PWM2   = PORTD6,
    PWM3   = PORTD7
};


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main (void)
{
    sei();

    stdin = stdout = &uart0_stream;

    // USB Serial 0
    uart0_init(UART_BAUD_SELECT(9600, F_CPU));

    // PORTA
    DDRA = 0x00; // All inputs
    PORTA =0x00; // No pull-ups

    // PORTB
    DDRB = 0x00; // All inputs
    PORTB = 0x00; // No pull-ups


    // PORTC
    DDRC = _BV(SCL) | _BV(SDA) | _BV(BRAKE1) | _BV(DIR1) | _BV(BRAKE2) | _BV(DIR2) | _BV(BRAKE3) | _BV(DIR3);
    PORTC = 0x00; // All off

    // PORTD
    DDRD = _BV(RX) | _BV(TX) | _BV(BRAKE0) | _BV(DIR0) | _BV(PWM0) | _BV(PWM1) | _BV(PWM2) | _BV(PWM3);
    PORTD = 0x00; // All off

    while (1) {
        PORTD &= ~_BV(DIR0);

        /* set pin 20 high to turn led on */
        PORTC |= _BV(SCL);
        PORTD |= _BV(PWM0);
        _delay_ms(BLINK_DELAY_MS);

        /* set pin 20 low to turn led off */
        PORTC &= ~_BV(SCL);
        PORTD &= ~_BV(PWM0);
        _delay_ms(BLINK_DELAY_MS);

        PORTD |= _BV(DIR0);

        /* set pin 20 high to turn led on */
        PORTC |= _BV(SCL);
        PORTD |= _BV(PWM0);
        _delay_ms(BLINK_DELAY_MS);

        /* set pin 20 low to turn led off */
        PORTC &= ~_BV(SCL);
        PORTD &= ~_BV(PWM0);
        _delay_ms(BLINK_DELAY_MS);

        printf("Hello, World!\n");
    }
}
#pragma clang diagnostic pop
