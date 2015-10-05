//#include <stdio.h>
#include <avr/io.h>
//#include <avr/interrupt.h>

#include <util/delay.h>
//#include <util/atomic.h>

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

enum {
 BLINK_DELAY_MS = 100,
};


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main (void)
{
    /* set pin 6 of PORTD for output*/
    DDRD |= _BV(DDD6);

    while (1) {
        /* set pin 20 high to turn led on */
        PORTD |= _BV(PORTD6);
        _delay_ms(BLINK_DELAY_MS);

        /* set pin 20 low to turn led off */
        PORTD &= ~_BV(PORTD6);
        _delay_ms(BLINK_DELAY_MS);

    }
}
#pragma clang diagnostic pop
